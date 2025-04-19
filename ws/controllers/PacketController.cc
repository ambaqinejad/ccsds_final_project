#include "PacketController.h"

// Add definition of your processing function here
void PacketController::getSIDPacketsByPagination(const HttpRequestPtr &req,
                                                 std::function<void(const HttpResponsePtr &)> &&callback) const {
    std::cout << 123;
//    std::cout << page;

}
