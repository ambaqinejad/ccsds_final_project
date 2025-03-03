#include "CCSDS_Packet.h"
#include <iostream>
#include <cstring>
#include <iomanip>

CCSDS_Packet::CCSDS_Packet() {
    main_frame_header = 0;
    packet_id = 0;
    packet_sequence_control = 0;
    packet_length = 0;
    data_field_header = 0;
    service_type = 0;
    sub_service_type = 0;
    sid = 0;
    timestamp = 0;
    crc_fail_upload_map = 0;
    flash_address = 0;
}
//
// uint16_t CCSDS_Packet::getSequence() const { return sequence; }
//
// void CCSDS_Packet::setSequence(uint16_t _sequence) { sequence = _sequence; }
//
// uint16_t CCSDS_Packet::getLength() const { return length; }
//
// void CCSDS_Packet::setLength(uint16_t _length) { length = _length; }
//
// uint16_t CCSDS_Packet::getHeader() const { return header; }
//
// void CCSDS_Packet::setHeader(uint16_t _header) { header = _header; }
//
// const std::vector<uint8_t> &CCSDS_Packet::getPayload() const { return payload; }
//
// void CCSDS_Packet::setPayload(const std::vector<uint8_t> &_payload) { payload = _payload; }

CCSDS_Packet CCSDS_Packet::deserialize_packet(vector<uint8_t> &chunk) {
    CCSDS_Packet packet;
    size_t offset = 0;

    auto read_uint16 = [&](size_t& offset) {
        uint16_t value;
        std::memcpy(&value, &chunk[offset], sizeof(value));
        offset += sizeof(value);
        return value;
    };

    auto read_uint32 = [&](size_t& offset) {
        uint32_t value;
        std::memcpy(&value, &chunk[offset], sizeof(value));
        offset += sizeof(value);
        return value;
    };

    auto read_uint64 = [&](size_t& offset) {
        uint64_t value;
        std::memcpy(&value, &chunk[offset], sizeof(value));
        offset += sizeof(value);
        return value;
    };

    // Read fixed fields
    packet.main_frame_header = read_uint16(offset);
    packet.packet_id = read_uint16(offset);
    packet.packet_sequence_control = read_uint16(offset);
    packet.packet_length = read_uint16(offset);
    packet.data_field_header = chunk[offset++];
    packet.service_type = chunk[offset++];
    packet.sub_service_type = chunk[offset++];
    packet.sid = chunk[offset++];
    packet.timestamp = read_uint32(offset);
    packet.crc_fail_upload_map = read_uint64(offset);
    packet.flash_address = read_uint32(offset);

    // Remaining bytes are payload
    packet.payload.assign(chunk.begin() + offset, chunk.end());

    return packet;
}

void CCSDS_Packet::parsePacket(const vector<uint8_t> &rawData) {
    // if (rawData.size() < 6) {
    //     cerr << "Packet is too short for parsing!" << endl;
    //     return;
    // }
    //
    // memcpy(&header, rawData.data(), 2);
    // memcpy(&sequence, rawData.data() + 2, 2);
    // memcpy(&length, rawData.data() + 4, 2);
    //
    // payload.assign(rawData.begin() + 6, rawData.end());
}

void CCSDS_Packet::printPacket() const {
    // cout << "CCSDS Packet Header Info:" << endl;
    // cout << "Version: " << ((header >> 13) & 0x07) << endl;
    // cout << "Type: " << ((header >> 12) & 0x01) << endl;
    // cout << "APID: " << (header & 0x07FF) << endl;
    // cout << "Packet Sequence Count: " << (sequence & 0x3FFF) << endl;
    // cout << "Payload Data: ";
    // for (uint8_t byte: payload) {
    //     cout << hex << setw(2) << setfill('0') << (int) byte << " ";
    // }
    // cout << dec << endl;
}