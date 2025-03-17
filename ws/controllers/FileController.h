#pragma once

#include <drogon/HttpController.h>
#include <drogon/drogon.h>
#include <fstream>
#include <thread>
#include <chrono>
#include <drogon/WebSocketConnection.h>

#include "logics/CCSDS_Packet.h"

using namespace drogon;
using namespace std;

class FileController : public drogon::HttpController<FileController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(FileController::uploadFile, "/upload", Post); // path is /absolute/path/{arg1}/{arg2}/list
    METHOD_LIST_END
    void uploadFile(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    static void processFile(const string &filename);
    static void parseData(std::vector<std::vector<uint8_t>> chunks, int count_of_valid_chunks);
    static void notifyClients(double progress, CCSDS_Packet &packet);

    static unordered_set<WebSocketConnectionPtr> clients;
    // static std::vector<CCSDS_Packet> packets;

};
