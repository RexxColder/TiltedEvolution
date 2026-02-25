#pragma once

#include "TESForm.h"

#if TP_FALLOUT4

struct TESPackage : TESForm
{
    uint8_t unk20[0xD8 - 0x20];
    int32_t ePROCEDURE_TYPE;
    uint32_t uiRefCount;
};

#endif
