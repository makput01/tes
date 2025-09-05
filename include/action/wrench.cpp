#include "pch.hpp"
#include "tools/string.hpp"
#include "wrench.hpp"

#include <cmath>

void action::wrench(ENetEvent& event, const std::string& header) 
{
    std::vector<std::string> pipes = readch(header, '|');
    if ((pipes[3zu] == "netid" && !pipes[4zu].empty()/*empty netid*/))
    {
        const short netid = atoi(pipes[4zu].c_str());
        peers(event, PEER_SAME_WORLD, [event, netid](ENetPeer& p) 
        {
            if (_peer[&p]->netid == netid)
            {
                auto &peer = _peer[&p];
                u_short lvl = peer->level.front();
                /* wrench yourself */
                if (peer->user_id == _peer[event.peer]->user_id)
                {
                    packet::create(p, false, 0, {
                        "OnDialogRequest",
                        std::format(
                            "embed_data|netID|{0}\n"
                            "add_popup_name|WrenchMenu|\n"
                            "set_default_color|`o\n"
                            "add_player_info|`{1}{2}``|{3}|{4}|{5}|\n"
                            "add_spacer|small|\n"
                            "add_spacer|small|\n"
                            "add_button|renew_pvp_license|Get Card Battle License|noflags|0|0|\n"
                            "add_spacer|small|\n"
                            "set_custom_spacing|x:5;y:10|\n"
                            "add_custom_button|open_personlize_profile|image:interface/large/gui_wrench_personalize_profile.rttex;image_size:400,260;width:0.19;|\n"
                            "add_custom_button|set_online_status|image:interface/large/gui_wrench_online_status_1green.rttex;image_size:400,260;width:0.19;|\n"
                            "add_custom_button|billboard_edit|image:interface/large/gui_wrench_edit_billboard.rttex;image_size:400,260;width:0.19;|\n"
                            "add_custom_button|notebook_edit|image:interface/large/gui_wrench_notebook.rttex;image_size:400,260;width:0.19;|\n"
                            "add_custom_button|goals|image:interface/large/gui_wrench_goals_quests.rttex;image_size:400,260;width:0.19;|\n"
                            "add_custom_button|bonus|image:interface/large/gui_wrench_daily_bonus_active.rttex;image_size:400,260;width:0.19;|\n"
                            "add_custom_button|my_worlds|image:interface/large/gui_wrench_my_worlds.rttex;image_size:400,260;width:0.19;|\n"
                            "add_custom_button|alist|image:interface/large/gui_wrench_achievements.rttex;image_size:400,260;width:0.19;|\n"
                            "add_custom_label|(0/173)|target:alist;top:0.72;left:0.5;size:small|\n"
                            "add_custom_button|emojis|image:interface/large/gui_wrench_growmojis.rttex;image_size:400,260;width:0.19;|\n"
                            "add_custom_button|marvelous_missions|image:interface/large/gui_wrench_marvelous_missions.rttex;image_size:400,260;width:0.19;|\n"
                            "add_custom_button|title_edit|image:interface/large/gui_wrench_title.rttex;image_size:400,260;width:0.19;|\n"
                            "add_custom_button|trade_scan|image:interface/large/gui_wrench_trades.rttex;image_size:400,260;width:0.19;|\n"
                            "embed_data|netID|{0}\n"
                            "add_custom_button|pets|image:interface/large/gui_wrench_battle_pets.rttex;image_size:400,260;width:0.19;|\n"
                            "add_custom_button|wrench_customization|image:interface/large/gui_wrench_customization.rttex;image_size:400,260;width:0.19;|\n"
                            "add_custom_break|\n"
                            "add_spacer|small|\n"
                            "set_custom_spacing|x:0;y:0|\n"
                            "add_spacer|small|\n"
                            "add_textbox|Surgeon Level: 0|left|\n"
                            "add_spacer|small|\n"
                            "add_textbox|`wActive effects:``|left|\n"
                            "{6}" // @todo add effects
                            "add_spacer|small|\n"
                            "add_textbox|`oYou have `w{7}`` backpack slots.``|left|\n"
                            "add_textbox|`oCurrent world: `w{8}`` (`w{9}``, `w{10}``) (`w0`` person)````|left|\n"
                            "add_spacer|small|\n"
                            "add_textbox|`oTotal time played is `w0.0`` hours.  This account was created `w0`` days ago.``|left|" // @todo add account creation
                            "add_spacer|small|\n"
                            "end_dialog|popup||Continue|\n"
                            "add_quick_exit|\n",
                        /*  {0}    {1}           {2}              {3}  {4}                 {5}                   {6}            {7}            */
                            netid, peer->prefix, peer->ltoken[0], lvl, peer->level.back(), 50 * (lvl * lvl + 2), ""/*effects*/, peer->slot_size, 
                        /*  {8}                         {9}                       {10}                    */
                            peer->recent_worlds.back(), std::round(peer->pos[0]), std::round(peer->pos[1])
                        ).c_str()
                    });
                }
                /* wrench someone else */
                else
                {
                     packet::create(p, false, 0, {
                        "OnDialogRequest",
                        std::format(
                            "embed_data|netID|{0}\n"
                            "add_popup_name|WrenchMenu|\n"
                            "set_default_color|`o\n"
                            "add_label_with_icon|big|`{1}{2} (`2{3}``)``|left|18|\n"
                            "embed_data|netID|{0}\n"
                            "add_spacer|small|\n"
                            "add_achieve|||left|26|\n"
                            "add_custom_margin|x:75;y:-70.85|\n"
                            "add_custom_margin|x:-75;y:70.85|\n"
                            "add_spacer|small|\n"
                            "add_label|small|`1Achievements:`` 0/173|left\n"
                            "add_spacer|small|\n"
                            "add_label|small|`1Account Age:`` 0 days|left\n" // @todo add account creation
                            "add_spacer|small|\n"
                            "add_button|trade|`wTrade``|noflags|0|0|\n"
                            "add_button|sendpm|`wSend Message``|noflags|0|0|\n"
                            "add_textbox|(No Battle Leash equipped)|left|\n"
                            "add_textbox|You need a valid license to battle!|left|\n"
                            "add_button|friend_add|`wAdd as friend``|noflags|0|0|\n"
                            "add_button|show_clothes|`wView worn clothes``|noflags|0|0|\n"
                            "add_button|ignore_player|`wIgnore Player``|noflags|0|0|\n"
                            "add_button|report_player|`wReport Player``|noflags|0|0|\n"
                            "add_spacer|small|\n"
                            "end_dialog|popup||Continue|\n"
                            "add_quick_exit|\n",
                            netid, peer->prefix, peer->ltoken[0], lvl
                        ).c_str()
                     });
                }
                return; // @note early exit else iteration will continue for EVERYONE in the world.
            }
        });
    }
}