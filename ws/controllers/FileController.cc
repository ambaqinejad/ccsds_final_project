#include "FileController.h"
#include <drogon/drogon.h>
#include <thread>
#include <iostream>
#include "helpers/CCSDSPacketFileHelper.h"
#include "helpers/UIDGeneratorHelper.h"
#include "helpers/EnvHelper.h"

// this class is for working with file that is uploaded to the server for processing

void FileController::uploadFile(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
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
    std::string fileUUID = UIDGeneratorHelper::generateUID();
    std::string fileName = fileUUID + "." + std::string(file.getFileExtension());
    auto md5 = file.getMd5();
    Json::Value msg;
    file.setFileName(fileName);
    file.save();
    string documentRoot = EnvHelper::readEnvVariable("DOCUMENT_ROOT",
                                     "/home/ambaqinejad/Desktop/drogon_ccsds/ccsds_final_project/ws/public");
    string uploadPath = documentRoot + "/uploads";
    string filePath = uploadPath + "/" + file.getFileName();
    msg["fileUUID"] = fileUUID;
    msg["message"] = "The uploaded file has been saved";
    auto resp = HttpResponse::newHttpJsonResponse(msg);
    thread([filePath, fileUUID]() { CCSDSPacketFileHelper::processFile(filePath, fileUUID); }).detach();
    LOG_INFO << "The uploaded file has been saved to the " + uploadPath;
    callback(resp);
}

//std::unordered_map<std::string, FileController::FileSession> FileController::fileSessions_;
//std::mutex FileController::sessionsMutex_;
//void FileController::uploadFile(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
//    MultiPartParser fileUpload;
//    if (fileUpload.parse(req) != 0) {
//        auto resp = HttpResponse::newHttpResponse();
//        resp->setBody("Invalid upload data");
//        resp->setStatusCode(k400BadRequest);
//        callback(resp);
//        return;
//    }
//
//    auto params = fileUpload.getParameters();
//
//    if (fileUpload.getFiles().size() != 1) {
//        auto resp = HttpResponse::newHttpResponse();
//        resp->setBody("No file chunk found");
//        resp->setStatusCode(k400BadRequest);
//        callback(resp);
//        return;
//    }
//
//    // Get chunk parameters
//    std::string fileId = params["fileId"];
//    int chunkIndex = std::stoi(params["chunkIndex"]);
//    int totalChunks = std::stoi(params["totalChunks"]);
//    std::string fileName = params["fileName"];
//
//    HttpFile file = fileUpload.getFiles()[0];
//
//    std::unique_lock<std::mutex> lock(sessionsMutex_);
//
//    // Create new session if needed
//    if (fileSessions_.find(fileId) == fileSessions_.end()) {
//        FileSession session;
//        session.fileName = fileName;
//        session.fileUUID = UIDGeneratorHelper::generateUID();
//        session.totalChunks = totalChunks;
//
//        // Create temp directory
//        string documentRoot = EnvHelper::readEnvVariable("DOCUMENT_ROOT",
//                                                         "/home/ambaqinejad/Desktop/drogon_ccsds/ccsds_final_project/ws/public");
//        string tempDir = documentRoot + "/uploads/" + session.fileUUID;
//        std::filesystem::create_directories(tempDir);
//        session.tempDir = tempDir;
//
//        fileSessions_[fileId] = session;
//    }
//    FileSession &session = fileSessions_[fileId];
//    session.lastUpdate = std::chrono::system_clock::now();
//
//    // Save chunk
//    std::string chunkPath = session.tempDir + "/chunk_" + std::to_string(chunkIndex);
//    file.saveAs(chunkPath);
//
//    session.receivedChunks++;
//
//    lock.unlock();
//
//    Json::Value response;
//    response["status"] = "success";
//    response["chunkIndex"] = chunkIndex;
//    response["fileUUID"] = session.fileUUID;
//
//    auto resp = HttpResponse::newHttpJsonResponse(response);
//    callback(resp);
//}

//void FileController::finalizeUpload(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
//    Json::Value jsonBody = req->getJsonObject() ? *req->getJsonObject() : Json::Value();
//
//    std::string fileId = jsonBody["fileId"].asString();
//
//    std::unique_lock<std::mutex> lock(sessionsMutex_);
//
//    if (fileSessions_.find(fileId) == fileSessions_.end()) {
//        auto resp = HttpResponse::newHttpResponse();
//        resp->setBody("Upload session not found");
//        resp->setStatusCode(k404NotFound);
//        callback(resp);
//        return;
//    }
//
//    FileSession session = fileSessions_[fileId];
//
//    // Verify all chunks received
//    if (session.receivedChunks != session.totalChunks) {
//        auto resp = HttpResponse::newHttpResponse();
//        resp->setBody("Not all chunks received. Got " +
//                      std::to_string(session.receivedChunks) + " of " +
//                      std::to_string(session.totalChunks));
//        resp->setStatusCode(k400BadRequest);
//        callback(resp);
//        return;
//    }
//
//    // Remove from sessions
//    fileSessions_.erase(fileId);
//    lock.unlock();
//
//    // Reassemble file in background thread
//    std::thread([session]() {
//        string documentRoot = EnvHelper::readEnvVariable("DOCUMENT_ROOT",
//                                                         "/home/ambaqinejad/Desktop/drogon_ccsds/ccsds_final_project/ws/public");
//        string finalPath = documentRoot + "/uploads/" + session.fileUUID;
//
//        // Get file extension from original name
//        size_t dotPos = session.fileName.find_last_of('.');
//        if (dotPos != std::string::npos) {
//            finalPath += session.fileName.substr(dotPos);
//        }
//
//        std::ofstream outputFile(finalPath, std::ios::binary);
//        if (!outputFile) {
//            LOG_ERROR << "Failed to create output file: " << finalPath;
//            return;
//        }
//
//        // Combine all chunks
//        for (int i = 0; i < session.totalChunks; ++i) {
//            std::string chunkPath = session.tempDir + "/chunk_" + std::to_string(i);
//            std::ifstream chunkFile(chunkPath, std::ios::binary);
//
//            if (!chunkFile) {
//                LOG_ERROR << "Failed to read chunk: " << chunkPath;
//                outputFile.close();
//                std::filesystem::remove(finalPath);
//                return;
//            }
//
//            outputFile << chunkFile.rdbuf();
//            chunkFile.close();
//
//            // Delete chunk file
//            std::filesystem::remove(chunkPath);
//        }
//        outputFile.close();
//
//        // Remove temp directory
//        std::filesystem::remove_all(session.tempDir);
//
//        // Process complete file
//        CCSDSPacketFileHelper::processFile(finalPath, session.fileUUID);
//
//        LOG_INFO << "File processed: " << finalPath;
//    }).detach();
//
//    Json::Value response;
//    response["fileUUID"] = session.fileUUID;
//    response["message"] = "File upload completed and processing started";
//
//    auto resp = HttpResponse::newHttpJsonResponse(response);
//    callback(resp);
//}



