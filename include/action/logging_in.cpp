#include "pch.hpp"
#include "tools/string.hpp"
#include "join_request.hpp"
#include "logging_in.hpp"

void action::logging_in(ENetEvent& event, const std::string& header)
{
    auto &peer = _peer[event.peer];

    try 
    {
        std::vector<std::string> pipes = readch(header, '|');
        if (pipes.size() < 4) throw std::runtime_error("");

        if (pipes[2zu] == "ltoken")
        {
            const std::string decoded = base64_decode(pipes[3zu]);
            if (decoded.empty()) throw std::runtime_error("");

            if (std::size_t pos = decoded.find("growId="); pos != std::string::npos) 
            {
                pos += sizeof("growId=")-1zu;
                peer->ltoken[0] = decoded.substr(pos, decoded.find('&', pos) - pos);
            }
            if (std::size_t pos = decoded.find("password="); pos != std::string::npos) 
            {
                pos += sizeof("password=")-1zu;
                peer->ltoken[1] = decoded.substr(pos);
            }
        } // @note delete decoded
    }
    catch (...) { packet::action(*event.peer, "logon_fail", ""); }
    peer->read(peer->ltoken[0]);
    
    packet::create(*event.peer, false, 0, {
        "OnSuperMainStartAcceptLogonHrdxs47254722215a",
        68720062u, // @note items.dat
        "ubistatic-a.akamaihd.net",
        "0098/31312214/cache/",
        "cc.cz.madkite.freedom org.aqua.gg idv.aqua.bulldog com.cih.gamecih2 com.cih.gamecih com.cih.game_cih cn.maocai.gamekiller com.gmd.speedtime org.dax.attack com.x0.strai.frep com.x0.strai.free org.cheatengine.cegui org.sbtools.gamehack com.skgames.traffikrider org.sbtoods.gamehaca com.skype.ralder org.cheatengine.cegui.xx.multi1458919170111 com.prohiro.macro me.autotouch.autotouch com.cygery.repetitouch.free com.cygery.repetitouch.pro com.proziro.zacro com.slash.gamebuster",
        "proto=217|choosemusic=audio/mp3/about_theme.mp3|active_holiday=0|wing_week_day=0|ubi_week_day=0|server_tick=41684313|game_theme=|clash_active=0|drop_lavacheck_faster=1|isPayingUser=1|usingStoreNavigation=1|enableInventoryTab=1|bigBackpack=1",
        0u // @note player_tribute.dat
    });
}