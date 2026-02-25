#pragma once

#if TP_FALLOUT4

#pragma once

#include <Components/BaseFormComponent.h>

struct BGSPerkRankArray : BaseFormComponent
{
    void* perkRanks;
    uint32_t count;
};


#endif
