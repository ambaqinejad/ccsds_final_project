#include "CCSDS_Packet.h"
#include <iostream>
#include <cstring>
#include <iomanip>
#include <arpa/inet.h>
#include "database/MongoDBHandler.h"

CCSDS_Packet::CCSDS_Packet() {
    main_frame_header = 0;
    packet_id = 0;
    packet_sequence_control = 0;
    packet_length = 0;
    data_field_header = 0;
    service_type = 0;
    sub_service_type = 0;
    sid = 0;
    timestamp = 0;
    crc_fail_upload_map = 0;
    flash_address = 0;
}

CCSDS_Packet CCSDS_Packet::deserialize_packet(vector<uint8_t> &chunk) {
    CCSDS_Packet packet;
    size_t offset = 0;

    auto read_uint16 = [&](size_t &offset) {
        uint16_t value;
        std::memcpy(&value, &chunk[offset], sizeof(value));
        offset += sizeof(value);
        return ntohs(value);
    };

    auto read_uint32 = [&](size_t &offset) {
        uint32_t value;
        std::memcpy(&value, &chunk[offset], sizeof(value));
        offset += sizeof(value);
        return ntohs(value);
    };

    auto read_uint64 = [&](size_t &offset) {
        uint64_t value;
        std::memcpy(&value, &chunk[offset], sizeof(value));
        offset += sizeof(value);
        return ntohs(value);
    };

    static const std::unordered_map<std::string, std::function<void(size_t &, const std::string &)>> handlers = {
            {"uint8_t", [&](size_t &offset, const std::string &name) {
                mapPayloadToMeaningfulData<uint8_t>(offset, name);
                offset += sizeof(uint8_t);
            }},
            {"uint16_t", [&](size_t &offset, const std::string &name) {
                mapPayloadToMeaningfulData<uint16_t>(offset, name);
                offset += sizeof(uint16_t);
            }},
            {"uint32_t", [&](size_t &offset, const std::string &name) {
                mapPayloadToMeaningfulData<uint32_t>(offset, name);
                offset += sizeof(uint32_t);
            }},
            {"uint64_t", [&](size_t &offset, const std::string &name) {
                mapPayloadToMeaningfulData<uint64_t>(offset, name);
                offset += sizeof(uint64_t);
            }},
            {"int8_t", [&](size_t &offset, const std::string &name) {
                mapPayloadToMeaningfulData<int8_t>(offset, name);
                offset += sizeof(int8_t);
            }},
            {"double", [&](size_t &offset, const std::string &name) {
                mapPayloadToMeaningfulData<double_t>(offset, name);
                offset += sizeof(double_t);
            }},
            {"float", [&](size_t &offset, const std::string &name) {
                mapPayloadToMeaningfulData<float_t>(offset, name);
                offset += sizeof(float_t);
            }},
            {"double_t", [&](size_t &offset, const std::string &name) {
                mapPayloadToMeaningfulData<double_t>(offset, name);
                offset += sizeof(double_t);
            }},
            {"float_t", [&](size_t &offset, const std::string &name) {
                mapPayloadToMeaningfulData<float_t>(offset, name);
                offset += sizeof(float_t);
            }},
    };

    // Read fixed fields
    packet.main_frame_header = read_uint16(offset);
    packet.packet_id = read_uint16(offset);
    packet.packet_sequence_control = read_uint16(offset);
    packet.packet_length = read_uint16(offset);
    packet.data_field_header = chunk[offset++];
    packet.service_type = chunk[offset++];
    packet.sub_service_type = chunk[offset++];
    packet.sid = chunk[offset++];
    packet.timestamp = read_uint32(offset);
    packet.crc_fail_upload_map = read_uint64(offset);
    packet.flash_address = read_uint32(offset);

    // Remaining bytes are payload
    packet.payload.assign(chunk.begin() + offset, chunk.end());
    auto it = MongoDBHandler::ccsds_structure_.begin();
    std::advance(it, packet.sid - 1);
    for (auto topple = it->begin(); topple != it->end(); ++topple) {
        const std::string& fieldName = topple.key();
        if (fieldName == "_id" || fieldName == "metadata") {
            continue;
        }
        std::string fieldType = topple.value();
        auto handler = handlers.find(fieldType);
        if (handler != handlers.end()) {
            handler->second(offset, fieldName);
        }
    }

    packet.parsedData = parsedData;
    return packet;
}

Json::Value CCSDS_Packet::toJson() const {
    Json::Value msg;
    std::stringstream ss;
    ss << std::hex << std::uppercase << std::setfill('0');

    auto formatHex = [&](int value, int width = 2) {
        ss.str("");
        ss.clear();
        ss << std::setw(width) << (value & 0xFF);
        return ss.str();
    };

    msg["main_frame_header"] = formatHex((main_frame_header >> 8) & 0xFF) + " " + formatHex(main_frame_header & 0xFF);
    msg["packet_id"] = formatHex((packet_id >> 8) & 0xFF) + " " + formatHex(packet_id & 0xFF);
    msg["packet_sequence_control"] =
            formatHex((packet_sequence_control >> 8) & 0xFF) + " " + formatHex(packet_sequence_control & 0xFF);
    msg["packet_length"] = formatHex((packet_length >> 8) & 0xFF) + " " + formatHex(packet_length & 0xFF);
    msg["data_field_header"] = formatHex(data_field_header);
    msg["service_type"] = formatHex(service_type);
    msg["sub_service_type"] = formatHex(sub_service_type);
    msg["sid"] = formatHex(sub_service_type);

    msg["timestamp"] = formatHex((timestamp >> 24) & 0xFF) + " " +
                       formatHex((timestamp >> 16) & 0xFF) + " " +
                       formatHex((timestamp >> 8) & 0xFF) + " " +
                       formatHex(timestamp & 0xFF);

    msg["crc_fail_upload_map"] = formatHex((crc_fail_upload_map >> 56) & 0xFF) + " " +
                                 formatHex((crc_fail_upload_map >> 48) & 0xFF) + " " +
                                 formatHex((crc_fail_upload_map >> 40) & 0xFF) + " " +
                                 formatHex((crc_fail_upload_map >> 32) & 0xFF) + " " +
                                 formatHex((crc_fail_upload_map >> 24) & 0xFF) + " " +
                                 formatHex((crc_fail_upload_map >> 16) & 0xFF) + " " +
                                 formatHex((crc_fail_upload_map >> 8) & 0xFF) + " " +
                                 formatHex(crc_fail_upload_map & 0xFF);

    msg["flash_address"] = formatHex((flash_address >> 24) & 0xFF) + " " +
                           formatHex((flash_address >> 16) & 0xFF) + " " +
                           formatHex((flash_address >> 8) & 0xFF) + " " +
                           formatHex(flash_address & 0xFF);

    // Optional: Dump payload as hex or array
    Json::Value parsedDataObj(Json::objectValue);
    parsedDataObj = parsedData;
//    for (const auto &byte: payload) {
//        payloadArray.append(byte); // or format as hex
//    }
    msg["payload"] = parsedDataObj;

    return msg;
}

template<typename T>
void CCSDS_Packet::mapPayloadToMeaningfulData(size_t offset, const string &fieldName) {
    T value;
    std::memcpy(&value, payload.data() + offset, sizeof(T));
//    if (value == INFINITY) {
//        value = 0;
//    }
    parsedData[fieldName] = value; // Implicitly constructs a FieldValue
}


