#include <drogon/drogon.h>
#include <iostream>
#include "database/MongoDBHandler.h"
#include "helpers/StructureHelper.h"

using namespace std;

#include <drogon/HttpFilter.h>
#include "helpers/EnvHelper.h"
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, const char *argv[]) {
    string documentRoot = EnvHelper::readEnvVariable("DOCUMENT_ROOT",
                          "/home/ambaqinejad/Desktop/drogon_ccsds/ccsds_final_project/ws/public");
    string uploadPath = documentRoot + "/uploads";
    MongoDBHandler dbHandler;
    if (!dbHandler.loadStructure()) {
        LOG_INFO << "Websocket server could not start because structure did not load.";
        return 0;
    }

    if (!fs::exists(documentRoot)) {
        if (!fs::create_directory(documentRoot)) {
            LOG_INFO << "Websocket server could not start because it can not create public folder.";
            return -1;
        }
    }

    if (!fs::exists(uploadPath)) {
        if (!fs::create_directory(uploadPath)) {
            LOG_INFO << "Websocket server could not start because it can not create upload folder.";
            return -1;
        }
    }

    int port = 5000;
    if (argc > 1) port = stoi(argv[1]);
    LOG_INFO << "Starting WebSocket server on port " << port;
    auto &app = drogon::app();

    // 1️⃣ Handle OPTIONS (CORS preflight)
    app.registerPreRoutingAdvice([](const drogon::HttpRequestPtr &req,
                                    drogon::AdviceCallback &&acb,
                                    drogon::AdviceChainCallback &&accb) {
        if (req->getMethod() == drogon::Options) {
            auto resp = drogon::HttpResponse::newHttpResponse();
            resp->addHeader("Access-Control-Allow-Origin", "*");
            resp->addHeader("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
            resp->addHeader("Access-Control-Allow-Headers",
                            "Content-Type, Authorization, X-Requested-With, x-signalr-user-agent");
            resp->setStatusCode(drogon::k200OK);
            acb(resp);  // Send immediate response for OPTIONS
        } else {
            accb();  // Continue normal routing
        }
    });

    // 3️⃣ Add CORS headers to all valid responses
    app.registerPostHandlingAdvice([](const drogon::HttpRequestPtr &req,
                                      const drogon::HttpResponsePtr &resp) {
        resp->addHeader("Access-Control-Allow-Origin", "*");
        resp->addHeader("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        resp->addHeader("Access-Control-Allow-Headers",
                        "Content-Type, Authorization, X-Requested-With, x-signalr-user-agent");
    });

    // 4️⃣ Configure Drogon app
    app.setClientMaxBodySize(200 * 2000 * 2000)
            .setUploadPath(uploadPath)
            .addListener("0.0.0.0", port)
            .setDocumentRoot(documentRoot)
//            .registerCustomExtensionMime("csv", "application/octet-stream") // Force download for CSV
//            .registerCustomExtensionMime("txt", "text/plain") // Explicitly set txt MIME type
            .run();
    return 0;
}
