#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>  // JSON for Modern C++
#include "StructureHelper.h"
#include "structure/structs.h"

// Function to convert JSON to C++ structs
void StructureHelper::generateStructsFromJson(const std::string& jsonFilePath, const std::string& outputFilePath) {
    // Read JSON file
    std::ifstream jsonFile(jsonFilePath);
    if (!jsonFile.is_open()) {
        std::cerr << "Failed to open JSON file!" << std::endl;
        return;
    }

    nlohmann::ordered_json j;
    jsonFile >> j;

    std::ofstream outputFile(outputFilePath);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file!" << std::endl;
        return;
    }

    int structCounter = 1;
    for (const auto& obj : j) {
        outputFile << "struct Struct" << structCounter++ << " {\n";

        for (auto it = obj.begin(); it != obj.end(); ++it) {
            outputFile << "    " << it.value() << " " << it.key() << ";\n";
        }

        outputFile << "};\n\n";
    }

    std::cout << "Structs generated successfully into " << outputFilePath << std::endl;

}