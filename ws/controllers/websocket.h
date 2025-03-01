#pragma once

#include <drogon/WebSocketController.h>

using namespace drogon;

class websocket : public drogon::WebSocketController<websocket>
{
  private:
    std::vector<uint8_t> _activeBuffer;
    std::mutex _bufferMutex;
    std::condition_variable _cv;
    bool isParsing = false;
    const int _CHUNK_SIZE = 128;
    const int _PARSE_UNIT = 10 * _CHUNK_SIZE; // 10 chunks (1280 bytes)
    bool _stopParser = false;
  public:
     void handleNewMessage(const WebSocketConnectionPtr&,
                                  std::string &&,
                                  const WebSocketMessageType &) override;
    void handleNewConnection(const HttpRequestPtr &,
                                     const WebSocketConnectionPtr&) override;
    void handleConnectionClosed(const WebSocketConnectionPtr&) override;

    void parseData(const std::vector<uint8_t>& data);

    void parsingThreadFunction();

    void receiveData(const std::vector<uint8_t>& data);

    WS_PATH_LIST_BEGIN
    // list path definitions here;
     WS_PATH_ADD("/ws", Get);
    WS_PATH_LIST_END
};
