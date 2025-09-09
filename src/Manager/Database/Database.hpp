#pragma once

#include <string>
#include <vector>
#include "nlohmann_json/json.hpp"

#include "Player/PlayerData.hpp"

class Database {
public:
    Database() = default;
    ~Database() = default;

    bool Connect(); // Will load players.json

    bool FindPlayer(const std::string& tank_id_name, PlayerData& result);
    bool InsertPlayer(const PlayerData& data);
    bool UpdatePlayer(const PlayerData& data);

    PlayerRegistration RegisterPlayer(const std::string& name, const std::string& password, const std::string& verifyPassword);

private:
    void load_database();
    void save_database();

    nlohmann::json m_player_database;
    const std::string m_player_database_path = "players.json";
};

Database* GetDatabase();