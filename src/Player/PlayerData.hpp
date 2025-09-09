#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <nlohmann_json/json.hpp>

struct PlayerRegistration {
public:
    enum class Result {
        SUCCESS,
        EXIST_GROWID,
        INVALID_GROWID,
        INVALID_PASSWORD, //
        INVALID_EMAIL_OR_DISCORD,
        INVALID_GROWID_LENGTH,
        INVALID_PASSWORD_LENGTH,
        MISMATCH_VERIFY_PASSWORD,
        BAD_CONNECTION
    };

public:
    PlayerRegistration::Result  m_result;
    std::string                 m_data;
};

struct PlayerData {
    int ID = 0;
    std::string requestedName;
    std::string tankIdName;
    std::string tankIdPass;
    std::string rawName;
    std::string displayName;
    std::string emailAddress;
    long long discordClientId = 0;
    int gems = 0;
    int playerFlags = 0;
    std::vector<uint8_t> playerItems;
    std::vector<uint8_t> playerClothes;
    std::vector<uint8_t> playMods;
    std::vector<uint8_t> characterState;
};

namespace nlohmann {
    template <>
    struct adl_serializer<PlayerData> {
        static void to_json(json& j, const PlayerData& p) {
            j = json{
                {"ID", p.ID},
                {"requestedName", p.requestedName},
                {"tankIdName", p.tankIdName},
                {"tankIdPass", p.tankIdPass},
                {"rawName", p.rawName},
                {"displayName", p.displayName},
                {"emailAddress", p.emailAddress},
                {"discordClientId", p.discordClientId},
                {"gems", p.gems},
                {"playerFlags", p.playerFlags},
                {"playerItems", p.playerItems},
                {"playerClothes", p.playerClothes},
                {"playMods", p.playMods},
                {"characterState", p.characterState}
            };
        }

        static void from_json(const json& j, PlayerData& p) {
            // Use .value() to handle missing keys gracefully, providing a default value.
            p.ID = j.value("ID", 0);
            p.requestedName = j.value("requestedName", "");
            p.tankIdName = j.value("tankIdName", "");
            p.tankIdPass = j.value("tankIdPass", "");
            p.rawName = j.value("rawName", "");
            p.displayName = j.value("displayName", "");
            p.emailAddress = j.value("emailAddress", "");
            p.discordClientId = j.value("discordClientId", 0LL);
            p.gems = j.value("gems", 0);
            p.playerFlags = j.value("playerFlags", 0);
            p.playerItems = j.value<std::vector<uint8_t>>("playerItems", {});
            p.playerClothes = j.value<std::vector<uint8_t>>("playerClothes", {});
            p.playMods = j.value<std::vector<uint8_t>>("playMods", {});
            p.characterState = j.value<std::vector<uint8_t>>("characterState", {});
        }
    };
}
