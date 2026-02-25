#pragma once

#include <Forms/TESForm.h>
#include <Misc/BSString.h>

#if TP_FALLOUT4

struct TESGlobal : TESForm
{
    void* unk14;
    uint8_t unk1C;
    uint8_t pad[3];
    union
    {
        uint32_t i;
        float f;
    };
};

#endif
