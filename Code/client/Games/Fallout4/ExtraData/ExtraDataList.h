#pragma once

#include "ExtraData.h"

#if TP_FALLOUT4

struct AlchemyItem;
struct EnchantmentItem;

struct ExtraDataList
{
    static ExtraDataList* New() noexcept { return nullptr; }

    bool Contains(ExtraDataType aType) const { return false; }
    void Set(ExtraDataType aType, bool aSet) {}

    bool Add(ExtraDataType aType, BSExtraData* apNewData) { return false; }
    bool Remove(ExtraDataType aType, BSExtraData* apNewData) { return false; }

    uint32_t GetCount() const { return 0; }

    void SetType(ExtraDataType aType, bool aClear) {}
    BSExtraData* GetByType(ExtraDataType type) const { return nullptr; }

    void SetSoulData(SOUL_LEVEL aSoulLevel) noexcept {}
    void SetChargeData(float aCharge) noexcept {}
    void SetWorn(bool aWornLeft) noexcept {}
    void SetPoison(AlchemyItem* apItem, uint32_t aCount) noexcept {}
    void SetHealth(float aHealth) noexcept {}
    void SetEnchantmentData(EnchantmentItem* apItem, uint16_t aCharge, bool aRemoveOnUnequip) noexcept {}

    [[nodiscard]] bool HasQuestObjectAlias() noexcept { return false; }

    virtual ~ExtraDataList() {}
    BSExtraData* data = nullptr;

    struct Bitfield
    {
        uint8_t data[0x18];
    };

    Bitfield* bitfield{};
    void* lock{};
};

#endif
