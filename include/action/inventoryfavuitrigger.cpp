#include "pch.hpp"
#include "inventoryfavuitrigger.hpp"

void action::inventoryfavuitrigger(ENetEvent& event, const std::string& header)
{
    packet::create(*event.peer, false, 0,  {
        "OnDialogRequest",
        "set_default_color|`o\n"
        "add_label_with_icon|big|`wFavorited Items``|left|13814|\n"
        "add_spacer|small|\n"
        "add_textbox|All favorited items are currently in your inventory. They can be unfavorited by tapping on the UNFAV button while having the item selected in your inventory.|left|\n"
        "add_spacer|small|\n"
        "end_dialog|unfavorite_items_dialog|Close||\n"
    });
}