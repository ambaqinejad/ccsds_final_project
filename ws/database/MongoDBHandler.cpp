//
// Created by ambaqinejad on 3/27/25.
//

#include "MongoDBHandler.h"

#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <json/json.h>
#include <cstdlib>
#include "logics/CCSDS_Packet.h"
#include <drogon/HttpController.h>
#include <stdexcept>

MongoDBHandler::MongoDBHandler() {
    static mongocxx::instance instance{}; // Required once per application
    const char* uri_env = std::getenv("MONGODB_URI");
    std::string uri = uri_env ? uri_env : "mongodb://192.168.102.94:27017";  // fallback if env not set

    std::cout << uri << std::endl;
    client_ = mongocxx::client{mongocxx::uri{uri}};
    database_ = client_["CCSDS_DB"];
}



void MongoDBHandler::insertPacket(const CCSDS_Packet &packet) {
    // Serialize the extended_payload
    try {
        mongocxx::collection collection;
        std::string collection_name = "SID" + std::to_string(packet.sid);
        collection = database_[collection_name];
        bsoncxx::builder::basic::document doc{};
        insertHeader(doc, packet);

        Json::StreamWriterBuilder writer;
        std::string jsonStr = Json::writeString(writer, packet.parsedData);

        // Step 3: Parse JSON string into BSON
        bsoncxx::document::value subDocument = bsoncxx::from_json(jsonStr);
        doc.append(bsoncxx::builder::basic::kvp("data", subDocument));
        collection.insert_one(doc.view());

        LOG_INFO << "Packet inserted successfully.\n";
    } catch (const exception &e) {
        LOG_ERROR << "Exception caught: " << e.what() << "\n";
    }

}

void MongoDBHandler::insertHeader(bsoncxx::builder::basic::document &document, const CCSDS_Packet &packet) {
    document.append(bsoncxx::builder::basic::kvp("main_frame_header", packet.main_frame_header));
    document.append(bsoncxx::builder::basic::kvp("packet_id", packet.packet_id));
    document.append(bsoncxx::builder::basic::kvp("packet_sequence_control", packet.packet_sequence_control));
    document.append(bsoncxx::builder::basic::kvp("packet_length", packet.packet_length));
    document.append(bsoncxx::builder::basic::kvp("data_field_header", static_cast<int>(packet.data_field_header)));
    document.append(bsoncxx::builder::basic::kvp("service_type", static_cast<int>(packet.service_type)));
    document.append(bsoncxx::builder::basic::kvp("sub_service_type", static_cast<int>(packet.sub_service_type)));
    document.append(bsoncxx::builder::basic::kvp("sid", static_cast<int>(packet.sid)));
    document.append(bsoncxx::builder::basic::kvp("timestamp", static_cast<int64_t>(packet.timestamp)));
    document.append(
            bsoncxx::builder::basic::kvp("crc_fail_upload_map", static_cast<int64_t>(packet.crc_fail_upload_map)));
    document.append(bsoncxx::builder::basic::kvp("flash_address", static_cast<int>(packet.flash_address)));
}

void MongoDBHandler::insertStructure(nlohmann::ordered_json json) {
    mongocxx::collection collection = database_["CCSDS_Structure"];
    collection.drop(); // Clear previous data

    int i = 1;
    for (auto& item : json.items()) {
        nlohmann::ordered_json obj = item.value();

        // Set the _id field to the value of sid
        obj["_id"] = i;

        bsoncxx::document::value doc = bsoncxx::from_json(obj.dump());
        collection.insert_one(doc.view());
        i++;
    }
}
nlohmann::ordered_json MongoDBHandler::ccsds_structure_;
bool MongoDBHandler::loadStructure() {
    mongocxx::collection collection;
    collection = database_["CCSDS_Structure"];
    auto cursor = collection.find({});
    MongoDBHandler::ccsds_structure_ = nlohmann::ordered_json::array();
    for (auto &&doc: cursor) {
        std::string json_str = bsoncxx::to_json(doc);
        nlohmann::ordered_json j = nlohmann::ordered_json::parse(json_str);
        MongoDBHandler::ccsds_structure_.push_back(j);
    }
    if (!MongoDBHandler::ccsds_structure_.empty()) {
        LOG_INFO << "Structure loaded successfully from DB to RAM!\n";
        return true;
    }

    LOG_INFO << "Structure could not load from DB to RAM!\n";
    return false;
}