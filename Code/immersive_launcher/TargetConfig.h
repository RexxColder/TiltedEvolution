// Copyright (C) 2021 TiltedPhoques SRL.
// For licensing information see LICENSE at the root of this distribution.
#pragma once

#include <cstdint>
#include <limits>
#include <BuildInfo.h>

#define CLIENT_DLL 0

struct TargetConfig
{
    const wchar_t* dllClientName;
    const wchar_t* fullGameName;
    uint32_t steamAppId;
    uint32_t exeLoadSz;
    // Needs to be kept up to date.
    uint32_t exeDiskSz;
};

// clang-format off

static constexpr TargetConfig CurrentTarget{
    L"FalloutTogether.dll", 
    L"Fallout 4", 
    377160, 0x40000000, 68993024};
#define TARGET_NAME L"Fallout4"
#define TARGET_NAME_A "Fallout4"
#define PRODUCT_NAME L"Fallout Together"
#define SHORT_NAME L"Fallout 4"

// clang-format on
