#pragma once

struct TESForm;
struct MiddleProcess;
struct TESAmmo;

#if TP_FALLOUT4

struct AIProcess
{
    void* unk0;
    MiddleProcess* middleProcess;
    void* unk8;
    void* packageLock;
    struct TESPackage* package;
    uint32_t unk10[7];
    uint32_t unk34[8];
    float unk54;
    uint32_t unk58[4];
    TESForm* equippedObject[2];

    uint8_t pad88[0x137 - 0x88];

    int8_t movementType;
};

struct HighProcessData
{
    uint8_t pad0[0x218];
    char* strVoiceSubtitle;
};

#endif
