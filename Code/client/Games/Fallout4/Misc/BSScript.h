#pragma once

#include <Misc/BSFixedString.h>

#if TP_FALLOUT4

struct BSScript
{
    struct Object
    {
        uint64_t GetHandle();
    };

    struct Variable
    {
        Variable();
        ~Variable() noexcept;

        void Reset() noexcept;
        void Clear() noexcept;
        Object* GetObject() const noexcept;

        template <class T> void Set(T aValue) noexcept
        {
        }

        enum Type : uint64_t
        {
            kEmpty,
            kObject,
            kString,
            kInteger,
            kFloat,
            kBoolean,
            kMax = 16
        };

        union Data
        {
            int32_t i;
            const char* s;
            float f;
            bool b;
            Object* pObj;
        };

        Type type;
        Data data;
    };

    struct StackFrame
    {
        void* pParent;
    };

    struct Stack
    {
        uint32_t GetPageForFrame(StackFrame* apFrame) { return 0; }
        Variable* GetStackFrameVariable(StackFrame* apFrame, uint32_t aIndex, uint32_t aPageHint) { return nullptr; }
    };

    struct IObjectHandlePolicy
    {
        static IObjectHandlePolicy* Get() noexcept;
        virtual ~IObjectHandlePolicy() {}
    };

    struct IVirtualMachine
    {
        virtual ~IVirtualMachine() {}
        virtual void SendEvent(uint64_t aId, const BSFixedString& acEventName, void* apArgs) const noexcept {}
    };
};

template <> void BSScript::Variable::Set(int32_t aValue) noexcept;
template <> void BSScript::Variable::Set(float aValue) noexcept;
template <> void BSScript::Variable::Set(bool aValue) noexcept;
template <> void BSScript::Variable::Set(const char* acpValue) noexcept;

#endif
