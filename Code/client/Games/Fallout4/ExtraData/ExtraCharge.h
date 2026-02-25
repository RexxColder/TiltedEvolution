#pragma once

#if TP_FALLOUT4

#pragma once

#include "ExtraData.h"

struct ExtraCharge : BSExtraData
{
    inline static constexpr auto eExtraData = ExtraDataType::Charge;

    float fCharge{};
};

static_assert(sizeof(ExtraCharge) == 0x18);


#endif
