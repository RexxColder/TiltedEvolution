#pragma once

#if TP_FALLOUT4

#pragma once

#include <Components/BaseFormComponent.h>

struct TESPackage;

struct TESAIForm : BaseFormComponent
{
    uint32_t flags;
    uint8_t unkC[0xC];
    GameList<TESPackage> AIPackList;
};


#endif
