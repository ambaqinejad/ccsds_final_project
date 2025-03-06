#include "ThreadedParser.h"
#include <iostream>
#include "../logics/CCSDS_Packet.h"

ThreadedParser::ThreadedParser() : _stopParser(false) {}

ThreadedParser::~ThreadedParser() {
    {
        std::lock_guard<std::mutex> lock(_bufferMutex);
        _stopParser = true;
    }
    _cv.notify_one();
    if (_parserThread.joinable()) {
        _parserThread.join();
    }
}

void ThreadedParser::start() {
        _stopParser = false;
        _parserThread = std::thread(&ThreadedParser::parsingThreadFunction, this);
}

void ThreadedParser::receiveData(const std::vector<uint8_t>& data) {
    {
        std::lock_guard<std::mutex> lock(_bufferMutex);
        _activeBuffer.insert(_activeBuffer.end(), data.begin(), data.end());
    }
    _cv.notify_one();
}

void ThreadedParser::parsingThreadFunction() {
    std::vector<uint8_t> leftoverData;

    while (true) {
        std::vector<uint8_t> localBuffer;

        {
            std::unique_lock<std::mutex> lock(_bufferMutex);
            _cv.wait(lock, [this] { return !_activeBuffer.empty() || _stopParser; });

            if (_stopParser) break;

            if (!leftoverData.empty()) {
                localBuffer.insert(localBuffer.end(), leftoverData.begin(), leftoverData.end());
            }

            localBuffer.insert(localBuffer.end(), _activeBuffer.begin(), _activeBuffer.end());
            _activeBuffer.clear();
        }

        leftoverData = parseData(localBuffer);
    }
}

std::vector<uint8_t> ThreadedParser::parseData(std::vector<uint8_t>& data) {

    size_t i = 0;
    std::vector<CCSDS_Packet> packets;

    while (i < data.size()) {
        if (i != data.size() - 1 && data[i] == 'H' && data[i+1] == 'H' && i + 128 <= data.size()) {
            std::vector<uint8_t> chunk(data.begin() + i, data.begin() + i + 128);
            CCSDS_Packet packet;
            packets.push_back(packet.deserialize_packet(chunk));
            data.erase(data.begin(), data.begin() + i + 128);
            i--;
            std::cout << "Parsing "  << " bytes of data. 1\n";
        } else if (i != data.size() - 1 && data[i] == 'H' && data[i+1] == 'H' && i + 128 > data.size()) {
            data.erase(data.begin(), data.begin() + i);
            std::cout << "Parsing "  << " bytes of data. 2\n";
            return data;
        } else if (i == data.size() - 1 && data[i] == 'H') {
            data.erase(data.begin(), data.begin() + i);
            std::cout << "Parsing "  << " bytes of data. 3\n";
            return data;
        }
        i++;
    }

    return {};
}
