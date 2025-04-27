#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class StructureController : public drogon::HttpController<StructureController>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    // METHOD_ADD(StructureController::get, "/{2}/{1}", Get); // path is /StructureController/{arg2}/{arg1}
    // METHOD_ADD(StructureController::your_method_name, "/{1}/{2}/list", Get); // path is /StructureController/{arg1}/{arg2}/list
    // ADD_METHOD_TO(StructureController::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list
    ADD_METHOD_TO(StructureController::uploadFile, "/upload-structure", Post); // path is /absolute/path/{arg1}/{arg2}/list

    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
     void uploadFile(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
};
