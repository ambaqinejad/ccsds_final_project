#include "StructureController.h"
#include "helpers/StructureHelper.h"

void StructureController::uploadFile(const drogon::HttpRequestPtr &req,
                                     std::function<void(const HttpResponsePtr &)> &&callback) {
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
    msg["message"] = "The uploaded file has been saved";
    LOG_INFO << "The uploaded file has been saved to the ./uploads "
                "directory";
    std::string resultMessage = StructureHelper::generateStructsFromJsonAndStoreInDB(filePath);
    msg["resultMessage"] = resultMessage;
    auto resp = HttpResponse::newHttpJsonResponse(msg);
    callback(resp);
}
// Add definition of your processing function here
