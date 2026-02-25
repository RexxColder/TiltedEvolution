#pragma once

#include <cstdint>
#include <type_traits>

namespace internal
{
template <class T> struct RttiLocator
{
    RttiLocator(uint32_t aId) {}
    static const void* Get() { return nullptr; }
};

using TDynamicCast = void*(void* apThis, uint32_t a1, const void* acpBaseRTTI, const void* acpTargetRTTI, uint32_t a4);
// DynamicCast is usually at a fixed address or AL ID
} // namespace internal

template <class T, class U> T* Cast(U* apPtr)
{
    if (!apPtr)
        return nullptr;

    // For FO4, we'll need to implement this correctly using the dynamic cast function from Address Library.
    // Temporarily, we use static_cast for classes we know are compatible,
    // but this is UNSAFE. For compilation purposes only.
    return static_cast<T*>(apPtr);
}

// Forward declarations
struct BaseFormComponent;
extern template struct internal::RttiLocator<BaseFormComponent>;
struct TESForm;
extern template struct internal::RttiLocator<TESForm>;
struct Actor;
extern template struct internal::RttiLocator<Actor>;
struct PlayerCharacter;
extern template struct internal::RttiLocator<PlayerCharacter>;
struct TESObjectREFR;
extern template struct internal::RttiLocator<TESObjectREFR>;
