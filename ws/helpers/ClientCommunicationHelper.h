//
// Created by ambaqinejad on 4/19/25.
//

#ifndef FINAL_PROJECT_CLIENTCOMMUNICATIONHELPER_H
#define FINAL_PROJECT_CLIENTCOMMUNICATIONHELPER_H


#include "logics/CCSDS_Packet.h"
#include <drogon/WebSocketConnection.h>
#include <drogon/drogon.h>

using namespace drogon;
using namespace std;

class ClientCommunicationHelper {
public:
    static void notifyClients(double progress, CCSDS_Packet packet);
    static unordered_set<WebSocketConnectionPtr> clients;
};


#endif //FINAL_PROJECT_CLIENTCOMMUNICATIONHELPER_H
