#pragma once

#include <Components/BaseFormComponent.h>
#include <Misc/BSFixedString.h>

#if TP_FALLOUT4

struct TESFullName : BaseFormComponent
{
    virtual ~TESFullName();

    BSFixedString value;
};

#endif
