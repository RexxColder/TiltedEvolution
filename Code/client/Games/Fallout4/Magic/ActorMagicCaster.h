#pragma once

#include "MagicCaster.h"

#if TP_FALLOUT4

#include <Games/Skyrim/NetImmerse/NiPointer.h>

struct Actor;
struct NiNode;

struct ActorMagicCaster : MagicCaster
{
    uint8_t unk48[0x70];
    Actor* pCasterActor;
    NiNode* pMagicNode;
};

#endif
