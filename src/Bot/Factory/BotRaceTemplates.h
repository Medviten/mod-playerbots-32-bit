/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef _PLAYERBOT_BOTRACETEMPLATES_H
#define _PLAYERBOT_BOTRACETEMPLATES_H

#include "Define.h"

#include <vector>

/// Bot-only settings of custom races, from playerbots_race_template. The race modpaks fill it.
class BotRaceTemplates
{
public:
    /// The race whose bot names a race uses, or 0 for generic names. Its kin unless the race has its own setting.
    static uint8 GetNameRace(uint8 race);
    /// The race's own mount spells, if any.
    static std::vector<uint32> const& GetMounts(uint8 race);
};

#endif
