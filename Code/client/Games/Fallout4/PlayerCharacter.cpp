#include <TiltedOnlinePCH.h>
#include <PlayerCharacter.h>
#include <World.h>

// ============================================================================
// PlayerCharacter — Fallout 4 implementation
// ============================================================================

PlayerCharacter* PlayerCharacter::Get() noexcept
{
    // F4SE: extern RelocPtr<PlayerCharacter*> g_player;
    POINTER_FALLOUT4(PlayerCharacter*, s_player, 101313); // Official FO4 AL ID
    return s_player.Get() ? *s_player.Get() : nullptr;
}

const GameArray<BGSCharacterTint::Entry*>& PlayerCharacter::GetTints() const noexcept
{
    // tints @ 0xD00 in FO4 (Skyrim: baseTints @ 0xB18)
    return *tints;
}

void PlayerCharacter::SetDifficulty(int32_t aDifficulty, bool aForceUpdate) noexcept
{
    // In FO4, there's a native game function for difficulty
    TP_THIS_FUNCTION(TSetDifficulty, void, PlayerCharacter, int32_t, bool);
    POINTER_FALLOUT4(TSetDifficulty, s_fn, 40889); // Official FO4 AL ID
    if (!s_fn.GetPtr())
        return;
    TiltedPhoques::ThisCall(s_fn.Get(), this, aDifficulty, aForceUpdate);
}
