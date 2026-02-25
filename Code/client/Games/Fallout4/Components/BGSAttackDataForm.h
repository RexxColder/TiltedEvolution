#pragma once

#include <Components/BaseFormComponent.h>

struct BGSAttackDataMap
{
    // Minimal for Forms.cpp
    void* attackDataMap;
};

struct BGSAttackDataForm : BaseFormComponent
{
    BGSAttackDataMap* attackDataMap;
};
