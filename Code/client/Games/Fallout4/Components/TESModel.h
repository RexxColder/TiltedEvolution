#pragma once

#if TP_FALLOUT4

#pragma once

#include <Components/BaseFormComponent.h>
#include <Misc/BSFixedString.h>

struct TESModel : BaseFormComponent
{
    BSFixedString name;
    void* unk8[2];
    uint8_t unk10[4];
};


#endif
