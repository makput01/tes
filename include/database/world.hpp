#pragma once
#ifndef WORLD_HPP
#define WORLD_HPP

    class block 
    {
    public:
        block(
            short _fg = 0, short _bg = 0, 
            bool __public = false, bool _toggled = false, std::chrono::steady_clock::time_point _tick = std::chrono::steady_clock::time_point(),
            std::string _label = ""
        ) : fg(_fg), bg(_bg), _public(__public), toggled(_toggled), tick(_tick), label(_label) {}
        short fg{0}, bg{0};
        
        bool _public{}; // @note tile can be interacted by anyone in the world
        bool toggled{}; // @note save toggle state
        std::chrono::steady_clock::time_point tick{}; // @note record a point in time for the tile e.g. tree growth, providers, ect.
        std::string label{}; // @note sign/door label
        bool water{};
        bool glue{};
        bool fire{};

        std::array<int, 2zu> hits{0, 0}; // @note fg, bg
    };
    #define cord(x,y) (y * 100 + x)

    class tamagotchi
    {
    public:
        std::string name{};
        std::array<int, 2zu> pos;
    };

    class door 
    {
    public:
        door(std::string _dest, std::string _id, std::string _password, std::array<int, 2zu> _pos) : 
            dest(_dest), id(_id), password(_password), pos(_pos) {}

        std::string dest{};
        std::string id{};
        std::string password{};
        std::array<int, 2zu> pos;
    };

    class ifloat 
    {
    public:
        ifloat(short _id, short _count, std::array<float, 2zu> _pos) : id(_id), count(_count), pos(_pos) {}
        short id{0};
        short count{0};
        std::array<float, 2zu> pos;
    };

    class world 
    {
    public:
        world(const std::string& name = "");
        std::string name{};

        int owner{ 00 }; // @note owner of world using peer's user id.
        std::array<int, 6zu> admin{}; // @note admins (by user id). excluding owner. (6 is a experimental amount, if increase update me if any issue occur -leeendl)
        bool _public{}; // @note checks if world is public to break/place

        u_char visitors{0}; // @note the current number of peers in a world, excluding invisable peers

        std::vector<::block> blocks; // @note all blocks, size of 1D meaning (6000) instead of 2D (100, 60)
        std::vector<::tamagotchi> tamagotchi_tachi;
        std::vector<::door> doors;
        int ifloat_uid{0}; // @note floating item UID
        std::unordered_map<int, ifloat> ifloats{}; // @note (i)tem floating
        ~world();
    };
    extern std::unordered_map<std::string, world> worlds;

    extern void send_data(ENetPeer& peer, const std::vector<std::byte> &&data);

    extern void state_visuals(ENetEvent& event, state &&s);

    extern void tile_apply_damage(ENetEvent& event, state s, block& b);

    extern void modify_item_inventory(ENetEvent& event, const std::array<short, 2zu>& im);

    extern int item_change_object(ENetEvent& event, const std::array<short, 2zu>& im, const std::array<float, 2zu>& pos, signed uid = 0);

    extern void tile_update(ENetEvent &event, state s, block &b, world& w);

    void generate_world(world &world, const std::string& name);

    bool door_mover(world &world, const std::array<int, 2ULL> &pos);

    namespace blast
    {
        void thermonuclear(world &world, const std::string& name);
    }

#endif