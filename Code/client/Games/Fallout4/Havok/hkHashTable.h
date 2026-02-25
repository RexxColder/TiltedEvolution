#pragma once

#include <Misc/BSFixedString.h>

#pragma pack(push, 1)

struct hkHashTable
{
    struct Entry
    {
        BSFixedString key;
        int32_t value;
        uint32_t padC;
        Entry* next;
    };

    uint32_t bucketCount;
    uint8_t pad4[0xC - 0x4];
    void* end;
    uint8_t pad[0x1C - 0x14];
    Entry* buckets;
};

#pragma pack(pop)

static_assert(offsetof(hkHashTable, end) == 0xC);
static_assert(offsetof(hkHashTable, buckets) == 0x1C);
