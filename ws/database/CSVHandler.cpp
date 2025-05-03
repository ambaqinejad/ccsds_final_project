////
//// Created by ambaqinejad on 4/16/25.
////
//
#include "CSVHandler.h"

#include <fstream>
#include <iomanip>
#include "logics/CCSDS_Packet.h"

CSVHandler::CSVHandler() {

}
//
void CSVHandler::insertPacket(const CCSDS_Packet &packet) {
    std::string filename = "ExtendedPayloadP" + std::to_string(packet.sid) + ".csv";

    // Open file in append mode
    std::ofstream csvFile(filename, std::ios::app);
    if (!csvFile.is_open()) {
        std::cerr << "Failed to open CSV file." << std::endl;
        return;
    }

    // Collect all keys from parsedData
    std::vector<std::string> keys;
    for (const auto& member : packet.parsedData.getMemberNames()) {
        keys.push_back(member);
    }

    // Check if header already exists
    std::ifstream checkFile(filename);
    bool isEmpty = (checkFile.peek() == std::ifstream::traits_type::eof());
    checkFile.close();

    if (isEmpty) {
        // Write header
        csvFile << "main_frame_header,packet_id,packet_sequence_control,packet_length,"
                   "data_field_header,service_type,sub_service_type,sid,timestamp,"
                   "crc_fail_upload_map,flash_address";
        for (const auto& key : keys) {
            csvFile << ',' << key;
        }
        csvFile << '\n';
    }

    // Write values
    csvFile << packet.main_frame_header << ',' << packet.packet_id;
    csvFile << packet.packet_sequence_control << ',' << packet.packet_length;
    csvFile << packet.data_field_header << ',' << packet.service_type;
    csvFile << packet.sub_service_type << ',' << packet.sid;
    csvFile << packet.timestamp << ',' << packet.crc_fail_upload_map;
    csvFile << packet.flash_address;
    for (const auto& key : keys) {
        if (packet.parsedData[key].isString())
            csvFile << ',' << std::quoted(packet.parsedData[key].asString());
        else if (packet.parsedData[key].isNumeric())
            csvFile << ',' << packet.parsedData[key].asDouble();
        else
            csvFile << ',' << std::quoted(packet.parsedData[key].toStyledString());
    }
    csvFile << '\n';

    csvFile.close();
    std::cout << "Packet written to CSV with flattened fields." << std::endl;

    std::cout << "Packet inserted successfully." << std::endl;
}
