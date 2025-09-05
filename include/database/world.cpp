#include "pch.hpp"
#include "items.hpp"
#include "peer.hpp"
#include "tools/ransuu.hpp"
#include "world.hpp"

#if defined(_MSC_VER)
    using namespace std::chrono;
#else
    using namespace std::chrono::_V2;
#endif
using namespace std::literals::chrono_literals;

class world_db {
private:
    sqlite3* db;

    void sqlite3_bind(sqlite3_stmt* stmt, int index, int value) 
    {
        sqlite3_bind_int(stmt, index, value);
    }
    void sqlite3_bind(sqlite3_stmt* stmt, int index, const std::string& value) 
    {
        sqlite3_bind_text(stmt, index, value.c_str(), -1, SQLITE_STATIC);
    }
public:
    world_db() {
        sqlite3_open("db/worlds.db", &db);
        create_tables();
    }~world_db() { sqlite3_close(db); }
    
    void create_tables() 
    {
        const char* sql = 
        "CREATE TABLE IF NOT EXISTS worlds (_n TEXT PRIMARY KEY, owner INTEGER, pub BOOLEAN);"

        "CREATE TABLE IF NOT EXISTS blocks ("
            "_n TEXT, _p INTEGER, fg INTEGER, bg INTEGER, pub BOOLEAN, tog BOOLEAN, tick INTEGER, l TEXT,"
            "water BOOLEAN, glue BOOLEAN, fire BOOLEAN,"
            "PRIMARY KEY (_n, _p),"
            "FOREIGN KEY (_n) REFERENCES worlds(_n)"
        ");"

        "CREATE TABLE IF NOT EXISTS ifloats ("
            "_n TEXT, uid INTEGER, i INTEGER, c INTEGER, x REAL, y REAL,"
            "PRIMARY KEY (_n, uid),"
            "FOREIGN KEY (_n) REFERENCES worlds(_n)"
        ");";
        sqlite3_exec(db, sql, nullptr, nullptr, nullptr);
    }
    
    template<typename F>
    void execute(const char* sql, F binder) 
    {
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) 
        {
            binder(stmt);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        }
    }
    
    template<typename F>
    void query(const char* sql, F &&processor, const std::string &name) 
    {
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) 
        {
            sqlite3_bind(stmt, 1, name);
            
            while (sqlite3_step(stmt) == SQLITE_ROW) 
            {
                processor(stmt);
            }
            sqlite3_finalize(stmt);
        }
    }
    
    void begin_transaction() {
        sqlite3_exec(db, "BEGIN TRANSACTION", nullptr, nullptr, nullptr);
    }
    
    void commit() {
        sqlite3_exec(db, "COMMIT", nullptr, nullptr, nullptr);
    }
};

world::world(const std::string& name) 
{
    world_db db;
    
    db.query("SELECT owner, pub FROM worlds WHERE _n = ?", [this, &name](sqlite3_stmt* stmt) 
    {
            this->owner = sqlite3_column_int(stmt, 0);
            this->_public = sqlite3_column_int(stmt, 1);
            this->name = name;
    }, name);

    blocks.resize(6000);
    db.query("SELECT _p, fg, bg, pub, tog, tick, l FROM blocks WHERE _n = ?", [this](sqlite3_stmt* stmt) 
    {
            int pos = sqlite3_column_int(stmt, 0);
            blocks[pos] = block(
                sqlite3_column_int(stmt, 1),
                sqlite3_column_int(stmt, 2),
                sqlite3_column_int(stmt, 3),
                sqlite3_column_int(stmt, 4),
                std::chrono::steady_clock::time_point(std::chrono::seconds(sqlite3_column_int(stmt, 5))),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6))
            );
    }, name);
     db.query("SELECT uid, i, c, x, y FROM ifloats WHERE _n = ?", [this](sqlite3_stmt* stmt) 
     {
            int uid = sqlite3_column_int(stmt, 0);
            ifloats.emplace(uid, ifloat(
                sqlite3_column_int(stmt, 1),
                sqlite3_column_int(stmt, 2),
                {
                    static_cast<float>(sqlite3_column_double(stmt, 3)), // @todo
                    static_cast<float>(sqlite3_column_double(stmt, 4)) // @todo
                }
            ));
            ifloat_uid = std::max(ifloat_uid, uid);
    }, name);
}

world::~world() 
{
    if (name.empty()) return;
    
    world_db db;
    db.begin_transaction();
    
    db.execute("REPLACE INTO worlds (_n, owner, pub) VALUES (?, ?, ?)", [this](sqlite3_stmt* stmt) 
    {
            sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 2, owner);
            sqlite3_bind_int(stmt, 3, _public);
    });
    
    db.execute("DELETE FROM blocks WHERE _n = ?", [this](auto stmt) {
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    });
    
    for (int pos = 0; pos < blocks.size(); pos++) {
        const block &b = blocks[pos];
        db.execute("INSERT INTO blocks (_n, _p, fg, bg, pub, tog, tick, l, water, glue, fire) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", [this, &b, &pos](sqlite3_stmt* stmt) 
        {
            int i = 1;
            sqlite3_bind_text(stmt, i++, name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, i++, pos);
            sqlite3_bind_int(stmt, i++, b.fg);
            sqlite3_bind_int(stmt, i++, b.bg);
            sqlite3_bind_int(stmt, i++, b._public);
            sqlite3_bind_int(stmt, i++, b.toggled);
            sqlite3_bind_int(stmt, i++, 
                static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(
                    b.tick.time_since_epoch()).count()));
            sqlite3_bind_text(stmt, i++, b.label.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, i++, b.water);
            sqlite3_bind_int(stmt, i++, b.glue);
            sqlite3_bind_int(stmt, i++, b.fire);
        });
    }

    db.execute("DELETE FROM ifloats WHERE _n = ?", [this](auto stmt) {
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    });
    
    for (const auto& [uid, item] : ifloats) 
    {
        db.execute("INSERT INTO ifloats (_n, uid, i, c, x, y) VALUES (?, ?, ?, ?, ?, ?)", [&](sqlite3_stmt* stmt) 
        {
            int i = 1;
            sqlite3_bind_text(stmt, i++, name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, i++, uid);
            sqlite3_bind_int(stmt, i++, item.id);
            sqlite3_bind_int(stmt, i++, item.count);
            sqlite3_bind_double(stmt, i++, item.pos[0]);
            sqlite3_bind_double(stmt, i++, item.pos[1]);
        });
    }
    
    db.commit();
}

std::unordered_map<std::string, world> worlds;

void send_data(ENetPeer& peer, const std::vector<std::byte> &&data)
{
    std::size_t size = data.size();
    ENetPacket *packet = enet_packet_create(nullptr, size + 5zu, ENET_PACKET_FLAG_RELIABLE);

    *reinterpret_cast<int*>(&packet->data[0]) = 04;
    std::memcpy(packet->data + 4, data.data(), size);
    
    enet_peer_send(&peer, 1, packet);
}

void state_visuals(ENetEvent& event, state &&state) 
{
    peers(event, PEER_SAME_WORLD, [&](ENetPeer& p) 
    {
        send_data(p, compress_state(state));
    });
}

void tile_apply_damage(ENetEvent& event, state state, block &block)
{
    (block.fg == 0) ? ++block.hits.back() : ++block.hits.front();
    state.type = 0x08; // @note PACKET_TILE_APPLY_DAMAGE
    state.id = 6; // @note idk exactly
    state.netid = _peer[event.peer]->netid;
	state_visuals(event, std::move(state));
}

void modify_item_inventory(ENetEvent& event, const std::array<short, 2zu>& im)
{
    ::state state{
        .type = (im[1] << 16) | 0x0d, // @noote 0x00{}000d
        .id = im[0]
    };
    state_visuals(event, std::move(state));
}

int item_change_object(ENetEvent& event, const std::array<short, 2zu>& im, const std::array<float, 2zu>& pos, signed uid) 
{
    state state{.type = 0x0e}; // @note PACKET_ITEM_CHANGE_OBJECT

    auto w = worlds.find(_peer[event.peer]->recent_worlds.back());
    if (w == worlds.end()) return -1;

    auto f = std::find_if(w->second.ifloats.begin(), w->second.ifloats.end(), [&](const std::pair<const int, ifloat>& entry) {
        return uid == 0 && entry.second.id == im[0] && entry.second.pos == pos;
    });
    if (f != w->second.ifloats.end()) // @note merge drop
    {
        f->second.count += im[1];
        state.netid = -3; // @note fd ff ff ff
        state.uid = f->first;
        state.count = static_cast<float>(f->second.count);
        state.id = f->second.id;
        state.pos = {f->second.pos[0] * 32, f->second.pos[1] * 32};
    }
    else if (im[1] == 0 || im[0] == 0) // @note remove drop
    {
        state.netid = _peer[event.peer]->netid;
        state.uid = -1;
        state.id = uid;
    }
    else // @note add new drop
    {
        auto it = w->second.ifloats.emplace(++w->second.ifloat_uid, ifloat{im[0], im[1], pos}); // @note a iterator ahead of time
        state.netid = -1;
        state.uid = it.first->first;
        state.count = static_cast<float>(im[1]);
        state.id = it.first->second.id;
        state.pos = {it.first->second.pos[0] * 32, it.first->second.pos[1] * 32};
    }
    state_visuals(event, std::move(state));
    return state.uid;
}

void tile_update(ENetEvent &event, state state, block &block, world& w) 
{
    state.type = 05; // @note PACKET_SEND_TILE_UPDATE_DATA
    state.peer_state = 0x08;
    std::vector<std::byte> data = compress_state(state);

    short pos = 56;
    data.resize(pos + 8zu); // @note {2} {2} 00 00 00 00
    *reinterpret_cast<short*>(&data[pos]) = block.fg; pos += sizeof(short);
    *reinterpret_cast<short*>(&data[pos]) = block.bg; pos += sizeof(short);
    pos += sizeof(short);
    pos += sizeof(short);
    
    if (block.water) data[pos - 1zu] |= std::byte{ 0x04 };
    if (block.glue)  data[pos - 1zu] |= std::byte{ 0x08 };
    if (block.fire)  data[pos - 1zu] |= std::byte{ 0x10 };
    // @todo add paint...
    switch (items[block.fg].type)
    {
        case type::ENTRANCE:
        {
            data[pos - 2zu] = (block._public) ? std::byte{ 0x90 } : std::byte{ 0x10 };
            break;
        }
        case type::DOOR:
        case type::PORTAL:
        {
            data[pos - 2zu] = std::byte{ 01 };
            short len = block.label.length();
            data.resize(pos + 1zu + 2zu + len + 1zu); // @note 01 {2} {} 0 0

            data[pos] = std::byte{ 01 }; pos += sizeof(std::byte);
            
            *reinterpret_cast<short*>(&data[pos]) = len; pos += sizeof(short);
            for (const char& c : block.label) data[pos++] = static_cast<std::byte>(c);
            pos += sizeof(std::byte); // @note '\0'
            break;
        }
        case type::SIGN:
        {
            data[pos - 2zu] = std::byte{ 0x19 };
            short len = block.label.length();
            data.resize(pos + 1zu + 2zu + len + 4zu); // @note 02 {2} {} ff ff ff ff

            data[pos] = std::byte{ 02 }; pos += sizeof(std::byte);

            *reinterpret_cast<short*>(&data[pos]) = len; pos += sizeof(short);
            for (const char& c : block.label) data[pos++] = static_cast<std::byte>(c);
            *reinterpret_cast<int*>(&data[pos]) = -1; pos += sizeof(int); // @note ff ff ff ff
            break;
        }
        case type::SEED:
        {
            data[pos - 2zu] = std::byte{ 0x11 };
            data.resize(pos + 1zu + 5zu);

            data[pos++] = std::byte{ 04 };
            *reinterpret_cast<short*>(&data[pos]) = (steady_clock::now() - block.tick) / 1s; pos += sizeof(short);
            *reinterpret_cast<short*>(&data[pos]) = (steady_clock::now() - block.tick) / 24h; pos += sizeof(short); // @todo confirm this
            data[pos++] = std::byte{ 03 }; // @note fruit on tree
            break;
        }
    }

    peers(event, PEER_SAME_WORLD, [&](ENetPeer& p) 
    {
        send_data(p, std::move(data));
    });
}

void generate_world(world &world, const std::string& name)
{
    ransuu ransuu;
    u_short main_door = ransuu[{2, 100 * 60 / 100 - 4}];
    std::vector<block> blocks(100 * 60, block{0, 0});
    
    for (auto &&[i, block] : blocks | std::views::enumerate)
    {
        if (i >= cord(0, 37))
        {
            block.bg = 14; // @note cave background
            if (i >= cord(0, 38) && i < cord(0, 50) /* (above) lava level */ && ransuu[{0, 38}] <= 1) block.fg = 10 /* rock */;
            else if (i > cord(0, 50) && i < cord(0, 54) /* (above) bedrock level */ && ransuu[{0, 8}] < 3) block.fg = 4 /* lava */;
            else block.fg = (i >= cord(0, 54)) ? 8 : 2;
        }
        if (i == cord(main_door, 36)) block.fg = 6; // @note main door
        else if (i == cord(main_door, 37)) block.fg = 8; // @note bedrock (below main door)
    }
    world.blocks = std::move(blocks);
    world.name = std::move(name);
}

bool door_mover(world &world, const std::array<int, 2ULL> &pos)
{
    if (world.blocks[cord(pos[0], pos[1])].fg != 0 ||
        world.blocks[cord(pos[0], (pos[1] + 1))].fg != 0) return false;

    for (std::size_t i = 0; i < world.blocks.size(); ++i)
    {
        block &block = world.blocks[i];
        if (block.fg == 6)
        {
            block.fg = 0; // @note remove main door
            world.blocks[cord(i % 100, (i / 100 + 1))].fg = 0; // @note remove bedrock (below main door)
            break;
        }
    }
    world.blocks[cord(pos[0], pos[1])].fg = 6;
    world.blocks[cord(pos[0], (pos[1] + 1))].fg = 8;
    return true;
}

void blast::thermonuclear(world &world, const std::string& name)
{
    ransuu ransuu;
    u_short main_door = ransuu[{2, 100 * 60 / 100 - 4}];
    std::vector<block> blocks(100 * 60, block{0, 0});
    
    for (auto &&[i, block] : blocks | std::views::enumerate)
    {
        block.fg = (i >= cord(0, 54)) ? 8 : 0;

        if (i == cord(main_door, 36)) block.fg = 6;
        else if (i == cord(main_door, 37)) block.fg = 8;
    }
    world.blocks = std::move(blocks);
    world.name = std::move(name);
}
