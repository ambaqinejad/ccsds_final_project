//
// Created by ambaqinejad on 3/27/25.
//

#ifndef MONGODBHANDLER_H
#define MONGODBHANDLER_H

#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include "logics/CCSDS_Packet.h"


class MongoDBHandler {
public:
    MongoDBHandler();

    void insertPacket(const CCSDS_Packet &packet);

private:
    mongocxx::client client;
    mongocxx::database database;
    mongocxx::collection collection;

    // Helper to serialize extended payloads
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP1(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP2(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP3(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP4(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP5(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP6(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP7(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP8(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP9(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP10(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP11(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP12(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP13(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP14(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP15(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP16(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP17(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP18(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP19(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP20(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP21(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP22(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP23(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP24(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP25(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP26(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP27(const T payload);
    template <typename T>
    bsoncxx::builder::basic::document serializeExtendedPayloadP28(const T payload);

};


#endif //MONGODBHANDLER_H
