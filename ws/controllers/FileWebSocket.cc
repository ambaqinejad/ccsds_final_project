#include "FileWebSocket.h"
#include "FileController.h"

void FileWebSocket::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    // write your application logic here
}

void FileWebSocket::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr& wsConnPtr)
{
    // write your application logic here
    FileController::clients.insert(wsConnPtr);
}

void FileWebSocket::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    // write your application logic here
//    FileController::clients.erase(wsConnPtr);
}
