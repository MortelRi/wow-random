#include <iostream>
#include <random>
#include <map>
#include <chrono>
#include <thread>
#include <string>

enum class Fraction
{
    ALLIANCE = 0,
    HORDE,

    UNKNOWN
};

enum class Races
{
    // Alliance
    HUMAN = 0,
    DWARF,
    NIGHT_ELF,
    GNOME,

    // Horde
    ORC = 4,
    UNDEAD,
    TAUREN,
    TROLL,

    UNKNOWN
};

enum class Classes
{
    PALADIN = 0,
    ROGUE,
    WARRIOR,
    DRUID,
    PRIEST,
    MAGE,
    HUNTER,
    WARLOCK,
    SHAMAN,

    UNKNOWN
};

std::ostream &operator<<(std::ostream &os, const Fraction &obj)
{
    switch (obj)
    {
    case Fraction::ALLIANCE:
        os << "Alliance";
        break;
    case Fraction::HORDE:
        os << "Horde";
        break;
    case Fraction::UNKNOWN:
        os << "Unknown";
        break;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const Races &obj)
{
    switch (obj)
    {
    case Races::HUMAN:
        os << "Human";
        break;
    case Races::DWARF:
        os << "Dwarf";
        break;
    case Races::NIGHT_ELF:
        os << "Night Elf";
        break;
    case Races::GNOME:
        os << "Gnome";
        break;
    case Races::ORC:
        os << "Orc";
        break;
    case Races::UNDEAD:
        os << "Undead";
        break;
    case Races::TAUREN:
        os << "Tauren";
        break;
    case Races::TROLL:
        os << "Troll";
        break;
    case Races::UNKNOWN:
        os << "Unknown";
        break;
    }

    return os;
}

std::ostream &operator<<(std::ostream &os, const Classes &obj)
{
    switch (obj)
    {
    case Classes::DRUID:
        os << "Druid";
        break;
    case Classes::HUNTER:
        os << "Hunter";
        break;
    case Classes::MAGE:
        os << "Mage";
        break;
    case Classes::PALADIN:
        os << "Paladin";
        break;
    case Classes::ROGUE:
        os << "Rogue";
        break;
    case Classes::SHAMAN:
        os << "Shaman";
        break;
    case Classes::WARLOCK:
        os << "Warlock";
        break;
    case Classes::WARRIOR:
        os << "Warrior";
        break;
    case Classes::PRIEST:
        os << "Priest";
        break;
    case Classes::UNKNOWN:
        os << "Unknown";
        break;
    }

    return os;
}

Fraction get_fraction(const Races &race)
{
    switch (race)
    {
    case Races::HUMAN:
    case Races::DWARF:
    case Races::NIGHT_ELF:
    case Races::GNOME:
        return Fraction::ALLIANCE;
    case Races::ORC:
    case Races::UNDEAD:
    case Races::TAUREN:
    case Races::TROLL:
        return Fraction::HORDE;
    case Races::UNKNOWN:
        return Fraction::UNKNOWN;
    }

    throw std::runtime_error("Something wrong in get_fraction!");
}

template <typename T>
T randomize(unsigned long long size)
{
    using time = std::chrono::high_resolution_clock;
    std::mt19937 gen(static_cast<uint32_t>(time::now().time_since_epoch().count()));
    std::uniform_int_distribution<unsigned long long> dis(0, std::numeric_limits<int>::max());
    return static_cast<T>(dis(gen) % size);
}

int main()
{
    std::map<Races, std::vector<Classes>> full_map =
    {
        {Races::HUMAN, {Classes::WARRIOR, Classes::ROGUE, Classes::PRIEST, Classes::PALADIN, Classes::WARLOCK, Classes::MAGE}},
        {Races::DWARF, {Classes::WARRIOR, Classes::ROGUE, Classes::PRIEST, Classes::PALADIN, Classes::HUNTER}},
        {Races::NIGHT_ELF, {Classes::WARRIOR, Classes::ROGUE, Classes::PRIEST, Classes::HUNTER, Classes::DRUID}},
        {Races::GNOME, {Classes::WARRIOR, Classes::ROGUE, Classes::MAGE, Classes::WARLOCK}},
        {Races::ORC, {Classes::WARRIOR, Classes::ROGUE, Classes::HUNTER, Classes::WARLOCK, Classes::SHAMAN}},
        {Races::UNDEAD, {Classes::WARRIOR, Classes::ROGUE, Classes::PRIEST, Classes::WARLOCK, Classes::MAGE}},
        {Races::TAUREN, {Classes::WARRIOR, Classes::DRUID, Classes::HUNTER, Classes::SHAMAN}},
        {Races::TROLL, {Classes::WARRIOR, Classes::ROGUE, Classes::PRIEST, Classes::HUNTER, Classes::SHAMAN, Classes::MAGE}}
    };

    auto fraction = Fraction::UNKNOWN;
    auto race = Races::UNKNOWN;
    auto ur_class = Classes::UNKNOWN;

    try
    {
        auto race_classes = full_map.find(randomize<Races>(full_map.size()));
        if (race_classes != full_map.end())
        {
            race = race_classes->first;
            fraction = get_fraction(race);
            auto class_vec = race_classes->second;
            ur_class = class_vec.at(randomize<size_t>(class_vec.size()));
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    std::cout << fraction << " " << race << " " << ur_class << std::endl;

    return 0;
}
