#pragma once

#if TP_FALLOUT4

struct hkbStateMachine
{
    virtual ~hkbStateMachine();

    uint8_t pad8[0x38 - 0x8];
    char* name;
};

#endif
