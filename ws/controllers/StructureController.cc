#include "StructureController.h"
#include "helpers/StructureHelper.h"

void StructureController::uploadFile(const drogon::HttpRequestPtr &req,
                                     std::function<void(const HttpResponsePtr &)> &&callback) const {
    MultiPartParser fileUpload;
    if (fileUpload.parse(req) != 0 || fileUpload.getFiles().size() != 1) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody("Must only be one file");
        resp->setStatusCode(k403Forbidden);
        callback(resp);
        return;
    }

    HttpFile file = fileUpload.getFiles()[0];
    auto md5 = file.getMd5();
    Json::Value msg;
    file.setFileName("structure.json");
    file.save();
    std::string filePath = "uploads/" + file.getFileName();
    msg["msg"] = "The uploaded file has been saved in path " + filePath;
    auto resp = HttpResponse::newHttpJsonResponse(msg);
    LOG_INFO << "The uploaded file has been saved to the ./uploads "
                "directory";
    StructureHelper::generateStructsFromJsonAndStoreInDB(filePath);
    callback(resp);

}
// Add definition of your processing function here
