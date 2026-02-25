#pragma once

#include <Forms/TESBoundAnimObject.h>
#include <Components/BGSAttackDataForm.h>
#include <Components/TESSpellList.h>

struct TESActorBase : TESBoundAnimObject
{
    BGSAttackDataForm attackDataForm;
    TESSpellList spellList;
    // Minimal for Forms.cpp
};
