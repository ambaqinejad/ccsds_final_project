#pragma once

#include <drogon/WebSocketController.h>

#include "threads/ThreadedParser.h"

using namespace drogon;

class websocket : public drogon::WebSocketController<websocket>
{
  private:
    std::unordered_map<WebSocketConnectionPtr, std::shared_ptr<ThreadedParser>> _parserMap;
    std::mutex _mapMutex;
  public:
     websocket();
     void handleNewMessage(const WebSocketConnectionPtr&,
                                  std::string &&,
                                  const WebSocketMessageType &) override;
    void handleNewConnection(const HttpRequestPtr &,
                                     const WebSocketConnectionPtr&) override;
    void handleConnectionClosed(const WebSocketConnectionPtr&) override;

    WS_PATH_LIST_BEGIN
    // list path definitions here;
     WS_PATH_ADD("/ws", Get);
    WS_PATH_LIST_END
};
