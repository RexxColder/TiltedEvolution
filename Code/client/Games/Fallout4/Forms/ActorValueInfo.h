#pragma once

#include <Forms/TESForm.h>
#include <Components/TESFullName.h>

#if TP_FALLOUT4

struct ActorValueInfo : TESForm
{
    enum
    {
        kHealth = 0,
        kAP = 1,
        kStamina = 2,
        kStrength = 3,
        kPerception = 4,
        kEndurance = 5,
        kCharisma = 6,
        kIntelligence = 7,
        kAgility = 8,
        kLuck = 9,
        kActionPoints = 10,
        kCarryWeight = 11,
        kCritChance = 12,
        kDamageResist = 13,
        kEnergyResist = 14,
        kFireResist = 15,
        kFrostResist = 16,
        kPoisonResist = 17,
        kSpeedMult = 18,
        kInventoryWeight = 19,
        kKarma = 20,
        kLife = 21,
    };

    static uint32_t Resolve(uint32_t aId) noexcept;

    virtual ~ActorValueInfo();

    TESFullName name;
    uint8_t pad30[0x50 - 0x30];
    BSFixedString key;
};

#endif
