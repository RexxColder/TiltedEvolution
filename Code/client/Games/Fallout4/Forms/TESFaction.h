#pragma once

#include <Forms/TESForm.h>
#include <Components/TESFullName.h>

#if TP_FALLOUT4

struct TESFaction : TESForm
{
    TESFullName fullname;
};

#endif
