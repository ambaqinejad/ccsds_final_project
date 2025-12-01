//
// Created by ambaqinejad on 12/1/25.
//

#ifndef FINAL_PROJECT_CONSTANTS_H
#define FINAL_PROJECT_CONSTANTS_H

#include <string>

class Constants {
public:
    // PATH
    inline static const std::string DEFAULT_DOCUMENT_ROOT = "/home/ambaqinejad/Desktop/drogon_ccsds/ccsds_final_project/ws/public";
    inline static const std::string DEFAULT_UPLOAD_DIR = "/uploads";

    // SERVER ERROR
    inline static const std::string SERVER_COULD_NOT_START_STRUCTURE = "Websocket server could not start because structure did not load.";
    inline static const std::string SERVER_COULD_NOT_START_PUBLIC_DIR = "Websocket server could not start because it can not create public directory.";
    inline static const std::string SERVER_COULD_NOT_START_UPLOAD_DIR = "Websocket server could not start because it can not create upload directory.";

    // SERVER INFO
    inline static const std::string SERVER_START_ON_PORT = "Starting WebSocket server on port ";

    // RESPONSE HEADER
    inline static const std::string ACCESS_CONTROL_ALLOW_ORIGIN_KEY = "Access-Control-Allow-Origin";
    inline static const std::string ACCESS_CONTROL_ALLOW_METHOD_KEY = "Access-Control-Allow-Methods";
    inline static const std::string ACCESS_CONTROL_ALLOW_HEADER_KEY = "Access-Control-Allow-Headers";
    inline static const std::string ACCESS_CONTROL_ALLOW_ALL_METHOD_VALUE = "GET, POST, PUT, DELETE, OPTIONS";
    inline static const std::string ACCESS_CONTROL_ALLOW_HEADER_VALUE = "Content-Type, Authorization, X-Requested-With, x-signalr-user-agent";
    inline static const std::string ALL = "*";

    // MONGODB
    inline static const std::string MONGODB_DEFAULT_URI = "mongodb://192.168.102.94:27017";

};
#endif //FINAL_PROJECT_CONSTANTS_H















