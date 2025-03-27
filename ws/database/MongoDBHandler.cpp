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

    // Convert payload to BSON array
    bsoncxx::builder::basic::array payload_array;
    for (auto byte : packet.payload) {
        payload_array.append(static_cast<int>(byte));
    }
    document.append(bsoncxx::builder::basic::kvp("payload", payload_array));

    collection.insert_one(document.view());
    std::cout << "Packet inserted successfully." << std::endl;

}


