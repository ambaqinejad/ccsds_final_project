#pragma once

#include <drogon/HttpController.h>
#include <drogon/drogon.h>
#include <fstream>
#include <thread>
#include <chrono>

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

    // static std::vector<CCSDS_Packet> packets;

};
