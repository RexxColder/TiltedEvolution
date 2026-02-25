#pragma once

#include <Misc/BSScript.h>

#if TP_FALLOUT4

struct FalloutVM
{
    virtual ~FalloutVM();

    static FalloutVM* Get();

    uint8_t pad8[0x200 - 0x8];
    BSScript::IVirtualMachine* virtualMachine;
};

using GameVM = FalloutVM;

#endif
