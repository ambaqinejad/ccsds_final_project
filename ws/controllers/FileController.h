#pragma once

#include <drogon/HttpController.h>
#include <drogon/drogon.h>
#include <fstream>
#include <thread>
#include <chrono>
#include <drogon/WebSocketConnection.h>

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
    static void notifyClients(int progress);

    static unordered_set<WebSocketConnectionPtr> clients;

};
