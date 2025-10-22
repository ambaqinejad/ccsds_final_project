#include <fstream>
#include "PacketController.h"
#include "helpers/ControllerErrorHelper.h"
#include "logics/CCSDS_Packet.h"
#include "helpers/CCSDSPacketFileHelper.h"
#include "database/MongoDBHandler.h"
#include "database/CSVHandler.h"
#include "helpers/ClientCommunicationHelper.h"

// Add definition of your processing function here
void PacketController::getSIDPacketsByPagination(const HttpRequestPtr &req,
                                                 std::function<void(const HttpResponsePtr &)> &&callback) {
    auto sidStr = (*req->getJsonObject())["sid"].asString();
    auto pageStr = (*req->getJsonObject())["page"].asString();
    auto pageSizeStr = (*req->getJsonObject())["pageSize"].asString();

    int _sid = 0;
    int _page = 0;
    int _pageSize = 0;

    try {
        _sid = std::stoi(sidStr);
        _page = std::stoi(pageStr);
        _pageSize = std::stoi(pageSizeStr); // Set your page size
    }
    catch (const std::exception &e) {
        ControllerErrorHelper::sendError(std::move(callback), k400BadRequest,
                                         "Invalid sid or page or pageSize parameter.");
    }
    std::string fileUUID = (*req->getJsonObject())["fileUUID"].asString();

    // Get packets from UUID mapping
    auto it = CCSDSPacketFileHelper::uuidToSavedPacketsMapper.find(fileUUID);
    if (it == CCSDSPacketFileHelper::uuidToSavedPacketsMapper.end()) {
        return ControllerErrorHelper::sendError(std::move(callback), k404NotFound, "File UUID not found.");
    }

    const std::vector<CCSDS_Packet> &allPackets = it->second;

    // Filter by SID
    std::vector<CCSDS_Packet> filteredPackets;
    for (const auto &pkt: allPackets) {
        if (pkt.sid == _sid) // assuming CCSDS_Packet has a `sid` field
        {
            filteredPackets.push_back(pkt);
        }
    }

    // Paginate
    int startIndex = (_page - 1) * _pageSize;
    int endIndex = std::min(startIndex + _pageSize, static_cast<int>(filteredPackets.size()));

    if (startIndex >= static_cast<int>(filteredPackets.size())) {
        return ControllerErrorHelper::sendError(std::move(callback), k404NotFound, "Page out of range.");
    }

    std::vector<CCSDS_Packet> paginatedPackets(filteredPackets.begin() + startIndex,
                                               filteredPackets.begin() + endIndex);

    // Convert to JSON
    Json::Value pktJson;
    pktJson["num of all packets"] = static_cast<int>(allPackets.size());
    pktJson["num of all packets with this sid"] = static_cast<int>(filteredPackets.size());
    pktJson["total pages"] = filteredPackets.size() % _pageSize != 0 ? filteredPackets.size() / _pageSize + 1 : filteredPackets.size() / _pageSize;
    pktJson["sid"] = _sid;
    Json::Value resultJson(Json::arrayValue);
    for (const auto &pkt: paginatedPackets) {
        // or whatever your serialization method is
        resultJson.append(pkt.toJson());
    }
    pktJson["packets"] = resultJson;
    auto resp = HttpResponse::newHttpJsonResponse(pktJson);
    callback(resp);

}

void PacketController::persistAllPacketsInMongoDB(const HttpRequestPtr &req,
                                                  function<void(const HttpResponsePtr &)> &&callback) {

    std::string fileUUID = (*req->getJsonObject())["fileUUID"].asString();
    auto it = CCSDSPacketFileHelper::uuidToSavedPacketsMapper.find(fileUUID);
    if (it == CCSDSPacketFileHelper::uuidToSavedPacketsMapper.end()) {
        return ControllerErrorHelper::sendError(std::move(callback), k404NotFound, "File UUID not found.");
    }

    const std::vector<CCSDS_Packet> allPackets = it->second;
    auto packetsCopy = std::make_shared<std::vector<CCSDS_Packet>>(allPackets);
    thread([packetsCopy]() {
        MongoDBHandler dbHandler;
        int eachTimeNotifyClients = (int)packetsCopy->size() / 10;
        for (size_t i = 0; i < packetsCopy->size(); ++i) {

            auto packet = packetsCopy->at(i);

            dbHandler.insertPacket(packet);
            if (i % eachTimeNotifyClients == 0) {
                int progress = std::ceil(((double)i / (double) packetsCopy->size()) * 100);
                ClientCommunicationHelper::notifyClients(progress);
            }
        }

    }).detach();
    Json::Value pktJson;
    pktJson["message"] = "Packets insertion is in progress.";
    auto resp = HttpResponse::newHttpJsonResponse(pktJson);
    callback(resp);
}

void PacketController::persistAllPacketsInMongoDBBasedOnSID(const HttpRequestPtr &req,
                                                            function<void(const HttpResponsePtr &)> &&callback) {
    MongoDBHandler dbHandler;
    auto sidStr = (*req->getJsonObject())["sid"].asString();
    int _sid = 0;
    try {
        _sid = std::stoi(sidStr);
    }
    catch (const std::exception &e) {
        return ControllerErrorHelper::sendError(std::move(callback), k400BadRequest,
                                         "Invalid sid parameter.");
    }
    std::string fileUUID = (*req->getJsonObject())["fileUUID"].asString();
    auto it = CCSDSPacketFileHelper::uuidToSavedPacketsMapper.find(fileUUID);
    if (it == CCSDSPacketFileHelper::uuidToSavedPacketsMapper.end()) {
        return ControllerErrorHelper::sendError(std::move(callback), k404NotFound, "File UUID not found.");
    }

    const std::vector<CCSDS_Packet> &allPackets = it->second;
    std::vector<CCSDS_Packet> filteredPackets;
    for (const auto &pkt: allPackets) {
        if (pkt.sid == _sid) // assuming CCSDS_Packet has a `sid` field
        {
            filteredPackets.push_back(pkt);
        }
    }
    auto packetsCopy = std::make_shared<std::vector<CCSDS_Packet>>(filteredPackets);
    thread([packetsCopy]() {
        MongoDBHandler dbHandler;
        int eachTimeNotifyClients = (int)packetsCopy->size() / 10;
        for (size_t i = 0; i < packetsCopy->size(); ++i) {

            auto packet = packetsCopy->at(i);

            dbHandler.insertPacket(packet);
            if (i % eachTimeNotifyClients == 0) {
                int progress = std::ceil(((double)i / (double)packetsCopy->size()) * 100);
                ClientCommunicationHelper::notifyClients(progress);
            }
        }

    }).detach();
    Json::Value pktJson;
    pktJson["message"] = "Packets inserted successfully.";
    auto resp = HttpResponse::newHttpJsonResponse(pktJson);
    callback(resp);
}

void PacketController::persistAllPacketsInCSVFile(const HttpRequestPtr &req,
                                                  function<void(const HttpResponsePtr &)> &&callback) {
    std::string fileUUID = (*req->getJsonObject())["fileUUID"].asString();
    auto it = CCSDSPacketFileHelper::uuidToSavedPacketsMapper.find(fileUUID);
    if (it == CCSDSPacketFileHelper::uuidToSavedPacketsMapper.end()) {
        return ControllerErrorHelper::sendError(std::move(callback), k404NotFound, "File UUID not found.");
    }

    const std::vector<CCSDS_Packet> allPackets = it->second;
    auto packetsCopy = std::make_shared<std::vector<CCSDS_Packet>>(allPackets);
    thread([packetsCopy]() {
        try {
            CSVHandler csvHandler;
            int eachTimeNotifyClients = (int)packetsCopy->size() / 10;
            for (size_t i = 0; i < packetsCopy->size(); ++i) {

                auto packet = packetsCopy->at(i);

                csvHandler.insertPacket(packet);
                if (i % eachTimeNotifyClients == 0) {
                    int progress = std::ceil(((double)i / (double)packetsCopy->size()) * 100);
                    ClientCommunicationHelper::notifyClients(progress);
                }
            }
        } catch (const exception &e) {
            ClientCommunicationHelper::notifyClients(-1);
            LOG_ERROR << "Exception caught: " << e.what() << "\n";
        }

    }).detach();
    Json::Value pktJson;
    pktJson["message"] = "Packets insertion is in progress.";
    auto resp = HttpResponse::newHttpJsonResponse(pktJson);
    callback(resp);

}

void
PacketController::downloadCSVFile(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback) {
    std::string sid = (*req->getJsonObject())["sid"].asString();

//    drogon::app().getDocumentRoot()
//    std::string fullPath = drogon::app().getDocumentRoot() + "uploads/ExtendedPayloadP" + sid + ".csv";
    std::string fullPath = "uploads/ExtendedPayloadP" + sid + ".csv";
    std::string filename = "ExtendedPayloadP" + sid + ".csv";
    std::ifstream file(fullPath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k404NotFound);
        resp->setBody("File not found");
        callback(resp);
        return;
    }

    auto fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::string fileData(fileSize, '\0');
    file.read(&fileData[0], fileSize);
    file.close();

    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(std::move(fileData));
    resp->addHeader("Content-Disposition", "attachment; filename=\"" + filename + "\"");
    resp->setContentTypeCode(CT_APPLICATION_OCTET_STREAM);
    callback(resp);
}

void
PacketController::getSidsList(const HttpRequestPtr &req, function<void(const HttpResponsePtr &)> &&callback, const string& fileUUID) {

//    if (fileUUID) {
//        return ControllerErrorHelper::sendError(std::move(callback), k400BadRequest, "Missing fileUUID.");
//    }

    // Get packets from UUID mapping
    auto it = CCSDSPacketFileHelper::uuidToSids.find(fileUUID);
    if (it == CCSDSPacketFileHelper::uuidToSids.end()) {
        return ControllerErrorHelper::sendError(std::move(callback), k404NotFound, "File UUID not found.");
    }

    const std::set<uint8_t > &allSids = it->second;

    // Convert to JSON
    Json::Value sidJson;
    sidJson["fileUUID"] = fileUUID;
    sidJson["num of all sids"] = static_cast<int>(allSids.size());
    Json::Value sidArray(Json::arrayValue);
    for (uint8_t sid : allSids) {
        sidArray.append(static_cast<int>(sid)); // JSON only has numbers, so cast to int
    }
    sidJson["sids"] = sidArray;
    auto resp = HttpResponse::newHttpJsonResponse(sidJson);
    callback(resp);
}


