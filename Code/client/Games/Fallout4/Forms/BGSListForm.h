#pragma once

#if TP_FALLOUT4

#pragma once

#include "TESForm.h"

struct BGSListForm : TESForm
{
    GameArray<TESForm*> ArrayOfForms{};
    GameArray<uint32_t>* pScriptAddedTempFormA{};
    uint32_t iScriptAddedFormCount{};
};

static_assert(sizeof(BGSListForm) == 0x48);


#endif
