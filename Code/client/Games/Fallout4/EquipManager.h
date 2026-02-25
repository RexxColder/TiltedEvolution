#pragma once

struct TESForm;
struct ExtraDataList;
struct Actor;

#if TP_FALLOUT4

struct EquipManager
{
    static EquipManager* Get() noexcept;

    void* Equip(Actor* apActor, TESForm* apItem, ExtraDataList* apExtraDataList, int aCount, TESForm* apSlot, bool abQueueEquip, bool abForceEquip, bool abPlaySound, bool abApplyNow);
    void* UnEquip(Actor* apActor, TESForm* apItem, ExtraDataList* apExtraDataList, int aCount, TESForm* apSlot, bool abQueueEquip, bool abForceEquip, bool abPlaySound, bool abApplyNow, TESForm* apSlotToReplace);
    void UnequipAll(Actor* apActor);
};

#endif
