#include "websocket.h"
#include <iostream>
#include "../logics/CCSDS_Packet.h"

using namespace std;

void websocket::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    // write your application logic here
    std::vector<uint8_t> receivedData(message.begin(), message.end());

    std::cout << "Received Binary Data (size: " << receivedData.size() << "): " << endl;
    receiveData(receivedData);
    std::string response {"Good"};
    wsConnPtr->send(response, WebSocketMessageType::Text);
}

void websocket::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr& wsConnPtr)
{
    // write your application logic here
    cout << "Handling new connection" << endl;
    std::thread parser(&websocket::parsingThreadFunction, this);
    parser.detach();
}

void websocket::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    // write your application logic here
    cout << "Connection closed" << endl;
}

// Function to simulate parsing
void websocket::parseData(const std::vector<uint8_t>& data) {
    std::cout << "Parsed " << data.size() << " bytes of data.\n";
    size_t i = 0;
    vector<CCSDS_Packet> packets;
    while (i < data.size()) {
        if (i != data.size() - 1 && data[i] == 'H' && data[i+1] == 'H') {
            vector<uint8_t> chunk;
            chunk.insert(chunk.begin(), data.begin() + i, data.begin() + i + 128);
            CCSDS_Packet packet;
            packets.push_back(packet.deserialize_packet(chunk));
            i += 128;
        }
    }
}

void websocket::parsingThreadFunction() {
    while (true) {
        std::vector<uint8_t> localBuffer;
        {
            std::unique_lock<std::mutex> lock(_bufferMutex);
            // Wait until there is enough data to process or stop signal is received
            _cv.wait(lock, [this] { return _activeBuffer.size() >= _PARSE_UNIT || _stopParser; });
            localBuffer.insert(localBuffer.end(), _activeBuffer.begin(), _activeBuffer.end());
            // Move PARSE_UNIT (1280 bytes) of data to local buffer
            _activeBuffer.erase(_activeBuffer.begin(), _activeBuffer.end());
        }
        // Process data outside of the locked section
        parseData(localBuffer);
    }
}

void websocket::receiveData(const std::vector<uint8_t>& data) {
    {
        std::lock_guard<std::mutex> lock(_bufferMutex);
        _activeBuffer.insert(_activeBuffer.end(), data.begin(), data.end());
    }
    _cv.notify_one();
}
