#include <drogon/drogon.h>
#include <iostream>
#include "database/MongoDBHandler.h"
#include "helpers/StructureHelper.h"

using namespace std;

#include <drogon/HttpFilter.h>

#include <drogon/drogon.h>
//#include "MongoDBHandler.h"

using namespace std;

int main(int argc, const char *argv[]) {

    const char* document_root = std::getenv("DOCUMENT_ROOT");
    string documentRoot = document_root ? document_root : "/home/ambaqinejad/Desktop/drogon_ccsds/ccsds_final_project/ws/public";

    MongoDBHandler dbHandler;
    if (!dbHandler.loadStructure()) {
        LOG_INFO << "Websocket server could not start because structure did not load.";
        return 0;
    }

    int port = 5000;
    if (argc > 1) port = stoi(argv[1]);
    cout << "Starting WebSocket server on port " << port << endl;
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
    app.setClientMaxBodySize(20 * 2000 * 2000)
            .setUploadPath("./uploads")
            .addListener("0.0.0.0", port)
            .setDocumentRoot(documentRoot)
            .registerCustomExtensionMime("csv", "application/octet-stream") // Force download for CSV
            .registerCustomExtensionMime("txt", "text/plain") // Explicitly set txt MIME type
            .run();
    cout << app.getUploadPath() << endl;
    return 0;
}
