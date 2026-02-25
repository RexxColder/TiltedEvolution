#pragma once

#include <TESObjectREFR.h>
#include <Games/Events.h>
#include <Structs/Inventory.h>
#include <Structs/ActorValues.h>

struct TESNPC;
struct TESRace;
struct ExActor;
struct ExPlayerCharacter;
struct ActorExtension;
struct TESIdleForm;
struct TESFaction;
struct TESPackage;
struct NiPoint3;

// ============================================================================
// ActorState — embedded at Actor+0x128  (Skyrim: Actor+0xC0)
// Movement/stance flags.
// ============================================================================
struct ActorState
{
    virtual ~ActorState() {}

    enum
    {
        kState_Running = 0x40,
        kState_Walking = 0x80,
        kState_Sprinting = 0x100,
        kState_Sneaking = 0x200,
        kState_Swimming = 0x400,
    };

    uint32_t flags04; // 0x08 within ActorState
    uint32_t flags08; // 0x0C

    bool IsWeaponDrawn() const noexcept { return ((flags08 >> 5) & 7) >= 3; }
};

// ============================================================================
// MagicTarget — embedded at Actor+0x110 (Skyrim: also Actor+0x98 → offset 0xA0)
// Minimal interface header — full implementation is game-side.
// ============================================================================
struct MagicTarget
{
    virtual ~MagicTarget() {}
    uint64_t unk08;
    uint64_t unk10;
};

// ============================================================================
// EquipData — one equipped item slot inside MiddleProcess::Data08
// NOTE: TBO_InstanceData is new in FO4 (weapon/armor instance modifications)
// ============================================================================
struct TBO_InstanceData;

struct ActorEquipData
{
    struct EquipSlot
    {
        struct TESForm* item;           // 0x00
        TBO_InstanceData* instanceData; // 0x08  FO4-specific (legendary/mod data)
        struct BGSEquipSlot* equipSlot; // 0x10
        uint64_t unk18;                 // 0x18
        void* equippedData;             // 0x20  EquippedWeaponData*
    };
};

// ============================================================================
// Actor — 0x490 bytes  (Skyrim: 0x2B8)
//
// Key differences from Skyrim Actor:
//  - No addedSpells / leftHandSpell / rightHandSpell / equippedShout
//  - MagicTarget @ 0x110 (SKY: 0x98)
//  - ActorState  @ 0x128 (SKY: 0xC0)
//  - 6 new BSTEventSink for movement events @ 0x138-0x160
//  - MiddleProcess* @ 0x300 (called middleProcess in FO4, processManager in SKY @ 0xF0)
//  - actorValueData (tArray) @ 0x338  — replaces SKY's permanent/temp/damage modifiers
//  - equipData @ 0x428, race @ 0x418
//  - actorFlags @ 0x2D0 (SKY: 0xE8 as flags1/flags2)
// ============================================================================
struct Actor : TESObjectREFR
{
    static constexpr FormType Type = FormType::Character;

    // ---- Creation helpers ----
    static GamePtr<Actor> New() noexcept;
    static GamePtr<Actor> Create(TESNPC* apBaseForm) noexcept;
    static GamePtr<Actor> Spawn(uint32_t aBaseFormId) noexcept;

    // ---- Virtual functions (FO4-specific vtable, inherits from TESObjectREFR) ----
    virtual void Unk_C4();
    virtual void Unk_C5();
    virtual void Unk_C6();
    virtual void Unk_C7();
    virtual void Unk_C8();
    virtual void Unk_C9();
    virtual void Unk_CA();
    virtual void Unk_CB();
    virtual void Unk_CC();
    virtual void Unk_CD();
    virtual void Unk_CE();
    virtual void Unk_CF();
    virtual void Unk_D0();
    virtual void Unk_D1();
    virtual void Unk_D2();
    virtual void Unk_D3();
    virtual void Unk_D4();
    virtual void Unk_D5();
    virtual void Unk_D6();
    virtual void Unk_D7();
    virtual void Unk_D8();
    virtual void Unk_D9();
    virtual void Unk_DA();
    virtual void Unk_DB();
    virtual void Unk_DC();
    virtual void Unk_DD();
    virtual void Unk_DE();
    virtual void Unk_DF();
    virtual void SetWeaponDrawn(bool aDraw); // Unk_E0 equivalent
    virtual void SetPosition(const NiPoint3& acPoint, bool aSyncHavok = true);
    virtual void Resurrect(bool aResetInventory);
    virtual bool IsInCombat(uint64_t aUnk1 = 0, uint64_t aUnk2 = 0) const noexcept; // 0xFE
    virtual void KillImpl(Actor* apAttacker, float aDamage, bool aSendEvent, bool aRagdollInstant);

    // ---- NOTE: These are NOT virtual in FO4 (unlike Skyrim) ----
    // MoveToHigh / MoveToLow / MoveToMiddleLow / MoveToMiddleHigh

    // ---- Actor flags ----
    enum ActorFlagsFO4 : uint32_t
    {
        kFlag_Teammate = (1u << 26),
    };

    // ---- Non-virtual member functions ----
    ActorExtension* GetExtension() noexcept;
    ExActor* AsExActor() noexcept;
    ExPlayerCharacter* AsExPlayerCharacter() noexcept;

    // Getters
    float GetActorValue(uint32_t aId) const noexcept;
    float GetActorPermanentValue(uint32_t aId) const noexcept;
    Inventory GetActorInventory() const noexcept;
    Inventory GetEquipment() const noexcept;
    int32_t GetGoldAmount() const noexcept;
    uint16_t GetLevel() const noexcept;
    ActorValues GetEssentialActorValues() const noexcept;

    [[nodiscard]] bool IsDead() const noexcept;
    [[nodiscard]] bool IsAlive() const noexcept;
    [[nodiscard]] bool IsPlayerTeammate() const noexcept { return (actorFlags & kFlag_Teammate) != 0; }
    [[nodiscard]] Actor* GetCombatTarget() const noexcept;
    [[nodiscard]] bool HasPerk(uint32_t aPerkFormId) const noexcept;
    [[nodiscard]] uint8_t GetPerkRank(uint32_t aPerkFormId) const noexcept;

    // Setters
    void SetActorValue(uint32_t aId, float aValue) noexcept;
    void ForceActorValue(uint32_t aMode, uint32_t aId, float aValue) noexcept;
    void SetActorValues(const ActorValues& acActorValues) noexcept;
    void SaveAnimationVariables(struct AnimationVariables& arVariables) const noexcept;
    void LoadAnimationVariables(const struct AnimationVariables& acVariables) noexcept;
    void SetSpeed(float aSpeed) noexcept;
    void SetLevelMod(uint32_t aLevel) noexcept;
    void SetActorInventory(const Inventory& aInventory) noexcept;
    void ForcePosition(const NiPoint3& acPosition) noexcept;
    void SetWeaponDrawnEx(bool aDraw) noexcept;
    void SetPackage(TESPackage* apPackage) noexcept;
    void SetPlayerTeammate(bool aSet) noexcept;

    // Actions
    void UnEquipAll() noexcept;
    void QueueUpdate() noexcept;
    void Reset() noexcept;
    void Kill() noexcept;
    void Respawn() noexcept;
    void StartCombat(Actor* apTarget) noexcept;
    void StopCombat() noexcept;
    bool PlayIdle(TESIdleForm* apIdle) noexcept;

    // ---- MiddleProcess (equivalent to ActorProcessManager in Skyrim) ----
    struct MiddleProcess
    {
        void* unk00; // 0x00

        struct Data08
        {
            uint64_t unk00[0x280 >> 3]; // 0x000-0x27F
            // SimpleLock @ 0x280 (size 0x8)
            uint64_t lock; // 0x280

            struct EquipData
            {
                TESForm* item;                  // 0x00
                TBO_InstanceData* instanceData; // 0x08
                struct BGSEquipSlot* equipSlot; // 0x10
                uint64_t unk18;                 // 0x18
                void* equippedData;             // 0x20 EquippedWeaponData*
            };
            static_assert(sizeof(EquipData) == 0x28);

            // tArray<EquipData> @ 0x288
            EquipData* equipData;   // 0x288 data ptr
            uint32_t equipCount;    // 0x290
            uint32_t equipCapacity; // 0x294

            uint64_t unk298[(0x3A0 - 0x298) >> 3];
            uint32_t unk3A0;
            uint32_t furnitureHandle1; // 0x3A4
            uint32_t furnitureHandle2; // 0x3A8
            uint32_t unk3AC;
            uint64_t unk3B0[(0x490 - 0x3B0) >> 3];
            uint32_t unk490;
            uint16_t unk494;
            uint16_t dirtyFlags; // 0x496
        };
        static_assert(offsetof(Data08, furnitureHandle1) == 0x3A4);
        static_assert(offsetof(Data08, equipData) == 0x288);

        Data08* unk08; // 0x08
    };

    // Member: actorValueData entry
    struct ActorValueData
    {
        uint32_t avFormID;
        float value;
    };
    struct ActorValueData3
    {
        uint32_t avFormID;
        float unk04;
        float unk08;
        float unk0C;
    };

    // ============================================================
    // Memory layout at FO4 offsets (TESObjectREFR ends at 0x110)
    // ============================================================
    MagicTarget magicTarget; // 0x110
    ActorState actorState;   // 0x128

    // 6 new movement event sinks unique to FO4 Actor:
    uint64_t movementDataChanged;   // 0x138  BSTEventSink<BSMovementDataChangedEvent>
    uint64_t transformDelta;        // 0x140  BSTEventSink<BSTransformDeltaEvent>
    uint64_t subGraphActivation;    // 0x148  BSTEventSink<BSSubGraphActivationUpdate>
    uint64_t characterMoveFinished; // 0x150 BSTEventSink<bhkCharacterMoveFinishEvent>
    uint64_t nonSupportContact;     // 0x158  BSTEventSink<bhkNonSupportContactEvent>
    uint64_t characterStateChanged; // 0x160 BSTEventSink<bhkCharacterStateChangeEvent>

    uint64_t unk168[(0x2D0 - 0x168) >> 3]; // 0x168 gap

    uint32_t actorFlags;                   // 0x2D0  (kFlag_Teammate = bit 26)
    uint32_t unk2D4;                       // 0x2D4
    uint64_t unk2D8[(0x300 - 0x2D8) >> 3]; // 0x2D8 gap

    MiddleProcess* middleProcess;          // 0x300  (Skyrim: processManager @ 0xF0)
    uint64_t unk308[(0x338 - 0x308) >> 3]; // 0x308 gap

    // tArray<ActorValueData> @ 0x338 (replaces Skyrim's healthModifiers etc.)
    ActorValueData* actorValueData; // 0x338
    uint32_t actorValueCount;       // 0x340
    uint32_t actorValueCapacity;    // 0x344
    uint32_t pad348;                // 0x348

    // tArray<ActorValueData3> @ 0x350
    ActorValueData3* unk350; // 0x350
    uint32_t unk358;
    uint32_t unk35C;

    uint64_t unk360[(0x418 - 0x360) >> 3]; // 0x360 gap

    TESRace* race;             // 0x418  (Skyrim: 0x1F0)
    uint64_t unk420;           // 0x420
    ActorEquipData* equipData; // 0x428  (NEW in FO4 — actor's equipped item data)
    uint64_t unk430;           // 0x430
    uint32_t unk438;           // 0x438
    uint32_t uiFlags;          // 0x43C

    uint64_t unk440[(0x490 - 0x440) >> 3]; // 0x440 gap
};

static_assert(offsetof(Actor, magicTarget) == 0x110);
static_assert(offsetof(Actor, actorState) == 0x128);
static_assert(offsetof(Actor, actorFlags) == 0x2D0);
static_assert(offsetof(Actor, middleProcess) == 0x300);
static_assert(offsetof(Actor, actorValueData) == 0x338);
static_assert(offsetof(Actor, race) == 0x418);
static_assert(offsetof(Actor, equipData) == 0x428);
static_assert(offsetof(Actor, uiFlags) == 0x43C);
static_assert(sizeof(Actor) == 0x490);
