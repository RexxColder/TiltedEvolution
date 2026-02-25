#pragma once

#pragma pack(push, 1)

// ============================================================================
// Fallout 4 Save / Load structures
// NOTE: In FO4 the manager class is BGSSaveLoadGame (not BGSSaveLoadManager).
//       The save name is passed as a direct parameter, not stored inside a
//       struct at a fixed offset like Skyrim does.
// ============================================================================

struct BGSSaveLoadGame
{
    virtual ~BGSSaveLoadGame() = 0;
};

// ---------------------------------------------------------------------------
// BGSSaveFormBuffer — same field layout as Skyrim, offsets validated via F4SE
// ---------------------------------------------------------------------------
struct BGSSaveFormBuffer
{
    BGSSaveFormBuffer();
    virtual ~BGSSaveFormBuffer() {}

    void WriteId(uint32_t aId) noexcept;

    char* buffer;         // 0x08
    uint32_t capacity;    // 0x10
    uint32_t position;    // 0x14
    uint8_t formId[3];    // 0x18
    uint32_t changeFlags; // 0x1B

    uint8_t pad[0x100]; // safety padding — exact size not fully reversed
};

static_assert(offsetof(BGSSaveFormBuffer, formId) == 0x18);
static_assert(offsetof(BGSSaveFormBuffer, changeFlags) == 0x1B);

// ---------------------------------------------------------------------------
// BGSSaveLoadBuffer — thin wrapper around a raw buffer pointer
// ---------------------------------------------------------------------------
struct BGSSaveLoadBuffer
{
    char* pBuffer;
};

static_assert(sizeof(BGSSaveLoadBuffer) == 0x8);

// ---------------------------------------------------------------------------
// BGSSaveGameBuffer
// ---------------------------------------------------------------------------
struct BGSSaveGameBuffer
{
    virtual ~BGSSaveGameBuffer();

    BGSSaveLoadBuffer Buffer;
    uint32_t iBufferSize;
    uint32_t iBufferPosition;
};

static_assert(sizeof(BGSSaveGameBuffer) == 0x18);

// ---------------------------------------------------------------------------
// BGSChangeFlags
// ---------------------------------------------------------------------------
struct BGSChangeFlags
{
    int32_t iFlags;
};

static_assert(sizeof(BGSChangeFlags) == 0x4);

// ---------------------------------------------------------------------------
// Auxiliary save data helpers (same as Skyrim)
// ---------------------------------------------------------------------------
struct BGSSaveLoadFormInfo
{
    uint8_t cData;
};

static_assert(sizeof(BGSSaveLoadFormInfo) == 0x1);

struct BGSNumericIDIndex
{
    uint8_t cData1;
    uint8_t cData2;
    uint8_t cData3;
};

struct BGSSaveLoadFormHeader
{
    BGSNumericIDIndex FormIDIndex;
    BGSChangeFlags iChangeFlags;
    BGSSaveLoadFormInfo FormInfo;
    uint8_t cVersion;
};

static_assert(sizeof(BGSSaveLoadFormHeader) == 0x9);

struct BGSSaveFormBufferReal : BGSSaveGameBuffer
{
    BGSSaveLoadFormHeader Header;
    uint8_t pad21[0x7];
    struct TESForm* pForm;
};

static_assert(sizeof(BGSSaveFormBufferReal) == 0x30);

// ---------------------------------------------------------------------------
// BGSLoadFormBuffer — layout matches Skyrim (used in cross-game SaveLoad.cpp)
// ---------------------------------------------------------------------------
struct BGSLoadFormBuffer
{
    BGSLoadFormBuffer(uint32_t aChangeFlags);
    virtual ~BGSLoadFormBuffer() {}

    void SetSize(const uint32_t aSize) noexcept { capacity = size1 = size2 = aSize; }

    const char* buffer;      // 0x08
    size_t capacity;         // 0x10
    uint32_t unk18;          // 0x18
    int32_t unk1C;           // 0x1C — init'd to -1
    uint32_t size1;          // 0x20
    uint32_t position;       // 0x24
    uint32_t formId;         // 0x28
    uint32_t size2;          // 0x2C
    uint32_t unk30;          // 0x30
    uint32_t unk34;          // 0x34
    struct TESForm* form;    // 0x38
    uint32_t changeFlags;    // 0x40
    uint32_t maybeMoreFlags; // 0x44
    uint8_t unk48;           // 0x48
    uint8_t unk49;
    uint8_t unk4A;
    uint8_t loadFlag; // 0x4B
};

static_assert(offsetof(BGSLoadFormBuffer, changeFlags) == 0x40);
static_assert(offsetof(BGSLoadFormBuffer, loadFlag) == 0x4B);

// ---------------------------------------------------------------------------
// BGSSaveLoadScrapBuffer / BGSLoadGameBuffer
// ---------------------------------------------------------------------------
struct __declspec(align(8)) BGSSaveLoadScrapBuffer
{
    char* pBuffer;
    struct ScrapHeap* pScrapHeap;
    uint32_t uiSize;
};

static_assert(sizeof(BGSSaveLoadScrapBuffer) == 0x18);

struct BGSLoadGameBuffer
{
    virtual ~BGSLoadGameBuffer();

    BGSSaveLoadScrapBuffer Buffer;
    uint32_t iBufferSize;
    uint32_t iBufferPosition;
};

static_assert(sizeof(BGSLoadGameBuffer) == 0x28);

struct __declspec(align(8)) BGSLoadFormData
{
    uint32_t iFormID;
    uint32_t uiDataSize;
    uint32_t uiUncompressedSize;
    TESForm* pForm;
    BGSChangeFlags iChangeFlags;
    BGSChangeFlags iOldChangeFlags;
    uint16_t usFlags;
    BGSSaveLoadFormInfo FormInfo;
    uint8_t cVersion;
};

struct BGSLoadFormBufferReal : BGSLoadGameBuffer, BGSLoadFormData
{
};

#pragma pack(pop)
