#include <TiltedOnlinePCH.h>
#include <Actor.h>
#include <World.h>
#include <Forms/TESForm.h>
#include <Structs/Inventory.h>
#include <Structs/ActorValues.h>

// ============================================================================
// Actor — Fallout 4 implementation
//
// DESIGN NOTES:
//  - FO4 has no spells / shouts / magic casters — those Skyrim functions
//    are simply absent.
//  - ActorValues now use the tArray<ActorValueData> at Actor+0x338.
//  - Inventory is managed via BGSInventoryList (via TESObjectREFR).
//  - EquipData is inside MiddleProcess::Data08 at 0x288 (with TBO_InstanceData).
// ============================================================================

float Actor::GetActorValue(uint32_t aId) const noexcept
{
    // ActorValueOwner is embedded in TESObjectREFR at 0x58 (FO4)
    // In FO4, ActorValueOwner::GetActorValue is at vtable index 1
    return actorValueOwner.GetActorValue(aId);
}

float Actor::GetActorPermanentValue(uint32_t aId) const noexcept
{
    return actorValueOwner.GetPermanentActorValue(aId);
}

void Actor::SetActorValue(uint32_t aId, float aValue) noexcept
{
    actorValueOwner.SetActorValue(aId, aValue);
}

void Actor::ForceActorValue(uint32_t aMode, uint32_t aId, float aValue) noexcept
{
    actorValueOwner.RestoreActorValue(aMode, aId, aValue);
}

void Actor::SetActorValues(const ActorValues& acActorValues) noexcept
{
    for (auto& [id, value] : acActorValues.ActorValuesList)
        SetActorValue(id, value);
}

void Actor::SaveAnimationVariables(AnimationVariables& arVariables) const noexcept
{
    // TODO(FO4): Implement actual animation variable capturing logic
    (void)arVariables;
}

void Actor::LoadAnimationVariables(const AnimationVariables& acVariables) noexcept
{
    // TODO(FO4): Implement actual animation variable applying logic
    (void)acVariables;
}

ActorValues Actor::GetEssentialActorValues() const noexcept
{
    // In FO4 the essential AV IDs differ from Skyrim (no Magicka, has Radiation)
    // Health=0x18C (396), ActionPoints=0x18D, StaminaEquiv=0x18E
    // For now we use a minimal set compatible with the common ID space.
    ActorValues result;
    // TODO(FO4): Map FO4-specific ActorValue IDs properly
    return result;
}

uint16_t Actor::GetLevel() const noexcept
{
    TP_THIS_FUNCTION(TGetLevel, uint16_t, const Actor);
    POINTER_FALLOUT4(TGetLevel, s_fn, 40822); // Official FO4 AL ID
    if (!s_fn.GetPtr())
        return 1;
    return TiltedPhoques::ThisCall(s_fn.Get(), this);
}

bool Actor::IsDead() const noexcept
{
    // actorFlags at 0x2D0; bit 0 = dead in FO4
    return (actorFlags & 1u) != 0;
}

bool Actor::IsAlive() const noexcept
{
    return !IsDead();
}

bool Actor::IsInCombat(uint64_t aUnk1, uint64_t aUnk2) const noexcept
{
    // FO4 virtual: IsInCombat(UInt64 unk1 = 0, UInt64 unk2 = 0)
    using TIsInCombat = bool(__thiscall*)(const Actor*, uint64_t, uint64_t);
    POINTER_FALLOUT4(void, s_vtbl, 0); // placeholder
    (void)s_vtbl;
    // TODO(FO4): Call via vtable index 0xFE
    return false;
}

Actor* Actor::GetCombatTarget() const noexcept
{
    // TODO(FO4): Access combat data from MiddleProcess
    return nullptr;
}

bool Actor::HasPerk(uint32_t aPerkFormId) const noexcept
{
    // In FO4, perk data is in actorValueData (tArray @ 0x338)
    // TODO(FO4): Proper FO4 perk lookup via Address Library
    return false;
}

uint8_t Actor::GetPerkRank(uint32_t aPerkFormId) const noexcept
{
    // TODO(FO4): Implement via actorValueData
    return 0;
}

int32_t Actor::GetGoldAmount() const noexcept
{
    // TODO(FO4): Look up Gold (caps) form ID from game data
    return 0;
}

Inventory Actor::GetActorInventory() const noexcept
{
    // FO4: Use BGSInventoryList from TESObjectREFR::inventoryList at 0xF8
    Inventory result;
    // TODO(FO4): Iterate inventoryList
    return result;
}

Inventory Actor::GetEquipment() const noexcept
{
    // FO4: Equipped items are in MiddleProcess::Data08::equipData at 0x288
    Inventory result;
    if (!middleProcess || !middleProcess->unk08)
        return result;
    // TODO(FO4): Iterate middleProcess->unk08->equipData
    return result;
}

void Actor::SetActorInventory(const Inventory& aInventory) noexcept
{
    // TODO(FO4): Implement using BGSInventoryList
}

void Actor::SetSpeed(float aSpeed) noexcept
{
    // TODO(FO4): Implementation via Address Library
}

void Actor::SetLevelMod(uint32_t aLevel) noexcept
{
    // TODO(FO4): Implementation via Address Library
}

void Actor::SetPlayerTeammate(bool aSet) noexcept
{
    if (aSet)
        actorFlags |= kFlag_Teammate;
    else
        actorFlags &= ~static_cast<uint32_t>(kFlag_Teammate);
}

void Actor::SetWeaponDrawnEx(bool aDraw) noexcept
{
    SetWeaponDrawn(aDraw);
}

void Actor::ForcePosition(const NiPoint3& acPosition) noexcept
{
    SetPosition(acPosition, true);
}

void Actor::SetPackage(TESPackage* apPackage) noexcept
{
    // TODO(FO4): Implement
}

void Actor::UnEquipAll() noexcept
{
    // TODO(FO4): Implement via Address Library
}

void Actor::QueueUpdate() noexcept
{
    // F4SE: DEFINE_MEMBER_FN(QueueUpdate, void, 0x00D8A1F0, bool, UInt32, bool, UInt32)
    TP_THIS_FUNCTION(TQueueUpdate, void, Actor, bool, uint32_t, bool, uint32_t);
    POINTER_FALLOUT4(TQueueUpdate, s_fn, 41042); // Official FO4 AL ID
    if (!s_fn.GetPtr())
        return;
    TiltedPhoques::ThisCall(s_fn.Get(), this, false, 0, true, 0);
}

void Actor::Reset() noexcept
{
    // TODO(FO4): Implement
}

void Actor::Kill() noexcept
{
    KillImpl(nullptr, 0.f, true, false);
}

void Actor::Respawn() noexcept
{
    Resurrect(false);
}

void Actor::StartCombat(Actor* apTarget) noexcept
{
    // TODO(FO4): Implement via Address Library
}

void Actor::StopCombat() noexcept
{
    // TODO(FO4): Implement via Address Library
}

bool Actor::PlayIdle(TESIdleForm* apIdle) noexcept
{
    // TODO(FO4): Implement via Address Library
    return false;
}

ActorExtension* Actor::GetExtension() noexcept
{
    auto* pExtension = reinterpret_cast<ActorExtension*>(reinterpret_cast<uintptr_t>(this) + sizeof(Actor));
    return pExtension;
}

ExActor* Actor::AsExActor() noexcept
{
    return reinterpret_cast<ExActor*>(this);
}

ExPlayerCharacter* Actor::AsExPlayerCharacter() noexcept
{
    return reinterpret_cast<ExPlayerCharacter*>(this);
}
