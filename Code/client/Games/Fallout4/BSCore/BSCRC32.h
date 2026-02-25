#pragma once

#if TP_FALLOUT4

#pragma once

namespace creation
{
struct BSCRC32
{
    void GenerateCRC(uint32_t& aiCRC, uint32_t auiData, uint32_t auiDefaultvalue);
};
} // namespace creation


#endif
