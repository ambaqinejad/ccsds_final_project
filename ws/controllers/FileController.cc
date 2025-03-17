#include "FileController.h"
#include <drogon/drogon.h>
#include <fstream>
#include <thread>
#include <chrono>

#include "logics/CCSDS_Packet.h"

#include <mongocxx/v_noabi/mongocxx/client.hpp>
#include <mongocxx/v_noabi/mongocxx/instance.hpp>
#include <mongocxx/v_noabi/mongocxx/uri.hpp>
#include <bsoncxx/v_noabi/bsoncxx/json.hpp>
#include <iostream>

std::unordered_set<WebSocketConnectionPtr> FileController::clients;

void FileController::uploadFile(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) const {
    MultiPartParser fileUpload;
    if (fileUpload.parse(req) != 0 || fileUpload.getFiles().size() != 1)
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody("Must only be one file");
        resp->setStatusCode(k403Forbidden);
        callback(resp);
        return;
    }

    auto &file = fileUpload.getFiles()[0];
    auto md5 = file.getMd5();
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(
        "The server has calculated the file's MD5 hash to be " + md5);
    file.save();
    string filename = "uploads/" + file.getFileName();
    thread([filename]() { processFile(filename); }).detach();
    LOG_INFO << "The uploaded file has been saved to the ./uploads "
                "directory";
    callback(resp);
}

void FileController::processFile(const string &filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }
    file.seekg(0, ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, ios::beg);

    // Allocate buffer and read data
    std::vector<unsigned char> buffer(fileSize);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), fileSize)) {
        std::cerr << "Error reading file!" << std::endl;
        return;
    }

    int count_of_valid_chunks = 0;
    std::vector<std::vector<uint8_t>> chunks;
    for (size_t i = 0; i < buffer.size() - 1; ++i) {
        if (buffer[i] == 0x48 && buffer[i + 1] == 0x48) {
            for (size_t j = i+2; j < buffer.size() - 1; ++j) {
                if (buffer[j] == 0x48 && buffer[j + 1] == 0x48) {
                    if (j - i == 128) {
                        vector<uint8_t> chunk;
                        chunk.insert(chunk.begin(), buffer.begin() + i, buffer.begin() + j);
                        chunks.push_back(chunk);
                        count_of_valid_chunks ++;
                    }
                    break;
                }
            }
        }
    }
    parseData(chunks, count_of_valid_chunks);

}

void FileController::parseData(std::vector<std::vector<uint8_t>> chunks, int count_of_valid_chunks) {
    for (size_t i = 0; i < chunks.size(); ++i) {
        CCSDS_Packet packet = packet.deserialize_packet(chunks.at(i));
        double progress = ((double)i / count_of_valid_chunks) * 100;
        notifyClients(progress, packet);
        // packets.push_back(packet);
    }
}


void FileController::notifyClients(double progress, CCSDS_Packet &packet) {
    Json::Value msg;
    msg["progress"] = progress;

    std::stringstream ss;
    ss << std::hex << std::uppercase << std::setfill('0');

    auto formatHex = [&](int value, int width = 2) {
        ss.str("");
        ss.clear();
        ss << std::setw(width) << (value & 0xFF);
        return ss.str();
    };

    msg["main_frame_header"] = formatHex((packet.main_frame_header >> 8) & 0xFF) + " " + formatHex(packet.main_frame_header & 0xFF);
    msg["packet_id"] = formatHex((packet.packet_id >> 8) & 0xFF) + " " + formatHex(packet.packet_id & 0xFF);
    msg["packet_sequence_control"] = formatHex((packet.packet_sequence_control >> 8) & 0xFF) + " " + formatHex(packet.packet_sequence_control & 0xFF);
    msg["packet_length"] = formatHex((packet.packet_length >> 8) & 0xFF) + " " + formatHex(packet.packet_length & 0xFF);
    msg["data_field_header"] = formatHex(packet.data_field_header);
    msg["service_type"] = formatHex(packet.service_type);
    msg["sub_service_type"] = formatHex(packet.sub_service_type);
    msg["sid"] = formatHex(packet.sub_service_type);

    msg["timestamp"] = formatHex((packet.timestamp >> 24) & 0xFF) + " " +
                        formatHex((packet.timestamp >> 16) & 0xFF) + " " +
                        formatHex((packet.timestamp >> 8) & 0xFF) + " " +
                        formatHex(packet.timestamp & 0xFF);

    msg["crc_fail_upload_map"] = formatHex((packet.crc_fail_upload_map >> 56) & 0xFF) + " " +
                                  formatHex((packet.crc_fail_upload_map >> 48) & 0xFF) + " " +
                                  formatHex((packet.crc_fail_upload_map >> 40) & 0xFF) + " " +
                                  formatHex((packet.crc_fail_upload_map >> 32) & 0xFF) + " " +
                                  formatHex((packet.crc_fail_upload_map >> 24) & 0xFF) + " " +
                                  formatHex((packet.crc_fail_upload_map >> 16) & 0xFF) + " " +
                                  formatHex((packet.crc_fail_upload_map >> 8) & 0xFF) + " " +
                                  formatHex(packet.crc_fail_upload_map & 0xFF);

    msg["flash_address"] = formatHex((packet.flash_address >> 24) & 0xFF) + " " +
                            formatHex((packet.flash_address >> 16) & 0xFF) + " " +
                            formatHex((packet.flash_address >> 8) & 0xFF) + " " +
                            formatHex(packet.flash_address & 0xFF);

    for (const auto &client : clients) {
        if (client && client->connected()) {
            client->send(msg.toStyledString());
        }
    }
}

