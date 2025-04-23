#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class PacketController : public drogon::HttpController<PacketController>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    // METHOD_ADD(PacketController::get, "/{2}/{1}", Get); // path is /PacketController/{arg2}/{arg1}
    // METHOD_ADD(PacketController::your_method_name, "/{1}/{2}/list", Get); // path is /PacketController/{arg1}/{arg2}/list
    // ADD_METHOD_TO(PacketController::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list
    ADD_METHOD_TO(PacketController::getSIDPacketsByPagination, "/getSIDPacketsByPagination", Post);
    ADD_METHOD_TO(PacketController::persistAllPacketsInMongoDB, "/persistAllPacketsInMongoDB", Post);
    ADD_METHOD_TO(PacketController::persistAllPacketsInMongoDBBasedOnSID, "/persistAllPacketsInMongoDBBasedOnSID", Post);

    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
     void getSIDPacketsByPagination(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
     void persistAllPacketsInMongoDB(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
     void persistAllPacketsInMongoDBBasedOnSID(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
};
