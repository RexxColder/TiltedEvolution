#pragma once

#include <Components/BaseFormComponent.h>
#include <Misc/BSFixedString.h>

enum class FormType : uint8_t
{
    Armor = 26,
    Book = 27,
    Container = 28,
    Door = 29,
    Ingredient = 30,
    Weapon = 41,
    Ammo = 42,
    Npc = 43,
    LeveledCharacter = 44,
    Alchemy = 46,
    LeveledItem = 53,
    Character = 62,
    QuestItem = 77,
    Count = 0x87
};

struct BGSSaveFormBuffer;
struct BGSLoadFormBuffer;

struct ChangeFlags
{
    uint32_t flags;
};

struct TESForm : BaseFormComponent
{
    static TESForm* GetById(uint32_t aId);

    virtual void sub_4();
    virtual void sub_5();
    virtual void sub_6();
    virtual void sub_7();
    virtual void sub_8();
    virtual void sub_9();
    virtual bool MarkChanged(uint32_t aChangeFlag);
    virtual bool UnsetChanged(uint32_t aChangeFlag);
    virtual void sub_C();
    virtual void sub_D();
    virtual void Save(BGSSaveFormBuffer* apBuffer) const noexcept;
    virtual void Load(BGSLoadFormBuffer* apBuffer);
    virtual void sub_10();
    virtual void sub_11();
    virtual void sub_12();
    virtual void InitializeComponents();
    virtual void sub_14();
    virtual FormType GetFormType();
    virtual void sub_16();
    virtual void sub_17();
    virtual void sub_18();
    virtual void sub_19();
    virtual void sub_1A();
    virtual void sub_1B();
    virtual void sub_1C();
    virtual void sub_1D();
    virtual void sub_1E();
    virtual void sub_1F();
    virtual void sub_20();
    virtual void sub_21();
    virtual void sub_22();
    virtual void sub_23();
    virtual void sub_24();
    virtual void sub_25();
    virtual void sub_26();
    virtual void sub_27();
    virtual void sub_28();
    virtual void sub_29();
    virtual void sub_2A();
    virtual void sub_2B();
    virtual void sub_2C();
    virtual void sub_2D();
    virtual const char* GetName(const BSFixedString& acTag = {}) const noexcept;
    virtual void CopyFrom(TESForm* apForm);

    uintptr_t unk08;
    uint32_t flags;
    uint32_t formID;
    uint16_t unk10;
    uint16_t unk12;
    uint32_t unk18;

    uint32_t GetChangeFlags() const noexcept;
    void SetSkipSaveFlag(bool aSet) noexcept;
    void Save_Reversed(uint32_t aChangeFlags, Buffer::Writer& aWriter);

    bool IsDisabled() const noexcept { return (flags & (1 << 0xB)) != 0; }
    bool IsTemporary() const noexcept { return formID >= 0xFF000000; }
};

static_assert(sizeof(TESForm) == 0x20);
