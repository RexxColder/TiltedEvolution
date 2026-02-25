#pragma once

#include <Games/Primitives.h>
#include <Havok/BShkbAnimationGraph.h>

struct BSFixedString;

struct BSAnimationGraphManager
{
    virtual ~BSAnimationGraphManager();
    virtual void sub_1(void* apUnk1);

    void Release()
    {
        if (InterlockedDecrement(&refCount) == 0)
            this->~BSAnimationGraphManager();
    }

    volatile LONG refCount;
    uint32_t pad0C;
    void* pad_ptrs[6];
    BSTSmallArray<BShkbAnimationGraph> animationGraphs;
    void* pad_ptrs2[9];
    BSRecursiveLock lock;
    void* unkPtrAfterLock;
    uint32_t animationGraphIndex;

    uint64_t GetDescriptorKey(int aForceIndex = -1);
    uint32_t ReSendEvent(BSFixedString* apEventName);
};

static_assert(offsetof(BSAnimationGraphManager, animationGraphs) == 0x40);
static_assert(offsetof(BSAnimationGraphManager, lock) == 0xA0);
static_assert(offsetof(BSAnimationGraphManager, animationGraphIndex) == 0xB0);
static_assert(sizeof(BSAnimationGraphManager) >= 0xB8);
