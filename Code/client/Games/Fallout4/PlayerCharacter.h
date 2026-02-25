#pragma once

#include <Actor.h>
#include <Structs/ActorValues.h>

// Forward declarations
struct TESWorldSpace;

// ============================================================================
// PlayerCharacter — 0xE10 bytes  (Skyrim: 0xBE8)
//
// Key differences from Skyrim PlayerCharacter:
//  - Inherits directly from Actor (no intermediate Character class)
//  - playerEquipData  @ 0xB70 (new in FO4)
//  - firstPersonSkeleton is NiNode* @ 0xB78  (Skyrim: BSFadeNode* @ 0x8F0)
//  - tints @ 0xD00 uses BGSCharacterTint::Entry*
//  - No addedPerks / perks / standingStonePerks / currentWorldSpace
//  - menuOpenClose event sink starts at 0x490 (Skyrim: 0x2B0)
// ============================================================================

namespace BGSCharacterTint
{
struct Entry;
}

struct PlayerCharacter : Actor
{
    static constexpr FormType Type = FormType::Character;

    static PlayerCharacter* Get() noexcept;

    // Additional virtual functions beyond Actor
    virtual void Unk_131();
    virtual void Unk_132();
    virtual void Unk_133();
    virtual void Unk_134();

    // ---- FO4-specific helpers ----
    const GameArray<BGSCharacterTint::Entry*>& GetTints() const noexcept;

    // In FO4, SetDifficulty uses a native function (no Papyrus detour needed)
    void SetDifficulty(int32_t aDifficulty, bool aForceUpdate = true) noexcept;

    // ---- Quest objective data ----
    struct Objective
    {
        void* unk00;            // 0x00
        struct TESQuest* owner; // 0x08
    };

    struct ObjectiveData
    {
        Objective* data;   // 0x00
        uint32_t instance; // 0x04
        uint32_t number;   // 0x08
    };

    // Actor ends at 0x490
    // ============================================================
    // Memory layout (all offsets relative to start of object)
    // ============================================================

    // Event sinks at 0x490+ (FO4 — Skyrim has these at 0x2B0)
    uint64_t menuOpenClose;          // 0x490  BSTEventSink<MenuOpenCloseEvent>
    uint64_t menuModeChange;         // 0x498  BSTEventSink<MenuModeChangeEvent>
    uint64_t userEventEnabled;       // 0x4A0  BSTEventSink<UserEventEnabledEvent>
    uint64_t hitEvent;               // 0x4A8  BSTEventSink<TESHitEvent>
    uint64_t perkValueEvents;        // 0x4B0  BSTEventSink<PerkEntryUpdatedEvent>
    uint64_t movementControlsFilter; // 0x4B8  IMovementPlayerControlsFilter

    uint8_t unk4C0[0x7D8 - 0x4C0]; // 0x4C0  gap

    // tArray<ObjectiveData> @ 0x7D8
    ObjectiveData* objDataPtr; // 0x7D8
    uint32_t objDataCount;     // 0x7E0
    uint32_t objDataCapacity;  // 0x7E4

    uint8_t unk7E8[0xB70 - 0x7E8]; // 0x7E8  gap

    // FO4-specific equip data (separate from Actor::equipData)
    ActorEquipData* playerEquipData; // 0xB70  (first-person equip data)
    NiNode* firstPersonSkeleton;     // 0xB78  (Skyrim: BSFadeNode* @ 0x8F0)

    uint8_t unkB80[0xD00 - 0xB80]; // 0xB80  gap

    // Tint data — FO4 uses BGSCharacterTint::Entry* instead of TintMask*
    GameArray<BGSCharacterTint::Entry*>* tints; // 0xD00

    uint8_t unkD08[0xE10 - 0xD08]; // 0xD08  gap
};

static_assert(offsetof(PlayerCharacter, menuOpenClose) == 0x490);
static_assert(offsetof(PlayerCharacter, objDataPtr) == 0x7D8);
static_assert(offsetof(PlayerCharacter, playerEquipData) == 0xB70);
static_assert(offsetof(PlayerCharacter, firstPersonSkeleton) == 0xB78);
static_assert(offsetof(PlayerCharacter, tints) == 0xD00);
static_assert(sizeof(PlayerCharacter) == 0xE10);
