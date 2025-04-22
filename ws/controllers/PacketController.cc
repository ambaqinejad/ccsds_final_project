#include "PacketController.h"
#include "helpers/ControllerErrorHelper.h"
#include "logics/CCSDS_Packet.h"
#include "helpers/CCSDSPacketFileHelper.h"

// Add definition of your processing function here
void PacketController::getSIDPacketsByPagination(const HttpRequestPtr &req,
                                                 std::function<void(const HttpResponsePtr &)> &&callback) const {
    auto sidStr = (*req->getJsonObject())["sid"].asString();
    auto pageStr = (*req->getJsonObject())["page"].asString();
    auto pageSizeStr = (*req->getJsonObject())["pageSize"].asString();

    int _sid = 0;
    int _page = 0;
    int _pageSize = 0;

    try
    {
        _sid = std::stoi(sidStr);
        _page = std::stoi(pageStr);
        _pageSize = std::stoi(pageSizeStr); // Set your page size

        std::string fileUUID = (*req->getJsonObject())["fileUUID"].asString();

        // Get packets from UUID mapping
        auto it = CCSDSPacketFileHelper::uuidToSavedPacketsMapper.find(fileUUID);
        if (it == CCSDSPacketFileHelper::uuidToSavedPacketsMapper.end())
        {
            return ControllerErrorHelper::sendError(std::move(callback), k404NotFound, "File UUID not found.");
        }

        const std::vector<CCSDS_Packet> &allPackets = it->second;

        // Filter by SID
        std::vector<CCSDS_Packet> filteredPackets;
        for (const auto &pkt : allPackets)
        {
            if (pkt.sid == _sid) // assuming CCSDS_Packet has a `sid` field
            {
                filteredPackets.push_back(pkt);
            }
        }

        // Paginate
        int startIndex = (_page - 1) * _pageSize;
        int endIndex = std::min(startIndex + _pageSize, static_cast<int>(filteredPackets.size()));

        if (startIndex >= static_cast<int>(filteredPackets.size()))
        {
            return ControllerErrorHelper::sendError(std::move(callback), k404NotFound, "Page out of range.");
        }

        std::vector<CCSDS_Packet> paginatedPackets(filteredPackets.begin() + startIndex,
                                                   filteredPackets.begin() + endIndex);

        // Convert to JSON
        Json::Value pktJson;
        pktJson["num of all packets"] = static_cast<int>(allPackets.size());
        pktJson["num of all packets with this sid"] = static_cast<int>(filteredPackets.size());
        pktJson["total pages"] = filteredPackets.size()/_pageSize + 1;
        pktJson["sid"] = _sid;
        Json::Value resultJson(Json::arrayValue);
        for (const auto &pkt : paginatedPackets)
        {
            // or whatever your serialization method is
            resultJson.append(pkt.toJson());
        }
        pktJson["packets"] = resultJson;
        auto resp = HttpResponse::newHttpJsonResponse(pktJson);
        callback(resp);

    }
    catch (const std::exception &e)
    {
        ControllerErrorHelper::sendError(std::move(callback), k400BadRequest, "Invalid sid or page or pageSize parameter.");
    }

}
