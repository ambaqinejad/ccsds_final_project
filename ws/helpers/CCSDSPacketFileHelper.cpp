//
// Created by ambaqinejad on 4/19/25.
//

#include "CCSDSPacketFileHelper.h"
#include <iostream>
#include <fstream>

#include "helpers/ClientCommunicationHelper.h"
#include <drogon/drogon.h>
#include <chrono>

using namespace std::chrono;


using namespace std;

void CCSDSPacketFileHelper::processFile(const string &filePath, const std::string &fileUUID) {
    ifstream file(filePath, ios::binary);
    if (!file) {
        LOG_INFO << "Error opening file!\n";
        return;
    }
    file.seekg(0, ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, ios::beg);

    // Allocate buffer and read data
    std::vector<unsigned char> buffer(fileSize);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), fileSize)) {
        LOG_INFO << "Error reading file!\n";
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
    parseData(chunks, count_of_valid_chunks, fileUUID);
}

std::map<std::string, std::vector<CCSDS_Packet>> CCSDSPacketFileHelper::uuidToSavedPacketsMapper;
void CCSDSPacketFileHelper::parseData(std::vector<std::vector<uint8_t>> chunks, int count_of_valid_chunks, const std::string &fileUUID) {

    int eachTimeNotifyClients = count_of_valid_chunks / 10;
    std::vector<CCSDS_Packet> packets {};
    for (size_t i = 0; i < chunks.size(); ++i) {
        auto start = high_resolution_clock::now();
        CCSDS_Packet packet = packet.deserialize_packet(chunks.at(i));
        auto end = high_resolution_clock::now();
        auto duration_us = duration_cast<microseconds>(end - start);  // microseconds
        cout << "Time (microseconds): " << duration_us.count() << " µs" << endl;
        packets.push_back(packet);
        int progress = std::ceil(((double)i / count_of_valid_chunks) * 100);
        // notify clients each n times
        if (i % eachTimeNotifyClients == 0) {
            ClientCommunicationHelper::notifyClients(progress, packet);
        }
    }
    CCSDSPacketFileHelper::uuidToSavedPacketsMapper[fileUUID] = packets;
}