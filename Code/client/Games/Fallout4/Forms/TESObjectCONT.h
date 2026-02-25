#pragma once

#if TP_FALLOUT4

#pragma once

#include <Forms/TESBoundAnimObject.h>

#include <Components/TESContainer.h>
#include <Components/TESFullName.h>

struct TESObjectCONT : TESBoundAnimObject
{
    TESContainer container;
    TESFullName fullName;
    // more stuff
};


#endif
