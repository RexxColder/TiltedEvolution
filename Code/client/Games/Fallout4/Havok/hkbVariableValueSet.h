#pragma once

#include <cstdint>

template <class T> struct hkbVariableValueSet
{
    virtual ~hkbVariableValueSet() {};

    uint8_t pad8[0x10 - 0x8];
    T* data;  // 10
    int size; // 18
};
