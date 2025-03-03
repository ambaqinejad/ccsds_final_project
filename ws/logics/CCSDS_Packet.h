#ifndef CCSDS_PARSER_CCSDS_PACKET_H
#define CCSDS_PARSER_CCSDS_PACKET_H

#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;

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

private:
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
};

#endif // CCSDS_PARSER_CCSDS_PACKET_H