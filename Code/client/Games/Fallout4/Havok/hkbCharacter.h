#pragma once

#include <cstdint>

struct CharacterContext;

struct hkbCharacter
{
    virtual ~hkbCharacter() {};

    uint8_t pad8[0xA0 - 0x8];
    CharacterContext* characterContext;
#if TP_SKYRIM
    uint8_t pad88[0xA0 - 0xA0]; // Adjust as needed
#else
    uint8_t pad88[1]; // FO4 padding
#endif
};
