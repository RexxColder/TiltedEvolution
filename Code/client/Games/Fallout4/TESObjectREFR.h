#pragma once

#include <Games/Primitives.h>
#include <Forms/TESForm.h>
#include <Games/Animation/IAnimationGraphManagerHolder.h>
#include <Games/Misc/Lock.h>
#include <Structs/Inventory.h>

// Forward declarations
struct TESWorldSpace;
struct TESBoundObject;
struct TESContainer;
struct BGSScene;
struct NiNode;
struct BGSInventoryList;
struct TESObjectCELL;

enum class ITEM_REMOVE_REASON
{
    kRemove,
    kSteal,
    kSelling,
    kDropping,
    kStoreInContainer,
    kStoreInTeammate
};

// ============================================================================
// F4SE: TESObjectREFR — 0x110 bytes
// Key layout differences from Skyrim (0xA0):
//   - More interfaces embedded directly (IAnimationGraphManagerHolder @ 0x48,
//     IKeywordFormBase @ 0x50, ActorValueOwner @ 0x58)
//   - baseForm  @ 0xE0 (Skyrim: 0x40)
//   - rot/pos   @ 0xC0/0xD0 (Skyrim: 0x48/0x54)
//   - parentCell@ 0xB8 (Skyrim: 0x60)
//   - New: BGSInventoryList* @ 0xF8
//   - extraDataList is a POINTER (not inline like Skyrim)
// ============================================================================

// Embedded in TESObjectREFR at 0x50
struct IKeywordFormBase
{
    virtual ~IKeywordFormBase() {}
    virtual bool HasKeyword(const struct BGSKeyword* apKeyword, void* apArg) { return false; }
    virtual bool GetKeywords(void* apOutKeywords) { return false; }
};

struct ActorValueOwner
{
    virtual ~ActorValueOwner() {}
    virtual float GetActorValue(uint32_t aActorValueId) const { return 0.0f; }
    virtual float GetPermanentActorValue(uint32_t aActorValueId) const { return 0.0f; }
    virtual float GetBaseActorValue(uint32_t aActorValueId) const { return 0.0f; }
    virtual void SetBaseActorValue(uint32_t aActorValueId, float aValue) {}
    virtual void RestoreActorValue(uint32_t aMode, uint32_t aActorValueId, float aValue) {}
    virtual void SetActorValue(uint32_t aActorValueId, float aValue) {}
    virtual float sub_06() { return 0.0f; }
};

// Stripped-down ExtraDataList for FO4 (pointer-based)
struct ExtraDataList;

struct TESObjectREFR : TESForm
{
    // ---- Change flags ----
    enum ChangeFlags : uint32_t
    {
        CHANGE_REFR_MOVE = 1 << 1,
        CHANGE_REFR_HAVOK_MOVE = 1 << 2,
        CHANGE_REFR_CELL_CHANGED = 1 << 3,
        CHANGE_REFR_SCALE = 1 << 4,
        CHANGE_REFR_INVENTORY = 1 << 5,
        CHANGE_REFR_EXTRA_OWNERSHIP = 1 << 6,
        CHANGE_REFR_BASEOBJECT = 1 << 7,
        CHANGE_REFR_PROMOTED = 1 << 25,
        CHANGE_REFR_EXTRA_ACTIVATING_CHILDREN = 1 << 26,
        CHANGE_REFR_LEVELED_INVENTORY = 1 << 27,
        CHANGE_REFR_ANIMATION = 1 << 28,
        CHANGE_REFR_EXTRA_ENCOUNTER_ZONE = 1 << 29,
        CHANGE_REFR_EXTRA_CREATED_ONLY = 1 << 30,
        CHANGE_REFR_EXTRA_GAME_ONLY = 1u << 31,
    };

    // ---- Static helpers ----
    static TESObjectREFR* GetByHandle(uint32_t aHandle) noexcept;
    static uint32_t* GetNullHandle() noexcept;

    // ---- Virtual table (vtable indices inherited from TESForm, starting at 0x48) ----
    virtual void Unk_48();
    virtual void Unk_49();
    virtual void Unk_4A();
    virtual void Unk_4B();
    virtual void Unk_4C();
    virtual void Unk_4D();
    virtual void Unk_4E();
    virtual void Unk_4F();
    virtual void Unk_50();
    virtual void Unk_51();
    virtual void Unk_52();
    virtual void Unk_53();
    virtual void Unk_54();
    virtual void Unk_55();
    virtual void Unk_56();
    virtual void Unk_57();
    virtual void Unk_58();
    virtual void Unk_59();
    virtual void Unk_5A();
    virtual void Unk_5B();
    virtual BGSScene* GetCurrentScene(); // 0x5C
    virtual void Unk_5D();
    virtual void Unk_5E();
    virtual void Unk_5F();
    virtual void Unk_60();
    virtual void Unk_61();
    virtual void Unk_62();
    virtual void Unk_63();
    virtual void Unk_64();
    virtual NiNode* GetActorRootNode(bool aFirstPerson);             // 0x8B
    virtual NiNode* GetObjectRootNode();                             // 0x8C
    virtual struct TESRace* GetActorRace();                          // 0x91
    virtual struct ActorEquipData** GetEquipData(bool aFirstPerson); // 0xA0

    // ---- Non-virtual helpers ----
    BSPointerHandle<TESObjectREFR> GetHandle() const noexcept;
    uint32_t GetCellId() const noexcept;
    TESWorldSpace* GetWorldSpace() const noexcept;
    TESObjectCELL* GetParentCellEx() const noexcept;
    ExtraDataList* GetExtraDataList() noexcept;
    void SetRotation(float aX, float aY, float aZ) noexcept;
    bool SendAnimationEvent(BSFixedString* apEventName) noexcept;
    void MoveTo(TESObjectCELL* apCell, const NiPoint3& acPosition) const noexcept;
    void Delete() const noexcept;
    void Disable() const noexcept;
    void Enable() const noexcept;

    Inventory GetInventory() const noexcept;
    bool IsItemInInventory(uint32_t aFormID) const noexcept;
    void SetInventory(const Inventory& acContainer) noexcept;

#if TP_FALLOUT4
    struct FO4HandleRefObject
    {
        uint64_t padding;
        inline void IncRef() {}
        inline void DecRefHandle() {}
    };
    static_assert(sizeof(FO4HandleRefObject) == 8, "FO4HandleRefObject must be 8 bytes");
    FO4HandleRefObject handleRefObject;
#else
    // BSHandleRefObject is embedded here (used for reference counting)
    uint64_t handleRefObject;
#endif

    // ---- Memory layout — FO4-specific offsets ----
    // TESForm ends at 0x20
    // BST event sinks (FO4-specific inlined interfaces):
    uint64_t unk28;                               // 0x28  (BSActiveGraphIfInactiveEvent sink)
    uint64_t unk30;                               // 0x30
    uint64_t unk38;                               // 0x38  (BSAnimationGraphEvent sink)
    uint64_t unk40;                               // 0x40  (BGSInventoryListEvent sink)
    IAnimationGraphManagerHolder animGraphHolder; // 0x48
    IKeywordFormBase keywordFormBase;             // 0x50
    ActorValueOwner actorValueOwner;              // 0x58

    uint64_t unk60; // 0x60
    uint64_t unk68; // 0x68
    uint32_t unk70; // 0x70
    uint32_t unk74; // 0x74
    uint32_t unk78; // 0x78
    uint32_t unk7C; // 0x7C
    uint64_t unk80; // 0x80
    uint64_t unk88; // 0x88
    uint64_t unk90; // 0x90
    uint64_t unk98; // 0x98
    uint64_t unkA0; // 0xA0
    uint64_t unkA8; // 0xA8
    uint64_t unkB0; // 0xB0

    TESObjectCELL* parentCell; // 0xB8  (Skyrim: 0x60)
    NiPoint3 rot;              // 0xC0, 0xC4, 0xC8
    float unkCC;               // 0xCC
    NiPoint3 pos;              // 0xD0, 0xD4, 0xD8  (Skyrim: 0x54)
    float unkDC;               // 0xDC
    TESForm* baseForm;         // 0xE0  (Skyrim: 0x40)
    uint64_t unkE8;            // 0xE8

    struct LoadedData
    {
        uint64_t unk00;
        NiNode* rootNode; // 0x08
        uint64_t unk10;
        uint64_t unk18;
        uint64_t flags; // kFlag_PhysicsInitialized = 1
    };

    LoadedData* loadedData;          // 0xF0  (root node at 0x08)
    BGSInventoryList* inventoryList; // 0xF8  (NEW in FO4 — not in Skyrim)
    ExtraDataList* extraDataList;    // 0x100 (Skyrim has this inline at 0x70)
    uint32_t unk104;                 // 0x104
    uint32_t unk108;                 // 0x108
};

static_assert(offsetof(TESObjectREFR, animGraphHolder) == 0x48);
static_assert(offsetof(TESObjectREFR, parentCell) == 0xB8);
static_assert(offsetof(TESObjectREFR, rot) == 0xC0);
static_assert(offsetof(TESObjectREFR, pos) == 0xD0);
static_assert(offsetof(TESObjectREFR, baseForm) == 0xE0);
static_assert(offsetof(TESObjectREFR, inventoryList) == 0xF8);
static_assert(offsetof(TESObjectREFR, extraDataList) == 0x100);
static_assert(sizeof(TESObjectREFR) == 0x110);
