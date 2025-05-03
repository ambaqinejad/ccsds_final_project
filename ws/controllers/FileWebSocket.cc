#include "FileWebSocket.h"
#include "FileController.h"
#include "helpers/ClientCommunicationHelper.h"

void FileWebSocket::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{}

void FileWebSocket::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr& wsConnPtr)
{
    // write your application logic here
    ClientCommunicationHelper::clients.insert(wsConnPtr);
}

void FileWebSocket::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{}
