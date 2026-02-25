#pragma once

#include <Forms/TESForm.h>
#include <Misc/BSString.h>

struct BGSKeyword : TESForm
{
    BSString keyword;
};

static_assert(sizeof(BGSKeyword) == 0x30); // 0x20 (TESForm) + 0x10 (BSString)
