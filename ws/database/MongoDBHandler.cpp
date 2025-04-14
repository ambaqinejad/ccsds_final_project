//
// Created by ambaqinejad on 3/27/25.
//

#include "MongoDBHandler.h"

#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include "logics/CCSDS_Packet.h"

MongoDBHandler::MongoDBHandler() {
    // mongocxx::instance instance;

    static mongocxx::instance instance{}; // Required once per application
    client = mongocxx::client{mongocxx::uri{"mongodb://192.168.102.79:27017"}};
    database = client["CCSDS_DB"];
    collection = database["packets"];
}

void MongoDBHandler::insertPacket(const CCSDS_Packet &packet) {
    bsoncxx::builder::basic::document document{};

    document.append(bsoncxx::builder::basic::kvp("main_frame_header", packet.main_frame_header));
    document.append(bsoncxx::builder::basic::kvp("packet_id", packet.packet_id));
    document.append(bsoncxx::builder::basic::kvp("packet_sequence_control", packet.packet_sequence_control));
    document.append(bsoncxx::builder::basic::kvp("packet_length", packet.packet_length));
    document.append(bsoncxx::builder::basic::kvp("data_field_header", static_cast<int>(packet.data_field_header)));
    document.append(bsoncxx::builder::basic::kvp("service_type", static_cast<int>(packet.service_type)));
    document.append(bsoncxx::builder::basic::kvp("sub_service_type", static_cast<int>(packet.sub_service_type)));
    document.append(bsoncxx::builder::basic::kvp("sid", static_cast<int>(packet.sid)));
    document.append(bsoncxx::builder::basic::kvp("timestamp", static_cast<int64_t>(packet.timestamp)));
    document.append(bsoncxx::builder::basic::kvp("crc_fail_upload_map", static_cast<int64_t>(packet.crc_fail_upload_map)));
    document.append(bsoncxx::builder::basic::kvp("flash_address", static_cast<int>(packet.flash_address)));

//    // Convert payload to BSON array
//    bsoncxx::builder::basic::array payload_array;
//    for (auto byte : packet.payload) {
//        payload_array.append(static_cast<int>(byte));
//    }
//    document.append(bsoncxx::builder::basic::kvp("payload", payload_array));
//

    // Serialize the extended_payload
    std::visit([&](auto &&arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::monostate>) {
            document.append(bsoncxx::builder::basic::kvp("type", "none"));
        } else if constexpr (std::is_same_v<T, ExtendedP1>) {
            serializeExtendedPayloadP1(arg);
        }
        else if constexpr (std::is_same_v<T, ExtendedP2>) {
            serializeExtendedPayloadP2(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP3>) {
            serializeExtendedPayloadP3(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP4>) {
            serializeExtendedPayloadP4(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP5>) {
            serializeExtendedPayloadP5(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP6>) {
            serializeExtendedPayloadP6(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP7>) {
            serializeExtendedPayloadP7(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP8>) {
            serializeExtendedPayloadP8(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP9>) {
            serializeExtendedPayloadP9(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP10>) {
            serializeExtendedPayloadP10(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP11>) {
            serializeExtendedPayloadP11(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP12>) {
            serializeExtendedPayloadP12(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP13>) {
            serializeExtendedPayloadP13(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP14>) {
            serializeExtendedPayloadP14(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP15>) {
            serializeExtendedPayloadP15(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP16>) {
            serializeExtendedPayloadP16(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP17>) {
            serializeExtendedPayloadP17(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP18>) {
            serializeExtendedPayloadP18(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP19>) {
            serializeExtendedPayloadP19(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP20>) {
            serializeExtendedPayloadP20(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP21>) {
            serializeExtendedPayloadP21(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP22>) {
            serializeExtendedPayloadP22(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP23>) {
            serializeExtendedPayloadP23(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP24>) {
            serializeExtendedPayloadP24(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP25>) {
            serializeExtendedPayloadP25(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP26>) {
            serializeExtendedPayloadP26(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP27>) {
            serializeExtendedPayloadP27(arg);
        } else if constexpr (std::is_same_v<T, ExtendedP28>) {
            serializeExtendedPayloadP28(arg);
        }
    }, packet.extended_payload);
    collection.insert_one(document.view());
    std::cout << "Packet inserted successfully." << std::endl;
}



template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP1(const T payload) {
    bsoncxx::builder::basic::document doc{};

    bsoncxx::builder::basic::array cam1_array;
    for (auto byte : payload.CameraPacket1) cam1_array.append(static_cast<int>(byte));
    doc.append(bsoncxx::builder::basic::kvp("CameraPacket2", cam1_array));
    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP2(const T payload) {
    bsoncxx::builder::basic::document doc{};

    bsoncxx::builder::basic::array cam2_array, cam3_array;
    for (auto byte : payload.CameraPacket2) cam2_array.append(static_cast<uint8_t>(byte));
    for (auto byte : payload.CameraPacket3) cam3_array.append(static_cast<uint8_t>(byte));
    doc.append(bsoncxx::builder::basic::kvp("CameraPacket2", cam2_array));
    doc.append(bsoncxx::builder::basic::kvp("CameraPacket3", cam3_array));

    doc.append(bsoncxx::builder::basic::kvp("res", payload.res));
    doc.append(bsoncxx::builder::basic::kvp("MemoryStatus", static_cast<int64_t>(payload.MemoryStatus)));
    doc.append(bsoncxx::builder::basic::kvp("StartFrequency", payload.StartFrequency));
    doc.append(bsoncxx::builder::basic::kvp("StopFrequency", payload.StopFrequency));
    doc.append(bsoncxx::builder::basic::kvp("CFARConstant", payload.CFARConstant));
    doc.append(bsoncxx::builder::basic::kvp("StepTime", payload.StepTime));
    doc.append(bsoncxx::builder::basic::kvp("RxGain", payload.RxGain));
    doc.append(bsoncxx::builder::basic::kvp("SigintResponseFlag", static_cast<int32_t >(payload.SigintResponseFlag)));
    doc.append(bsoncxx::builder::basic::kvp("MRAMAdcsConfigFlag", payload.MRAMAdcsConfigFlag));
    doc.append(bsoncxx::builder::basic::kvp("MRAMSatParameterFlag", payload.MRAMSatParameterFlag));
    doc.append(bsoncxx::builder::basic::kvp("MRAMTeleCounterFlag", payload.MRAMTeleCounterFlag));
    doc.append(bsoncxx::builder::basic::kvp("LastResetSource", payload.LastResetSource));
    doc.append(bsoncxx::builder::basic::kvp("TeleCounterOnline", static_cast<int32_t >(payload.TeleCounterOnline)));
    doc.append(bsoncxx::builder::basic::kvp("TeleCounterOffline", static_cast<int32_t >(payload.TeleCounterOffline)));
    doc.append(bsoncxx::builder::basic::kvp("TaskResetCnt", payload.TaskResetCnt));
    doc.append(bsoncxx::builder::basic::kvp("LastTaskResetNum", payload.LastTaskResetNum));
    bsoncxx::builder::basic::array respart2_2;
    for (auto byte : payload.respart2_2) respart2_2.append(static_cast<uint8_t>(byte));
    doc.append(bsoncxx::builder::basic::kvp("respart2_2", respart2_2));
    doc.append(bsoncxx::builder::basic::kvp("UV_TransmitterFreq", static_cast<int32_t >(payload.UV_TransmitterFreq)));
    doc.append(bsoncxx::builder::basic::kvp("UV_RecieverFreq", static_cast<int32_t >(payload.UV_RecieverFreq)));

    doc.append(bsoncxx::builder::basic::kvp("UV_TX", static_cast<int32_t >(payload.UV_TX)));
    doc.append(bsoncxx::builder::basic::kvp("respart2_3", payload.respart2_3));
    // Add more fields if needed
    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP3(const T payload) {
    bsoncxx::builder::basic::document doc{};

    // Serialize all uint8_t[4] arrays
    auto append_array = [](bsoncxx::builder::basic::document& doc, const std::string& key, const uint8_t* data, size_t size = 4) {
        bsoncxx::builder::basic::array arr;
        for (size_t i = 0; i < size; ++i)
            arr.append(static_cast<uint8_t>(data[i]));
        doc.append(bsoncxx::builder::basic::kvp(key, arr));
    };

    append_array(doc, "UV_RX", payload.UV_RX);
    append_array(doc, "UV_AES_Config", payload.UV_AES_Config);
    append_array(doc, "UV_TR_Output_Power", payload.UV_TR_Output_Power);
    append_array(doc, "UV_BeacanRepeatTime", payload.UV_BeacanRepeatTime);
    append_array(doc, "UV_Voltage", payload.UV_Voltage);
    append_array(doc, "UV_RSSI", payload.UV_RSSI);
    append_array(doc, "UV_Temperature", payload.UV_Temperature);
    append_array(doc, "UV_Temperature_OverHeat", payload.UV_Temperature_OverHeat);
    append_array(doc, "UV_Rf_Telemetry", payload.UV_Rf_Telemetry);

    // Serialize int8_t[3] and int8_t[4] arrays
    {
        bsoncxx::builder::basic::array arr;
        for (int i = 0; i < 3; ++i)
            arr.append(static_cast<int8_t>(payload.RF_telemetry_X[i]));
        doc.append(bsoncxx::builder::basic::kvp("RF_telemetry_X", arr));
    }

    {
        bsoncxx::builder::basic::array arr;
        for (int i = 0; i < 4; ++i)
            arr.append(static_cast<int8_t>(payload.TEMP_telemetry_X[i]));
        doc.append(bsoncxx::builder::basic::kvp("TEMP_telemetry_X", arr));
    }

    doc.append(bsoncxx::builder::basic::kvp("XdataRate", payload.XdataRate));

    {
        bsoncxx::builder::basic::array arr;
        for (int i = 0; i < 4; ++i)
            arr.append(static_cast<int8_t>(payload.voltage_telemetry_X[i]));
        doc.append(bsoncxx::builder::basic::kvp("voltage_telemetry_X", arr));
    }

    doc.append(bsoncxx::builder::basic::kvp("Transmitter_Status_X", static_cast<int8_t>(payload.Transmitter_Status_X)));
    doc.append(bsoncxx::builder::basic::kvp("OutputPower", static_cast<int8_t>(payload.OutputPower)));
    doc.append(bsoncxx::builder::basic::kvp("CAN_Status_X", static_cast<int8_t>(payload.CAN_Status_X)));
    doc.append(bsoncxx::builder::basic::kvp("Transmitter_mode_X", static_cast<int8_t>(payload.Transmitter_mode_X)));
    doc.append(bsoncxx::builder::basic::kvp("Tx_frequency_X", payload.Tx_frequency_X));

    doc.append(bsoncxx::builder::basic::kvp("S_TR_Scratch", payload.S_TR_Scratch));
    doc.append(bsoncxx::builder::basic::kvp("S_TR_AES_Index", payload.S_TR_AES_Index));
    doc.append(bsoncxx::builder::basic::kvp("S_TR_Modulation", payload.S_TR_Modulation));
    doc.append(bsoncxx::builder::basic::kvp("S_TR_Bitrate", payload.S_TR_Bitrate));
    doc.append(bsoncxx::builder::basic::kvp("S_TR_Fdiviation", payload.S_TR_Fdiviation));
    doc.append(bsoncxx::builder::basic::kvp("S_TR_BandWidth", payload.S_TR_BandWidth));
    doc.append(bsoncxx::builder::basic::kvp("S_TR_CrcInit", payload.S_TR_CrcInit));
    doc.append(bsoncxx::builder::basic::kvp("S_TR_Lmx2572_Freq", payload.S_TR_Lmx2572_Freq));
    doc.append(bsoncxx::builder::basic::kvp("S_TR_Fifo_State", payload.S_TR_Fifo_State));
    doc.append(bsoncxx::builder::basic::kvp("S_TR_SystemFaults", payload.S_TR_SystemFaults));

    {
        bsoncxx::builder::basic::array arr;
        for (int i = 0; i < 3; ++i)
            arr.append(static_cast<uint8_t>(payload.resp2[i]));
        doc.append(bsoncxx::builder::basic::kvp("resp2", arr));
    }

    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP4(const T payload) {
    bsoncxx::builder::basic::document doc{};

    doc.append(bsoncxx::builder::basic::kvp("S_TR_ReadLogAmp", payload.S_TR_ReadLogAmp));
    doc.append(bsoncxx::builder::basic::kvp("S_TR_TempSens1", payload.S_TR_TempSens1));
    doc.append(bsoncxx::builder::basic::kvp("S_TR_TempSens2", payload.S_TR_TempSens2));
    doc.append(bsoncxx::builder::basic::kvp("S_TR_Power", payload.S_TR_Power));
    doc.append(bsoncxx::builder::basic::kvp("S_TR_IntThr", payload.S_TR_IntThr));
    doc.append(bsoncxx::builder::basic::kvp("S_TR_TransCuttOffTemp", payload.S_TR_TransCuttOffTemp));
    doc.append(bsoncxx::builder::basic::kvp("S_RX_Scratch", payload.S_RX_Scratch));
    doc.append(bsoncxx::builder::basic::kvp("S_RX_AES_Index", payload.S_RX_AES_Index));
    doc.append(bsoncxx::builder::basic::kvp("S_RX_Modulation", payload.S_RX_Modulation));
    doc.append(bsoncxx::builder::basic::kvp("S_RX_Bitrate", payload.S_RX_Bitrate));
    doc.append(bsoncxx::builder::basic::kvp("RX_Fdiviation", payload.RX_Fdiviation));
    doc.append(bsoncxx::builder::basic::kvp("S_RX_BandWidth", payload.S_RX_BandWidth));
    doc.append(bsoncxx::builder::basic::kvp("S_RX_CrcInit", payload.S_RX_CrcInit));
    doc.append(bsoncxx::builder::basic::kvp("S_RX_Lmx2572_Freq", payload.S_RX_Lmx2572_Freq));
    doc.append(bsoncxx::builder::basic::kvp("S_RX_Fifo_State", payload.S_RX_Fifo_State));
    doc.append(bsoncxx::builder::basic::kvp("S_RX_SystemFaults", payload.S_RX_SystemFaults));
    doc.append(bsoncxx::builder::basic::kvp("S_RX_ReadLogAmp", payload.S_RX_ReadLogAmp));
    doc.append(bsoncxx::builder::basic::kvp("S_RX_TempSens1", payload.S_RX_TempSens1));
    doc.append(bsoncxx::builder::basic::kvp("S_RX_TempSens2", payload.S_RX_TempSens2));
    doc.append(bsoncxx::builder::basic::kvp("S_RX_Power", payload.S_RX_Power));
    doc.append(bsoncxx::builder::basic::kvp("S_RX_IntThr", payload.S_RX_IntThr));
    doc.append(bsoncxx::builder::basic::kvp("S_RX_Reciever_SyncCrcErr", payload.S_RX_Reciever_SyncCrcErr));
    doc.append(bsoncxx::builder::basic::kvp("S_RX_RSSI_Const", payload.S_RX_RSSI_Const));
    doc.append(bsoncxx::builder::basic::kvp("S_RX_RSSI", payload.S_RX_RSSI));
    doc.append(bsoncxx::builder::basic::kvp("S_RX_RS485BD", payload.S_RX_RS485BD));

    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP5(const T payload) {
    bsoncxx::builder::basic::document doc{};

    bsoncxx::builder::basic::array pmu_array;
    for (int i = 0; i < 100; ++i) {
        pmu_array.append(static_cast<uint8_t>(payload.PMU1[i]));
    }

    doc.append(bsoncxx::builder::basic::kvp("PMU1", pmu_array));

    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP6(const T payload) {
    bsoncxx::builder::basic::document doc{};

    bsoncxx::builder::basic::array pmu_array;
    for (int i = 0; i < 100; ++i) {
        pmu_array.append(static_cast<uint8_t>(payload.PMU2[i]));
    }

    doc.append(bsoncxx::builder::basic::kvp("PMU2", pmu_array));

    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP7(const T payload) {
    bsoncxx::builder::basic::document doc{};

    bsoncxx::builder::basic::array pmu_array;
    for (int i = 0; i < 100; ++i) {
        pmu_array.append(static_cast<uint8_t>(payload.PMU3[i]));
    }

    doc.append(bsoncxx::builder::basic::kvp("PMU3", pmu_array));

    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP8(const T payload) {
    bsoncxx::builder::basic::document doc{};

    doc.append(bsoncxx::builder::basic::kvp("FDIRReportFlags", payload.FDIRReportFlags));
    doc.append(bsoncxx::builder::basic::kvp("FDIROverCurrentReport", payload.FDIROverCurrentReport));
    doc.append(bsoncxx::builder::basic::kvp("OBCConfigReport", payload.OBCConfigReport));

    doc.append(bsoncxx::builder::basic::kvp("SFResetCnt", payload.SFResetCnt));
    doc.append(bsoncxx::builder::basic::kvp("CBResetCnt", payload.CBResetCnt));
    doc.append(bsoncxx::builder::basic::kvp("IRPDUResetCnt", payload.IRPDUResetCnt));
    doc.append(bsoncxx::builder::basic::kvp("Sun1DevStatus", payload.Sun1DevStatus));
    doc.append(bsoncxx::builder::basic::kvp("Sun2DevStatus", payload.Sun2DevStatus));
    doc.append(bsoncxx::builder::basic::kvp("Sun3DevStatus", payload.Sun3DevStatus));
    doc.append(bsoncxx::builder::basic::kvp("Sun4DevStatus", payload.Sun4DevStatus));
    doc.append(bsoncxx::builder::basic::kvp("Sun5DevStatus", payload.Sun5DevStatus));
    doc.append(bsoncxx::builder::basic::kvp("Sun6DevStatus", payload.Sun6DevStatus));
    doc.append(bsoncxx::builder::basic::kvp("Gyro1DevStatus", payload.Gyro1DevStatus));
    doc.append(bsoncxx::builder::basic::kvp("Gyro2DevStatus", payload.Gyro2DevStatus));
    doc.append(bsoncxx::builder::basic::kvp("RW1DevStatus", payload.RW1DevStatus));
    doc.append(bsoncxx::builder::basic::kvp("RW2DevStatus", payload.RW2DevStatus));
    doc.append(bsoncxx::builder::basic::kvp("RW3DevStatus", payload.RW3DevStatus));
    doc.append(bsoncxx::builder::basic::kvp("RW4DevStatus", payload.RW4DevStatus));
    doc.append(bsoncxx::builder::basic::kvp("RW5DevStatus", payload.RW5DevStatus));

    doc.append(bsoncxx::builder::basic::kvp("StarTrackerDevStatus", payload.StarTrackerDevStatus));
    doc.append(bsoncxx::builder::basic::kvp("IRStarTrackerDevStatus", payload.IRStarTrackerDevStatus));
    doc.append(bsoncxx::builder::basic::kvp("CameraLCCDevStatus", payload.CameraLCCDevStatus));
    doc.append(bsoncxx::builder::basic::kvp("UVBandDevStatus", payload.UVBandDevStatus));
    doc.append(bsoncxx::builder::basic::kvp("MT_Isis5vDevStatus", payload.MT_Isis5vDevStatus));
    doc.append(bsoncxx::builder::basic::kvp("MT_Isis33vDevStatus", payload.MT_Isis33vDevStatus));
    doc.append(bsoncxx::builder::basic::kvp("MT_HescoDevStatus", payload.MT_HescoDevStatus));
    doc.append(bsoncxx::builder::basic::kvp("XBand5vDevStatus", payload.XBand5vDevStatus));
    doc.append(bsoncxx::builder::basic::kvp("XBandVBatDevStatus", payload.XBandVBatDevStatus));
    doc.append(bsoncxx::builder::basic::kvp("MM_HMR1DevStatus", payload.MM_HMR1DevStatus));
    doc.append(bsoncxx::builder::basic::kvp("MM_HMR2DevStatus", payload.MM_HMR2DevStatus));
    doc.append(bsoncxx::builder::basic::kvp("SBandRxDevStatus", payload.SBandRxDevStatus));
    doc.append(bsoncxx::builder::basic::kvp("SBandTxDevStatus", payload.SBandTxDevStatus));
    doc.append(bsoncxx::builder::basic::kvp("SIGINTDevStatus", payload.SIGINTDevStatus));
    doc.append(bsoncxx::builder::basic::kvp("GPS1DevStatus", payload.GPS1DevStatus));
    doc.append(bsoncxx::builder::basic::kvp("GPS2DevStatus", payload.GPS2DevStatus));

    doc.append(bsoncxx::builder::basic::kvp("PRP8vDevStatus", payload.PRP8vDevStatus));
    doc.append(bsoncxx::builder::basic::kvp("PRP12vDevStatus", payload.PRP12vDevStatus));
    doc.append(bsoncxx::builder::basic::kvp("TempSensorDevStatus", payload.TempSensorDevStatus));
    doc.append(bsoncxx::builder::basic::kvp("BatteryHeaterDevStatus", payload.BatteryHeaterDevStatus));
    doc.append(bsoncxx::builder::basic::kvp("Onewire1DevStatus", payload.Onewire1DevStatus));
    doc.append(bsoncxx::builder::basic::kvp("Onewire2DevStatus", payload.Onewire2DevStatus));
    doc.append(bsoncxx::builder::basic::kvp("NandCommandFlag", payload.NandCommandFlag));
    doc.append(bsoncxx::builder::basic::kvp("NandInitFlag", payload.NandInitFlag));
    doc.append(bsoncxx::builder::basic::kvp("MMC_InitFlag", payload.MMC_InitFlag));
    doc.append(bsoncxx::builder::basic::kvp("PRPNumberSample", payload.PRPNumberSample));
    doc.append(bsoncxx::builder::basic::kvp("FreeRunningCnt1", payload.FreeRunningCnt1));
    doc.append(bsoncxx::builder::basic::kvp("FreeRunningCnt2", payload.FreeRunningCnt2));

    doc.append(bsoncxx::builder::basic::kvp("CB1Temprature", payload.CB1Temprature));
    doc.append(bsoncxx::builder::basic::kvp("CAMTemprature1", payload.CAMTemprature1));
    doc.append(bsoncxx::builder::basic::kvp("CAMTemprature2", payload.CAMTemprature2));
    doc.append(bsoncxx::builder::basic::kvp("CB2Temprature1", payload.CB2Temprature1));
    doc.append(bsoncxx::builder::basic::kvp("CB2Temprature2", payload.CB2Temprature2));
    doc.append(bsoncxx::builder::basic::kvp("PRPTimeSampling", payload.PRPTimeSampling));

    // Packed bitfield group (flattened here)
    doc.append(bsoncxx::builder::basic::kvp("FaultFlags_Part1", payload.NumberOfResetPMUConnection));
    doc.append(bsoncxx::builder::basic::kvp("FaultFlags_Part2", payload.MMCBlkCnt));
    doc.append(bsoncxx::builder::basic::kvp("MMC_WriteErrors", payload.MMC_WriteErrors));
    doc.append(bsoncxx::builder::basic::kvp("processSPIDataPacketErrorCnt", payload.processSPIDataPacketErrorCnt));

    bsoncxx::builder::basic::array rw_dev_id_array;
    for (int i = 0; i < 4; ++i) {
        rw_dev_id_array.append(static_cast<uint8_t>(payload.RWDevID[i]));
    }
    doc.append(bsoncxx::builder::basic::kvp("RWDevID", rw_dev_id_array));

    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP9(const T payload) {
    bsoncxx::builder::basic::document doc{};

    // UC1_SunReceiveCnt
    bsoncxx::builder::basic::array uc1_sun_receive;
    for (int i = 0; i < 3; ++i) {
        uc1_sun_receive.append(payload.UC1_SunReceiveCnt[i]);
    }
    doc.append(bsoncxx::builder::basic::kvp("UC1_SunReceiveCnt", uc1_sun_receive));

    doc.append(bsoncxx::builder::basic::kvp("UC2_LastGetTime", payload.UC2_LastGetTime));
    doc.append(bsoncxx::builder::basic::kvp("UC2_TransmitCnt", payload.UC2_TransmitCnt));
    doc.append(bsoncxx::builder::basic::kvp("UC2_SFReceiveCnt", payload.UC2_SFReceiveCnt));
    doc.append(bsoncxx::builder::basic::kvp("UC2_SwitchCmd", payload.UC2_SwitchCmd));
    doc.append(bsoncxx::builder::basic::kvp("UC2_SwitchRealState", payload.UC2_SwitchRealState));
    doc.append(bsoncxx::builder::basic::kvp("UC2_SwitchFlagState", payload.UC2_SwitchFlagState));

    // UC2_SunReceiveCnt
    bsoncxx::builder::basic::array uc2_sun_receive;
    for (int i = 0; i < 3; ++i) {
        uc2_sun_receive.append(payload.UC2_SunReceiveCnt[i]);
    }
    doc.append(bsoncxx::builder::basic::kvp("UC2_SunReceiveCnt", uc2_sun_receive));

    doc.append(bsoncxx::builder::basic::kvp("HE_durationProcess", payload.HE_durationProcess));
    doc.append(bsoncxx::builder::basic::kvp("HE_SFduration", payload.HE_SFduration));

    // HE_OBCTaskRunning
    bsoncxx::builder::basic::array obc_tasks;
    for (int i = 0; i < 32; ++i) {
        obc_tasks.append(payload.HE_OBCTaskRunning[i]);
    }
    doc.append(bsoncxx::builder::basic::kvp("HE_OBCTaskRunning", obc_tasks));

    doc.append(bsoncxx::builder::basic::kvp("Heater33vTimer", payload.Heater33vTimer));
    doc.append(bsoncxx::builder::basic::kvp("OAPPowerDisipation", payload.OAPPowerDisipation));
    doc.append(bsoncxx::builder::basic::kvp("HE_SPIGetCounter", payload.HE_SPIGetCounter));

    // HE_MRAMCnt
    bsoncxx::builder::basic::array mram_cnt;
    for (int i = 0; i < 3; ++i) {
        mram_cnt.append(payload.HE_MRAMCnt[i]);
    }
    doc.append(bsoncxx::builder::basic::kvp("HE_MRAMCnt", mram_cnt));

    doc.append(bsoncxx::builder::basic::kvp("HE_ObcCounter", payload.HE_ObcCounter));

    // RTC times
    bsoncxx::builder::basic::array rtc1, rtc2, rtc3;
    for (int i = 0; i < 3; ++i) {
        rtc1.append(payload.HE_RTCTime1[i]);
        rtc2.append(payload.HE_RTCTime2[i]);
        rtc3.append(payload.HE_RTCTime3[i]);
    }
    doc.append(bsoncxx::builder::basic::kvp("HE_RTCTime1", rtc1));
    doc.append(bsoncxx::builder::basic::kvp("HE_RTCTime2", rtc2));
    doc.append(bsoncxx::builder::basic::kvp("HE_RTCTime3", rtc3));

    doc.append(bsoncxx::builder::basic::kvp("HE_JulianDate", payload.HE_JulianDate));

    doc.append(bsoncxx::builder::basic::kvp("RW1TimeSetCommand", payload.RW1TimeSetCommand));
    doc.append(bsoncxx::builder::basic::kvp("RW1LastGetTime", payload.RW1LastGetTime));
    doc.append(bsoncxx::builder::basic::kvp("RW2TimeSetCommand", payload.RW2TimeSetCommand));
    doc.append(bsoncxx::builder::basic::kvp("RW2LastGetTime", payload.RW2LastGetTime));
    doc.append(bsoncxx::builder::basic::kvp("RW3TimeSetCommand", payload.RW3TimeSetCommand));
    doc.append(bsoncxx::builder::basic::kvp("RW3LastGetTime", payload.RW3LastGetTime));
    doc.append(bsoncxx::builder::basic::kvp("RW4TimeSetCommand", payload.RW4TimeSetCommand));

    doc.append(bsoncxx::builder::basic::kvp("SunIRLastGetTime", payload.SunIRLastGetTime));
    doc.append(bsoncxx::builder::basic::kvp("RWRLastGetTime", payload.RWRLastGetTime));
    doc.append(bsoncxx::builder::basic::kvp("StarIRLastGetTime", payload.StarIRLastGetTime));
    doc.append(bsoncxx::builder::basic::kvp("HescoLastGetTime", payload.HescoLastGetTime));
    doc.append(bsoncxx::builder::basic::kvp("BatteryFreeRunning", payload.BatteryFreeRunning));

    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP10(const T payload) {
    bsoncxx::builder::basic::document doc{};

    doc.append(bsoncxx::builder::basic::kvp("SS1LastGetTime", payload.SS1LastGetTime));
    doc.append(bsoncxx::builder::basic::kvp("SS1NumberSample", payload.SS1NumberSample));
    doc.append(bsoncxx::builder::basic::kvp("SS2LastGetTime", payload.SS2LastGetTime));
    doc.append(bsoncxx::builder::basic::kvp("SS2NumberSample", payload.SS2NumberSample));
    doc.append(bsoncxx::builder::basic::kvp("SS3LastGetTime", payload.SS3LastGetTime));
    doc.append(bsoncxx::builder::basic::kvp("SS3NumberSample", payload.SS3NumberSample));
    doc.append(bsoncxx::builder::basic::kvp("SS4LastGetTime", payload.SS4LastGetTime));
    doc.append(bsoncxx::builder::basic::kvp("SS4NumberSample", payload.SS4NumberSample));
    doc.append(bsoncxx::builder::basic::kvp("SS5LastGetTime", payload.SS5LastGetTime));
    doc.append(bsoncxx::builder::basic::kvp("SS5NumberSample", payload.SS5NumberSample));
    doc.append(bsoncxx::builder::basic::kvp("Gyro1LastGetTime", payload.Gyro1LastGetTime));
    doc.append(bsoncxx::builder::basic::kvp("Gyro1NumberSample", payload.Gyro1NumberSample));
    doc.append(bsoncxx::builder::basic::kvp("Gyro2LastGetTime", payload.Gyro2LastGetTime));
    doc.append(bsoncxx::builder::basic::kvp("Gyro2NumberSample", payload.Gyro2NumberSample));
    doc.append(bsoncxx::builder::basic::kvp("MMLastGetTime", payload.MMLastGetTime));
    doc.append(bsoncxx::builder::basic::kvp("MMNumberSample", payload.MMNumberSample));
    doc.append(bsoncxx::builder::basic::kvp("GPSLastGetTime", payload.GPSLastGetTime));
    doc.append(bsoncxx::builder::basic::kvp("GPSNumberSample", payload.GPSNumberSample));
    doc.append(bsoncxx::builder::basic::kvp("ClydeFreeRunning", payload.ClydeFreeRunning));
    doc.append(bsoncxx::builder::basic::kvp("ErrorCounterClyde", payload.ErrorCounterClyde));
    doc.append(bsoncxx::builder::basic::kvp("ErrorCounterClydeBattery", payload.ErrorCounterClydeBattery));
    doc.append(bsoncxx::builder::basic::kvp("OneWireFlagSwitch", payload.OneWireFlagSwitch));
    doc.append(bsoncxx::builder::basic::kvp("Year", payload.Year));
    doc.append(bsoncxx::builder::basic::kvp("Month", payload.Month));
    doc.append(bsoncxx::builder::basic::kvp("Day", payload.Day));
    doc.append(bsoncxx::builder::basic::kvp("Hour", payload.Hour));
    doc.append(bsoncxx::builder::basic::kvp("Minute", payload.Minute));
    doc.append(bsoncxx::builder::basic::kvp("Second", payload.Second));

    // OBC_RTC array
    bsoncxx::builder::basic::array obc_rtc_array;
    for (int i = 0; i < 6; ++i) {
        obc_rtc_array.append(payload.OBC_RTC[i]);
    }
    doc.append(bsoncxx::builder::basic::kvp("OBC_RTC", obc_rtc_array));

    doc.append(bsoncxx::builder::basic::kvp("OBC_MB_Temp", payload.OBC_MB_Temp));
    doc.append(bsoncxx::builder::basic::kvp("OBC_ID_", payload.OBC_ID_));
    doc.append(bsoncxx::builder::basic::kvp("BootCounter", payload.BootCounter));
    doc.append(bsoncxx::builder::basic::kvp("OBC_CommandCounter", payload.OBC_CommandCounter));
    doc.append(bsoncxx::builder::basic::kvp("OBC_Counter", payload.OBC_Counter));
    doc.append(bsoncxx::builder::basic::kvp("OBC_CpuUsage", payload.OBC_CpuUsage));
    doc.append(bsoncxx::builder::basic::kvp("OBC_Mode", payload.OBC_Mode));
    doc.append(bsoncxx::builder::basic::kvp("OBC_Current", payload.OBC_Current));
    doc.append(bsoncxx::builder::basic::kvp("OBC_RcvdCmdCounter", payload.OBC_RcvdCmdCounter));
    doc.append(bsoncxx::builder::basic::kvp("OBC_ExecutedCmdCounter", payload.OBC_ExecutedCmdCounter));
    doc.append(bsoncxx::builder::basic::kvp("UV_Fail_Timer", payload.UV_Fail_Timer));
    doc.append(bsoncxx::builder::basic::kvp("OBC_WaitingTCToRun", payload.OBC_WaitingTCToRun));
    doc.append(bsoncxx::builder::basic::kvp("OBC_ParameterAdd", payload.OBC_ParameterAdd));
    doc.append(bsoncxx::builder::basic::kvp("MMC_Write_BLK_ADD", payload.MMC_Write_BLK_ADD));
    doc.append(bsoncxx::builder::basic::kvp("MMC_Read_BLK_ADD", payload.MMC_Read_BLK_ADD));
    doc.append(bsoncxx::builder::basic::kvp("OBC_LINK_TYPE", payload.OBC_LINK_TYPE));
    doc.append(bsoncxx::builder::basic::kvp("RW4LastGetTime", payload.RW4LastGetTime));
    doc.append(bsoncxx::builder::basic::kvp("STRTimeSampling", payload.STRTimeSampling));
    doc.append(bsoncxx::builder::basic::kvp("MTTimeSetCmd", payload.MTTimeSetCmd));
    doc.append(bsoncxx::builder::basic::kvp("MTTimeSampling", payload.MTTimeSampling));
    doc.append(bsoncxx::builder::basic::kvp("FailCRC", payload.FailCRC));
    doc.append(bsoncxx::builder::basic::kvp("Flash_program_Add", payload.Flash_program_Add));
    doc.append(bsoncxx::builder::basic::kvp("ready_program", payload.ready_program));
    doc.append(bsoncxx::builder::basic::kvp("Program_Mode", payload.Program_Mode));
    doc.append(bsoncxx::builder::basic::kvp("ProgramVersion", payload.ProgramVersion));

    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP11(const T payload) {
    bsoncxx::builder::basic::document doc{};

    doc.append(bsoncxx::builder::basic::kvp("KeyIndexEncrypt_UV", payload.KeyIndexEncrypt_UV));
    doc.append(bsoncxx::builder::basic::kvp("KeyIndexEncrypt_X", payload.KeyIndexEncrypt_X));
    doc.append(bsoncxx::builder::basic::kvp("KeyIndexEncrypt_S_TX", payload.KeyIndexEncrypt_S_TX));
    doc.append(bsoncxx::builder::basic::kvp("KeyIndexEncrypt_S_RX", payload.KeyIndexEncrypt_S_RX));
    doc.append(bsoncxx::builder::basic::kvp("Num_active_Tasks", payload.Num_active_Tasks));
    doc.append(bsoncxx::builder::basic::kvp("MRAMs_Usage", payload.MRAMs_Usage));
    doc.append(bsoncxx::builder::basic::kvp("Nandflash_Usage", payload.Nandflash_Usage));
    doc.append(bsoncxx::builder::basic::kvp("SF_JulianDate", payload.SF_JulianDate));

    bsoncxx::builder::basic::array sf_mtdipole;
    for (int i = 0; i < 3; ++i) sf_mtdipole.append(payload.SF_MTDipoleActuation[i]);
    doc.append(bsoncxx::builder::basic::kvp("SF_MTDipoleActuation", sf_mtdipole));

    doc.append(bsoncxx::builder::basic::kvp("SF_SysTimerCnt", payload.SF_SysTimerCnt));
    doc.append(bsoncxx::builder::basic::kvp("SF_TransmitCnt", payload.SF_TransmitCnt));
    doc.append(bsoncxx::builder::basic::kvp("SF_MTDipoleDuaration", payload.SF_MTDipoleDuaration));

    bsoncxx::builder::basic::array sf_wheel_ref_cmd;
    for (int i = 0; i < 5; ++i) sf_wheel_ref_cmd.append(payload.SF_WheelRefrenceCommand[i]);
    doc.append(bsoncxx::builder::basic::kvp("SF_WheelRefrenceCommand", sf_wheel_ref_cmd));

    doc.append(bsoncxx::builder::basic::kvp("SF_CpuUsage", payload.SF_CpuUsage));
    doc.append(bsoncxx::builder::basic::kvp("SF_MTDurationOffTime", payload.SF_MTDurationOffTime));
    doc.append(bsoncxx::builder::basic::kvp("SF_RWInterfaceCfg", payload.SF_RWInterfaceCfg));
    doc.append(bsoncxx::builder::basic::kvp("SF_PowerDeviceCfg", payload.SF_PowerDeviceCfg));
    doc.append(bsoncxx::builder::basic::kvp("SF_AOCSFerquency", payload.SF_AOCSFerquency));

    bsoncxx::builder::basic::array i2c_status;
    for (int i = 0; i < 2; ++i) i2c_status.append(payload.SF_I2CStatus[i]);
    doc.append(bsoncxx::builder::basic::kvp("SF_I2CStatus", i2c_status));

    bsoncxx::builder::basic::array cb1_power_switch;
    for (int i = 0; i < 2; ++i) cb1_power_switch.append(payload.SF_CB1PowerSwitchCfg[i]);
    doc.append(bsoncxx::builder::basic::kvp("SF_CB1PowerSwitchCfg", cb1_power_switch));

    bsoncxx::builder::basic::array sf_cmd_mtdipole;
    for (int i = 0; i < 3; ++i) sf_cmd_mtdipole.append(payload.SFCmd_MTDipoleActuation[i]);
    doc.append(bsoncxx::builder::basic::kvp("SFCmd_MTDipoleActuation", sf_cmd_mtdipole));

    doc.append(bsoncxx::builder::basic::kvp("SFCmd_MTDipoleDuaration", payload.SFCmd_MTDipoleDuaration));

    bsoncxx::builder::basic::array sf_cmd_wheel_cmd;
    for (int i = 0; i < 5; ++i) sf_cmd_wheel_cmd.append(payload.SFCmd_WheelRefrenceCommand[i]);
    doc.append(bsoncxx::builder::basic::kvp("SFCmd_WheelRefrenceCommand", sf_cmd_wheel_cmd));

    doc.append(bsoncxx::builder::basic::kvp("SFCmd_MTDurationOffTime", payload.SFCmd_MTDurationOffTime));
    doc.append(bsoncxx::builder::basic::kvp("SFCmd_RWInterfaceCfg", payload.SFCmd_RWInterfaceCfg));
    doc.append(bsoncxx::builder::basic::kvp("SFCmd_PowerDeviceCfg", payload.SFCmd_PowerDeviceCfg));
    doc.append(bsoncxx::builder::basic::kvp("SFCmd_AOCSFerquency", payload.SFCmd_AOCSFerquency));

    doc.append(bsoncxx::builder::basic::kvp("UC1_LastGetTime", payload.UC1_LastGetTime));
    doc.append(bsoncxx::builder::basic::kvp("UC1_TransmitCnt", payload.UC1_TransmitCnt));
    doc.append(bsoncxx::builder::basic::kvp("UC1_SFReceiveCnt", payload.UC1_SFReceiveCnt));
    doc.append(bsoncxx::builder::basic::kvp("UC1_SwitchCmd", payload.UC1_SwitchCmd));
    doc.append(bsoncxx::builder::basic::kvp("UC1_SwitchRealState", payload.UC1_SwitchRealState));
    doc.append(bsoncxx::builder::basic::kvp("UC1_SwitchFlagState", payload.UC1_SwitchFlagState));
    doc.append(bsoncxx::builder::basic::kvp("DisableFaultPowerFDIR", payload.DisableFaultPowerFDIR));

    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP12(const T payload) {
    bsoncxx::builder::basic::document doc{};

    doc.append(bsoncxx::builder::basic::kvp("MMHMR1_X", payload.MMHMR1_X));
    doc.append(bsoncxx::builder::basic::kvp("MMHMR1_Y", payload.MMHMR1_Y));
    doc.append(bsoncxx::builder::basic::kvp("MMHMR1_Z", payload.MMHMR1_Z));
    doc.append(bsoncxx::builder::basic::kvp("MMHMR2_X", payload.MMHMR2_X));
    doc.append(bsoncxx::builder::basic::kvp("MMHMR2_Y", payload.MMHMR2_Y));
    doc.append(bsoncxx::builder::basic::kvp("MMHMR2_Z", payload.MMHMR2_Z));
    doc.append(bsoncxx::builder::basic::kvp("Gyro_Num", payload.Gyro_Num));
    doc.append(bsoncxx::builder::basic::kvp("Gyro1RateX", payload.Gyro1RateX));
    doc.append(bsoncxx::builder::basic::kvp("Gyro1RateY", payload.Gyro1RateY));
    doc.append(bsoncxx::builder::basic::kvp("Gyro1RateZ", payload.Gyro1RateZ));
    doc.append(bsoncxx::builder::basic::kvp("Gyro2RateX", payload.Gyro2RateX));
    doc.append(bsoncxx::builder::basic::kvp("Gyro2RateY", payload.Gyro2RateY));
    doc.append(bsoncxx::builder::basic::kvp("Gyro2RateZ", payload.Gyro2RateZ));
    doc.append(bsoncxx::builder::basic::kvp("Gyro1TempX", payload.Gyro1TempX));
    doc.append(bsoncxx::builder::basic::kvp("Gyro1TempY", payload.Gyro1TempY));
    doc.append(bsoncxx::builder::basic::kvp("Gyro1TempZ", payload.Gyro1TempZ));
    doc.append(bsoncxx::builder::basic::kvp("GPS_number", payload.GPS_number));
    doc.append(bsoncxx::builder::basic::kvp("GPS_State", payload.GPS_State));
    doc.append(bsoncxx::builder::basic::kvp("GPS_Temperature", payload.GPS_Temperature));
    doc.append(bsoncxx::builder::basic::kvp("TOW", payload.TOW));
    doc.append(bsoncxx::builder::basic::kvp("WeakNumber", payload.WeakNumber));
    doc.append(bsoncxx::builder::basic::kvp("UTC_Offset", payload.UTC_Offset));
    doc.append(bsoncxx::builder::basic::kvp("GPSLatitude", payload.GPSLatitude));
    doc.append(bsoncxx::builder::basic::kvp("GPSLongitude", payload.GPSLongitude));
    doc.append(bsoncxx::builder::basic::kvp("GPSAltitude", payload.GPSAltitude));

    bsoncxx::builder::basic::array gps_visible, gps_used, glonass_visible, glonass_used;
    for (int i = 0; i < 4; ++i) {
        gps_visible.append(payload.GPS_Visible[i]);
        gps_used.append(payload.GPS_Used[i]);
        glonass_visible.append(payload.GlonassVisible[i]);
        glonass_used.append(payload.GlonassUsed[i]);
    }
    doc.append(bsoncxx::builder::basic::kvp("GPS_Visible", gps_visible));
    doc.append(bsoncxx::builder::basic::kvp("GPS_Used", gps_used));
    doc.append(bsoncxx::builder::basic::kvp("GlonassVisible", glonass_visible));
    doc.append(bsoncxx::builder::basic::kvp("GlonassUsed", glonass_used));

    doc.append(bsoncxx::builder::basic::kvp("GPSPosX", payload.GPSPosX));
    doc.append(bsoncxx::builder::basic::kvp("GPSPosY", payload.GPSPosY));
    doc.append(bsoncxx::builder::basic::kvp("GPSPosZ", payload.GPSPosZ));
    doc.append(bsoncxx::builder::basic::kvp("GPSProcVX", payload.GPSProcVX));
    doc.append(bsoncxx::builder::basic::kvp("GPSProcVY", payload.GPSProcVY));
    doc.append(bsoncxx::builder::basic::kvp("GPSProcVZ", payload.GPSProcVZ));
    doc.append(bsoncxx::builder::basic::kvp("GPSPDOP", payload.GPSPDOP));
    doc.append(bsoncxx::builder::basic::kvp("GPSHDop", payload.GPSHDop));
    doc.append(bsoncxx::builder::basic::kvp("GPSVDop", payload.GPSVDop));
    doc.append(bsoncxx::builder::basic::kvp("GPSTDop", payload.GPSTDop));
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH11_SNR", payload.GPS1_CH11_SNR));
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH12_SNR", payload.GPS1_CH12_SNR));
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH13_SNR", payload.GPS1_CH13_SNR));
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH14_SNR", payload.GPS1_CH14_SNR));
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH15_SNR", payload.GPS1_CH15_SNR));

    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP13(const T payload) {
    bsoncxx::builder::basic::document doc{};

    // GPS SNR data
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH16_SNR", payload.GPS1_CH16_SNR));
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH17_SNR", payload.GPS1_CH17_SNR));
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH18_SNR", payload.GPS1_CH18_SNR));
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH19_SNR", payload.GPS1_CH19_SNR));
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH110_SNR", payload.GPS1_CH110_SNR));
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH111_SNR", payload.GPS1_CH111_SNR));
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH112_SNR", payload.GPS1_CH112_SNR));
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH21_SNR", payload.GPS1_CH21_SNR));
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH22_SNR", payload.GPS1_CH22_SNR));
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH23_SNR", payload.GPS1_CH23_SNR));
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH24_SNR", payload.GPS1_CH24_SNR));
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH25_SNR", payload.GPS1_CH25_SNR));
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH26_SNR", payload.GPS1_CH26_SNR));
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH27_SNR", payload.GPS1_CH27_SNR));
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH28_SNR", payload.GPS1_CH28_SNR));
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH29_SNR", payload.GPS1_CH29_SNR));
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH210_SNR", payload.GPS1_CH210_SNR));
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH211_SNR", payload.GPS1_CH211_SNR));
    doc.append(bsoncxx::builder::basic::kvp("GPS1_CH212_SNR", payload.GPS1_CH212_SNR));

    // SS data
    doc.append(bsoncxx::builder::basic::kvp("SS1ALPHA", payload.SS1ALPHA));
    doc.append(bsoncxx::builder::basic::kvp("SS1BETA", payload.SS1BETA));
    doc.append(bsoncxx::builder::basic::kvp("SS1sundetection", payload.SS1sundetection));
    doc.append(bsoncxx::builder::basic::kvp("SS1ERR", payload.SS1ERR));

    doc.append(bsoncxx::builder::basic::kvp("SS2ALPHA", payload.SS2ALPHA));
    doc.append(bsoncxx::builder::basic::kvp("SS2BETA", payload.SS2BETA));
    doc.append(bsoncxx::builder::basic::kvp("SS2sundetection", payload.SS2sundetection));
    doc.append(bsoncxx::builder::basic::kvp("SS2ERR", payload.SS2ERR));

    doc.append(bsoncxx::builder::basic::kvp("SS3ALPHA", payload.SS3ALPHA));
    doc.append(bsoncxx::builder::basic::kvp("SS3BETA", payload.SS3BETA));
    doc.append(bsoncxx::builder::basic::kvp("SS3sundetection", payload.SS3sundetection));
    doc.append(bsoncxx::builder::basic::kvp("SS3ERR", payload.SS3ERR));

    doc.append(bsoncxx::builder::basic::kvp("SS4ALPHA", payload.SS4ALPHA));
    doc.append(bsoncxx::builder::basic::kvp("SS4BETA", payload.SS4BETA));
    doc.append(bsoncxx::builder::basic::kvp("SS4sundetection", payload.SS4sundetection));
    doc.append(bsoncxx::builder::basic::kvp("SS4ERR", payload.SS4ERR));

    doc.append(bsoncxx::builder::basic::kvp("SS5ALPHA", payload.SS5ALPHA));
    doc.append(bsoncxx::builder::basic::kvp("SS5BETA", payload.SS5BETA));
    doc.append(bsoncxx::builder::basic::kvp("SS5sundetection", payload.SS5sundetection));
    doc.append(bsoncxx::builder::basic::kvp("SS5ERR", payload.SS5ERR));

    // HFP SS data
    doc.append(bsoncxx::builder::basic::kvp("HFP_SS_VecX", payload.HFP_SS_VecX));
    doc.append(bsoncxx::builder::basic::kvp("HFP_SS_VecY", payload.HFP_SS_VecY));
    doc.append(bsoncxx::builder::basic::kvp("HFP_SS_VecZ", payload.HFP_SS_VecZ));
    doc.append(bsoncxx::builder::basic::kvp("HFP_qq", payload.HFP_qq));
    doc.append(bsoncxx::builder::basic::kvp("HFP_gg", payload.HFP_gg));
    doc.append(bsoncxx::builder::basic::kvp("HFP_SS_Time", payload.HFP_SS_Time));

    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP14(const T payload) {
    bsoncxx::builder::basic::document doc{};

    // HFP SS data
    doc.append(bsoncxx::builder::basic::kvp("HFP_SS_Temp", payload.HFP_SS_Temp));
    doc.append(bsoncxx::builder::basic::kvp("HFP_SS_Voltage", payload.HFP_SS_Voltage));

    // Gyro2 temperature data
    doc.append(bsoncxx::builder::basic::kvp("Gyro2TempX", payload.Gyro2TempX));
    doc.append(bsoncxx::builder::basic::kvp("Gyro2TempY", payload.Gyro2TempY));
    doc.append(bsoncxx::builder::basic::kvp("Gyro2TempZ", payload.Gyro2TempZ));

    // Reserved data
    doc.append(bsoncxx::builder::basic::kvp("Reserv0", payload.Reserv0));
    doc.append(bsoncxx::builder::basic::kvp("Reserv1", payload.Reserv1));
    doc.append(bsoncxx::builder::basic::kvp("Reserv2", payload.Reserv2));

    // IMTQ data
    doc.append(bsoncxx::builder::basic::kvp("IMTQ_CMDDipX", payload.IMTQ_CMDDipX));
    doc.append(bsoncxx::builder::basic::kvp("IMTQ_CMDDipY", payload.IMTQ_CMDDipY));
    doc.append(bsoncxx::builder::basic::kvp("IMTQ_CMDDipZ", payload.IMTQ_CMDDipZ));
    doc.append(bsoncxx::builder::basic::kvp("IMTQCurX", payload.IMTQCurX));
    doc.append(bsoncxx::builder::basic::kvp("IMTQCury", payload.IMTQCury));
    doc.append(bsoncxx::builder::basic::kvp("IMTQCurz", payload.IMTQCurz));
    doc.append(bsoncxx::builder::basic::kvp("IMTQCoilTempX", payload.IMTQCoilTempX));
    doc.append(bsoncxx::builder::basic::kvp("IMTQCoilTempy", payload.IMTQCoilTempy));
    doc.append(bsoncxx::builder::basic::kvp("IMTQCoilTempz", payload.IMTQCoilTempz));
    doc.append(bsoncxx::builder::basic::kvp("IMTQ_MCUTemp", payload.IMTQ_MCUTemp));

    // Status data
    doc.append(bsoncxx::builder::basic::kvp("Status_cmd", payload.Status_cmd));
    doc.append(bsoncxx::builder::basic::kvp("status", payload.status));

    // Hes data
    doc.append(bsoncxx::builder::basic::kvp("HesMMFilteredX", payload.HesMMFilteredX));
    doc.append(bsoncxx::builder::basic::kvp("HesMMFilteredY", payload.HesMMFilteredY));
    doc.append(bsoncxx::builder::basic::kvp("HesMMFilteredZ", payload.HesMMFilteredZ));
    doc.append(bsoncxx::builder::basic::kvp("HesCMD_DipX", payload.HesCMD_DipX));
    doc.append(bsoncxx::builder::basic::kvp("HesCMD_DipY", payload.HesCMD_DipY));
    doc.append(bsoncxx::builder::basic::kvp("HesCMD_DipZ", payload.HesCMD_DipZ));
    doc.append(bsoncxx::builder::basic::kvp("HesCurX", payload.HesCurX));
    doc.append(bsoncxx::builder::basic::kvp("HesCurY", payload.HesCurY));
    doc.append(bsoncxx::builder::basic::kvp("HesCurZ", payload.HesCurZ));
    doc.append(bsoncxx::builder::basic::kvp("HesCoilTempX", payload.HesCoilTempX));
    doc.append(bsoncxx::builder::basic::kvp("HesCoilTempY", payload.HesCoilTempY));
    doc.append(bsoncxx::builder::basic::kvp("HesCoilTempZ", payload.HesCoilTempZ));
    doc.append(bsoncxx::builder::basic::kvp("HesMCUTemp", payload.HesMCUTemp));

    // RW1 data
    doc.append(bsoncxx::builder::basic::kvp("RW1Speed", payload.RW1Speed));
    doc.append(bsoncxx::builder::basic::kvp("RW1RefSpeed", payload.RW1RefSpeed));
    doc.append(bsoncxx::builder::basic::kvp("RW1Cur", payload.RW1Cur));
    doc.append(bsoncxx::builder::basic::kvp("RW1stat_Err_flg", payload.RW1stat_Err_flg));

    // RW2 data
    doc.append(bsoncxx::builder::basic::kvp("RW2Speed", payload.RW2Speed));
    doc.append(bsoncxx::builder::basic::kvp("RW2RefSpeed", payload.RW2RefSpeed));
    doc.append(bsoncxx::builder::basic::kvp("RW2Cur", payload.RW2Cur));
    doc.append(bsoncxx::builder::basic::kvp("RW2stat_Err_flg", payload.RW2stat_Err_flg));

    // RW3 data
    doc.append(bsoncxx::builder::basic::kvp("RW3Speed", payload.RW3Speed));
    doc.append(bsoncxx::builder::basic::kvp("RW3RefSpeed", payload.RW3RefSpeed));
    doc.append(bsoncxx::builder::basic::kvp("RW3Cur", payload.RW3Cur));
    doc.append(bsoncxx::builder::basic::kvp("RW3stat_Err_flg", payload.RW3stat_Err_flg));

    // RW4 data
    doc.append(bsoncxx::builder::basic::kvp("RW4Speed", payload.RW4Speed));
    doc.append(bsoncxx::builder::basic::kvp("RW4RefSpeed", payload.RW4RefSpeed));
    doc.append(bsoncxx::builder::basic::kvp("RW4Cur", payload.RW4Cur));
    doc.append(bsoncxx::builder::basic::kvp("RW4stat_Err_flg", payload.RW4stat_Err_flg));

    // RWHesco data
    doc.append(bsoncxx::builder::basic::kvp("RWHescoSpeed", payload.RWHescoSpeed));
    doc.append(bsoncxx::builder::basic::kvp("RWHescoRefSpeed", payload.RWHescoRefSpeed));
    doc.append(bsoncxx::builder::basic::kvp("RWHescoCur", payload.RWHescoCur));

    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP15(const T payload) {
    bsoncxx::builder::basic::document doc{};

    // RWHestat Error Flag
    doc.append(bsoncxx::builder::basic::kvp("RWHestat_Err_flg", payload.RWHestat_Err_flg));

    // TY Star Attitude and Time data
    doc.append(bsoncxx::builder::basic::kvp("TY_Star_attitudeQ1", payload.TY_Star_attitudeQ1));
    doc.append(bsoncxx::builder::basic::kvp("TY_Star_attitudeQ2", payload.TY_Star_attitudeQ2));
    doc.append(bsoncxx::builder::basic::kvp("TY_Star_attitudeQ3", payload.TY_Star_attitudeQ3));
    doc.append(bsoncxx::builder::basic::kvp("TY_Star_attitudeQ4", payload.TY_Star_attitudeQ4));
    doc.append(bsoncxx::builder::basic::kvp("TY_Star_internal_time", payload.TY_Star_internal_time));
    doc.append(bsoncxx::builder::basic::kvp("TY_StarTemp", payload.TY_StarTemp));
    doc.append(bsoncxx::builder::basic::kvp("TY_StarImage_expo_value", payload.TY_StarImage_expo_value));
    doc.append(bsoncxx::builder::basic::kvp("TY_StarImage_threshold", payload.TY_StarImage_threshold));
    doc.append(bsoncxx::builder::basic::kvp("TY_Star_background_value", payload.TY_Star_background_value));
    doc.append(bsoncxx::builder::basic::kvp("TY_StarReporting", payload.TY_StarReporting));
    doc.append(bsoncxx::builder::basic::kvp("TY_NumberOfExtractedStars", payload.TY_NumberOfExtractedStars));
    doc.append(bsoncxx::builder::basic::kvp("TY_ExternalImageSwitchStatus", payload.TY_ExternalImageSwitchStatus));
    doc.append(bsoncxx::builder::basic::kvp("TY_AttitudeEffectiveSign", payload.TY_AttitudeEffectiveSign));

    // IR Star Attitude and Time data
    doc.append(bsoncxx::builder::basic::kvp("IR_Star_attitudeQ1", payload.IR_Star_attitudeQ1));
    doc.append(bsoncxx::builder::basic::kvp("IR_Star_attitudeQ2", payload.IR_Star_attitudeQ2));
    doc.append(bsoncxx::builder::basic::kvp("IR_Star_attitudeQ3", payload.IR_Star_attitudeQ3));
    doc.append(bsoncxx::builder::basic::kvp("IR_Star_attitudeQ4", payload.IR_Star_attitudeQ4));
    doc.append(bsoncxx::builder::basic::kvp("IR_Star_internal_time", *reinterpret_cast<const double*>(payload.bytes)));  // Converting byte array to double
    doc.append(bsoncxx::builder::basic::kvp("IR_StarTemp", payload.IR_StarTemp));
    doc.append(bsoncxx::builder::basic::kvp("IR_StarImage_expo_value", payload.IR_StarImage_expo_value));
    doc.append(bsoncxx::builder::basic::kvp("IR_StarImage_threshold", payload.IR_StarImage_threshold));
    doc.append(bsoncxx::builder::basic::kvp("IR_Star_background_value", payload.IR_Star_background_value));
    doc.append(bsoncxx::builder::basic::kvp("IR_StarReporting", payload.IR_StarReporting));
    doc.append(bsoncxx::builder::basic::kvp("IR_NumberOfExtractedStars", payload.IR_NumberOfExtractedStars));
    doc.append(bsoncxx::builder::basic::kvp("IR_ExternalImageSwitchStatus", payload.IR_ExternalImageSwitchStatus));
    doc.append(bsoncxx::builder::basic::kvp("IR_AttitudeEffectiveSign", payload.IR_AttitudeEffectiveSign));

    // SS and MM magnetic field data
    doc.append(bsoncxx::builder::basic::kvp("SS_B_X", payload.SS_B_X));
    doc.append(bsoncxx::builder::basic::kvp("SS_B_Y", payload.SS_B_Y));
    doc.append(bsoncxx::builder::basic::kvp("SS_B_Z", payload.SS_B_Z));
    doc.append(bsoncxx::builder::basic::kvp("SS_ID", payload.SS_ID));
    doc.append(bsoncxx::builder::basic::kvp("MM_B_X", payload.MM_B_X));
    doc.append(bsoncxx::builder::basic::kvp("MM_B_Y", payload.MM_B_Y));
    doc.append(bsoncxx::builder::basic::kvp("MM_B_Z", payload.MM_B_Z));

    // Gyro data
    doc.append(bsoncxx::builder::basic::kvp("Gyro_B_X", payload.Gyro_B_X));
    doc.append(bsoncxx::builder::basic::kvp("Gyro_B_Y", payload.Gyro_B_Y));

    // Reserved data
    doc.append(bsoncxx::builder::basic::kvp("res_p15", bsoncxx::builder::basic::array{payload.res_p15[0], payload.res_p15[1] }));

    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP16(const T payload) {
    bsoncxx::builder::basic::document doc{};

    // Gyro and ST attitude data
    doc.append(bsoncxx::builder::basic::kvp("Gyro_B_Z", payload.Gyro_B_Z));
    doc.append(bsoncxx::builder::basic::kvp("ST_Q1_IM", payload.ST_Q1_IM));
    doc.append(bsoncxx::builder::basic::kvp("ST_Q2_IM", payload.ST_Q2_IM));
    doc.append(bsoncxx::builder::basic::kvp("ST_Q3_IM", payload.ST_Q3_IM));
    doc.append(bsoncxx::builder::basic::kvp("ST_Q4_IM", payload.ST_Q4_IM));
    doc.append(bsoncxx::builder::basic::kvp("ST_ID", payload.ST_ID));

    // GPS position and velocity data
    doc.append(bsoncxx::builder::basic::kvp("GPS_Rx", payload.GPS_Rx));
    doc.append(bsoncxx::builder::basic::kvp("GPS_Ry", payload.GPS_Ry));
    doc.append(bsoncxx::builder::basic::kvp("GPS_Rz", payload.GPS_Rz));
    doc.append(bsoncxx::builder::basic::kvp("GPS_Vx", payload.GPS_Vx));
    doc.append(bsoncxx::builder::basic::kvp("GPS_Vy", payload.GPS_Vy));
    doc.append(bsoncxx::builder::basic::kvp("GPS_Vz", payload.GPS_Vz));
    doc.append(bsoncxx::builder::basic::kvp("GPSJD", payload.GPSJD));

    // MT and RW commands
    doc.append(bsoncxx::builder::basic::kvp("MT_CMD_Act_x", payload.MT_CMD_Act_x));
    doc.append(bsoncxx::builder::basic::kvp("MT_CMD_Act_y", payload.MT_CMD_Act_y));
    doc.append(bsoncxx::builder::basic::kvp("MT_CMD_Act_z", payload.MT_CMD_Act_z));
    doc.append(bsoncxx::builder::basic::kvp("RW_CMD_Act_x", payload.RW_CMD_Act_x));
    doc.append(bsoncxx::builder::basic::kvp("RW_CMD_Act_y", payload.RW_CMD_Act_y));
    doc.append(bsoncxx::builder::basic::kvp("RW_CMD_Act_z", payload.RW_CMD_Act_z));

    // Interface manager flags (array)
    doc.append(bsoncxx::builder::basic::kvp("interfaceManagerVariablesflags", bsoncxx::builder::basic::array{
            payload.interfaceManagerVariablesflags[0], payload.interfaceManagerVariablesflags[1],
            payload.interfaceManagerVariablesflags[2], payload.interfaceManagerVariablesflags[3],
            payload.interfaceManagerVariablesflags[4], payload.interfaceManagerVariablesflags[5],
            payload.interfaceManagerVariablesflags[6]
    }));

    // Estimated quaternion values
    doc.append(bsoncxx::builder::basic::kvp("q0_Estimated", payload.q0_Estimated));
    doc.append(bsoncxx::builder::basic::kvp("q1_Estimated", payload.q1_Estimated));
    doc.append(bsoncxx::builder::basic::kvp("q2_Estimated", payload.q2_Estimated));
    doc.append(bsoncxx::builder::basic::kvp("q3_Estimated", payload.q3_Estimated));

    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP17(const T payload) {
    bsoncxx::builder::basic::document doc{};

    // Estimated values for W (angular velocity) and quaternion
    doc.append(bsoncxx::builder::basic::kvp("W_X_Estimated", payload.W_X_Estimated));
    doc.append(bsoncxx::builder::basic::kvp("W_Y_Estimated", payload.W_Y_Estimated));
    doc.append(bsoncxx::builder::basic::kvp("W_Z_Estimated", payload.W_Z_Estimated));
    doc.append(bsoncxx::builder::basic::kvp("q0_EKF", payload.q0_EKF));
    doc.append(bsoncxx::builder::basic::kvp("q1_EKF", payload.q1_EKF));
    doc.append(bsoncxx::builder::basic::kvp("q2_EKF", payload.q2_EKF));
    doc.append(bsoncxx::builder::basic::kvp("q3_EKF", payload.q3_EKF));
    doc.append(bsoncxx::builder::basic::kvp("W_X_EKF", payload.W_X_EKF));
    doc.append(bsoncxx::builder::basic::kvp("W_Y_EKF", payload.W_Y_EKF));
    doc.append(bsoncxx::builder::basic::kvp("W_Z_EKF", payload.W_Z_EKF));

    // Estimated values for EKF-SG
    doc.append(bsoncxx::builder::basic::kvp("q0_EKFSG", payload.q0_EKFSG));
    doc.append(bsoncxx::builder::basic::kvp("q1_EKFSG", payload.q1_EKFSG));
    doc.append(bsoncxx::builder::basic::kvp("q2_EKFSG", payload.q2_EKFSG));
    doc.append(bsoncxx::builder::basic::kvp("q3_EKFSG", payload.q3_EKFSG));
    doc.append(bsoncxx::builder::basic::kvp("W_X_EKFSG", payload.W_X_EKFSG));
    doc.append(bsoncxx::builder::basic::kvp("W_Y_EKFSG", payload.W_Y_EKFSG));
    doc.append(bsoncxx::builder::basic::kvp("W_Z_EKFSG", payload.W_Z_EKFSG));

    // Star Gyro and battery/power data
    doc.append(bsoncxx::builder::basic::kvp("q0_StarGyro", payload.q0_StarGyro));
    doc.append(bsoncxx::builder::basic::kvp("CurrentBatteryCapacity", payload.CurrentBatteryCapacity));
    doc.append(bsoncxx::builder::basic::kvp("PowerInputGeneration", payload.PowerInputGeneration));
    doc.append(bsoncxx::builder::basic::kvp("TotalPowerDisipation", payload.TotalPowerDisipation));
    doc.append(bsoncxx::builder::basic::kvp("OAPPowerDisipation", payload.OAPPowerDisipation));
    doc.append(bsoncxx::builder::basic::kvp("OAPPowerGeneration", payload.OAPPowerGeneration));

    // MRAM flags and status
    doc.append(bsoncxx::builder::basic::kvp("globalStatesMRAMFlag", payload.globalStatesMRAMFlag));
    doc.append(bsoncxx::builder::basic::kvp("globalConfigurationMRAMFlag", payload.globalConfigurationMRAMFlag));
    doc.append(bsoncxx::builder::basic::kvp("globalScheduleTableMRAMFlag", payload.globalScheduleTableMRAMFlag));
    doc.append(bsoncxx::builder::basic::kvp("MRAM1Status", payload.MRAM1Status));
    doc.append(bsoncxx::builder::basic::kvp("MRAM2Status", payload.MRAM2Status));
    doc.append(bsoncxx::builder::basic::kvp("MRAM3Status", payload.MRAM3Status));

    // Reserved space (if necessary)
    doc.append(bsoncxx::builder::basic::kvp("res_part17", bsoncxx::builder::basic::array{
            payload.res_part17[0], payload.res_part17[1]
    }));

    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP18(const T payload) {
    bsoncxx::builder::basic::document doc{};

    // Star Gyro and EKF (Extended Kalman Filter) data
    doc.append(bsoncxx::builder::basic::kvp("q1_StarGyro", payload.q1_StarGyro));
    doc.append(bsoncxx::builder::basic::kvp("q2_StarGyro", payload.q2_StarGyro));
    doc.append(bsoncxx::builder::basic::kvp("q3_StarGyro", payload.q3_StarGyro));
    doc.append(bsoncxx::builder::basic::kvp("W_X_EKFSG", payload.W_X_EKFSG));
    doc.append(bsoncxx::builder::basic::kvp("W_Y_EKFSG", payload.W_Y_EKFSG));
    doc.append(bsoncxx::builder::basic::kvp("W_Z_EKFSG", payload.W_Z_EKFSG));
    doc.append(bsoncxx::builder::basic::kvp("PNormEKF", payload.PNormEKF));
    doc.append(bsoncxx::builder::basic::kvp("PNormEKFSG", payload.PNormEKFSG));
    doc.append(bsoncxx::builder::basic::kvp("ConditionNumberEKF", payload.ConditionNumberEKF));
    doc.append(bsoncxx::builder::basic::kvp("ConditionNumberEKFSG", payload.ConditionNumberEKFSG));

    // Path data
    doc.append(bsoncxx::builder::basic::kvp("q0_Path", payload.q0_Path));
    doc.append(bsoncxx::builder::basic::kvp("q1_Path", payload.q1_Path));
    doc.append(bsoncxx::builder::basic::kvp("q2_Path", payload.q2_Path));
    doc.append(bsoncxx::builder::basic::kvp("q3_Path", payload.q3_Path));
    doc.append(bsoncxx::builder::basic::kvp("W_X_Path", payload.W_X_Path));
    doc.append(bsoncxx::builder::basic::kvp("W_Y_Path", payload.W_Y_Path));
    doc.append(bsoncxx::builder::basic::kvp("W_Z_Path", payload.W_Z_Path));

    // ADCS (Attitude Determination and Control System) data
    doc.append(bsoncxx::builder::basic::kvp("dt_ADCS", payload.dt_ADCS));
    doc.append(bsoncxx::builder::basic::kvp("T_Des_X", payload.T_Des_X));
    doc.append(bsoncxx::builder::basic::kvp("T_Des_Y", payload.T_Des_Y));
    doc.append(bsoncxx::builder::basic::kvp("T_Des_Z", payload.T_Des_Z));
    doc.append(bsoncxx::builder::basic::kvp("ADCSMTDipoleX", payload.ADCSMTDipoleX));
    doc.append(bsoncxx::builder::basic::kvp("ADCSMTDipoleY", payload.ADCSMTDipoleY));
    doc.append(bsoncxx::builder::basic::kvp("ADCSMTDipoleZ", payload.ADCSMTDipoleZ));
    doc.append(bsoncxx::builder::basic::kvp("ADCSRWTorqueX", payload.ADCSRWTorqueX));

    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP19(const T payload) {
    bsoncxx::builder::basic::document doc{};

    // ADCS (Attitude Determination and Control System) and related data
    doc.append(bsoncxx::builder::basic::kvp("ADCSRWTorqueY", payload.ADCSRWTorqueY));
    doc.append(bsoncxx::builder::basic::kvp("ADCSRWTorqueZ", payload.ADCSRWTorqueZ));
    doc.append(bsoncxx::builder::basic::kvp("RWRPMCommand_X", payload.RWRPMCommand_X));
    doc.append(bsoncxx::builder::basic::kvp("RWRPMCommand_Y", payload.RWRPMCommand_Y));
    doc.append(bsoncxx::builder::basic::kvp("RWRPMCommand_Z", payload.RWRPMCommand_Z));
    doc.append(bsoncxx::builder::basic::kvp("KpC", payload.KpC));
    doc.append(bsoncxx::builder::basic::kvp("KpF", payload.KpF));
    doc.append(bsoncxx::builder::basic::kvp("KdC", payload.KdC));
    doc.append(bsoncxx::builder::basic::kvp("KdF", payload.KdF));
    doc.append(bsoncxx::builder::basic::kvp("ADCS_JD", payload.ADCS_JD));
    doc.append(bsoncxx::builder::basic::kvp("adcsToInterfaceManagerFlag", bsoncxx::builder::basic::array{
            payload.adcsToInterfaceManagerFlag[0],
            payload.adcsToInterfaceManagerFlag[1],
            payload.adcsToInterfaceManagerFlag[2]
    }));

    // Orbit-related data
    doc.append(bsoncxx::builder::basic::kvp("OrbitJulianDate", payload.OrbitJulianDate));
    doc.append(bsoncxx::builder::basic::kvp("GPSJDDiff", payload.GPSJDDiff));
    doc.append(bsoncxx::builder::basic::kvp("Orbit_dt", payload.Orbit_dt));
    doc.append(bsoncxx::builder::basic::kvp("R_InECI_x", payload.R_InECI_x));
    doc.append(bsoncxx::builder::basic::kvp("R_InECI_y", payload.R_InECI_y));
    doc.append(bsoncxx::builder::basic::kvp("R_InECI_z", payload.R_InECI_z));

    doc.append(bsoncxx::builder::basic::kvp("V_InECI_x", payload.V_InECI_x));
    doc.append(bsoncxx::builder::basic::kvp("V_InECI_y", payload.V_InECI_y));
    doc.append(bsoncxx::builder::basic::kvp("V_InECI_z", payload.V_InECI_z));

    // Sun model data in ECI (Earth-Centered Inertial) coordinates
    doc.append(bsoncxx::builder::basic::kvp("SunModelInECI_x", payload.SunModelInECI_x));
    doc.append(bsoncxx::builder::basic::kvp("SunModelInECI_y", payload.SunModelInECI_y));
    doc.append(bsoncxx::builder::basic::kvp("SunModelInECI_z", payload.SunModelInECI_z));

    // Reserved field
    doc.append(bsoncxx::builder::basic::kvp("res_p19", payload.res_p19));

    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP20(const T payload) {
    bsoncxx::builder::basic::document doc{};

    // IGRF (International Geomagnetic Reference Field) data in ECI frame
    doc.append(bsoncxx::builder::basic::kvp("IGRFInECI_x", payload.IGRFInECI_x));
    doc.append(bsoncxx::builder::basic::kvp("IGRFInECI_y", payload.IGRFInECI_y));
    doc.append(bsoncxx::builder::basic::kvp("IGRFInECI_z", payload.IGRFInECI_z));

    // Orbit data for interface manager
    doc.append(bsoncxx::builder::basic::kvp("OrbitToInterfaceManagerFlag", bsoncxx::builder::basic::array{
            payload.OrbitToInterfaceManagerFlag[0],
            payload.OrbitToInterfaceManagerFlag[1]
    }));

    // Position and velocity in ECI frame (for programming/trajectory tracking)
    doc.append(bsoncxx::builder::basic::kvp("R_InECI_Prog_x", payload.R_InECI_Prog_x));
    doc.append(bsoncxx::builder::basic::kvp("R_InECI_Prog_y", payload.R_InECI_Prog_y));
    doc.append(bsoncxx::builder::basic::kvp("R_InECI_Prog_z", payload.R_InECI_Prog_z));
    doc.append(bsoncxx::builder::basic::kvp("V_InECI_Prog_x", payload.V_InECI_Prog_x));
    doc.append(bsoncxx::builder::basic::kvp("V_InECI_Prog_y", payload.V_InECI_Prog_y));
    doc.append(bsoncxx::builder::basic::kvp("V_InECI_Prog_z", payload.V_InECI_Prog_z));

    // Custom MT (Magnetic Torquers) and RW (Reaction Wheel) data
    doc.append(bsoncxx::builder::basic::kvp("MTCustomDipole_x", payload.MTCustomDipole_x));
    doc.append(bsoncxx::builder::basic::kvp("MTCustomDipole_y", payload.MTCustomDipole_y));
    doc.append(bsoncxx::builder::basic::kvp("MTCustomDipole_z", payload.MTCustomDipole_z));
    doc.append(bsoncxx::builder::basic::kvp("RWCustomjRPM_x", payload.RWCustomjRPM_x));
    doc.append(bsoncxx::builder::basic::kvp("RWCustomjRPM_y", payload.RWCustomjRPM_y));
    doc.append(bsoncxx::builder::basic::kvp("RWCustomjRPM_z", payload.RWCustomjRPM_z));

    // Buffer norm and criteria data
    doc.append(bsoncxx::builder::basic::kvp("WBuffNorm", payload.WBuffNorm));
    doc.append(bsoncxx::builder::basic::kvp("CriteriaMode", payload.CriteriaMode));
    doc.append(bsoncxx::builder::basic::kvp("CriteriaCounter", payload.CriteriaCounter));

    // Task ID, hardware status, and supervisor flags
    doc.append(bsoncxx::builder::basic::kvp("TaskID", payload.TaskID));
    doc.append(bsoncxx::builder::basic::kvp("hardwareStatus", payload.hardwareStatus));
    doc.append(bsoncxx::builder::basic::kvp("supervisorToInterfaceManagerFlg", payload.supervisorToInterfaceManagerFlg));

    // CPU and exception counters for OBC (Onboard Computer)
    doc.append(bsoncxx::builder::basic::kvp("OS_CPU_ARM_EXCEPT_RESETCnt", payload.OS_CPU_ARM_EXCEPT_RESETCnt));
    doc.append(bsoncxx::builder::basic::kvp("ARM_EXCEPT_UNDEF_INSTRCnt", payload.ARM_EXCEPT_UNDEF_INSTRCnt));
    doc.append(bsoncxx::builder::basic::kvp("OS_CPU_ARM_EXCEPT_SWICnt", payload.OS_CPU_ARM_EXCEPT_SWICnt));
    doc.append(bsoncxx::builder::basic::kvp("OS_CPU_ARM_EXCEPT_PREFETCH_ABORTCnt", payload.OS_CPU_ARM_EXCEPT_PREFETCH_ABORTCnt));
    doc.append(bsoncxx::builder::basic::kvp("OS_CPU_ARM_EXCEPT_DATA_ABORTCnt", payload.OS_CPU_ARM_EXCEPT_DATA_ABORTCnt));
    doc.append(bsoncxx::builder::basic::kvp("OS_CPU_ARM_EXCEPT_ADDR_ABORTCnt", payload.OS_CPU_ARM_EXCEPT_ADDR_ABORTCnt));
    doc.append(bsoncxx::builder::basic::kvp("OS_CPU_ARM_EXCEPT_FIQCnt", payload.OS_CPU_ARM_EXCEPT_FIQCnt));
    doc.append(bsoncxx::builder::basic::kvp("OS_CPU_ARM_EXCEPT_OtherCnt", payload.OS_CPU_ARM_EXCEPT_OtherCnt));

    // Error and critical status flags
    doc.append(bsoncxx::builder::basic::kvp("MMC_Errorr_Counter", payload.MMC_Errorr_Counter));
    doc.append(bsoncxx::builder::basic::kvp("MRAMOBCCriticalStatusDataFlag", payload.MRAMOBCCriticalStatusDataFlag));
    doc.append(bsoncxx::builder::basic::kvp("MRAMCPUExceptionFlag", payload.MRAMCPUExceptionFlag));

    // Reserved field
    doc.append(bsoncxx::builder::basic::kvp("respart19", bsoncxx::builder::basic::array{
            payload.respart19[0], payload.respart19[1], payload.respart19[2], payload.respart19[3],
            payload.respart19[4], payload.respart19[5], payload.respart19[6], payload.respart19[7],
            payload.respart19[8], payload.respart19[9], payload.respart19[10], payload.respart19[11],
            payload.respart19[12], payload.respart19[13], payload.respart19[14]
    }));

    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP21(const T payload) {
    bsoncxx::builder::basic::document doc{};

    // Serialize ID_CMD_REC_Return (array of 100 bytes)
    doc.append(bsoncxx::builder::basic::kvp("ID_CMD_REC_Return", bsoncxx::builder::basic::array{
            payload.ID_CMD_REC_Return[0], payload.ID_CMD_REC_Return[1], payload.ID_CMD_REC_Return[2], // ... up to 100
            payload.ID_CMD_REC_Return[99]
    }));

    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP22(const T payload) {
    bsoncxx::builder::basic::document doc{};

    // Serialize ID_CMD_REC_Return (array of 100 bytes)
    bsoncxx::builder::basic::array arr;
    for (int i = 0; i < 100; ++i)
        arr.append(static_cast<int8_t>(payload.ID_CMD_REC_Return[i]));
    doc.append(bsoncxx::builder::basic::kvp("ID_CMD_REC_Return", arr));
    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP23(const T payload) {
    bsoncxx::builder::basic::document doc{};

    // Serialize ID_CMD_REC_Return (array of 100 bytes)
    bsoncxx::builder::basic::array arr;
    for (int i = 0; i < 100; ++i)
        arr.append(static_cast<int8_t>(payload.ID_CMD_REC_Return[i]));
    doc.append(bsoncxx::builder::basic::kvp("ID_CMD_REC_Return", arr));
    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP24(const T payload) {
    bsoncxx::builder::basic::document doc{};

    // Serialize ID_CMD_REC_Return (array of 100 bytes)
    bsoncxx::builder::basic::array arr;
    for (int i = 0; i < 100; ++i)
        arr.append(static_cast<int8_t>(payload.ID_CMD_Executed_Return[i]));
    doc.append(bsoncxx::builder::basic::kvp("ID_CMD_Executed_Return", arr));
    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP25(const T payload) {
    bsoncxx::builder::basic::document doc{};

    // Serialize ID_CMD_REC_Return (array of 100 bytes)
    bsoncxx::builder::basic::array arr;
    for (int i = 0; i < 100; ++i)
        arr.append(static_cast<int8_t>(payload.ID_CMD_Executed_Return[i]));
    doc.append(bsoncxx::builder::basic::kvp("ID_CMD_Executed_Return", arr));
    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP26(const T payload) {
    bsoncxx::builder::basic::document doc{};

    // Serialize ID_CMD_REC_Return (array of 100 bytes)
    bsoncxx::builder::basic::array arr;
    for (int i = 0; i < 100; ++i)
        arr.append(static_cast<int8_t>(payload.ID_CMD_Executed_Return[i]));
    doc.append(bsoncxx::builder::basic::kvp("ID_CMD_Executed_Return", arr));
    return doc;
}

template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP27(const T payload) {
    bsoncxx::builder::basic::document doc{};

    // SETPARAM
    doc.append(bsoncxx::builder::basic::kvp("SETPARAM_VAR_TYPE", payload.SETPARAM_VAR_TYPE));
    doc.append(bsoncxx::builder::basic::kvp("SETPARAM_MEM_ADD", payload.SETPARAM_MEM_ADD));

    bsoncxx::builder::basic::array SETPARAM_MEM_VAL_array;
    for (int i = 0; i < 8; ++i)
        SETPARAM_MEM_VAL_array.append(payload.SETPARAM_MEM_VAL[i]);
    doc.append(bsoncxx::builder::basic::kvp("SETPARAM_MEM_VAL", SETPARAM_MEM_VAL_array));

    doc.append(bsoncxx::builder::basic::kvp("Get_Param_length", payload.Get_Param_length));
    doc.append(bsoncxx::builder::basic::kvp("Get_param_Start_Add", payload.Get_param_Start_Add));

    bsoncxx::builder::basic::array Get_param_Value_array;
    for (int i = 0; i < 40; ++i)
        Get_param_Value_array.append(payload.Get_param_Value[i]);
    doc.append(bsoncxx::builder::basic::kvp("Get_param_Value", Get_param_Value_array));

    // IRPDU 1
    doc.append(bsoncxx::builder::basic::kvp("IRPDU_Enable1", payload.IRPDU_Enable1));
    doc.append(bsoncxx::builder::basic::kvp("IRPDU_Flag1", payload.IRPDU_Flag1));
    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CurrentSband1", payload.IRPDU_CurrentSband1));
    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CurrentGps1", payload.IRPDU_CurrentGps1));
    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CurrentProp8V1", payload.IRPDU_CurrentProp8V1));
    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CurrentProp12V1", payload.IRPDU_CurrentProp12V1));
    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CurrentMThesco", payload.IRPDU_CurrentMThesco));
    doc.append(bsoncxx::builder::basic::kvp("IRPDU_TemperatureSen1", payload.IRPDU_TemperatureSen1));
    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CommandCounter1", payload.IRPDU_CommandCounter1));
    doc.append(bsoncxx::builder::basic::kvp("IRPDU_TelemetryCounter1", payload.IRPDU_TelemetryCounter1));

    // IRPDU 2
    doc.append(bsoncxx::builder::basic::kvp("IRPDU_Enable2", payload.IRPDU_Enable2));
    doc.append(bsoncxx::builder::basic::kvp("IRPDU_Flag2", payload.IRPDU_Flag2));
    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CurrentSband2", payload.IRPDU_CurrentSband2));
    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CurrentGps2", payload.IRPDU_CurrentGps2));
    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CurrentProp8V2", payload.IRPDU_CurrentProp8V2));
    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CurrentProp12V2", payload.IRPDU_CurrentProp12V2));
    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CurrentMM_HMR", payload.IRPDU_CurrentMM_HMR));
    doc.append(bsoncxx::builder::basic::kvp("IRPDU_TemperatureSen2", payload.IRPDU_TemperatureSen2));
    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CommandCounter2", payload.IRPDU_CommandCounter2));
    doc.append(bsoncxx::builder::basic::kvp("IRPDU_TelemetryCounter2", payload.IRPDU_TelemetryCounter2));

    // Switch states
    doc.append(bsoncxx::builder::basic::kvp("CB_SwitchState", payload.CB_SwitchState));
    doc.append(bsoncxx::builder::basic::kvp("PmuState", payload.PmuState));
    doc.append(bsoncxx::builder::basic::kvp("CBPmuState", payload.CBPmuState));

    // Reserved bytes
    bsoncxx::builder::basic::array res_array;
    for (int i = 0; i < 4; ++i)
        res_array.append(payload.res[i]);
    doc.append(bsoncxx::builder::basic::kvp("res", res_array));

    return doc;
}


template<typename T>
bsoncxx::builder::basic::document MongoDBHandler::serializeExtendedPayloadP28(const T payload) {
    bsoncxx::builder::basic::document doc{};

    // Serialize Analog Sensors (int16_t)
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_1", payload.Analog_Sensor_1));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_2", payload.Analog_Sensor_2));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_3", payload.Analog_Sensor_3));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_4", payload.Analog_Sensor_4));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_5", payload.Analog_Sensor_5));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_6", payload.Analog_Sensor_6));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_7", payload.Analog_Sensor_7));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_8", payload.Analog_Sensor_8));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_9", payload.Analog_Sensor_9));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_10", payload.Analog_Sensor_10));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_11", payload.Analog_Sensor_11));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_12", payload.Analog_Sensor_12));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_13", payload.Analog_Sensor_13));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_14", payload.Analog_Sensor_14));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_15", payload.Analog_Sensor_15));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_16", payload.Analog_Sensor_16));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_17", payload.Analog_Sensor_17));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_18", payload.Analog_Sensor_18));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_19", payload.Analog_Sensor_19));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_20", payload.Analog_Sensor_20));

    // Serialize more Analog Sensors (int16_t)
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_21", payload.Analog_Sensor_21));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_22", payload.Analog_Sensor_22));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_23", payload.Analog_Sensor_23));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_24", payload.Analog_Sensor_24));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_25", payload.Analog_Sensor_25));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_26", payload.Analog_Sensor_26));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_27", payload.Analog_Sensor_27));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_28", payload.Analog_Sensor_28));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_29", payload.Analog_Sensor_29));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_30", payload.Analog_Sensor_30));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_31", payload.Analog_Sensor_31));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_32", payload.Analog_Sensor_32));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_33", payload.Analog_Sensor_33));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_34", payload.Analog_Sensor_34));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_35", payload.Analog_Sensor_35));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_36", payload.Analog_Sensor_36));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_37", payload.Analog_Sensor_37));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_38", payload.Analog_Sensor_38));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_39", payload.Analog_Sensor_39));
    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_40", payload.Analog_Sensor_40));

    // Serialize Temp Sensors (int8_t)
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor1", payload.Temp_Sensor1));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor2", payload.Temp_Sensor2));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor3", payload.Temp_Sensor3));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor4", payload.Temp_Sensor4));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor5", payload.Temp_Sensor5));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor6", payload.Temp_Sensor6));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor7", payload.Temp_Sensor7));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor8", payload.Temp_Sensor8));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor9", payload.Temp_Sensor9));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor10", payload.Temp_Sensor10));

    // Serialize more Temp Sensors (int8_t)
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor11", payload.Temp_Sensor11));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor12", payload.Temp_Sensor12));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor13", payload.Temp_Sensor13));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor14", payload.Temp_Sensor14));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor15", payload.Temp_Sensor15));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor16", payload.Temp_Sensor16));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor17", payload.Temp_Sensor17));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor18", payload.Temp_Sensor18));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor19", payload.Temp_Sensor19));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor20", payload.Temp_Sensor20));

    // Serialize remaining Temp Sensors (int8_t)
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor21", payload.Temp_Sensor21));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor22", payload.Temp_Sensor22));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor23", payload.Temp_Sensor23));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor24", payload.Temp_Sensor24));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor25", payload.Temp_Sensor25));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor26", payload.Temp_Sensor26));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor27", payload.Temp_Sensor27));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor28", payload.Temp_Sensor28));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor29", payload.Temp_Sensor29));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor30", payload.Temp_Sensor30));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor31", payload.Temp_Sensor31));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor32", payload.Temp_Sensor32));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor33", payload.Temp_Sensor33));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor34", payload.Temp_Sensor34));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor35", payload.Temp_Sensor35));
    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor36", payload.Temp_Sensor36));

    // Serialize prop_Status, prop_TankTemp, prop_PlenumTemp, prop_TankPressure, prop_PlenumPressure
    doc.append(bsoncxx::builder::basic::kvp("prop_Status", payload.prop_Status));
    doc.append(bsoncxx::builder::basic::kvp("prop_TankTemp", payload.prop_TankTemp));
    doc.append(bsoncxx::builder::basic::kvp("prop_PlenumTemp", payload.prop_PlenumTemp));
    doc.append(bsoncxx::builder::basic::kvp("prop_TankPressure", payload.prop_TankPressure));
    doc.append(bsoncxx::builder::basic::kvp("prop_PlenumPressure", payload.prop_PlenumPressure));

    // Serialize prop Durations, Delays, and PWM values
    doc.append(bsoncxx::builder::basic::kvp("prop_Duration1", payload.prop_Duration1));
    doc.append(bsoncxx::builder::basic::kvp("prop_Duration2", payload.prop_Duration2));
    doc.append(bsoncxx::builder::basic::kvp("prop_Delay1", payload.prop_Delay1));
    doc.append(bsoncxx::builder::basic::kvp("prop_Delay2", payload.prop_Delay2));
    doc.append(bsoncxx::builder::basic::kvp("prop_PWM1", payload.prop_PWM1));
    doc.append(bsoncxx::builder::basic::kvp("prop_PWM2", payload.prop_PWM2));

    return doc;
}
