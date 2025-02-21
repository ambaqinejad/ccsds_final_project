#include "CCSDSController.h"
#include <cstdlib>

void CCSDSController::startWebSocket(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, int port) {
    // Start WebSocket process dynamically
    std::string command = "/workspace/ws/build/final-project " + std::to_string(port) + " &";  // Run in background
    int result = std::system(command.c_str());

    if (result == 0)
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody("WebSocket started on port " + std::to_string(port));
        callback(resp);
    }
    else
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody("Failed to start WebSocket");
        callback(resp);
    }
}

// Add definition of your processing function here
