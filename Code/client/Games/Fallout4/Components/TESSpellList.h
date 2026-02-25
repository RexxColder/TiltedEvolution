#pragma once

#include <Components/BaseFormComponent.h>

struct TESSpellList : BaseFormComponent
{
    struct Lists
    {
        void* spells;
        void* unk4;
        void* shouts;
        uint32_t spellCount;
        uint32_t unk4Count;
        uint32_t shoutCount;
    };

    Lists* lists;

    void Initialize();
};
