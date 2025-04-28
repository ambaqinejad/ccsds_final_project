#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>  // JSON for Modern C++
#include "StructureHelper.h"
#include "database/MongoDBHandler.h"

// Function to convert JSON to C++ structs
void StructureHelper::generateStructsFromJsonAndStoreInDB(const std::string& jsonFilePath) {
    // Read JSON file
    std::ifstream jsonFile(jsonFilePath);
    if (!jsonFile.is_open()) {
        std::cerr << "Failed to open JSON file!" << std::endl;
        return;
    }

    nlohmann::ordered_json j;
    jsonFile >> j;

    MongoDBHandler dbHandler;
    dbHandler.insertStructure(j);

    std::cout << "Structs generated successfully into db." << std::endl;

}