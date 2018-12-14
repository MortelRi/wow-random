#include <iostream>
#include <random>
#include <map>
#include <chrono>
#include <thread>
#include <string>

enum class Expension
{
    CLASSIC = 0,
    TBC,
    WOTLK,

    UNKNOWN
};

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

    // TBC
    DRAENEI = 8,
    BLOOD_ELF,

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

    //WOTLK
    DEATH_KNIGHT = 9,

    UNKNOWN
};

std::istream &operator>>(std::istream &is, Expension &obj)
{
    int n;
    is >> n;
    --n;
    switch(static_cast<Expension>(n))
    {
    case Expension::CLASSIC:
        obj = Expension::CLASSIC;
        break;
    case Expension::TBC:
        obj = Expension::TBC;
        break;
    case Expension::WOTLK:
        obj = Expension::WOTLK;
        break;
    default:
        obj = Expension::UNKNOWN;
        break;
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const Expension &obj)
{
    switch (obj)
    {
    case Expension::CLASSIC:
        os << "Classic";
        break;
    case Expension::TBC:
        os << "The Burning Crusade";
        break;
    case Expension::WOTLK:
        os << "Wrath of the Lich King";
        break;
    case Expension::UNKNOWN:
        os << "Unknown";
        break;
    }
    return os;
}

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
    case Races::DRAENEI:
        os << "Draenei";
        break;
    case Races::BLOOD_ELF:
        os << "Blood Elf";
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
    case Classes::DEATH_KNIGHT:
        os << "Death Knight";
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
    case Races::DRAENEI:
        return Fraction::ALLIANCE;
    case Races::ORC:
    case Races::UNDEAD:
    case Races::TAUREN:
    case Races::TROLL:
    case Races::BLOOD_ELF:
        return Fraction::HORDE;
    case Races::UNKNOWN:
        return Fraction::UNKNOWN;
    }

    throw std::runtime_error("Something wrong in get_fraction!");
}

template <typename T>
T randomize(size_t size)
{
    using time = std::chrono::high_resolution_clock;
    std::mt19937 gen(static_cast<uint32_t>(time::now().time_since_epoch().count()));
    std::uniform_int_distribution<size_t> dis(0, std::numeric_limits<int>::max());
    return static_cast<T>(dis(gen) % size);
}

int main()
{
    std::cout << "Welcome to World of Warcraft Character Randomizer!\n\nSelect your Expension:" << std::endl;
    for (int i = static_cast<int>(Expension::CLASSIC); i < static_cast<int>(Expension::UNKNOWN); ++i)
    {
        std::cout << "[" << i + 1 << "]\t" << static_cast<Expension>(i) << "\n";
    }

    auto expension = Expension::UNKNOWN;

    while (expension == Expension::UNKNOWN)
    {
        std::cin >> expension;
    };

    std::cout << "Selected Expension is " << expension << "\n\nYour Character [Fraction | Race | Class]:" << std::endl;

    std::map<Races, std::vector<Classes>> fullMap =
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

    if(expension == Expension::TBC || expension == Expension::WOTLK)
    {
        fullMap.emplace(Races::DRAENEI, std::vector<Classes>{Classes::WARRIOR, Classes::PALADIN, Classes::HUNTER, Classes::PRIEST, Classes::SHAMAN, Classes::MAGE});
        fullMap.emplace(Races::BLOOD_ELF, std::vector<Classes>{Classes::PALADIN, Classes::HUNTER, Classes::ROGUE, Classes::PRIEST, Classes::MAGE, Classes::WARLOCK});

        if(expension == Expension::WOTLK)
        {
            for(auto &raceClasses : fullMap)
            {
                raceClasses.second.push_back(Classes::DEATH_KNIGHT);
            }
        }
    }

    auto fraction = Fraction::UNKNOWN;
    auto race = Races::UNKNOWN;
    auto klass = Classes::UNKNOWN;

    try
    {
        auto raceClasses = fullMap.find(randomize<Races>(fullMap.size()));
        if (raceClasses != fullMap.end())
        {
            race = raceClasses->first;
            fraction = get_fraction(race);
            auto classVector = raceClasses->second;
            klass = classVector.at(randomize<size_t>(classVector.size()));
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    std::cout << fraction << " | " << race << " | " << klass << std::endl;
    return 0;
}
