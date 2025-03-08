#include <drogon/drogon.h>
#include <iostream>
#include "./logics/SIDs.h"
using namespace std;

int main(int argc, char *argv[]) {
    cout << sizeof(ExtendedP5) << endl;
    int port = 5000;

    if (argc > 1) {
      port = stoi(argv[1]);
    }
    std::cout << "Starting WebSocket server on port " << port << std::endl;

    //Set HTTP listener address and port
    drogon::app().addListener("0.0.0.0", port);
    drogon::app().run();
    return 0;
}
