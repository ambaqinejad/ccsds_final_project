#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class StructureController : public drogon::HttpController<StructureController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(StructureController::uploadFile, "/upload-structure", Post); // path is /absolute/path/{arg1}/{arg2}/list

    METHOD_LIST_END
    void uploadFile(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
};
