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

    // Helper to serialize extended payloads
    template <typename T>
    void serializeExtendedPayloadP1(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP2(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP3(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP4(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP5(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP6(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP7(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP8(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP9(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP10(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP11(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP12(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP13(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP14(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP15(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP16(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP17(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP18(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP19(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP20(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP21(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP22(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP23(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP24(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP25(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP26(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP27(const T payload, const CCSDS_Packet& packet, std::ofstream &file);
    template <typename T>
    void serializeExtendedPayloadP28(const T payload, const CCSDS_Packet& packet, std::ofstream &file);

    void insertHeader(const CCSDS_Packet &packet, std::ofstream &file);
    template <typename ArrayType>
    std::string writeArray(const ArrayType* arr, size_t size);
};

#endif //FINAL_PROJECT_CSVHANDLER_H
