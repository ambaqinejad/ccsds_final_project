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
};


#endif //MONGODBHANDLER_H
