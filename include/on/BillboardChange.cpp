#include "pch.hpp"
#include "tools/string.hpp"
#include "BillboardChange.hpp"

void on::BillboardChange(ENetEvent& event)
{
    auto &peer = _peer[event.peer];
    packet::create(*event.peer, true, 0, {
        "OnBillboardChange",
        peer->netid,
        signed{peer->billboard.id},
        std::format("{},{}", to_char(peer->billboard.show), to_char(peer->billboard.isBuying)).c_str(),
        peer->billboard.price,
        signed{peer->billboard.perItem}
    });
}