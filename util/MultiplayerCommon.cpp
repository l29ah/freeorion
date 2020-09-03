#include "MultiplayerCommon.h"

#include "Directories.h"
#include "GameRules.h"
#include "i18n.h"
#include "LoggerWithOptionsDB.h"
#include "OptionsDB.h"
#include "Random.h"
#include "AppInterface.h"


#if defined(_MSC_VER) && defined(int64_t)
#undef int64_t
#endif


const std::string MP_SAVE_FILE_EXTENSION = ".mps";
const std::string SP_SAVE_FILE_EXTENSION = ".sav";


namespace {
    // command-line options
    void AddOptions(OptionsDB& db) {
        db.Add<std::string>("resource.path",                UserStringNop("OPTIONS_DB_RESOURCE_DIR"),           PathToString(GetRootDataDir() / "default"));
        db.Add<std::string>('S', "save.path",               UserStringNop("OPTIONS_DB_SAVE_DIR"),               PathToString(GetUserDataDir() / "save"));
        db.Add<std::string>("save.server.path",             UserStringNop("OPTIONS_DB_SERVER_SAVE_DIR"),        PathToString(GetUserDataDir() / "save"));
        db.Add<std::string>("log-level",                    UserStringNop("OPTIONS_DB_LOG_LEVEL"),              "",
                            OrValidator<std::string>(LogLevelValidator(), DiscreteValidator<std::string>("")),  false);
        db.Add<std::string>("log-file",                     UserStringNop("OPTIONS_DB_LOG_FILE"),               "",
                            Validator<std::string>(),                                                           false);
        // Default stringtable filename is deferred to i18n.cpp::InitStringtableFileName
        db.Add<std::string>("resource.stringtable.path",    UserStringNop("OPTIONS_DB_STRINGTABLE_FILENAME"),   "");
        db.Add("save.format.binary.enabled",                UserStringNop("OPTIONS_DB_BINARY_SERIALIZATION"),   false);
        db.Add("save.format.xml.zlib.enabled",              UserStringNop("OPTIONS_DB_XML_ZLIB_SERIALIZATION"), true);
        db.Add("save.auto.hostless.enabled",                UserStringNop("OPTIONS_DB_AUTOSAVE_HOSTLESS"),      true);
        db.Add("save.auto.hostless.each-player.enabled",    UserStringNop("OPTIONS_DB_AUTOSAVE_HOSTLESS_EACH_PLAYER"), false);
        db.Add<int>("save.auto.interval",                   UserStringNop("OPTIONS_DB_AUTOSAVE_INTERVAL"),      0);
        db.Add<std::string>("load",                         UserStringNop("OPTIONS_DB_LOAD"),                   "",                     Validator<std::string>(), false);
        db.Add("save.auto.exit.enabled",                    UserStringNop("OPTIONS_DB_AUTOSAVE_GAME_CLOSE"),    true);
        db.AddFlag('q', "quickstart",                       UserStringNop("OPTIONS_DB_QUICKSTART"),             false);

        // Common galaxy settings
        db.Add("setup.seed",                UserStringNop("OPTIONS_DB_GAMESETUP_SEED"),                         std::string("0"),       Validator<std::string>());
        db.Add("setup.star.count",          UserStringNop("OPTIONS_DB_GAMESETUP_STARS"),                        150,                    RangedValidator<int>(10, 5000));
        db.Add("setup.galaxy.shape",        UserStringNop("OPTIONS_DB_GAMESETUP_GALAXY_SHAPE"),                 DISC,                   RangedValidator<Shape>(SPIRAL_2, RANDOM));
        db.Add("setup.galaxy.age",          UserStringNop("OPTIONS_DB_GAMESETUP_GALAXY_AGE"),                   GALAXY_SETUP_MEDIUM,    RangedValidator<GalaxySetupOption>(GALAXY_SETUP_LOW, GALAXY_SETUP_RANDOM));
        db.Add("setup.planet.density",      UserStringNop("OPTIONS_DB_GAMESETUP_PLANET_DENSITY"),               GALAXY_SETUP_MEDIUM,    RangedValidator<GalaxySetupOption>(GALAXY_SETUP_LOW, GALAXY_SETUP_RANDOM));
        db.Add("setup.starlane.frequency",  UserStringNop("OPTIONS_DB_GAMESETUP_STARLANE_FREQUENCY"),           GALAXY_SETUP_MEDIUM,    RangedValidator<GalaxySetupOption>(GALAXY_SETUP_LOW, GALAXY_SETUP_RANDOM));
        db.Add("setup.specials.frequency",  UserStringNop("OPTIONS_DB_GAMESETUP_SPECIALS_FREQUENCY"),           GALAXY_SETUP_MEDIUM,    RangedValidator<GalaxySetupOption>(GALAXY_SETUP_NONE, GALAXY_SETUP_RANDOM));
        db.Add("setup.monster.frequency",   UserStringNop("OPTIONS_DB_GAMESETUP_MONSTER_FREQUENCY"),            GALAXY_SETUP_MEDIUM,    RangedValidator<GalaxySetupOption>(GALAXY_SETUP_NONE, GALAXY_SETUP_RANDOM));
        db.Add("setup.native.frequency",    UserStringNop("OPTIONS_DB_GAMESETUP_NATIVE_FREQUENCY"),             GALAXY_SETUP_MEDIUM,    RangedValidator<GalaxySetupOption>(GALAXY_SETUP_NONE, GALAXY_SETUP_RANDOM));
        db.Add("setup.ai.player.count",     UserStringNop("OPTIONS_DB_GAMESETUP_NUM_AI_PLAYERS"),               6,                      RangedValidator<int>(0, IApp::MAX_AI_PLAYERS()));
        db.Add("setup.ai.aggression",       UserStringNop("OPTIONS_DB_GAMESETUP_AI_MAX_AGGRESSION"),            MANIACAL,               RangedValidator<Aggression>(BEGINNER, MANIACAL));


        // AI Testing options-- the following options are to facilitate AI testing and do not currently have an options page widget;
        // they are intended to be changed via the command line and are not currently storable in the configuration file.
        db.Add<std::string>("ai-path",                      UserStringNop("OPTIONS_DB_AI_FOLDER_PATH"),         "python/AI",
                            Validator<std::string>(),                                                           false);
        db.Add<std::string>("ai-config",                    UserStringNop("OPTIONS_DB_AI_CONFIG"),              "",
                            Validator<std::string>(),                                                           false);
    }
    bool temp_bool = RegisterOptions(&AddOptions);

    void AddRules(GameRules& rules) {
        rules.Add<int>("RULE_THRESHOLD_HUMAN_PLAYER_WIN", "RULE_THRESHOLD_HUMAN_PLAYER_WIN_DESC",
                       "MULTIPLAYER", 0, true,  RangedValidator<int>(0, 999));

        rules.Add<bool>("RULE_ONLY_ALLIANCE_WIN", "RULE_ONLY_ALLIANCE_WIN_DESC",
                       "MULTIPLAYER", true, true);

        rules.Add<bool>("RULE_ALLOW_CONCEDE", "RULE_ALLOW_CONCEDE_DESC",
                       "MULTIPLAYER", false, true);

        rules.Add<int>("RULE_CONCEDE_COLONIES_THRESHOLD", "RULE_CONCEDE_COLONIES_THRESHOLD_DESC",
                       "MULTIPLAYER", 1, true,  RangedValidator<int>(0, 9999));
    }
    bool temp_bool2 = RegisterGameRules(&AddRules);

    const std::string EMPTY_STRING;
}

/////////////////////////////////////////////////////
// GalaxySetupData
/////////////////////////////////////////////////////
namespace {
    // returns number in range 0 to one less than the interger representation of
    // enum_vals_count, determined by the random seed
    template <typename T1>
    int GetIdx(const T1& enum_vals_count, const std::string& seed) {
        DebugLogger() << "hashing seed: " << seed;
        // use probably-bad but adequate for this purpose hash function to
        // convert seed into a hash value
        int hash_value = 223;
        for (size_t i = 0; i < seed.length(); ++i) {
            //DebugLogger() << "hash value: " << hash_value << " char: " << static_cast<int>(seed[i]);
            hash_value += (seed[i] * 61);
            hash_value %= 191;
        }
        DebugLogger() << "final hash value: " << hash_value
                      << " and returning: " << hash_value % static_cast<int>(enum_vals_count)
                      << " from 0 to " << static_cast<int>(enum_vals_count) - 1;
        return hash_value % static_cast<int>(enum_vals_count);
    }

    static char alphanum[] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
}

const std::string& TextForGalaxySetupSetting(GalaxySetupOption gso) {
    switch (gso) {
        case GALAXY_SETUP_NONE:     return UserString("GSETUP_NONE");
        case GALAXY_SETUP_LOW:      return UserString("GSETUP_LOW");
        case GALAXY_SETUP_MEDIUM:   return UserString("GSETUP_MEDIUM");
        case GALAXY_SETUP_HIGH:     return UserString("GSETUP_HIGH");
        case GALAXY_SETUP_RANDOM:   return UserString("GSETUP_RANDOM");
        default:                    return EMPTY_STRING;
    }
}

const std::string& TextForGalaxyShape(Shape shape) {
    switch (shape) {
        case SPIRAL_2:      return UserString("GSETUP_2ARM");
        case SPIRAL_3:      return UserString("GSETUP_3ARM");
        case SPIRAL_4:      return UserString("GSETUP_4ARM");
        case CLUSTER:       return UserString("GSETUP_CLUSTER");
        case ELLIPTICAL:    return UserString("GSETUP_ELLIPTICAL");
        case DISC:          return UserString("GSETUP_DISC");
        case BOX:           return UserString("GSETUP_BOX");
        case IRREGULAR:     return UserString("GSETUP_IRREGULAR");
        case RING:          return UserString("GSETUP_RING");
        case RANDOM:        return UserString("GSETUP_RANDOM");
        default:            return EMPTY_STRING;
    }
}

const std::string& TextForAIAggression(Aggression a) {
    switch (a) {
        case BEGINNER:      return UserString("GSETUP_BEGINNER");
        case TURTLE:        return UserString("GSETUP_TURTLE");
        case CAUTIOUS:      return UserString("GSETUP_CAUTIOUS");
        case TYPICAL:       return UserString("GSETUP_TYPICAL");
        case AGGRESSIVE:    return UserString("GSETUP_AGGRESSIVE");
        case MANIACAL:      return UserString("GSETUP_MANIACAL");
        default:            return EMPTY_STRING;
    }
}

GalaxySetupData::GalaxySetupData() :
    size(100),
    shape(SPIRAL_2),
    age(GALAXY_SETUP_MEDIUM),
    starlane_freq(GALAXY_SETUP_MEDIUM),
    planet_density(GALAXY_SETUP_MEDIUM),
    specials_freq(GALAXY_SETUP_MEDIUM),
    monster_freq(GALAXY_SETUP_MEDIUM),
    native_freq(GALAXY_SETUP_MEDIUM),
    ai_aggr(MANIACAL),
    encoding_empire(ALL_EMPIRES)
{}

GalaxySetupData::GalaxySetupData(GalaxySetupData&& base) :
    seed(std::move(base.seed)),
    size(base.size),
    shape(base.shape),
    age(base.age),
    starlane_freq(base.starlane_freq),
    planet_density(base.planet_density),
    specials_freq(base.specials_freq),
    monster_freq(base.monster_freq),
    native_freq(base.native_freq),
    ai_aggr(base.ai_aggr),
    game_rules(std::move(base.game_rules)),
    game_uid(std::move(base.game_uid)),
    encoding_empire(base.encoding_empire)
{ SetSeed(seed); }

const std::string& GalaxySetupData::GetSeed() const
{ return seed; }

int GalaxySetupData::GetSize() const
{ return size; }

Shape GalaxySetupData::GetShape() const {
    if (shape != RANDOM)
        return shape;
    size_t num_shapes = static_cast<size_t>(GALAXY_SHAPES) - 1; // -1 so that RANDOM isn't counted
    return static_cast<Shape>(GetIdx(num_shapes, seed + "shape"));
}

GalaxySetupOption GalaxySetupData::GetAge() const {
    if (age != GALAXY_SETUP_RANDOM)
        return age;
    return static_cast<GalaxySetupOption>(GetIdx(3, seed + "age") + 1);       // need range 1-3 for age
}

GalaxySetupOption GalaxySetupData::GetStarlaneFreq() const {
    if (starlane_freq != GALAXY_SETUP_RANDOM)
        return starlane_freq;
    return static_cast<GalaxySetupOption>(GetIdx(3, seed + "lanes") + 1);     // need range 1-3 for starlane freq
}

GalaxySetupOption GalaxySetupData::GetPlanetDensity() const {
    if (planet_density != GALAXY_SETUP_RANDOM)
        return planet_density;
    return static_cast<GalaxySetupOption>(GetIdx(3, seed + "planets") + 1);   // need range 1-3 for planet density
}

GalaxySetupOption GalaxySetupData::GetSpecialsFreq() const {
    if (specials_freq != GALAXY_SETUP_RANDOM)
        return specials_freq;
    return static_cast<GalaxySetupOption>(GetIdx(4, seed + "specials"));      // need range 0-3 for planet density
}

GalaxySetupOption GalaxySetupData::GetMonsterFreq() const {
    if (monster_freq != GALAXY_SETUP_RANDOM)
        return monster_freq;
    return static_cast<GalaxySetupOption>(GetIdx(4, seed + "monsters"));      // need range 0-3 for monster frequency
}

GalaxySetupOption GalaxySetupData::GetNativeFreq() const {
    if (native_freq != GALAXY_SETUP_RANDOM)
        return native_freq;
    return static_cast<GalaxySetupOption>(GetIdx(4, seed + "natives"));       // need range 0-3 for native frequency
}

Aggression GalaxySetupData::GetAggression() const
{ return ai_aggr; }

const std::map<std::string, std::string>& GalaxySetupData::GetGameRules() const
{ return game_rules; }

const std::string& GalaxySetupData::GetGameUID() const
{ return game_uid; }

void GalaxySetupData::SetSeed(const std::string& seed_) {
    std::string new_seed = seed_;
    if (new_seed.empty() || new_seed == "RANDOM") {
        ClockSeed();
        new_seed.clear();
        for (int i = 0; i < 8; ++i)
            new_seed += alphanum[RandInt(0, (sizeof(alphanum) - 2))];
        DebugLogger() << "Set empty or requested random seed to " << new_seed;
    }
    seed = std::move(new_seed);
}

void GalaxySetupData::SetGameUID(const std::string& game_uid_)
{ game_uid = game_uid_; }

/////////////////////////////////////////////////////
// PlayerSetupData
/////////////////////////////////////////////////////
bool operator==(const PlayerSetupData& lhs, const PlayerSetupData& rhs) {
    return  lhs.client_type == rhs.client_type &&
            lhs.empire_color == rhs.empire_color &&
            lhs.empire_name == rhs.empire_name &&
            lhs.player_name == rhs.player_name &&
            lhs.save_game_empire_id == rhs.save_game_empire_id &&
            lhs.starting_species_name == rhs.starting_species_name &&
            lhs.player_ready == rhs.player_ready &&
            lhs.starting_team == rhs.starting_team;
}

bool operator!=(const PlayerSetupData& lhs, const PlayerSetupData& rhs)
{ return !(lhs == rhs); }


////////////////////////////////////////////////////
// MultiplayerLobbyData
/////////////////////////////////////////////////////
std::string MultiplayerLobbyData::Dump() const {
    std::stringstream stream;
    for (const std::pair<int, PlayerSetupData>& psd : players) {
        stream << psd.first << ": " << (psd.second.player_name.empty() ? "NO NAME" : psd.second.player_name) << "  ";
        if (psd.second.client_type == Networking::CLIENT_TYPE_AI_PLAYER)
            stream << "AI PLAYER";
        else if (psd.second.client_type == Networking::CLIENT_TYPE_HUMAN_PLAYER)
            stream << "HUMAN PLAYER";
        else if (psd.second.client_type == Networking::CLIENT_TYPE_HUMAN_OBSERVER)
            stream << "HUMAN OBSERVER";
        else if (psd.second.client_type == Networking::CLIENT_TYPE_HUMAN_MODERATOR)
            stream << "HUMAN MODERATOR";
        else
            stream << "UNKNOWN CLIENT TPYE";
        stream << "  " << (psd.second.empire_name.empty() ? "NO EMPIRE NAME" : psd.second.empire_name) << "\n";
    }
    return stream.str();
}

