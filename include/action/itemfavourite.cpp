#include "pch.hpp"
#include "tools/string.hpp"
#include "itemfavourite.hpp"

void action::itemfavourite(ENetEvent& event, const std::string& header)
{
    std::string id{readch(header, '|')[4]};
    if (id.empty()) return;

    auto &peer = _peer[event.peer];
    auto it = std::ranges::find(peer->fav, stoi(id));
    bool fav = it != peer->fav.end();
    if (peer->fav.size() >= 20 && !fav)
    {
        constexpr std::string_view message = "You cannot favorite any more items. Remove some from your list and try again.";
        packet::create(*event.peer, false, 0, { "OnTalkBubble", peer->netid, message.data(), 0u, 1u });
        packet::create(*event.peer, false, 0, { "OnConsoleMessage", message.data() });
        return;
    }

    packet::create(*event.peer, false, 0, {
        "OnFavItemUpdated",
        stoi(id),
        (fav) ? 0 : 1
    });
    if (fav) peer->fav.erase(it);
    else peer->fav.emplace_back(stoi(id));
}
