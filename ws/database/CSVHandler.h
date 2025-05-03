//
// Created by ambaqinejad on 4/16/25.
//

#ifndef FINAL_PROJECT_CSVHANDLER_H
#define FINAL_PROJECT_CSVHANDLER_H
#include "logics/CCSDS_Packet.h"


class CSVHandler {
public:
    CSVHandler();

    void insertPacket(const CCSDS_Packet &packet);


private:
    std::string csvFilePath;

    void insertHeader(const CCSDS_Packet &packet, std::ofstream &file);
    template <typename ArrayType>
    std::string writeArray(const ArrayType* arr, size_t size);
};

#endif //FINAL_PROJECT_CSVHANDLER_H
