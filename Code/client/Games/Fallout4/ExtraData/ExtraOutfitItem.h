#pragma once

#if TP_FALLOUT4

#pragma once

#include "ExtraData.h"

struct ExtraOutfitItem : BSExtraData
{
    inline static constexpr auto eExtraData = ExtraDataType::OutfitItem;

    TESForm* pOutfit;
};

static_assert(sizeof(ExtraOutfitItem) == 0x18);


#endif
