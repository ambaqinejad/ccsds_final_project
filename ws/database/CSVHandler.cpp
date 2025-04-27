////
//// Created by ambaqinejad on 4/16/25.
////
//
//#include "CSVHandler.h"
//
//#include <mongocxx/instance.hpp>
//#include <mongocxx/uri.hpp>
//#include <mongocxx/client.hpp>
//#include <bsoncxx/builder/stream/document.hpp>
//#include <bsoncxx/json.hpp>
//#include <fstream>
//
//#include "logics/CCSDS_Packet.h"
//
//CSVHandler::CSVHandler() {
//
//}
//
//void CSVHandler::insertPacket(const CCSDS_Packet &packet) {
//    std::ofstream file(csvFilePath);
//    file
//            << "main_frame_header, packet_id, packet_sequence_control, packet_length, data_field_header, service_type, sub_service_type, sid, timestamp, crc_fail_upload_map, flash_address,";
//    // Serialize the extended_payload
//    std::visit([&](auto &&arg) {
//        using T = std::decay_t<decltype(arg)>;
//        if constexpr (std::is_same_v<T, ExtendedP1>) {
//            serializeExtendedPayloadP1(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP2>) {
//            serializeExtendedPayloadP2(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP3>) {
//            serializeExtendedPayloadP3(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP4>) {
//            serializeExtendedPayloadP4(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP5>) {
//            serializeExtendedPayloadP5(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP6>) {
//            serializeExtendedPayloadP6(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP7>) {
//            serializeExtendedPayloadP7(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP8>) {
//            serializeExtendedPayloadP8(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP9>) {
//            serializeExtendedPayloadP9(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP10>) {
//            serializeExtendedPayloadP10(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP11>) {
//            serializeExtendedPayloadP11(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP12>) {
//            serializeExtendedPayloadP12(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP13>) {
//            serializeExtendedPayloadP13(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP14>) {
//            serializeExtendedPayloadP14(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP15>) {
//            serializeExtendedPayloadP15(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP16>) {
//            serializeExtendedPayloadP16(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP17>) {
//            serializeExtendedPayloadP17(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP18>) {
//            serializeExtendedPayloadP18(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP19>) {
//            serializeExtendedPayloadP19(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP20>) {
//            serializeExtendedPayloadP20(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP21>) {
//            serializeExtendedPayloadP21(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP22>) {
//            serializeExtendedPayloadP22(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP23>) {
//            serializeExtendedPayloadP23(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP24>) {
//            serializeExtendedPayloadP24(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP25>) {
//            serializeExtendedPayloadP25(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP26>) {
//            serializeExtendedPayloadP26(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP27>) {
//            serializeExtendedPayloadP27(arg, packet, file);
//        } else if constexpr (std::is_same_v<T, ExtendedP28>) {
//            serializeExtendedPayloadP28(arg, packet, file);
//        }
//    }, packet.extended_payload);
//
//    std::cout << "Packet inserted successfully." << std::endl;
//}
//
//template<typename ArrayType>
//std::string CSVHandler::writeArray(const ArrayType *arr, size_t size) {
//    std::ostringstream oss;
//    oss << "[";
//    for (size_t i = 0; i < size; ++i) {
//        oss << static_cast<int>(arr[i]);
//        if (i < size - 1) oss << ",";
//    }
//    oss << "]";
//    return oss.str();
//}
//
//void CSVHandler::insertHeader(const CCSDS_Packet &packet, std::ofstream &file) {
//    file << packet.main_frame_header << ",";
//    file << packet.packet_id << ",";
//    file << packet.packet_sequence_control << ",";
//    file << packet.packet_length << ",";
//    file << packet.data_field_header << ",";
//    file << packet.service_type << ",";
//    file << packet.sub_service_type << ",";
//    file << packet.sid << ",";
//    file << packet.timestamp << ",";
//    file << packet.crc_fail_upload_map << ",";
//    file << packet.flash_address << ",";
//}
//
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP1(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    file << "CameraPacket1\n";
//    insertHeader(packet, file);
//    file << "[";
//    for (auto byte: payload.CameraPacket1) file << static_cast<int>(byte) << ",";
//    file << "]";
//    file.close();
//}
//
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP2(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    file << "CameraPacket2,CameraPacket3,res,MemoryStatus,StartFrequency,StopFrequency,CFARConstant,StepTime,RxGain,SigintResponseFlag,MRAMAdcsConfigFlag,MRAMSatParameterFlag,MRAMTeleCounterFlag,LastResetSource,TeleCounterOnline,TeleCounterOffline,TaskResetCnt,LastTaskResetNum,respart2_2,UV_TransmitterFreq,UV_RecieverFreq,UV_TX,respart2_3\n";
//    insertHeader(packet, file);
//    file << writeArray(payload.CameraPacket2, 26) << ",";
//    file << writeArray(payload.CameraPacket3, 20) << ",";
//    file << payload.res << ",";
//    file << static_cast<int64_t>(payload.MemoryStatus) << ",";
//    file << payload.StartFrequency << ",";
//    file << payload.StopFrequency << ",";
//    file << payload.CFARConstant << ",";
//    file << payload.StepTime << ",";
//    file << payload.RxGain << ",";
//    file << static_cast<int32_t>(payload.SigintResponseFlag) << ",";
//    file << payload.MRAMAdcsConfigFlag << ",";
//    file << payload.MRAMSatParameterFlag << ",";
//    file << payload.MRAMTeleCounterFlag << ",";
//    file << payload.LastResetSource << ",";
//    file << static_cast<int32_t>(payload.TeleCounterOnline) << ",";
//    file << static_cast<int32_t>(payload.TeleCounterOffline) << ",";
//    file << payload.TaskResetCnt << ",";
//    file << payload.LastTaskResetNum << ",";
//    file << writeArray(payload.respart2_2, 4) << ",";
//    file << static_cast<int32_t>(payload.UV_TransmitterFreq) << ",";
//    file << static_cast<int32_t>(payload.UV_RecieverFreq) << ",";
//    file << static_cast<int32_t>(payload.UV_TX) << ",";
//    file << payload.respart2_3 << "\n";
//
//    file.close();
//}
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP3(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    // Header line (write this once if multiple entries are appended)
//    file << "UV_RX,UV_AES_Config,UV_TR_Output_Power,UV_BeacanRepeatTime,UV_Voltage,UV_RSSI,UV_Temperature,"
//         << "UV_Temperature_OverHeat,UV_Rf_Telemetry,RF_telemetry_X,TEMP_telemetry_X,XdataRate,"
//         << "voltage_telemetry_X,Transmitter_Status_X,OutputPower,CAN_Status_X,Transmitter_mode_X,Tx_frequency_X,"
//         << "S_TR_Scratch,S_TR_AES_Index,S_TR_Modulation,S_TR_Bitrate,S_TR_Fdiviation,S_TR_BandWidth,S_TR_CrcInit,"
//         << "S_TR_Lmx2572_Freq,S_TR_Fifo_State,S_TR_SystemFaults,resp2\n";
//    insertHeader(packet, file);
//    // Value line
//    file
//            << writeArray(payload.UV_RX, 4) << ","
//            << writeArray(payload.UV_AES_Config, 4) << ","
//            << writeArray(payload.UV_TR_Output_Power, 4) << ","
//            << writeArray(payload.UV_BeacanRepeatTime, 4) << ","
//            << writeArray(payload.UV_Voltage, 4) << ","
//            << writeArray(payload.UV_RSSI, 4) << ","
//            << writeArray(payload.UV_Temperature, 4) << ","
//            << writeArray(payload.UV_Temperature_OverHeat, 4) << ","
//            << writeArray(payload.UV_Rf_Telemetry, 4) << ","
//            << writeArray(payload.RF_telemetry_X, 3) << ","
//            << writeArray(payload.TEMP_telemetry_X, 4) << ","
//            << payload.XdataRate << ","
//            << writeArray(payload.voltage_telemetry_X, 4) << ","
//            << payload.Transmitter_Status_X << ","
//            << payload.OutputPower << ","
//            << payload.CAN_Status_X << ","
//            << payload.Transmitter_mode_X << ","
//            << static_cast<int32_t>(payload.Tx_frequency_X) << ","
//            << static_cast<int32_t>(payload.S_TR_Scratch) << ","
//            << static_cast<int32_t>(payload.S_TR_AES_Index) << ","
//            << static_cast<int32_t>(payload.S_TR_Modulation) << ","
//            << static_cast<int32_t>(payload.S_TR_Bitrate) << ","
//            << static_cast<int32_t>(payload.S_TR_Fdiviation) << ","
//            << static_cast<int32_t>(payload.S_TR_BandWidth) << ","
//            << static_cast<int32_t>(payload.S_TR_CrcInit) << ","
//            << static_cast<int32_t>(payload.S_TR_Lmx2572_Freq) << ","
//            << static_cast<int32_t>(payload.S_TR_Fifo_State) << ","
//            << static_cast<int32_t>(payload.S_TR_SystemFaults) << ","
//            << writeArray(payload.resp2, 3) << "\n";
//
//    file.close();
//}
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP4(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    // Writing the headers (labels) for each field
//    file << "S_TR_ReadLogAmp,"
//         << "S_TR_TempSens1,"
//         << "S_TR_TempSens2,"
//         << "S_TR_Power,"
//         << "S_TR_IntThr,"
//         << "S_TR_TransCuttOffTemp,"
//         << "S_RX_Scratch,"
//         << "S_RX_AES_Index,"
//         << "S_RX_Modulation,"
//         << "S_RX_Bitrate,"
//         << "RX_Fdiviation,"
//         << "S_RX_BandWidth,"
//         << "S_RX_CrcInit,"
//         << "S_RX_Lmx2572_Freq,"
//         << "S_RX_Fifo_State,"
//         << "S_RX_SystemFaults,"
//         << "S_RX_ReadLogAmp,"
//         << "S_RX_TempSens1,"
//         << "S_RX_TempSens2,"
//         << "S_RX_Power,"
//         << "S_RX_IntThr,"
//         << "S_RX_Reciever_SyncCrcErr,"
//         << "S_RX_RSSI_Const,"
//         << "S_RX_RSSI,"
//         << "S_RX_RS485BD\n";
//    insertHeader(packet, file);
//    // Writing the data
//    file << static_cast<int32_t>(payload.S_TR_ReadLogAmp) << ","
//         << static_cast<int32_t>(payload.S_TR_TempSens1) << ","
//         << static_cast<int32_t>(payload.S_TR_TempSens2) << ","
//         << static_cast<int32_t>(payload.S_TR_Power) << ","
//         << static_cast<int32_t>(payload.S_TR_IntThr) << ","
//         << static_cast<int32_t>(payload.S_TR_TransCuttOffTemp) << ","
//         << static_cast<int32_t>(payload.S_RX_Scratch) << ","
//         << static_cast<int32_t>(payload.S_RX_AES_Index) << ","
//         << static_cast<int32_t>(payload.S_RX_Modulation) << ","
//         << static_cast<int32_t>(payload.S_RX_Bitrate) << ","
//         << static_cast<int32_t>(payload.RX_Fdiviation) << ","
//         << static_cast<int32_t>(payload.S_RX_BandWidth) << ","
//         << static_cast<int32_t>(payload.S_RX_CrcInit) << ","
//         << static_cast<int32_t>(payload.S_RX_Lmx2572_Freq) << ","
//         << static_cast<int32_t>(payload.S_RX_Fifo_State) << ","
//         << static_cast<int32_t>(payload.S_RX_SystemFaults) << ","
//         << static_cast<int32_t>(payload.S_RX_ReadLogAmp) << ","
//         << static_cast<int32_t>(payload.S_RX_TempSens1) << ","
//         << static_cast<int32_t>(payload.S_RX_TempSens2) << ","
//         << static_cast<int32_t>(payload.S_RX_Power) << ","
//         << static_cast<int32_t>(payload.S_RX_IntThr) << ","
//         << static_cast<int32_t>(payload.S_RX_Reciever_SyncCrcErr) << ","
//         << static_cast<int32_t>(payload.S_RX_RSSI_Const) << ","
//         << static_cast<int32_t>(payload.S_RX_RSSI) << ","
//         << static_cast<int32_t>(payload.S_RX_RS485BD) << "\n";
//
//    file.close();
//}
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP5(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    // Write the header (column label) for PMU1
//    file << "PMU1\n";
//
//    // Serialize the PMU1 array into a single string
//    std::string pmu1Data = writeArray(payload.PMU1, 100);
//
//    // Write the serialized PMU1 array as a single entry in the CSV
//    file << pmu1Data << "\n";
//
//    file.close();
//}
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP6(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    // Write the header (column label) for PMU1
//    file << "PMU2\n";
//
//    // Serialize the PMU1 array into a single string
//    std::string pmu1Data = writeArray(payload.PMU2, 100);
//
//    // Write the serialized PMU1 array as a single entry in the CSV
//    file << pmu1Data << "\n";
//
//    file.close();
//}
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP7(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    // Write the header (column label) for PMU1
//    file << "PMU3\n";
//
//    // Serialize the PMU1 array into a single string
//    std::string pmu1Data = writeArray(payload.PMU3, 100);
//
//    // Write the serialized PMU1 array as a single entry in the CSV
//    file << pmu1Data << "\n";
//
//    file.close();
//}
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP8(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    // Write the header (column labels) for the CSV
//    file << "FDIRReportFlags,FDIROverCurrentReport,OBCConfigReport,SFResetCnt,CBResetCnt,IRPDUResetCnt,Sun1DevStatus,Sun2DevStatus,Sun3DevStatus,Sun4DevStatus,Sun5DevStatus,Sun6DevStatus,Gyro1DevStatus,Gyro2DevStatus,RW1DevStatus,RW2DevStatus,RW3DevStatus,RW4DevStatus,RW5DevStatus,StarTrackerDevStatus,IRStarTrackerDevStatus,CameraLCCDevStatus,UVBandDevStatus,MT_Isis5vDevStatus,MT_Isis33vDevStatus,MT_HescoDevStatus,XBand5vDevStatus,XBandVBatDevStatus,MM_HMR1DevStatus,MM_HMR2DevStatus,SBandRxDevStatus,SBandTxDevStatus,SIGINTDevStatus,GPS1DevStatus,GPS2DevStatus,PRP8vDevStatus,PRP12vDevStatus,TempSensorDevStatus,BatteryHeaterDevStatus,Onewire1DevStatus,Onewire2DevStatus,NandCommandFlag,NandInitFlag,MMC_InitFlag,PRPNumberSample,FreeRunningCnt1,FreeRunningCnt2,CB1Temprature,CAMTemprature1,CAMTemprature2,CB2Temprature1,CB2Temprature2,PRPTimeSampling,processSPIDataPacketErrorCnt,RWDevID\n";
//
//    // Serialize the fields and write them to the CSV file
//    file << static_cast<int32_t>(payload.FDIRReportFlags) << ",";
//    file << static_cast<int32_t>(payload.FDIROverCurrentReport) << ",";
//    file << static_cast<int32_t>(payload.OBCConfigReport) << ",";
//    file << payload.SFResetCnt << ",";
//    file << payload.CBResetCnt << ",";
//    file << payload.IRPDUResetCnt << ",";
//    file << payload.Sun1DevStatus << ",";
//    file << payload.Sun2DevStatus << ",";
//    file << payload.Sun3DevStatus << ",";
//    file << payload.Sun4DevStatus << ",";
//    file << payload.Sun5DevStatus << ",";
//    file << payload.Sun6DevStatus << ",";
//    file << payload.Gyro1DevStatus << ",";
//    file << payload.Gyro2DevStatus << ",";
//    file << payload.RW1DevStatus << ",";
//    file << payload.RW2DevStatus << ",";
//    file << payload.RW3DevStatus << ",";
//    file << payload.RW4DevStatus << ",";
//    file << payload.RW5DevStatus << ",";
//    file << payload.StarTrackerDevStatus << ",";
//    file << payload.IRStarTrackerDevStatus << ",";
//    file << payload.CameraLCCDevStatus << ",";
//    file << payload.UVBandDevStatus << ",";
//    file << payload.MT_Isis5vDevStatus << ",";
//    file << payload.MT_Isis33vDevStatus << ",";
//    file << payload.MT_HescoDevStatus << ",";
//    file << payload.XBand5vDevStatus << ",";
//    file << payload.XBandVBatDevStatus << ",";
//    file << payload.MM_HMR1DevStatus << ",";
//    file << payload.MM_HMR2DevStatus << ",";
//    file << payload.SBandRxDevStatus << ",";
//    file << payload.SBandTxDevStatus << ",";
//    file << payload.SIGINTDevStatus << ",";
//    file << payload.GPS1DevStatus << ",";
//    file << payload.GPS2DevStatus << ",";
//    file << payload.PRP8vDevStatus << ",";
//    file << payload.PRP12vDevStatus << ",";
//    file << payload.TempSensorDevStatus << ",";
//    file << payload.BatteryHeaterDevStatus << ",";
//    file << payload.Onewire1DevStatus << ",";
//    file << payload.Onewire2DevStatus << ",";
//    file << payload.NandCommandFlag << ",";
//    file << payload.NandInitFlag << ",";
//    file << payload.MMC_InitFlag << ",";
//    file << payload.PRPNumberSample << ",";
//    file << payload.FreeRunningCnt1 << ",";
//    file << payload.FreeRunningCnt2 << ",";
//    file << payload.CB1Temprature << ",";
//    file << payload.CAMTemprature1 << ",";
//    file << payload.CAMTemprature2 << ",";
//    file << payload.CB2Temprature1 << ",";
//    file << payload.CB2Temprature2 << ",";
//    file << payload.PRPTimeSampling << ",";
//    file << payload.processSPIDataPacketErrorCnt << ",";
//
//    // Serialize the RWDevID array into a single entry
//    std::string rwDevIdData = writeArray(payload.RWDevID, 4);
//    file << rwDevIdData << "\n";
//
//    file.close();
//}
//
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP9(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    mongocxx::collection collection;
//    collection = database["ExtendedPayloadP9"];
//    bsoncxx::builder::basic::document doc{};
//    insertHeader(doc, packet);
//    // UC1_SunReceiveCnt
//    bsoncxx::builder::basic::array uc1_sun_receive;
//    for (int i = 0; i < 3; ++i) {
//        uc1_sun_receive.append(payload.UC1_SunReceiveCnt[i]);
//    }
//    doc.append(bsoncxx::builder::basic::kvp("UC1_SunReceiveCnt", uc1_sun_receive));
//
//    doc.append(bsoncxx::builder::basic::kvp("UC2_LastGetTime", payload.UC2_LastGetTime));
//    doc.append(bsoncxx::builder::basic::kvp("UC2_TransmitCnt", payload.UC2_TransmitCnt));
//    doc.append(bsoncxx::builder::basic::kvp("UC2_SFReceiveCnt", payload.UC2_SFReceiveCnt));
//    doc.append(bsoncxx::builder::basic::kvp("UC2_SwitchCmd", payload.UC2_SwitchCmd));
//    doc.append(bsoncxx::builder::basic::kvp("UC2_SwitchRealState", payload.UC2_SwitchRealState));
//    doc.append(bsoncxx::builder::basic::kvp("UC2_SwitchFlagState", payload.UC2_SwitchFlagState));
//
//    // UC2_SunReceiveCnt
//    bsoncxx::builder::basic::array uc2_sun_receive;
//    for (int i = 0; i < 3; ++i) {
//        uc2_sun_receive.append(payload.UC2_SunReceiveCnt[i]);
//    }
//    doc.append(bsoncxx::builder::basic::kvp("UC2_SunReceiveCnt", uc2_sun_receive));
//
//    doc.append(bsoncxx::builder::basic::kvp("HE_durationProcess", payload.HE_durationProcess));
//    doc.append(bsoncxx::builder::basic::kvp("HE_SFduration", payload.HE_SFduration));
//
//    // HE_OBCTaskRunning
//    bsoncxx::builder::basic::array obc_tasks;
//    for (int i = 0; i < 32; ++i) {
//        obc_tasks.append(payload.HE_OBCTaskRunning[i]);
//    }
//    doc.append(bsoncxx::builder::basic::kvp("HE_OBCTaskRunning", obc_tasks));
//
//    doc.append(bsoncxx::builder::basic::kvp("Heater33vTimer", payload.Heater33vTimer));
//    doc.append(bsoncxx::builder::basic::kvp("OAPPowerDisipation", payload.OAPPowerDisipation));
//    doc.append(bsoncxx::builder::basic::kvp("HE_SPIGetCounter", payload.HE_SPIGetCounter));
//
//    // HE_MRAMCnt
//    bsoncxx::builder::basic::array mram_cnt;
//    for (int i = 0; i < 3; ++i) {
//        mram_cnt.append(payload.HE_MRAMCnt[i]);
//    }
//    doc.append(bsoncxx::builder::basic::kvp("HE_MRAMCnt", mram_cnt));
//
//    doc.append(bsoncxx::builder::basic::kvp("HE_ObcCounter", static_cast<int32_t>(payload.HE_ObcCounter)));
//
//    // RTC times
//    bsoncxx::builder::basic::array rtc1, rtc2, rtc3;
//    for (int i = 0; i < 3; ++i) {
//        rtc1.append(payload.HE_RTCTime1[i]);
//        rtc2.append(payload.HE_RTCTime2[i]);
//        rtc3.append(payload.HE_RTCTime3[i]);
//    }
//    doc.append(bsoncxx::builder::basic::kvp("HE_RTCTime1", rtc1));
//    doc.append(bsoncxx::builder::basic::kvp("HE_RTCTime2", rtc2));
//    doc.append(bsoncxx::builder::basic::kvp("HE_RTCTime3", rtc3));
//
//    doc.append(bsoncxx::builder::basic::kvp("HE_JulianDate", payload.HE_JulianDate));
//
//    doc.append(bsoncxx::builder::basic::kvp("RW1TimeSetCommand", payload.RW1TimeSetCommand));
//    doc.append(bsoncxx::builder::basic::kvp("RW1LastGetTime", payload.RW1LastGetTime));
//    doc.append(bsoncxx::builder::basic::kvp("RW2TimeSetCommand", payload.RW2TimeSetCommand));
//    doc.append(bsoncxx::builder::basic::kvp("RW2LastGetTime", payload.RW2LastGetTime));
//    doc.append(bsoncxx::builder::basic::kvp("RW3TimeSetCommand", payload.RW3TimeSetCommand));
//    doc.append(bsoncxx::builder::basic::kvp("RW3LastGetTime", payload.RW3LastGetTime));
//    doc.append(bsoncxx::builder::basic::kvp("RW4TimeSetCommand", payload.RW4TimeSetCommand));
//
//    doc.append(bsoncxx::builder::basic::kvp("SunIRLastGetTime", payload.SunIRLastGetTime));
//    doc.append(bsoncxx::builder::basic::kvp("RWRLastGetTime", payload.RWRLastGetTime));
//    doc.append(bsoncxx::builder::basic::kvp("StarIRLastGetTime", payload.StarIRLastGetTime));
//    doc.append(bsoncxx::builder::basic::kvp("HescoLastGetTime", payload.HescoLastGetTime));
//    doc.append(bsoncxx::builder::basic::kvp("BatteryFreeRunning", payload.BatteryFreeRunning));
//
//    collection.insert_one(doc.view());
//
//}
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP10(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    insertHeaderCSV(packet, file);
//
//    file << payload.SS1LastGetTime << ",";
//    file << static_cast<int>(payload.SS1NumberSample) << ",";
//    file << payload.SS2LastGetTime << ",";
//    file << static_cast<int>(payload.SS2NumberSample) << ",";
//    file << payload.SS3LastGetTime << ",";
//    file << static_cast<int>(payload.SS3NumberSample) << ",";
//    file << payload.SS4LastGetTime << ",";
//    file << static_cast<int>(payload.SS4NumberSample) << ",";
//    file << payload.SS5LastGetTime << ",";
//    file << static_cast<int>(payload.SS5NumberSample) << ",";
//    file << payload.Gyro1LastGetTime << ",";
//    file << payload.Gyro1NumberSample << ",";
//    file << payload.Gyro2LastGetTime << ",";
//    file << payload.Gyro2NumberSample << ",";
//    file << payload.MMLastGetTime << ",";
//    file << static_cast<int>(payload.MMNumberSample) << ",";
//    file << payload.GPSLastGetTime << ",";
//    file << static_cast<int>(payload.GPSNumberSample) << ",";
//    file << static_cast<int>(payload.ClydeFreeRunning) << ",";
//    file << payload.ErrorCounterClyde << ",";
//    file << payload.ErrorCounterClydeBattery << ",";
//    file << static_cast<int>(payload.OneWireFlagSwitch) << ",";
//    file << static_cast<int>(payload.Year) << ",";
//    file << static_cast<int>(payload.Month) << ",";
//    file << static_cast<int>(payload.Day) << ",";
//    file << static_cast<int>(payload.Hour) << ",";
//    file << static_cast<int>(payload.Minute) << ",";
//    file << static_cast<int>(payload.Second) << ",";
//
//    // OBC_RTC array
//    file << writeArray(payload.OBC_RTC, 6) << ",";
//
//    file << static_cast<int>(payload.OBC_MB_Temp) << ",";
//    file << static_cast<int>(payload.OBC_ID_) << ",";
//    file << payload.BootCounter << ",";
//    file << payload.OBC_CommandCounter << ",";
//    file << payload.OBC_Counter << ",";
//    file << payload.OBC_CpuUsage << ",";
//    file << static_cast<int>(payload.OBC_Mode) << ",";
//    file << payload.OBC_Current << ",";
//    file << payload.OBC_RcvdCmdCounter << ",";
//    file << payload.OBC_ExecutedCmdCounter << ",";
//    file << payload.UV_Fail_Timer << ",";
//    file << static_cast<int>(payload.OBC_WaitingTCToRun) << ",";
//    file << payload.OBC_ParameterAdd << ",";
//    file << payload.MMC_Write_BLK_ADD << ",";
//    file << payload.MMC_Read_BLK_ADD << ",";
//    file << static_cast<int>(payload.OBC_LINK_TYPE) << ",";
//    file << payload.RW4LastGetTime << ",";
//    file << payload.STRTimeSampling << ",";
//    file << payload.MTTimeSetCmd << ",";
//    file << payload.MTTimeSampling << ",";
//    file << static_cast<int>(payload.FailCRC) << ",";
//    file << payload.Flash_program_Add << ",";
//    file << static_cast<int>(payload.ready_program) << ",";
//    file << static_cast<int>(payload.Program_Mode) << ",";
//    file << static_cast<int>(payload.ProgramVersion);
//
//    file << "\n";
//}
//
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP11(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    mongocxx::collection collection;
//    collection = database["ExtendedPayloadP11"];
//    bsoncxx::builder::basic::document doc{};
//    insertHeader(doc, packet);
//    doc.append(bsoncxx::builder::basic::kvp("KeyIndexEncrypt_UV", payload.KeyIndexEncrypt_UV));
//    doc.append(bsoncxx::builder::basic::kvp("KeyIndexEncrypt_X", payload.KeyIndexEncrypt_X));
//    doc.append(bsoncxx::builder::basic::kvp("KeyIndexEncrypt_S_TX", payload.KeyIndexEncrypt_S_TX));
//    doc.append(bsoncxx::builder::basic::kvp("KeyIndexEncrypt_S_RX", payload.KeyIndexEncrypt_S_RX));
//    doc.append(bsoncxx::builder::basic::kvp("Num_active_Tasks", payload.Num_active_Tasks));
//    doc.append(bsoncxx::builder::basic::kvp("MRAMs_Usage", payload.MRAMs_Usage));
//    doc.append(bsoncxx::builder::basic::kvp("Nandflash_Usage", payload.Nandflash_Usage));
//    doc.append(bsoncxx::builder::basic::kvp("SF_JulianDate", payload.SF_JulianDate));
//
//    bsoncxx::builder::basic::array sf_mtdipole;
//    for (int i = 0; i < 3; ++i) sf_mtdipole.append(payload.SF_MTDipoleActuation[i]);
//    doc.append(bsoncxx::builder::basic::kvp("SF_MTDipoleActuation", sf_mtdipole));
//
//    doc.append(bsoncxx::builder::basic::kvp("SF_SysTimerCnt", static_cast<int32_t>(payload.SF_SysTimerCnt)));
//    doc.append(bsoncxx::builder::basic::kvp("SF_TransmitCnt", static_cast<int32_t>(payload.SF_TransmitCnt)));
//    doc.append(bsoncxx::builder::basic::kvp("SF_MTDipoleDuaration", payload.SF_MTDipoleDuaration));
//
//    bsoncxx::builder::basic::array sf_wheel_ref_cmd;
//    for (int i = 0; i < 5; ++i) sf_wheel_ref_cmd.append(payload.SF_WheelRefrenceCommand[i]);
//    doc.append(bsoncxx::builder::basic::kvp("SF_WheelRefrenceCommand", sf_wheel_ref_cmd));
//
//    doc.append(bsoncxx::builder::basic::kvp("SF_CpuUsage", payload.SF_CpuUsage));
//    doc.append(bsoncxx::builder::basic::kvp("SF_MTDurationOffTime", payload.SF_MTDurationOffTime));
//    doc.append(bsoncxx::builder::basic::kvp("SF_RWInterfaceCfg", payload.SF_RWInterfaceCfg));
//    doc.append(bsoncxx::builder::basic::kvp("SF_PowerDeviceCfg", payload.SF_PowerDeviceCfg));
//    doc.append(bsoncxx::builder::basic::kvp("SF_AOCSFerquency", payload.SF_AOCSFerquency));
//
//    bsoncxx::builder::basic::array i2c_status;
//    for (int i = 0; i < 2; ++i) i2c_status.append(payload.SF_I2CStatus[i]);
//    doc.append(bsoncxx::builder::basic::kvp("SF_I2CStatus", i2c_status));
//
//    bsoncxx::builder::basic::array cb1_power_switch;
//    for (int i = 0; i < 2; ++i) cb1_power_switch.append(payload.SF_CB1PowerSwitchCfg[i]);
//    doc.append(bsoncxx::builder::basic::kvp("SF_CB1PowerSwitchCfg", cb1_power_switch));
//
//    bsoncxx::builder::basic::array sf_cmd_mtdipole;
//    for (int i = 0; i < 3; ++i) sf_cmd_mtdipole.append(payload.SFCmd_MTDipoleActuation[i]);
//    doc.append(bsoncxx::builder::basic::kvp("SFCmd_MTDipoleActuation", sf_cmd_mtdipole));
//
//    doc.append(bsoncxx::builder::basic::kvp("SFCmd_MTDipoleDuaration", payload.SFCmd_MTDipoleDuaration));
//
//    bsoncxx::builder::basic::array sf_cmd_wheel_cmd;
//    for (int i = 0; i < 5; ++i) sf_cmd_wheel_cmd.append(payload.SFCmd_WheelRefrenceCommand[i]);
//    doc.append(bsoncxx::builder::basic::kvp("SFCmd_WheelRefrenceCommand", sf_cmd_wheel_cmd));
//
//    doc.append(bsoncxx::builder::basic::kvp("SFCmd_MTDurationOffTime", payload.SFCmd_MTDurationOffTime));
//    doc.append(bsoncxx::builder::basic::kvp("SFCmd_RWInterfaceCfg", payload.SFCmd_RWInterfaceCfg));
//    doc.append(bsoncxx::builder::basic::kvp("SFCmd_PowerDeviceCfg", payload.SFCmd_PowerDeviceCfg));
//    doc.append(bsoncxx::builder::basic::kvp("SFCmd_AOCSFerquency", payload.SFCmd_AOCSFerquency));
//
//    doc.append(bsoncxx::builder::basic::kvp("UC1_LastGetTime", payload.UC1_LastGetTime));
//    doc.append(bsoncxx::builder::basic::kvp("UC1_TransmitCnt", payload.UC1_TransmitCnt));
//    doc.append(bsoncxx::builder::basic::kvp("UC1_SFReceiveCnt", payload.UC1_SFReceiveCnt));
//    doc.append(bsoncxx::builder::basic::kvp("UC1_SwitchCmd", payload.UC1_SwitchCmd));
//    doc.append(bsoncxx::builder::basic::kvp("UC1_SwitchRealState", payload.UC1_SwitchRealState));
//    doc.append(bsoncxx::builder::basic::kvp("UC1_SwitchFlagState", payload.UC1_SwitchFlagState));
//    doc.append(
//            bsoncxx::builder::basic::kvp("DisableFaultPowerFDIR",
//                                         static_cast<int32_t>(payload.DisableFaultPowerFDIR)));
//
//    collection.insert_one(doc.view());
//
//}
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP12(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    insertHeader(file, packet); // Assuming a CSV-friendly insertHeader()
//
//    file << payload.MMHMR1_X << ",";
//    file << payload.MMHMR1_Y << ",";
//    file << payload.MMHMR1_Z << ",";
//    file << payload.MMHMR2_X << ",";
//    file << payload.MMHMR2_Y << ",";
//    file << payload.MMHMR2_Z << ",";
//    file << payload.Gyro_Num << ",";
//    file << payload.Gyro1RateX << ",";
//    file << payload.Gyro1RateY << ",";
//    file << payload.Gyro1RateZ << ",";
//    file << payload.Gyro2RateX << ",";
//    file << payload.Gyro2RateY << ",";
//    file << payload.Gyro2RateZ << ",";
//    file << payload.Gyro1TempX << ",";
//    file << payload.Gyro1TempY << ",";
//    file << payload.Gyro1TempZ << ",";
//    file << payload.GPS_number << ",";
//    file << payload.GPS_State << ",";
//    file << payload.GPS_Temperature << ",";
//    file << static_cast<int32_t>(payload.TOW) << ",";
//    file << payload.WeakNumber << ",";
//    file << payload.UTC_Offset << ",";
//    file << payload.GPSLatitude << ",";
//    file << payload.GPSLongitude << ",";
//    file << payload.GPSAltitude << ",";
//
//    for (int i = 0; i < 4; ++i) file << payload.GPS_Visible[i] << ",";
//    for (int i = 0; i < 4; ++i) file << payload.GPS_Used[i] << ",";
//    for (int i = 0; i < 4; ++i) file << payload.GlonassVisible[i] << ",";
//    for (int i = 0; i < 4; ++i) file << payload.GlonassUsed[i] << ",";
//
//    file << payload.GPSPosX << ",";
//    file << payload.GPSPosY << ",";
//    file << payload.GPSPosZ << ",";
//    file << payload.GPSProcVX << ",";
//    file << payload.GPSProcVY << ",";
//    file << payload.GPSProcVZ << ",";
//    file << payload.GPSPDOP << ",";
//    file << payload.GPSHDop << ",";
//    file << payload.GPSVDop << ",";
//    file << payload.GPSTDop << ",";
//    file << payload.GPS1_CH11_SNR << ",";
//    file << payload.GPS1_CH12_SNR << ",";
//    file << payload.GPS1_CH13_SNR << ",";
//    file << payload.GPS1_CH14_SNR << ",";
//    file << payload.GPS1_CH15_SNR;
//
//    file << "\n"; // End of row
//}
//
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP13(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    // Write the CSV header
//    file << "PacketID,SequenceControl,PacketLength,Timestamp,"; // Assuming basic CCSDS fields
//    file << "GPS1_CH16_SNR,GPS1_CH17_SNR,GPS1_CH18_SNR,GPS1_CH19_SNR,GPS1_CH110_SNR,GPS1_CH111_SNR,GPS1_CH112_SNR,";
//    file << "GPS1_CH21_SNR,GPS1_CH22_SNR,GPS1_CH23_SNR,GPS1_CH24_SNR,GPS1_CH25_SNR,GPS1_CH26_SNR,GPS1_CH27_SNR,GPS1_CH28_SNR,GPS1_CH29_SNR,";
//    file << "GPS1_CH210_SNR,GPS1_CH211_SNR,GPS1_CH212_SNR,";
//    file << "SS1ALPHA,SS1BETA,SS1sundetection,SS1ERR,";
//    file << "SS2ALPHA,SS2BETA,SS2sundetection,SS2ERR,";
//    file << "SS3ALPHA,SS3BETA,SS3sundetection,SS3ERR,";
//    file << "SS4ALPHA,SS4BETA,SS4sundetection,SS4ERR,";
//    file << "SS5ALPHA,SS5BETA,SS5sundetection,SS5ERR,";
//    file << "HFP_SS_VecX,HFP_SS_VecY,HFP_SS_VecZ,HFP_qq,HFP_gg,HFP_SS_Time\n";
//
//    // Write the CSV data row
//    file << packet.PacketID << ",";
//    file << packet.SequenceControl << ",";
//    file << packet.PacketLength << ",";
//    file << packet.Timestamp << ","; // Adjust if timestamp formatting is needed
//
//    file << payload.GPS1_CH16_SNR << ",";
//    file << payload.GPS1_CH17_SNR << ",";
//    file << payload.GPS1_CH18_SNR << ",";
//    file << payload.GPS1_CH19_SNR << ",";
//    file << payload.GPS1_CH110_SNR << ",";
//    file << payload.GPS1_CH111_SNR << ",";
//    file << payload.GPS1_CH112_SNR << ",";
//    file << payload.GPS1_CH21_SNR << ",";
//    file << payload.GPS1_CH22_SNR << ",";
//    file << payload.GPS1_CH23_SNR << ",";
//    file << payload.GPS1_CH24_SNR << ",";
//    file << payload.GPS1_CH25_SNR << ",";
//    file << payload.GPS1_CH26_SNR << ",";
//    file << payload.GPS1_CH27_SNR << ",";
//    file << payload.GPS1_CH28_SNR << ",";
//    file << payload.GPS1_CH29_SNR << ",";
//    file << payload.GPS1_CH210_SNR << ",";
//    file << payload.GPS1_CH211_SNR << ",";
//    file << payload.GPS1_CH212_SNR << ",";
//
//    file << payload.SS1ALPHA << ",";
//    file << payload.SS1BETA << ",";
//    file << payload.SS1sundetection << ",";
//    file << payload.SS1ERR << ",";
//
//    file << payload.SS2ALPHA << ",";
//    file << payload.SS2BETA << ",";
//    file << payload.SS2sundetection << ",";
//    file << payload.SS2ERR << ",";
//
//    file << payload.SS3ALPHA << ",";
//    file << payload.SS3BETA << ",";
//    file << payload.SS3sundetection << ",";
//    file << payload.SS3ERR << ",";
//
//    file << payload.SS4ALPHA << ",";
//    file << payload.SS4BETA << ",";
//    file << payload.SS4sundetection << ",";
//    file << payload.SS4ERR << ",";
//
//    file << payload.SS5ALPHA << ",";
//    file << payload.SS5BETA << ",";
//    file << payload.SS5sundetection << ",";
//    file << payload.SS5ERR << ",";
//
//    file << payload.HFP_SS_VecX << ",";
//    file << payload.HFP_SS_VecY << ",";
//    file << payload.HFP_SS_VecZ << ",";
//    file << payload.HFP_qq << ",";
//    file << payload.HFP_gg << ",";
//    file << payload.HFP_SS_Time;
//
//    file << "\n"; // End of row
//}
//
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP14(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    // Write the CSV header
//    file << "PacketID,SequenceControl,PacketLength,Timestamp,";
//    file << "HFP_SS_Temp,HFP_SS_Voltage,";
//    file << "Gyro2TempX,Gyro2TempY,Gyro2TempZ,";
//    file << "Reserv0,Reserv1,Reserv2,";
//    file << "IMTQ_CMDDipX,IMTQ_CMDDipY,IMTQ_CMDDipZ,IMTQCurX,IMTQCury,IMTQCurz,";
//    file << "IMTQCoilTempX,IMTQCoilTempy,IMTQCoilTempz,IMTQ_MCUTemp,";
//    file << "Status_cmd,status,";
//    file << "HesMMFilteredX,HesMMFilteredY,HesMMFilteredZ,";
//    file << "HesCMD_DipX,HesCMD_DipY,HesCMD_DipZ,";
//    file << "HesCurX,HesCurY,HesCurZ,";
//    file << "HesCoilTempX,HesCoilTempY,HesCoilTempZ,HesMCUTemp,";
//    file << "RW1Speed,RW1RefSpeed,RW1Cur,RW1stat_Err_flg,";
//    file << "RW2Speed,RW2RefSpeed,RW2Cur,RW2stat_Err_flg,";
//    file << "RW3Speed,RW3RefSpeed,RW3Cur,RW3stat_Err_flg,";
//    file << "RW4Speed,RW4RefSpeed,RW4Cur,RW4stat_Err_flg,";
//    file << "RWHescoSpeed,RWHescoRefSpeed,RWHescoCur\n";
//
//    // Write the CSV data row
//    file << packet.PacketID << ",";
//    file << packet.SequenceControl << ",";
//    file << packet.PacketLength << ",";
//    file << packet.Timestamp << ",";
//
//    file << payload.HFP_SS_Temp << ",";
//    file << payload.HFP_SS_Voltage << ",";
//
//    file << payload.Gyro2TempX << ",";
//    file << payload.Gyro2TempY << ",";
//    file << payload.Gyro2TempZ << ",";
//
//    file << payload.Reserv0 << ",";
//    file << payload.Reserv1 << ",";
//    file << payload.Reserv2 << ",";
//
//    file << payload.IMTQ_CMDDipX << ",";
//    file << payload.IMTQ_CMDDipY << ",";
//    file << payload.IMTQ_CMDDipZ << ",";
//    file << payload.IMTQCurX << ",";
//    file << payload.IMTQCury << ",";
//    file << payload.IMTQCurz << ",";
//    file << payload.IMTQCoilTempX << ",";
//    file << payload.IMTQCoilTempy << ",";
//    file << payload.IMTQCoilTempz << ",";
//    file << payload.IMTQ_MCUTemp << ",";
//
//    file << payload.Status_cmd << ",";
//    file << payload.status << ",";
//
//    file << payload.HesMMFilteredX << ",";
//    file << payload.HesMMFilteredY << ",";
//    file << payload.HesMMFilteredZ << ",";
//
//    file << payload.HesCMD_DipX << ",";
//    file << payload.HesCMD_DipY << ",";
//    file << payload.HesCMD_DipZ << ",";
//
//    file << payload.HesCurX << ",";
//    file << payload.HesCurY << ",";
//    file << payload.HesCurZ << ",";
//
//    file << payload.HesCoilTempX << ",";
//    file << payload.HesCoilTempY << ",";
//    file << payload.HesCoilTempZ << ",";
//    file << payload.HesMCUTemp << ",";
//
//    file << payload.RW1Speed << ",";
//    file << payload.RW1RefSpeed << ",";
//    file << payload.RW1Cur << ",";
//    file << payload.RW1stat_Err_flg << ",";
//
//    file << payload.RW2Speed << ",";
//    file << payload.RW2RefSpeed << ",";
//    file << payload.RW2Cur << ",";
//    file << payload.RW2stat_Err_flg << ",";
//
//    file << payload.RW3Speed << ",";
//    file << payload.RW3RefSpeed << ",";
//    file << payload.RW3Cur << ",";
//    file << payload.RW3stat_Err_flg << ",";
//
//    file << payload.RW4Speed << ",";
//    file << payload.RW4RefSpeed << ",";
//    file << payload.RW4Cur << ",";
//    file << payload.RW4stat_Err_flg << ",";
//
//    file << payload.RWHescoSpeed << ",";
//    file << payload.RWHescoRefSpeed << ",";
//    file << payload.RWHescoCur;
//
//    file << "\n"; // End of data row
//}
//
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP15(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    // Write the CSV header
//    file << "PacketID,SequenceControl,PacketLength,Timestamp,";
//    file << "RWHestat_Err_flg,";
//    file << "TY_Star_attitudeQ1,TY_Star_attitudeQ2,TY_Star_attitudeQ3,TY_Star_attitudeQ4,";
//    file << "TY_Star_internal_time,TY_StarTemp,TY_StarImage_expo_value,TY_StarImage_threshold,";
//    file << "TY_Star_background_value,TY_StarReporting,TY_NumberOfExtractedStars,TY_ExternalImageSwitchStatus,TY_AttitudeEffectiveSign,";
//    file << "IR_Star_attitudeQ1,IR_Star_attitudeQ2,IR_Star_attitudeQ3,IR_Star_attitudeQ4,";
//    file << "IR_Star_internal_time,IR_StarTemp,IR_StarImage_expo_value,IR_StarImage_threshold,";
//    file << "IR_Star_background_value,IR_StarReporting,IR_NumberOfExtractedStars,IR_ExternalImageSwitchStatus,IR_AttitudeEffectiveSign,";
//    file << "SS_B_X,SS_B_Y,SS_B_Z,SS_ID,MM_B_X,MM_B_Y,MM_B_Z,";
//    file << "Gyro_B_X,Gyro_B_Y,";
//    file << "res_p15_0,res_p15_1\n";
//
//    // Write the CSV data row
//    file << packet.PacketID << ",";
//    file << packet.SequenceControl << ",";
//    file << packet.PacketLength << ",";
//    file << packet.Timestamp << ",";
//
//    file << payload.RWHestat_Err_flg << ",";
//
//    file << payload.TY_Star_attitudeQ1 << ",";
//    file << payload.TY_Star_attitudeQ2 << ",";
//    file << payload.TY_Star_attitudeQ3 << ",";
//    file << payload.TY_Star_attitudeQ4 << ",";
//
//    file << payload.TY_Star_internal_time << ",";
//    file << payload.TY_StarTemp << ",";
//    file << payload.TY_StarImage_expo_value << ",";
//    file << payload.TY_StarImage_threshold << ",";
//    file << payload.TY_Star_background_value << ",";
//    file << payload.TY_StarReporting << ",";
//    file << payload.TY_NumberOfExtractedStars << ",";
//    file << payload.TY_ExternalImageSwitchStatus << ",";
//    file << payload.TY_AttitudeEffectiveSign << ",";
//
//    file << payload.IR_Star_attitudeQ1 << ",";
//    file << payload.IR_Star_attitudeQ2 << ",";
//    file << payload.IR_Star_attitudeQ3 << ",";
//    file << payload.IR_Star_attitudeQ4 << ",";
//
//    // IR_Star_internal_time: reinterpret bytes to double
//    file << (*reinterpret_cast<const double *>(payload.bytes)) << ",";
//
//    file << payload.IR_StarTemp << ",";
//    file << payload.IR_StarImage_expo_value << ",";
//    file << payload.IR_StarImage_threshold << ",";
//    file << payload.IR_Star_background_value << ",";
//    file << payload.IR_StarReporting << ",";
//    file << payload.IR_NumberOfExtractedStars << ",";
//    file << payload.IR_ExternalImageSwitchStatus << ",";
//    file << payload.IR_AttitudeEffectiveSign << ",";
//
//    file << payload.SS_B_X << ",";
//    file << payload.SS_B_Y << ",";
//    file << payload.SS_B_Z << ",";
//    file << payload.SS_ID << ",";
//    file << payload.MM_B_X << ",";
//    file << payload.MM_B_Y << ",";
//    file << payload.MM_B_Z << ",";
//
//    file << payload.Gyro_B_X << ",";
//    file << payload.Gyro_B_Y << ",";
//
//    file << payload.res_p15[0] << ",";
//    file << payload.res_p15[1];
//
//    file << "\n"; // End of data row
//}
//
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP16(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    // Write the CSV header
//    file << "PacketID,SequenceControl,PacketLength,Timestamp,";
//    file << "Gyro_B_Z,";
//    file << "ST_Q1_IM,ST_Q2_IM,ST_Q3_IM,ST_Q4_IM,ST_ID,";
//    file << "GPS_Rx,GPS_Ry,GPS_Rz,GPS_Vx,GPS_Vy,GPS_Vz,GPSJD,";
//    file << "MT_CMD_Act_x,MT_CMD_Act_y,MT_CMD_Act_z,";
//    file << "RW_CMD_Act_x,RW_CMD_Act_y,RW_CMD_Act_z,";
//    file << "interfaceManagerVariablesflags_0,interfaceManagerVariablesflags_1,interfaceManagerVariablesflags_2,";
//    file << "interfaceManagerVariablesflags_3,interfaceManagerVariablesflags_4,interfaceManagerVariablesflags_5,interfaceManagerVariablesflags_6,";
//    file << "q0_Estimated,q1_Estimated,q2_Estimated,q3_Estimated\n";
//
//    // Write the CSV data row
//    file << packet.packet_id << ",";
//    file << packet.packet_sequence_control << ",";
//    file << packet.packet_length << ",";
//    file << packet.timestamp << ",";
//
//    file << payload.Gyro_B_Z << ",";
//
//    file << payload.ST_Q1_IM << ",";
//    file << payload.ST_Q2_IM << ",";
//    file << payload.ST_Q3_IM << ",";
//    file << payload.ST_Q4_IM << ",";
//    file << payload.ST_ID << ",";
//
//    file << payload.GPS_Rx << ",";
//    file << payload.GPS_Ry << ",";
//    file << payload.GPS_Rz << ",";
//    file << payload.GPS_Vx << ",";
//    file << payload.GPS_Vy << ",";
//    file << payload.GPS_Vz << ",";
//    file << payload.GPSJD << ",";
//
//    file << payload.MT_CMD_Act_x << ",";
//    file << payload.MT_CMD_Act_y << ",";
//    file << payload.MT_CMD_Act_z << ",";
//
//    file << payload.RW_CMD_Act_x << ",";
//    file << payload.RW_CMD_Act_y << ",";
//    file << payload.RW_CMD_Act_z << ",";
//
//    for (int i = 0; i < 7; ++i) {
//        file << payload.interfaceManagerVariablesflags[i];
//        if (i != 6) file << ",";
//    }
//    file << ",";
//
//    file << payload.q0_Estimated << ",";
//    file << payload.q1_Estimated << ",";
//    file << payload.q2_Estimated << ",";
//    file << payload.q3_Estimated;
//
//    file << "\n"; // End of data row
//}
//
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP17(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    mongocxx::collection collection;
//    collection = database["ExtendedPayloadP17"];
//    bsoncxx::builder::basic::document doc{};
//    insertHeader(doc, packet);
//    // Estimated values for W (angular velocity) and quaternion
//    doc.append(bsoncxx::builder::basic::kvp("W_X_Estimated", payload.W_X_Estimated));
//    doc.append(bsoncxx::builder::basic::kvp("W_Y_Estimated", payload.W_Y_Estimated));
//    doc.append(bsoncxx::builder::basic::kvp("W_Z_Estimated", payload.W_Z_Estimated));
//    doc.append(bsoncxx::builder::basic::kvp("q0_EKF", payload.q0_EKF));
//    doc.append(bsoncxx::builder::basic::kvp("q1_EKF", payload.q1_EKF));
//    doc.append(bsoncxx::builder::basic::kvp("q2_EKF", payload.q2_EKF));
//    doc.append(bsoncxx::builder::basic::kvp("q3_EKF", payload.q3_EKF));
//    doc.append(bsoncxx::builder::basic::kvp("W_X_EKF", payload.W_X_EKF));
//    doc.append(bsoncxx::builder::basic::kvp("W_Y_EKF", payload.W_Y_EKF));
//    doc.append(bsoncxx::builder::basic::kvp("W_Z_EKF", payload.W_Z_EKF));
//
//    // Estimated values for EKF-SG
//    doc.append(bsoncxx::builder::basic::kvp("q0_EKFSG", payload.q0_EKFSG));
//    doc.append(bsoncxx::builder::basic::kvp("q1_EKFSG", payload.q1_EKFSG));
//    doc.append(bsoncxx::builder::basic::kvp("q2_EKFSG", payload.q2_EKFSG));
//    doc.append(bsoncxx::builder::basic::kvp("q3_EKFSG", payload.q3_EKFSG));
//    doc.append(bsoncxx::builder::basic::kvp("W_X_EKFSG", payload.W_X_EKFSG));
//    doc.append(bsoncxx::builder::basic::kvp("W_Y_EKFSG", payload.W_Y_EKFSG));
//    doc.append(bsoncxx::builder::basic::kvp("W_Z_EKFSG", payload.W_Z_EKFSG));
//
//    // Star Gyro and battery/power data
//    doc.append(bsoncxx::builder::basic::kvp("q0_StarGyro", payload.q0_StarGyro));
//    doc.append(bsoncxx::builder::basic::kvp("CurrentBatteryCapacity", payload.CurrentBatteryCapacity));
//    doc.append(bsoncxx::builder::basic::kvp("PowerInputGeneration", payload.PowerInputGeneration));
//    doc.append(bsoncxx::builder::basic::kvp("TotalPowerDisipation", payload.TotalPowerDisipation));
//    doc.append(bsoncxx::builder::basic::kvp("OAPPowerDisipation", payload.OAPPowerDisipation));
//    doc.append(bsoncxx::builder::basic::kvp("OAPPowerGeneration", payload.OAPPowerGeneration));
//
//    // MRAM flags and status
//    doc.append(bsoncxx::builder::basic::kvp("globalStatesMRAMFlag", payload.globalStatesMRAMFlag));
//    doc.append(bsoncxx::builder::basic::kvp("globalConfigurationMRAMFlag", payload.globalConfigurationMRAMFlag));
//    doc.append(bsoncxx::builder::basic::kvp("globalScheduleTableMRAMFlag", payload.globalScheduleTableMRAMFlag));
//    doc.append(bsoncxx::builder::basic::kvp("MRAM1Status", payload.MRAM1Status));
//    doc.append(bsoncxx::builder::basic::kvp("MRAM2Status", payload.MRAM2Status));
//    doc.append(bsoncxx::builder::basic::kvp("MRAM3Status", payload.MRAM3Status));
//
//    // Reserved space (if necessary)
//    bsoncxx::builder::basic::array res_part17;
//    for (int i = 0; i < 2; ++i) res_part17.append(payload.res_part17[i]);
//    doc.append(bsoncxx::builder::basic::kvp("res_part17", res_part17));
//
//    collection.insert_one(doc.view());
//
//}
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP18(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    mongocxx::collection collection;
//    collection = database["ExtendedPayloadP18"];
//    bsoncxx::builder::basic::document doc{};
//    insertHeader(doc, packet);
//    // Star Gyro and EKF (Extended Kalman Filter) data
//    doc.append(bsoncxx::builder::basic::kvp("q1_StarGyro", payload.q1_StarGyro));
//    doc.append(bsoncxx::builder::basic::kvp("q2_StarGyro", payload.q2_StarGyro));
//    doc.append(bsoncxx::builder::basic::kvp("q3_StarGyro", payload.q3_StarGyro));
//    doc.append(bsoncxx::builder::basic::kvp("W_X_EKFSG", payload.W_X_EKFSG));
//    doc.append(bsoncxx::builder::basic::kvp("W_Y_EKFSG", payload.W_Y_EKFSG));
//    doc.append(bsoncxx::builder::basic::kvp("W_Z_EKFSG", payload.W_Z_EKFSG));
//    doc.append(bsoncxx::builder::basic::kvp("PNormEKF", payload.PNormEKF));
//    doc.append(bsoncxx::builder::basic::kvp("PNormEKFSG", payload.PNormEKFSG));
//    doc.append(bsoncxx::builder::basic::kvp("ConditionNumberEKF", payload.ConditionNumberEKF));
//    doc.append(bsoncxx::builder::basic::kvp("ConditionNumberEKFSG", payload.ConditionNumberEKFSG));
//
//    // Path data
//    doc.append(bsoncxx::builder::basic::kvp("q0_Path", payload.q0_Path));
//    doc.append(bsoncxx::builder::basic::kvp("q1_Path", payload.q1_Path));
//    doc.append(bsoncxx::builder::basic::kvp("q2_Path", payload.q2_Path));
//    doc.append(bsoncxx::builder::basic::kvp("q3_Path", payload.q3_Path));
//    doc.append(bsoncxx::builder::basic::kvp("W_X_Path", payload.W_X_Path));
//    doc.append(bsoncxx::builder::basic::kvp("W_Y_Path", payload.W_Y_Path));
//    doc.append(bsoncxx::builder::basic::kvp("W_Z_Path", payload.W_Z_Path));
//
//    // ADCS (Attitude Determination and Control System) data
//    doc.append(bsoncxx::builder::basic::kvp("dt_ADCS", payload.dt_ADCS));
//    doc.append(bsoncxx::builder::basic::kvp("T_Des_X", payload.T_Des_X));
//    doc.append(bsoncxx::builder::basic::kvp("T_Des_Y", payload.T_Des_Y));
//    doc.append(bsoncxx::builder::basic::kvp("T_Des_Z", payload.T_Des_Z));
//    doc.append(bsoncxx::builder::basic::kvp("ADCSMTDipoleX", payload.ADCSMTDipoleX));
//    doc.append(bsoncxx::builder::basic::kvp("ADCSMTDipoleY", payload.ADCSMTDipoleY));
//    doc.append(bsoncxx::builder::basic::kvp("ADCSMTDipoleZ", payload.ADCSMTDipoleZ));
//    doc.append(bsoncxx::builder::basic::kvp("ADCSRWTorqueX", payload.ADCSRWTorqueX));
//
//    collection.insert_one(doc.view());
//
//}
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP19(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    mongocxx::collection collection;
//    collection = database["ExtendedPayloadP19"];
//    bsoncxx::builder::basic::document doc{};
//    insertHeader(doc, packet);
//    // ADCS (Attitude Determination and Control System) and related data
//    doc.append(bsoncxx::builder::basic::kvp("ADCSRWTorqueY", payload.ADCSRWTorqueY));
//    doc.append(bsoncxx::builder::basic::kvp("ADCSRWTorqueZ", payload.ADCSRWTorqueZ));
//    doc.append(bsoncxx::builder::basic::kvp("RWRPMCommand_X", payload.RWRPMCommand_X));
//    doc.append(bsoncxx::builder::basic::kvp("RWRPMCommand_Y", payload.RWRPMCommand_Y));
//    doc.append(bsoncxx::builder::basic::kvp("RWRPMCommand_Z", payload.RWRPMCommand_Z));
//    doc.append(bsoncxx::builder::basic::kvp("KpC", payload.KpC));
//    doc.append(bsoncxx::builder::basic::kvp("KpF", payload.KpF));
//    doc.append(bsoncxx::builder::basic::kvp("KdC", payload.KdC));
//    doc.append(bsoncxx::builder::basic::kvp("KdF", payload.KdF));
//    doc.append(bsoncxx::builder::basic::kvp("ADCS_JD", payload.ADCS_JD));
//
//    bsoncxx::builder::basic::array adcsToInterfaceManagerFlag;
//    for (int i = 0; i < 3; ++i) adcsToInterfaceManagerFlag.append(payload.adcsToInterfaceManagerFlag[i]);
//    doc.append(bsoncxx::builder::basic::kvp("adcsToInterfaceManagerFlag", adcsToInterfaceManagerFlag));
//
//
//    // Orbit-related data
//    doc.append(bsoncxx::builder::basic::kvp("OrbitJulianDate", payload.OrbitJulianDate));
//    doc.append(bsoncxx::builder::basic::kvp("GPSJDDiff", payload.GPSJDDiff));
//    doc.append(bsoncxx::builder::basic::kvp("Orbit_dt", payload.Orbit_dt));
//    doc.append(bsoncxx::builder::basic::kvp("R_InECI_x", payload.R_InECI_x));
//    doc.append(bsoncxx::builder::basic::kvp("R_InECI_y", payload.R_InECI_y));
//    doc.append(bsoncxx::builder::basic::kvp("R_InECI_z", payload.R_InECI_z));
//
//    doc.append(bsoncxx::builder::basic::kvp("V_InECI_x", payload.V_InECI_x));
//    doc.append(bsoncxx::builder::basic::kvp("V_InECI_y", payload.V_InECI_y));
//    doc.append(bsoncxx::builder::basic::kvp("V_InECI_z", payload.V_InECI_z));
//
//    // Sun model data in ECI (Earth-Centered Inertial) coordinates
//    doc.append(bsoncxx::builder::basic::kvp("SunModelInECI_x", payload.SunModelInECI_x));
//    doc.append(bsoncxx::builder::basic::kvp("SunModelInECI_y", payload.SunModelInECI_y));
//    doc.append(bsoncxx::builder::basic::kvp("SunModelInECI_z", payload.SunModelInECI_z));
//
//    // Reserved field
//    doc.append(bsoncxx::builder::basic::kvp("res_p19", payload.res_p19));
//
//    collection.insert_one(doc.view());
//
//}
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP20(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    mongocxx::collection collection;
//    collection = database["ExtendedPayloadP20"];
//    bsoncxx::builder::basic::document doc{};
//    insertHeader(doc, packet);
//    // IGRF (International Geomagnetic Reference Field) data in ECI frame
//    doc.append(bsoncxx::builder::basic::kvp("IGRFInECI_x", payload.IGRFInECI_x));
//    doc.append(bsoncxx::builder::basic::kvp("IGRFInECI_y", payload.IGRFInECI_y));
//    doc.append(bsoncxx::builder::basic::kvp("IGRFInECI_z", payload.IGRFInECI_z));
//
//    // Orbit data for interface manager
//    bsoncxx::builder::basic::array OrbitToInterfaceManagerFlag;
//    for (int i = 0; i < 3; ++i) OrbitToInterfaceManagerFlag.append(payload.OrbitToInterfaceManagerFlag[i]);
//    doc.append(bsoncxx::builder::basic::kvp("OrbitToInterfaceManagerFlag", OrbitToInterfaceManagerFlag));
//
//
//    // Position and velocity in ECI frame (for programming/trajectory tracking)
//    doc.append(bsoncxx::builder::basic::kvp("R_InECI_Prog_x", payload.R_InECI_Prog_x));
//    doc.append(bsoncxx::builder::basic::kvp("R_InECI_Prog_y", payload.R_InECI_Prog_y));
//    doc.append(bsoncxx::builder::basic::kvp("R_InECI_Prog_z", payload.R_InECI_Prog_z));
//    doc.append(bsoncxx::builder::basic::kvp("V_InECI_Prog_x", payload.V_InECI_Prog_x));
//    doc.append(bsoncxx::builder::basic::kvp("V_InECI_Prog_y", payload.V_InECI_Prog_y));
//    doc.append(bsoncxx::builder::basic::kvp("V_InECI_Prog_z", payload.V_InECI_Prog_z));
//
//    // Custom MT (Magnetic Torquers) and RW (Reaction Wheel) data
//    doc.append(bsoncxx::builder::basic::kvp("MTCustomDipole_x", payload.MTCustomDipole_x));
//    doc.append(bsoncxx::builder::basic::kvp("MTCustomDipole_y", payload.MTCustomDipole_y));
//    doc.append(bsoncxx::builder::basic::kvp("MTCustomDipole_z", payload.MTCustomDipole_z));
//    doc.append(bsoncxx::builder::basic::kvp("RWCustomjRPM_x", payload.RWCustomjRPM_x));
//    doc.append(bsoncxx::builder::basic::kvp("RWCustomjRPM_y", payload.RWCustomjRPM_y));
//    doc.append(bsoncxx::builder::basic::kvp("RWCustomjRPM_z", payload.RWCustomjRPM_z));
//
//    // Buffer norm and criteria data
//    doc.append(bsoncxx::builder::basic::kvp("WBuffNorm", payload.WBuffNorm));
//    doc.append(bsoncxx::builder::basic::kvp("CriteriaMode", payload.CriteriaMode));
//    doc.append(bsoncxx::builder::basic::kvp("CriteriaCounter", static_cast<int32_t >(payload.CriteriaCounter)));
//
//    // Task ID, hardware status, and supervisor flags
//    doc.append(bsoncxx::builder::basic::kvp("TaskID", payload.TaskID));
//    doc.append(bsoncxx::builder::basic::kvp("hardwareStatus", payload.hardwareStatus));
//    doc.append(
//            bsoncxx::builder::basic::kvp("supervisorToInterfaceManagerFlg",
//                                         payload.supervisorToInterfaceManagerFlg));
//
//    // CPU and exception counters for OBC (Onboard Computer)
//    doc.append(bsoncxx::builder::basic::kvp("OS_CPU_ARM_EXCEPT_RESETCnt", payload.OS_CPU_ARM_EXCEPT_RESETCnt));
//    doc.append(bsoncxx::builder::basic::kvp("ARM_EXCEPT_UNDEF_INSTRCnt", payload.ARM_EXCEPT_UNDEF_INSTRCnt));
//    doc.append(bsoncxx::builder::basic::kvp("OS_CPU_ARM_EXCEPT_SWICnt", payload.OS_CPU_ARM_EXCEPT_SWICnt));
//    doc.append(bsoncxx::builder::basic::kvp("OS_CPU_ARM_EXCEPT_PREFETCH_ABORTCnt",
//                                            payload.OS_CPU_ARM_EXCEPT_PREFETCH_ABORTCnt));
//    doc.append(
//            bsoncxx::builder::basic::kvp("OS_CPU_ARM_EXCEPT_DATA_ABORTCnt",
//                                         payload.OS_CPU_ARM_EXCEPT_DATA_ABORTCnt));
//    doc.append(
//            bsoncxx::builder::basic::kvp("OS_CPU_ARM_EXCEPT_ADDR_ABORTCnt",
//                                         payload.OS_CPU_ARM_EXCEPT_ADDR_ABORTCnt));
//    doc.append(bsoncxx::builder::basic::kvp("OS_CPU_ARM_EXCEPT_FIQCnt", payload.OS_CPU_ARM_EXCEPT_FIQCnt));
//    doc.append(bsoncxx::builder::basic::kvp("OS_CPU_ARM_EXCEPT_OtherCnt", payload.OS_CPU_ARM_EXCEPT_OtherCnt));
//
//    // Error and critical status flags
//    doc.append(bsoncxx::builder::basic::kvp("MMC_Errorr_Counter", payload.MMC_Errorr_Counter));
//    doc.append(
//            bsoncxx::builder::basic::kvp("MRAMOBCCriticalStatusDataFlag", payload.MRAMOBCCriticalStatusDataFlag));
//    doc.append(bsoncxx::builder::basic::kvp("MRAMCPUExceptionFlag", payload.MRAMCPUExceptionFlag));
//
//    // Reserved field
//    bsoncxx::builder::basic::array respart19;
//    for (int i = 0; i < 15; ++i) respart19.append(payload.respart19[i]);
//    doc.append(bsoncxx::builder::basic::kvp("respart19", respart19));
//
//    collection.insert_one(doc.view());
//
//}
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP21(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    mongocxx::collection collection;
//    collection = database["ExtendedPayloadP21"];
//    bsoncxx::builder::basic::document doc{};
//    insertHeader(doc, packet);
//    // Serialize ID_CMD_REC_Return (array of 100 bytes)
//
//    bsoncxx::builder::basic::array ID_CMD_REC_Return;
//    for (int i = 0; i < 100; ++i) ID_CMD_REC_Return.append(payload.ID_CMD_REC_Return[i]);
//    doc.append(bsoncxx::builder::basic::kvp("ID_CMD_REC_Return", ID_CMD_REC_Return));
//
//    collection.insert_one(doc.view());
//
//}
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP22(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    mongocxx::collection collection;
//    collection = database["ExtendedPayloadP22"];
//    bsoncxx::builder::basic::document doc{};
//    insertHeader(doc, packet);
//    // Serialize ID_CMD_REC_Return (array of 100 bytes)
//    bsoncxx::builder::basic::array arr;
//    for (int i = 0; i < 100; ++i)
//        arr.append(static_cast<int8_t>(payload.ID_CMD_REC_Return[i]));
//    doc.append(bsoncxx::builder::basic::kvp("ID_CMD_REC_Return", arr));
//    collection.insert_one(doc.view());
//
//}
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP23(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    mongocxx::collection collection;
//    collection = database["ExtendedPayloadP23"];
//    bsoncxx::builder::basic::document doc{};
//    insertHeader(doc, packet);
//    // Serialize ID_CMD_REC_Return (array of 100 bytes)
//    bsoncxx::builder::basic::array arr;
//    for (int i = 0; i < 100; ++i)
//        arr.append(static_cast<int8_t>(payload.ID_CMD_REC_Return[i]));
//    doc.append(bsoncxx::builder::basic::kvp("ID_CMD_REC_Return", arr));
//    collection.insert_one(doc.view());
//
//}
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP24(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    mongocxx::collection collection;
//    collection = database["ExtendedPayloadP24"];
//    bsoncxx::builder::basic::document doc{};
//    insertHeader(doc, packet);
//    // Serialize ID_CMD_REC_Return (array of 100 bytes)
//    bsoncxx::builder::basic::array arr;
//    for (int i = 0; i < 100; ++i)
//        arr.append(static_cast<int8_t>(payload.ID_CMD_Executed_Return[i]));
//    doc.append(bsoncxx::builder::basic::kvp("ID_CMD_Executed_Return", arr));
//    collection.insert_one(doc.view());
//
//}
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP25(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    mongocxx::collection collection;
//    collection = database["ExtendedPayloadP25"];
//    bsoncxx::builder::basic::document doc{};
//    insertHeader(doc, packet);
//    // Serialize ID_CMD_REC_Return (array of 100 bytes)
//    bsoncxx::builder::basic::array arr;
//    for (int i = 0; i < 100; ++i)
//        arr.append(static_cast<int8_t>(payload.ID_CMD_Executed_Return[i]));
//    doc.append(bsoncxx::builder::basic::kvp("ID_CMD_Executed_Return", arr));
//    collection.insert_one(doc.view());
//
//}
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP26(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    mongocxx::collection collection;
//    collection = database["ExtendedPayloadP26"];
//    bsoncxx::builder::basic::document doc{};
//    insertHeader(doc, packet);
//    // Serialize ID_CMD_REC_Return (array of 100 bytes)
//    bsoncxx::builder::basic::array arr;
//    for (int i = 0; i < 100; ++i)
//        arr.append(static_cast<int8_t>(payload.ID_CMD_Executed_Return[i]));
//    doc.append(bsoncxx::builder::basic::kvp("ID_CMD_Executed_Return", arr));
//    collection.insert_one(doc.view());
//
//}
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP27(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    mongocxx::collection collection;
//    collection = database["ExtendedPayloadP27"];
//    bsoncxx::builder::basic::document doc{};
//    insertHeader(doc, packet);
//    // SETPARAM
//    doc.append(bsoncxx::builder::basic::kvp("SETPARAM_VAR_TYPE", payload.SETPARAM_VAR_TYPE));
//    doc.append(bsoncxx::builder::basic::kvp("SETPARAM_MEM_ADD", static_cast<int32_t >(payload.SETPARAM_MEM_ADD)));
//
//    bsoncxx::builder::basic::array SETPARAM_MEM_VAL_array;
//    for (int i = 0; i < 8; ++i)
//        SETPARAM_MEM_VAL_array.append(payload.SETPARAM_MEM_VAL[i]);
//    doc.append(bsoncxx::builder::basic::kvp("SETPARAM_MEM_VAL", SETPARAM_MEM_VAL_array));
//
//    doc.append(bsoncxx::builder::basic::kvp("Get_Param_length", payload.Get_Param_length));
//    doc.append(bsoncxx::builder::basic::kvp("Get_param_Start_Add",
//                                            static_cast<int32_t >(payload.Get_param_Start_Add)));
//
//    bsoncxx::builder::basic::array Get_param_Value_array;
//    for (int i = 0; i < 40; ++i)
//        Get_param_Value_array.append(payload.Get_param_Value[i]);
//    doc.append(bsoncxx::builder::basic::kvp("Get_param_Value", Get_param_Value_array));
//
//    // IRPDU 1
//    doc.append(bsoncxx::builder::basic::kvp("IRPDU_Enable1", payload.IRPDU_Enable1));
//    doc.append(bsoncxx::builder::basic::kvp("IRPDU_Flag1", payload.IRPDU_Flag1));
//    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CurrentSband1", payload.IRPDU_CurrentSband1));
//    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CurrentGps1", payload.IRPDU_CurrentGps1));
//    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CurrentProp8V1", payload.IRPDU_CurrentProp8V1));
//    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CurrentProp12V1", payload.IRPDU_CurrentProp12V1));
//    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CurrentMThesco", payload.IRPDU_CurrentMThesco));
//    doc.append(bsoncxx::builder::basic::kvp("IRPDU_TemperatureSen1", payload.IRPDU_TemperatureSen1));
//    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CommandCounter1", payload.IRPDU_CommandCounter1));
//    doc.append(bsoncxx::builder::basic::kvp("IRPDU_TelemetryCounter1", payload.IRPDU_TelemetryCounter1));
//
//    // IRPDU 2
//    doc.append(bsoncxx::builder::basic::kvp("IRPDU_Enable2", payload.IRPDU_Enable2));
//    doc.append(bsoncxx::builder::basic::kvp("IRPDU_Flag2", payload.IRPDU_Flag2));
//    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CurrentSband2", payload.IRPDU_CurrentSband2));
//    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CurrentGps2", payload.IRPDU_CurrentGps2));
//    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CurrentProp8V2", payload.IRPDU_CurrentProp8V2));
//    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CurrentProp12V2", payload.IRPDU_CurrentProp12V2));
//    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CurrentMM_HMR", payload.IRPDU_CurrentMM_HMR));
//    doc.append(bsoncxx::builder::basic::kvp("IRPDU_TemperatureSen2", payload.IRPDU_TemperatureSen2));
//    doc.append(bsoncxx::builder::basic::kvp("IRPDU_CommandCounter2", payload.IRPDU_CommandCounter2));
//    doc.append(bsoncxx::builder::basic::kvp("IRPDU_TelemetryCounter2", payload.IRPDU_TelemetryCounter2));
//
//    // Switch states
//    doc.append(bsoncxx::builder::basic::kvp("CB_SwitchState", payload.CB_SwitchState));
//    doc.append(bsoncxx::builder::basic::kvp("PmuState", payload.PmuState));
//    doc.append(bsoncxx::builder::basic::kvp("CBPmuState", payload.CBPmuState));
//
//    // Reserved bytes
//    bsoncxx::builder::basic::array res_array;
//    for (int i = 0; i < 4; ++i)
//        res_array.append(payload.res[i]);
//    doc.append(bsoncxx::builder::basic::kvp("res", res_array));
//    collection.insert_one(doc.view());
//
//
//}
//
//
//template<typename T>
//void CSVHandler::serializeExtendedPayloadP28(const T payload, const CCSDS_Packet &packet, std::ofstream &file) {
//    mongocxx::collection collection;
//    collection = database["ExtendedPayloadP28"];
//    bsoncxx::builder::basic::document doc{};
//    insertHeader(doc, packet);
//    // Serialize Analog Sensors (int16_t)
//    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_1", payload.Analog_Sensor_1));
//    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_2", payload.Analog_Sensor_2));
//    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_3", payload.Analog_Sensor_3));
//    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_4", payload.Analog_Sensor_4));
//    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_5", payload.Analog_Sensor_5));
//    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_6", payload.Analog_Sensor_6));
//    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_7", payload.Analog_Sensor_7));
//    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_8", payload.Analog_Sensor_8));
//    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_9", payload.Analog_Sensor_9));
//    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_10", payload.Analog_Sensor_10));
//    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_11", payload.Analog_Sensor_11));
//    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_12", payload.Analog_Sensor_12));
//    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_13", payload.Analog_Sensor_13));
//    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_14", payload.Analog_Sensor_14));
//    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_15", payload.Analog_Sensor_15));
//    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_16", payload.Analog_Sensor_16));
//    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_17", payload.Analog_Sensor_17));
//    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_18", payload.Analog_Sensor_18));
//    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_19", payload.Analog_Sensor_19));
//    doc.append(bsoncxx::builder::basic::kvp("Analog_Sensor_20", payload.Analog_Sensor_20));
//
//
//    // Serialize Temp Sensors (int8_t)
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor1", payload.Temp_Sensor1));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor2", payload.Temp_Sensor2));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor3", payload.Temp_Sensor3));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor4", payload.Temp_Sensor4));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor5", payload.Temp_Sensor5));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor6", payload.Temp_Sensor6));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor7", payload.Temp_Sensor7));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor8", payload.Temp_Sensor8));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor9", payload.Temp_Sensor9));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor10", payload.Temp_Sensor10));
//
//    // Serialize more Temp Sensors (int8_t)
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor11", payload.Temp_Sensor11));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor12", payload.Temp_Sensor12));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor13", payload.Temp_Sensor13));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor14", payload.Temp_Sensor14));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor15", payload.Temp_Sensor15));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor16", payload.Temp_Sensor16));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor17", payload.Temp_Sensor17));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor18", payload.Temp_Sensor18));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor19", payload.Temp_Sensor19));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor20", payload.Temp_Sensor20));
//
//    // Serialize remaining Temp Sensors (int8_t)
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor21", payload.Temp_Sensor21));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor22", payload.Temp_Sensor22));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor23", payload.Temp_Sensor23));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor24", payload.Temp_Sensor24));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor25", payload.Temp_Sensor25));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor26", payload.Temp_Sensor26));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor27", payload.Temp_Sensor27));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor28", payload.Temp_Sensor28));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor29", payload.Temp_Sensor29));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor30", payload.Temp_Sensor30));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor31", payload.Temp_Sensor31));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor32", payload.Temp_Sensor32));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor33", payload.Temp_Sensor33));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor34", payload.Temp_Sensor34));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor35", payload.Temp_Sensor35));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor36", payload.Temp_Sensor36));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor37", payload.Temp_Sensor37));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor38", payload.Temp_Sensor38));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor39", payload.Temp_Sensor39));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor40", payload.Temp_Sensor40));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor41", payload.Temp_Sensor41));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor42", payload.Temp_Sensor42));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor43", payload.Temp_Sensor43));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor44", payload.Temp_Sensor44));
//    doc.append(bsoncxx::builder::basic::kvp("Temp_Sensor45", payload.Temp_Sensor45));
//
//    // Serialize prop_Status, prop_TankTemp, prop_PlenumTemp, prop_TankPressure, prop_PlenumPressure
//    doc.append(bsoncxx::builder::basic::kvp("prop_Status", payload.prop_Status));
//    doc.append(bsoncxx::builder::basic::kvp("prop_TankTemp", payload.prop_TankTemp));
//    doc.append(bsoncxx::builder::basic::kvp("prop_PlenumTemp", payload.prop_PlenumTemp));
//    doc.append(bsoncxx::builder::basic::kvp("prop_TankPressure", payload.prop_TankPressure));
//    doc.append(bsoncxx::builder::basic::kvp("prop_PlenumPressure", payload.prop_PlenumPressure));
//
//    // Serialize prop Durations, Delays, and PWM values
//    doc.append(bsoncxx::builder::basic::kvp("prop_Duration1", payload.prop_Duration1));
//    doc.append(bsoncxx::builder::basic::kvp("prop_Duration2", payload.prop_Duration2));
//    doc.append(bsoncxx::builder::basic::kvp("prop_Delay1", payload.prop_Delay1));
//    doc.append(bsoncxx::builder::basic::kvp("prop_Delay2", payload.prop_Delay2));
//    doc.append(bsoncxx::builder::basic::kvp("prop_PWM1", payload.prop_PWM1));
//    doc.append(bsoncxx::builder::basic::kvp("prop_PWM2", payload.prop_PWM2));
//    collection.insert_one(doc.view());
//}
//
//* /