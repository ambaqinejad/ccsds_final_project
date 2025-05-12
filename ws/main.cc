#include <drogon/drogon.h>
#include <iostream>
#include "./logics/SIDs.h"
#include "database/MongoDBHandler.h"
using namespace std;

int main(int argc, char *argv[]) {

    MongoDBHandler dbHandler;
    if (dbHandler.loadStructure()) {
        int port = 5000;
        if (argc > 1) {
            port = stoi(argv[1]);
        }
        std::cout << "Starting WebSocket server on port " << port << std::endl;
        //Set HTTP listener address and port
        drogon::app()
                .setClientMaxBodySize(20*2000*2000)
                .setUploadPath("./uploads")
                .addListener("0.0.0.0", port);
        drogon::app().run();
    } else {
        LOG_INFO << "Websocket server could not started due to structer did not load.";
    }
    return 0;
}
