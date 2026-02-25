#pragma once

#include <Forms/TESForm.h>
#include <Misc/BSFixedString.h>

struct TESObjectREFR;
struct TESWorldSpace;

struct TESObjectCELL : TESForm
{
    // FO4: cellFlags at 0x40 (Skyrim: 0x40)
    uint8_t pad20[0x40 - 0x20];
    uint32_t cellFlags;
    uint32_t unk44;

    // FO4: worldspace at 0x110 (Skyrim: 0x128)
    uint8_t pad48[0x110 - 0x48];
    TESWorldSpace* worldspace;
};

static_assert(offsetof(TESObjectCELL, cellFlags) == 0x40);
static_assert(offsetof(TESObjectCELL, worldspace) == 0x110);
