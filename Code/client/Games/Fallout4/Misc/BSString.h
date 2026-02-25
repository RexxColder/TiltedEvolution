#pragma once

#include <cstdint>

struct BSString
{
    BSString()
        : data{nullptr}
        , length{0}
        , capacity{0}
    {
    }
    ~BSString();

    [[nodiscard]] const char* AsAscii() { return data; }

private:
    const char* data;
    uint32_t length;
    uint32_t capacity;
};

static_assert(sizeof(BSString) == 0x10);
