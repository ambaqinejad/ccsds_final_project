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

    // 2️⃣ Handle routes like /ws/negotiate that may not hit controllers
    app.registerPostRoutingAdvice([](const drogon::HttpRequestPtr &req,
                                     drogon::AdviceCallback &&acb,
                                     drogon::AdviceChainCallback &&accb) {
        if (req->path().find("/ws2") != std::string::npos) {
            cout << "!23";
            auto resp = drogon::HttpResponse::newHttpResponse();
            resp->addHeader("Access-Control-Allow-Origin", "*");
            resp->addHeader("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
            resp->addHeader("Access-Control-Allow-Headers",
                            "Content-Type, Authorization, X-Requested-With, x-signalr-user-agent");
            resp->setStatusCode(drogon::k200OK);
            acb(resp);
        } else {
            accb();  // Continue normal response flow
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

    // ✅ 3. Create /ws2/negotiate endpoint for SignalR/WebSocket clients
//    app.registerHandler(
//            "/ws2/negotiate",
//            [](const drogon::HttpRequestPtr &req,
//               std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
//                Json::Value responseJson;
//                responseJson["connectionId"] = "dummy-connection-id";
//                responseJson["connectionToken"] = "dummy-connection-token";
//                responseJson["protocolVersion"] = "1.5";
//
//                Json::Value wsTransport;
//                wsTransport["transport"] = "WebSockets";
//                wsTransport["transferFormats"] = Json::arrayValue;
//                wsTransport["transferFormats"].append("Text");
//
//                responseJson["availableTransports"] = Json::arrayValue;
//                responseJson["availableTransports"].append(wsTransport);
//
//                auto resp = drogon::HttpResponse::newHttpJsonResponse(responseJson);
//                resp->addHeader("Access-Control-Allow-Origin", "*");
//                resp->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
//                resp->addHeader("Access-Control-Allow-Headers",
//                                "Content-Type, Authorization, X-Requested-With, x-signalr-user-agent");
//
//                callback(resp);
//            },
//            {drogon::Get, drogon::Post, drogon::Options});

    // 4️⃣ Configure Drogon app
    app.setClientMaxBodySize(20 * 2000 * 2000)
            .setUploadPath("./uploads")
            .addListener("0.0.0.0", port)
            .run();

    return 0;
}
