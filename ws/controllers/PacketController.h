#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class PacketController : public drogon::HttpController<PacketController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(PacketController::getSIDPacketsByPagination, "/getSIDPacketsByPagination", Post);
    ADD_METHOD_TO(PacketController::persistAllPacketsInMongoDB, "/persistAllPacketsInMongoDB", Post);
    ADD_METHOD_TO(PacketController::persistAllPacketsInMongoDBBasedOnSID, "/persistAllPacketsInMongoDBBasedOnSID", Post);
        ADD_METHOD_TO(PacketController::persistAllPacketsInCSVFile, "/persistAllPacketsInCSVFile", Post);


    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
     void getSIDPacketsByPagination(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
     void persistAllPacketsInMongoDB(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
     void persistAllPacketsInMongoDBBasedOnSID(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
    void persistAllPacketsInCSVFile(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;

};
