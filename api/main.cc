#include <drogon/drogon.h>
int main() {
    //Set HTTP listener address and port
    int port = 5000;
    drogon::app().addListener("0.0.0.0", port);
    LOG_INFO << "Starting api server on port " << port << "\n";
    //Load config file
    //drogon::app().loadConfigFile("../config.json");
    //drogon::app().loadConfigFile("../config.yaml");
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}
