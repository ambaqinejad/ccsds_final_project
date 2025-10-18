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
    ADD_METHOD_TO(PacketController::downloadCSVFile, "/downloadCSVFile", Post);


    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    static void getSIDPacketsByPagination(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) ;
    static void persistAllPacketsInMongoDB(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) ;
    static void persistAllPacketsInMongoDBBasedOnSID(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) ;
    static void persistAllPacketsInCSVFile(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) ;
    static void downloadCSVFile(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) ;

};
