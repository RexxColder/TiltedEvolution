#pragma once

#include <Forms/TESActorBase.h>
#include <Components/TESRaceForm.h>

struct BGSHeadPart;
struct TESClass;
struct TESCombatStyle;
struct BGSOutfit;
struct TESRace;

struct TESNPC : TESActorBase
{
    static constexpr FormType Type = FormType::Npc;

    static TESNPC* Create(const String& acBuffer, uint32_t aChangeFlags) noexcept;

    // Components used in Forms.cpp
    TESRaceForm raceForm;
    TESClass* npcClass;
    TESCombatStyle* combatStyle;
    TESRace* overlayRace;
    BGSOutfit* outfits[2];

    BGSHeadPart** headparts;
    uint8_t headpartsCount;
    uint8_t padBase[7]; // Assuming alignment

    BGSHeadPart* GetHeadPart(uint32_t aType);
    void Serialize(String* apSaveBuffer) const noexcept;
    void Deserialize(const String& acBuffer, uint32_t aChangeFlags) noexcept;
    void Initialize() noexcept;
};
