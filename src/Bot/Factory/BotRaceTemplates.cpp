/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BotRaceTemplates.h"

#include "DatabaseEnv.h"
#include "Field.h"
#include "QueryResult.h"
#include "RaceMgr.h"
#include "StringConvert.h"
#include "Tokenize.h"

#include <unordered_map>

namespace
{
    struct BotRaceTemplate
    {
        bool hasNameRace = false;
        uint8 nameRace = 0;
        std::vector<uint32> mounts;
    };

    std::unordered_map<uint8, BotRaceTemplate> const& GetTemplates()
    {
        static std::unordered_map<uint8, BotRaceTemplate> const templates = []
        {
            std::unordered_map<uint8, BotRaceTemplate> loaded;

            QueryResult result = WorldDatabase.Query("SELECT race, name_race, mounts FROM playerbots_race_template");
            if (!result)
                return loaded;

            do
            {
                Field* fields = result->Fetch();
                BotRaceTemplate& entry = loaded[fields[0].Get<uint8>()];
                entry.hasNameRace = !fields[1].IsNull();
                entry.nameRace = entry.hasNameRace ? fields[1].Get<uint8>() : 0;

                std::string const mounts = fields[2].Get<std::string>();
                for (std::string_view token : Acore::Tokenize(mounts, ' ', false))
                    if (Optional<uint32> spell = Acore::StringTo<uint32>(token))
                        entry.mounts.push_back(*spell);
            } while (result->NextRow());

            return loaded;
        }();

        return templates;
    }
}

uint8 BotRaceTemplates::GetNameRace(uint8 race)
{
    auto const& templates = GetTemplates();
    auto itr = templates.find(race);
    return itr != templates.end() && itr->second.hasNameRace ? itr->second.nameRace : sRaceMgr->GetKinRace(race);
}

std::vector<uint32> const& BotRaceTemplates::GetMounts(uint8 race)
{
    static std::vector<uint32> const none;

    auto const& templates = GetTemplates();
    auto itr = templates.find(race);
    return itr != templates.end() ? itr->second.mounts : none;
}
