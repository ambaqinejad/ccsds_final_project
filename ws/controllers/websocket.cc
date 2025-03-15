#include "websocket.h"
#include <iostream>

#include "FileController.h"
#include "../logics/CCSDS_Packet.h"

using namespace std;

websocket::websocket() {
    // Initialize parser in constructor
}


void websocket::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    // write your application logic here
    std::vector<uint8_t> receivedData(message.begin(), message.end());
    std::lock_guard<std::mutex> lock(_mapMutex);
    if (_parserMap.find(wsConnPtr) != _parserMap.end()) {
        _parserMap[wsConnPtr]->receiveData(receivedData);
    }

    std::string response = "Good";
    wsConnPtr->send(response, WebSocketMessageType::Text);
}

void websocket::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr& wsConnPtr)
{
    FileController::clients.insert(wsConnPtr);
    // write your application logic here
    cout << "Handling new connection" << endl;
    // Create a new parser instance for this connection
    auto parser = std::make_shared<ThreadedParser>();
    parser->start();

    {
        std::lock_guard<std::mutex> lock(_mapMutex);
        _parserMap[wsConnPtr] = parser;  // Store parser per connection
    }
}

void websocket::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    std::cout << "Connection closed" << std::endl;
    FileController::clients.erase(wsConnPtr);

    std::lock_guard<std::mutex> lock(_mapMutex);
    if (_parserMap.find(wsConnPtr) != _parserMap.end()) {
        _parserMap.erase(wsConnPtr);  // Remove parser when connection closes
    }
}