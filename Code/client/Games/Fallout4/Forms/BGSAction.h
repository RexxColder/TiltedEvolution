#pragma once

#include <Forms/BGSKeyword.h>

struct BGSAction : BGSKeyword
{
    uint32_t counter;
};

static_assert(sizeof(BGSAction) == 0x38); // 0x30 (BGSKeyword) + 4 + padding
