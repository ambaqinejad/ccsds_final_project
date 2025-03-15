#include "FileController.h"
#include <drogon/drogon.h>
#include <fstream>
#include <thread>
#include <chrono>

std::unordered_set<WebSocketConnectionPtr> FileController::clients;

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

    auto &file = fileUpload.getFiles()[0];
    auto md5 = file.getMd5();
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(
        "The server has calculated the file's MD5 hash to be " + md5);
    file.save();
    string filename = "uploads/" + file.getFileName();
    thread([filename]() { processFile(filename); }).detach();
    LOG_INFO << "The uploaded file has been saved to the ./uploads "
                "directory";
    callback(resp);
}

void FileController::processFile(const string &filename) {
    ifstream file(filename, ios::binary);
    file.seekg(0, ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, ios::beg);

    size_t processed = 0;
    size_t segmentSize = fileSize / 10;

    for (int i = 1; i <= 10; ++i) {
        this_thread::sleep_for(chrono::seconds(1));
        processed += segmentSize;
        notifyClients(i * 10);
    }

    notifyClients(100);
}

void FileController::notifyClients(int progress) {
    Json::Value msg;
    msg["progress"] = progress;
    for (const auto &client : clients) {
        if (client && client->connected()) {
            client->send(msg.toStyledString());
        }
    }
}

