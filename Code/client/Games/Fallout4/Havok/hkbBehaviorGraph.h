#pragma once

#include <Havok/hkbVariableValueSet.h>

struct hkEventContext;
struct hkEventType;
struct hkbGenerator;
struct hkbSymbolIdMap;
struct hkbStateMachine;

struct SomeData
{
    uint8_t pad0[0x58];
    hkbGenerator* generator;
    struct hkbBehaviorGraph* behaviorGraph;
    uint8_t pad68[0x84 - 0x68];
    uint8_t byte84;
    uint8_t byte85;
    uint8_t pad86[0x90 - 0x86];
};

struct hkbBehaviorGraph
{
    virtual ~hkbBehaviorGraph();

    virtual void sub_01();
    virtual void sub_02();
    virtual void sub_03();
    virtual void sub_04();
    virtual void sub_05();
    virtual void SendEvent(hkEventContext& aContext, hkEventType& aType);

    struct Struct98
    {
        SomeData* data;
        int count;
    };

    uint8_t pad8[0x80 - 0x8];
    hkbStateMachine* stateMachine;
    uint8_t pad88[0x98 - 0x88];
    Struct98* struct98;
    uint8_t padA0[0xB8 - 0xA0];
    hkbSymbolIdMap* symbolIdMap;
    uint8_t padC0[0xD8 - 0xC0];
    hkbVariableValueSet<uint32_t>* animationVariables;
    uint8_t padE0[0x12C - 0xE0];
    uint8_t byte12C;
    uint8_t byte12D;
    uint8_t byte12E;
};

static_assert(offsetof(hkbBehaviorGraph, struct98) == 0x98);
static_assert(offsetof(hkbBehaviorGraph, symbolIdMap) == 0xB8);
static_assert(offsetof(hkbBehaviorGraph, animationVariables) == 0xD8);
