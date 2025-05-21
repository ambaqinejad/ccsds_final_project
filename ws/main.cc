#include <drogon/drogon.h>
#include <iostream>
#include "./logics/SIDs.h"
#include "database/MongoDBHandler.h"
#include "helpers/StructureHelper.h"

using namespace std;

int main(int argc, char *argv[]) {

    MongoDBHandler dbHandler;

    bool isLoaded = dbHandler.loadStructure();
    if (!isLoaded) {
        const char* structure_file_path_env = std::getenv("DEFAULT_STRUCTURE_FILE_PATH");
        std::string structure_file_path = structure_file_path_env ? structure_file_path_env : "uploads/default_structure.json";
        cout << structure_file_path_env << endl;
        StructureHelper::generateStructsFromJsonAndStoreInDB(structure_file_path);
        std::cout << "Default structure will be loaded." << std::endl;
        dbHandler.loadStructure();
    }
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
    return 0;
}
