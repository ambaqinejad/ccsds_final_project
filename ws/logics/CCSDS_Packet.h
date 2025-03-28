#ifndef CCSDS_PARSER_CCSDS_PACKET_H
#define CCSDS_PARSER_CCSDS_PACKET_H

#include <iostream>
#include <cstdint>
#include <vector>
#include <variant>
#include <memory>

#include "SIDs.h"

using namespace std;

using ExtendedPayload = std::variant<
    std::monostate, ExtendedP1, ExtendedP2, ExtendedP3, ExtendedP4,
    ExtendedP5, ExtendedP6, ExtendedP7, ExtendedP8, ExtendedP9,
    ExtendedP10, ExtendedP11, ExtendedP12, ExtendedP13, ExtendedP14,
    ExtendedP15, ExtendedP16, ExtendedP17, ExtendedP18, ExtendedP19,
    ExtendedP20, ExtendedP21, ExtendedP22, ExtendedP23, ExtendedP24,
    ExtendedP25, ExtendedP26, ExtendedP27, ExtendedP28>;

class CCSDS_Packet {
public:
    // [[nodiscard]] uint16_t getSequence() const;
    // void setSequence(uint16_t sequence);
    // [[nodiscard]] uint16_t getLength() const;
    // void setLength(uint16_t length);
    // [[nodiscard]] const vector<uint8_t> &getPayload() const;
    // void setPayload(const vector<uint8_t> &payload);
    // [[nodiscard]] uint16_t getHeader() const;
    // void setHeader(uint16_t header);

    // Constructor
    CCSDS_Packet();

    // Function to deserialize the 128-byte chunk into a Packet structure
    CCSDS_Packet deserialize_packet(vector<uint8_t> &data);

    // Parse raw binary data
    void parsePacket(const vector<uint8_t>& rawData);

    // Display Parsed Packet Data
    void printPacket() const;

// private:
    uint16_t main_frame_header;
    uint16_t packet_id;
    uint16_t packet_sequence_control;
    uint16_t packet_length;
    uint8_t data_field_header;
    uint8_t service_type;
    uint8_t sub_service_type;
    uint8_t sid;
    uint32_t timestamp;
    uint64_t crc_fail_upload_map;
    uint32_t flash_address;
    vector<uint8_t> payload;
    ExtendedPayload extended_payload;  // Store the extended data
};

#endif // CCSDS_PARSER_CCSDS_PACKET_H