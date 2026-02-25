#pragma once

#if TP_FALLOUT4

#pragma once

#include "TESLeveledList.h"

struct TESLevItem : TESBoundObject, TESLeveledList
{
};

static_assert(sizeof(TESLevItem) == 0x58);


#endif
