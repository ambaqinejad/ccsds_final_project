#include "websocket.h"
#include <iostream>

using namespace std;

void websocket::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    // write your application logic here
    cout << "Handling new message " << message << endl;
    std::string response {"Good"};
    wsConnPtr->send(response, WebSocketMessageType::Text);
}

void websocket::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr& wsConnPtr)
{
    // write your application logic here
    cout << "Handling new connection" << endl;
}

void websocket::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    // write your application logic here
    cout << "Connection closed" << endl;
}
