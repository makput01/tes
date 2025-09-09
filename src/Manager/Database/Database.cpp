#include "Database.hpp"
#include <fstream>
#include <iostream>
#include <Utils/MiscUtils.hpp>
#include <fmt/core.h>
#include <Logger/Logger.hpp>

static Database g_database {};

bool Database::IsAccountExist(const std::string& name) {
    PlayerData dummy;
    return FindPlayer(name, dummy);
}

PlayerRegistration Database::RegisterPlayer(const std::string& name, const std::string& password, const std::string& verifyPassword) {
    std::string lowerCase = name;

    if (password.length() < 8 || password.length() > 24)
        return PlayerRegistration {
            .m_result   = PlayerRegistration::Result::INVALID_PASSWORD_LENGTH,
            .m_data     = "`4Oops!``  Your password must be between `$8`` and `$24`` characters long."
        };
    if (verifyPassword != password)
        return PlayerRegistration {
            .m_result   = PlayerRegistration::Result::MISMATCH_VERIFY_PASSWORD,
            .m_data     = "`4Oops!``  Passwords don't match.  Try again."
        };
    if (!Utils::ToLowerCase(lowerCase))
        return PlayerRegistration {
            .m_result   = PlayerRegistration::Result::INVALID_GROWID,
            .m_data     = "`4Oops!``  the name is includes invalid characters."
        };
    if (lowerCase.length() < 3 || lowerCase.length() > 18)
        return PlayerRegistration {
            .m_result   = PlayerRegistration::Result::INVALID_GROWID_LENGTH,
            .m_data     = "`4Oops!``  Your `wGrowID`` must be between `$3`` and `$18`` characters long."
        };
    if (this->IsAccountExist(lowerCase))
        return PlayerRegistration {
            .m_result   = PlayerRegistration::Result::EXIST_GROWID,
            .m_data     = fmt::format("`4Oops!``  The name `w{}`` is so cool someone else has already taken it.  Please choose a different name.", name)
        };

    return PlayerRegistration {
        .m_result   = PlayerRegistration::Result::SUCCESS,
        .m_data     = ""
    };
}
Database* GetDatabase() {
    return &g_database;
}

bool Database::Connect() {
    load_database();
    Logger::Print(INFO, "Initializing {}, using JSON file storage.",
        fmt::format(fmt::emphasis::bold | fg(fmt::color::cornsilk), "Database"));
    return true;
}

void Database::load_database() {
    std::ifstream file(m_player_database_path);
    if (file.good()) {
        try {
            file >> m_player_database;
            if (!m_player_database.is_array()) {
                m_player_database = nlohmann::json::array();
            }
        } catch (const nlohmann::json::parse_error& e) {
            std::cerr << "Error parsing " << m_player_database_path << ": " << e.what() << std::endl;
            m_player_database = nlohmann::json::array();
        }
    } else {
        m_player_database = nlohmann::json::array();
    }
}

void Database::save_database() {
    std::ofstream file(m_player_database_path);
    if (file.is_open()) {
        file << m_player_database.dump(4); // pretty print with 4 spaces
    } else {
        std::cerr << "Error: Could not open " << m_player_database_path << " for writing." << std::endl;
    }
}

bool Database::FindPlayer(const std::string& tank_id_name, PlayerData& result) {
    for (const auto& player_json : m_player_database) {
        if (player_json.is_object() && player_json.value("tankIdName", "") == tank_id_name) {
            result = player_json.get<PlayerData>();
            return true;
        }
    }
    return false;
}

bool Database::InsertPlayer(const PlayerData& data) {
    for (const auto& player_json : m_player_database) {
        if (player_json.is_object() && player_json.value("tankIdName", "") == data.tankIdName) {
            return false; // Player already exists
        }
    }

    nlohmann::json new_player_json = data;
    m_player_database.push_back(new_player_json);
    save_database();
    return true;
}

bool Database::UpdatePlayer(const PlayerData& data) {
    for (auto& player_json : m_player_database) {
        if (player_json.is_object() && player_json.value("tankIdName", "") == data.tankIdName) {
            player_json = data;
            save_database();
            return true;
        }
    }
    return false; // Player not found
}