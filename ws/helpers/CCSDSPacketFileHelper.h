//
// Created by ambaqinejad on 4/19/25.
//

#ifndef FINAL_PROJECT_CCSDSPACKETFILEHELPER_H
#define FINAL_PROJECT_CCSDSPACKETFILEHELPER_H


#include <vector>
#include <cstdint>
#include <string>
#include <map>
#include <vector>
#include <string>
#include "logics/CCSDS_Packet.h"

class CCSDSPacketFileHelper {
public:
    static void processFile(const std::string &filePath, const std::string &fileUUID);
    static void parseData(std::vector<std::vector<uint8_t>> chunks, int count_of_valid_chunks, const std::string &fileUUID);
    static std::map<std::string, std::vector<CCSDS_Packet>> uuidToSavedPacketsMapper;
};


#endif //FINAL_PROJECT_CCSDSPACKETFILEHELPER_H
