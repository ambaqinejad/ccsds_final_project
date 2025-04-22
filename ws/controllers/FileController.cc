#include "FileController.h"
#include <drogon/drogon.h>
#include <fstream>
#include <thread>
#include <chrono>
#include <iostream>

#include "database/MongoDBHandler.h"
#include "helpers/CCSDSPacketFileHelper.h"
#include "helpers/UIDGeneratorHelper.h"

void FileController::uploadFile(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) const {
    MultiPartParser fileUpload;
    if (fileUpload.parse(req) != 0 || fileUpload.getFiles().size() != 1)
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody("Must only be one file");
        resp->setStatusCode(k403Forbidden);
        callback(resp);
        return;
    }

    HttpFile file = fileUpload.getFiles()[0];
    std::string fileUUID = UIDGeneratorHelper::generateUID() + "." + std::string(file.getFileExtension());
    auto md5 = file.getMd5();
    Json::Value msg;
    file.setFileName(fileUUID);
    file.save();
    string filePath = "uploads/" + file.getFileName();
    msg["fileUUID"] = fileUUID;
    msg["msg"] = "The uploaded file has been saved in path " + filePath;
    auto resp = HttpResponse::newHttpJsonResponse(msg);
    thread([filePath, fileUUID]() { CCSDSPacketFileHelper::processFile(filePath, fileUUID); }).detach();
    LOG_INFO << "The uploaded file has been saved to the ./uploads "
                "directory";
    callback(resp);
}



