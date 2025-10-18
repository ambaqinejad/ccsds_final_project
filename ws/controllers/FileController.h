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
  // this class is for working with file that is uploaded to the server for processing
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(FileController::uploadFile, "/upload", Post);
    METHOD_LIST_END
    static void uploadFile(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) ;
};
