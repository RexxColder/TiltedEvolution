#pragma once

#include <TESObjectREFR.h>

template <class T> struct BSTEventSink;

// Very nasty work around to avoid template code duplication
namespace details
{
void InternalRegisterSink(void* apEventDispatcher, void* apSink) noexcept;
void InternalUnRegisterSink(void* apEventDispatcher, void* apSink) noexcept;
void InternalPushEvent(void* apEventDispatcher, void* apEvent) noexcept;
} // namespace details

template <class T> struct EventDispatcher
{
    void RegisterSink(BSTEventSink<T>* apSink) noexcept { details::InternalRegisterSink(reinterpret_cast<void*>(this), reinterpret_cast<void*>(apSink)); }

    void UnRegisterSink(BSTEventSink<T>* apSink) noexcept { details::InternalUnRegisterSink(reinterpret_cast<void*>(this), reinterpret_cast<void*>(apSink)); }

    void PushEvent(const T* apEvent) noexcept { details::InternalPushEvent(reinterpret_cast<void*>(this), reinterpret_cast<void*>(apEvent)); }

    uint8_t pad0[0x58];
};

struct TESLoadGameEvent
{
};

// Add other events as needed for compilation
struct TESActivateEvent
{
    TESObjectREFR* object;
};

struct TESDeathEvent
{
    TESObjectREFR* pActorDying;
    TESObjectREFR* pActorKiller;
    bool isDead;
};

struct TESHitEvent
{
    TESObjectREFR* hit;
    TESObjectREFR* hitter;
};

struct EventDispatcherManager
{
    static EventDispatcherManager* Get() noexcept;

    // Minimal set of dispatchers for now
    EventDispatcher<TESLoadGameEvent> loadGameEvent;
    EventDispatcher<TESActivateEvent> activateEvent;
    EventDispatcher<TESDeathEvent> deathEvent;
    EventDispatcher<TESHitEvent> hitEvent;

    // Fallout 4 might have different amount of dispatchers and different offsets.
    // This is just a placeholder to make it compile.
};
