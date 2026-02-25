#include <TiltedOnlinePCH.h>

#include <Games/TES.h>

#include <Actor.h>

#if TP_FALLOUT4

ModManager* ModManager::Get() noexcept
{
    POINTER_FALLOUT4(ModManager*, modManager, 0);
    return *modManager.Get();
}

uint32_t Mod::GetFormId(uint32_t aBaseId) const noexcept
{
    if (IsLite())
    {
        aBaseId &= 0xFFF;
        aBaseId |= 0xFE000000;
        aBaseId |= uint32_t(liteId) << 12;
    }
    else
    {
        aBaseId &= 0xFFFFFF;
        aBaseId |= uint32_t(standardId) << 24;
    }

    return aBaseId;
}

uint32_t ModManager::Spawn(NiPoint3& aPosition, NiPoint3& aRotation, TESObjectCELL* apParentCell, TESWorldSpace* apWorldSpace, Actor* apCharacter) noexcept
{
    return 0;
}

Mod* ModManager::GetByName(const char* acpName) const noexcept
{
    return nullptr;
}

TESObjectCELL* ModManager::GetCellFromCoordinates(int32_t aX, int32_t aY, TESWorldSpace* aWorldSpace, bool aSpawnCell) noexcept
{
    return nullptr;
}

#endif
