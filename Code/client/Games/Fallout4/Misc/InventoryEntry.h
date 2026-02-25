#pragma once

#if TP_FALLOUT4

#pragma once

struct TESBoundObject;
struct ExtraDataList;

struct InventoryEntry
{
    TESBoundObject* pObject;
    GameList<ExtraDataList>* pExtraLists;
    int32_t count;
};


#endif
