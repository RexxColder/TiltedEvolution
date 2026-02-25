#include <TiltedOnlinePCH.h>
#include <TESObjectREFR.h>
#include <World.h>
#include <Forms/TESForm.h>
#include <Forms/TESObjectCELL.h>

// ============================================================================
// TESObjectREFR — Fallout 4 implementation
// ============================================================================

TESObjectREFR* TESObjectREFR::GetByHandle(uint32_t aHandle) noexcept
{
    // TODO(FO4): Implement using FO4 Address Library ID for LookupREFRByHandle
    // In Skyrim: POINTER_SKYRIMSE(TLookupREFRByHandle, s_fn, 15208);
    return nullptr;
}

uint32_t* TESObjectREFR::GetNullHandle() noexcept
{
    // TODO(FO4): Implement using FO4 Address Library ID for g_invalidRefHandle
    static uint32_t s_null = 0;
    return &s_null;
}

BSPointerHandle<TESObjectREFR> TESObjectREFR::GetHandle() const noexcept
{
    BSPointerHandle<TESObjectREFR> handle;
    // TODO(FO4): Call game function to create/retrieve handle
    return handle;
}

uint32_t TESObjectREFR::GetCellId() const noexcept
{
    if (parentCell)
        return parentCell->formID;
    return 0;
}

TESWorldSpace* TESObjectREFR::GetWorldSpace() const noexcept
{
    // F4SE: DEFINE_MEMBER_FN(GetWorldspace, TESWorldSpace*, 0x0040F290)
    TP_THIS_FUNCTION(TGetWorldSpace, TESWorldSpace*, TESObjectREFR);
    POINTER_FALLOUT4(TGetWorldSpace, s_fn, 18919); // Official FO4 AL ID
    if (!s_fn.GetPtr())
        return nullptr;
    return TiltedPhoques::ThisCall(s_fn.Get(), const_cast<TESObjectREFR*>(this));
}

TESObjectCELL* TESObjectREFR::GetParentCellEx() const noexcept
{
    // parentCell is at 0xB8 in FO4 (0x60 in Skyrim)
    return parentCell;
}

ExtraDataList* TESObjectREFR::GetExtraDataList() noexcept
{
    // In FO4 extraDataList is a pointer at 0x100 (inline in Skyrim at 0x70)
    return extraDataList;
}

void TESObjectREFR::SetRotation(float aX, float aY, float aZ) noexcept
{
    rot.x = aX;
    rot.y = aY;
    rot.z = aZ;
}

bool TESObjectREFR::SendAnimationEvent(BSFixedString* apEventName) noexcept
{
    // TODO(FO4): Implement via IAnimationGraphManagerHolder
    return false;
}

void TESObjectREFR::MoveTo(TESObjectCELL* apCell, const NiPoint3& acPosition) const noexcept
{
    // F4SE: extern RelocAddr<_MoveRefrToPosition> MoveRefrToPosition;
    TP_THIS_FUNCTION(TMoveToPosition, void, TESObjectREFR, uint32_t*, TESObjectCELL*, void*, const NiPoint3*, const NiPoint3*);
    POINTER_FALLOUT4(TMoveToPosition, s_fn, 19163); // Official FO4 AL ID
    if (!s_fn.GetPtr())
        return;
    const NiPoint3 zeroRot(0.f, 0.f, 0.f);
    uint32_t nullHandle = 0;
    TiltedPhoques::ThisCall(s_fn.Get(), const_cast<TESObjectREFR*>(this), &nullHandle, apCell, nullptr, &acPosition, &zeroRot);
}

void TESObjectREFR::Delete() const noexcept
{
    // TODO(FO4): Implement
}

void TESObjectREFR::Disable() const noexcept
{
    // TODO(FO4): Implement
}

void TESObjectREFR::Enable() const noexcept
{
    // TODO(FO4): Implement
}

Inventory TESObjectREFR::GetInventory() const noexcept
{
    Inventory result;
    // TODO(FO4): Use BGSInventoryList (at 0xF8) instead of ExtraContainerChanges
    // FO4 has a dedicated BGSInventoryList* inventoryList at 0xF8
    return result;
}

bool TESObjectREFR::IsItemInInventory(uint32_t aFormID) const noexcept
{
    // TODO(FO4): Iterate BGSInventoryList
    return false;
}

void TESObjectREFR::SetInventory(const Inventory& acContainer) noexcept
{
    // TODO(FO4): Implement using BGSInventoryList
}
