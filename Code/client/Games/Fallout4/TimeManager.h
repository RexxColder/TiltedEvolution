#pragma once

#include <Forms/TESGlobal.h>

#if TP_FALLOUT4

struct TimeData
{
    static TimeData* Get() noexcept;

    char pad0[0x8];
    TESGlobal* GameYear;
    TESGlobal* GameMonth;
    TESGlobal* GameDay;
    TESGlobal* GameHour;
    TESGlobal* GameDaysPassed;
    TESGlobal* TimeScale;
    float unk1;
    float rawDaysPassed;
    char pad_40[0x88];
};

#endif
