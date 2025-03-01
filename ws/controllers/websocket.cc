#include "websocket.h"
#include <iostream>

using namespace std;

void websocket::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    // write your application logic here
    std::vector<uint8_t> receivedData(message.begin(), message.end());

    std::cout << "Received Binary Data (size: " << receivedData.size() << "): ";
//    for (auto byte : receivedData) {
//      uint8_t u = (uint8_t) byte;
//      std::cout << u << " " << std::endl;
//      int i = (int) byte;
//      std::cout << i << " " << std::endl;
//    }
//    std::cout << std::dec << std::endl;
//    cout << "------------------------"<< std::endl;
    receiveData(receivedData);
    std::string response {"Good"};
    wsConnPtr->send(response, WebSocketMessageType::Text);
}

void websocket::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr& wsConnPtr)
{
    // write your application logic here
    cout << "Handling new connection" << endl;
    std::thread parser(&websocket::parsingThreadFunction, this);
}

void websocket::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    // write your application logic here
    cout << "Connection closed" << endl;
}

// Function to simulate parsing
void websocket::parseData(const std::vector<uint8_t>& data) {
    std::this_thread::sleep_for(std::chrono::seconds(5)); // Simulate processing time
    std::cout << "Parsed " << data.size() << " bytes of data.\n";
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
