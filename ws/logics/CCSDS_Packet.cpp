#include "CCSDS_Packet.h"
#include <iostream>
#include <cstring>
#include <iomanip>
#include <arpa/inet.h>
#include "SIDs.h"

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
        return ntohs(value);
    };

    auto read_uint32 = [&](size_t& offset) {
        uint32_t value;
        std::memcpy(&value, &chunk[offset], sizeof(value));
        offset += sizeof(value);
        return ntohs(value);
    };

    auto read_uint64 = [&](size_t& offset) {
        uint64_t value;
        std::memcpy(&value, &chunk[offset], sizeof(value));
        offset += sizeof(value);
        return ntohs(value);
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

    if (packet.sid == 1) {
        ExtendedP1 p1;
        std::memcpy(&p1, packet.payload.data(), sizeof(ExtendedP1));
        packet.extended_payload = p1;
    } else if (packet.sid == 2) {
        ExtendedP2 p2;
        std::memcpy(&p2, packet.payload.data(), sizeof(ExtendedP2));
        packet.extended_payload = p2;
    } else if (packet.sid == 3) {
        ExtendedP3 p3;
        std::memcpy(&p3, packet.payload.data(), sizeof(ExtendedP3));
        packet.extended_payload = p3;
    } else if (packet.sid == 4) {
        ExtendedP4 p4;
        std::memcpy(&p4, packet.payload.data(), sizeof(ExtendedP4));
        packet.extended_payload = p4;
    } else if (packet.sid == 5) {
        ExtendedP5 p5;
        std::memcpy(&p5, packet.payload.data(), sizeof(ExtendedP5));
        packet.extended_payload = p5;
    } else if (packet.sid == 6) {
        ExtendedP6 p6;
        std::memcpy(&p6, packet.payload.data(), sizeof(ExtendedP6));
        packet.extended_payload = p6;
    } else if (packet.sid == 7) {
        ExtendedP7 p7;
        std::memcpy(&p7, packet.payload.data(), sizeof(ExtendedP7));
        packet.extended_payload = p7;
    } else if (packet.sid == 8) {
        ExtendedP8 p8;
        std::memcpy(&p8, packet.payload.data(), sizeof(ExtendedP8));
        packet.extended_payload = p8;
    } else if (packet.sid == 9) {
        ExtendedP9 p9;
        std::memcpy(&p9, packet.payload.data(), sizeof(ExtendedP9));
        packet.extended_payload = p9;
    } else if (packet.sid == 10) {
        ExtendedP10 p10;
        std::memcpy(&p10, packet.payload.data(), sizeof(ExtendedP10));
        packet.extended_payload = p10;
    } else if (packet.sid == 11) {
        ExtendedP11 p11;
        std::memcpy(&p11, packet.payload.data(), sizeof(ExtendedP11));
        packet.extended_payload = p11;
    } else if (packet.sid == 12) {
        ExtendedP12 p12;
        std::memcpy(&p12, packet.payload.data(), sizeof(ExtendedP12));
        packet.extended_payload = p12;
    } else if (packet.sid == 13) {
        ExtendedP13 p13;
        std::memcpy(&p13, packet.payload.data(), sizeof(ExtendedP13));
        packet.extended_payload = p13;
    } else if (packet.sid == 14) {
        ExtendedP14 p14;
        std::memcpy(&p14, packet.payload.data(), sizeof(ExtendedP14));
        packet.extended_payload = p14;
    } else if (packet.sid == 15) {
        ExtendedP15 p15;
        std::memcpy(&p15, packet.payload.data(), sizeof(ExtendedP15));
        packet.extended_payload = p15;
    } else if (packet.sid == 16) {
        ExtendedP16 p16;
        std::memcpy(&p16, packet.payload.data(), sizeof(ExtendedP16));
        packet.extended_payload = p16;
    } else if (packet.sid == 17) {
        ExtendedP17 p17;
        std::memcpy(&p17, packet.payload.data(), sizeof(ExtendedP17));
        packet.extended_payload = p17;
    } else if (packet.sid == 18) {
        ExtendedP18 p18;
        std::memcpy(&p18, packet.payload.data(), sizeof(ExtendedP18));
        packet.extended_payload = p18;
    } else if (packet.sid == 19) {
        ExtendedP19 p19;
        std::memcpy(&p19, packet.payload.data(), sizeof(ExtendedP19));
        packet.extended_payload = p19;
    } else if (packet.sid == 20) {
        ExtendedP20 p20;
        std::memcpy(&p20, packet.payload.data(), sizeof(ExtendedP20));
        packet.extended_payload = p20;
    } else if (packet.sid == 21) {
        ExtendedP21 p21;
        std::memcpy(&p21, packet.payload.data(), sizeof(ExtendedP21));
        packet.extended_payload = p21;
    } else if (packet.sid == 22) {
        ExtendedP22 p22;
        std::memcpy(&p22, packet.payload.data(), sizeof(ExtendedP22));
        packet.extended_payload = p22;
    } else if (packet.sid == 23) {
        ExtendedP23 p23;
        std::memcpy(&p23, packet.payload.data(), sizeof(ExtendedP23));
        packet.extended_payload = p23;
    } else if (packet.sid == 24) {
        ExtendedP24 p24;
        std::memcpy(&p24, packet.payload.data(), sizeof(ExtendedP24));
        packet.extended_payload = p24;
    } else if (packet.sid == 25) {
        ExtendedP25 p25;
        std::memcpy(&p25, packet.payload.data(), sizeof(ExtendedP25));
        packet.extended_payload = p25;
    } else if (packet.sid == 26) {
        ExtendedP26 p26;
        std::memcpy(&p26, packet.payload.data(), sizeof(ExtendedP26));
        packet.extended_payload = p26;
    } else if (packet.sid == 27) {
        ExtendedP27 p27;
        std::memcpy(&p27, packet.payload.data(), sizeof(ExtendedP27));
        packet.extended_payload = p27;
    } else if (packet.sid == 28) {
        ExtendedP28 p28;
        std::memcpy(&p28, packet.payload.data(), sizeof(ExtendedP28));
        packet.extended_payload = p28;
    }

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