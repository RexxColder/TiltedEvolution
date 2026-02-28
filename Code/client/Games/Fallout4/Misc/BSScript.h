#pragma once

#include <Misc/BSFixedString.h>
#include <Games/ActorExtension.h>

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
        uint32_t GetPageForFrame() { return 0; }
        Variable* GetStackFrameVariable(uint32_t aIndex, uint32_t aPageHint, void* aUnk) { return nullptr; }
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
        virtual void GetScriptObjectType1(BSFixedString* apName, void** apPtr) {}
    };

    struct IFunction
    {
        virtual ~IFunction() {}
        virtual BSFixedString& GetName() = 0;
        virtual BSFixedString& GetObjectTypeName() = 0;
        virtual BSFixedString& GetStateName() = 0;
        virtual Variable::Type& GetReturnType() = 0;
        virtual uint32_t GetParamCount() = 0;
        virtual void GetParam(uint32_t aIndex, BSFixedString& apNameOut, Variable::Type& aTypeOut) = 0;
        virtual uint32_t GetStackFrameSize() = 0;
        virtual bool GetIsNative() = 0;
        virtual bool GetIsStatic() = 0;
        virtual bool GetIsEmpty() = 0;
        virtual void* GetFunctionType() = 0;
        virtual uint32_t GetUserFlags() = 0;
        virtual BSFixedString& GetDocString() = 0;
        virtual void InsertLocals(StackFrame*) = 0;
        virtual void Call(Stack*, void*, IVirtualMachine*, bool) = 0;
        virtual BSFixedString& GetSourceFilename() = 0;
        virtual bool TranslateIPToLineNumber(uint32_t, uint32_t& aLineNumberOut) = 0;
        virtual bool GetVarNameForStackIndex(uint32_t aIndex, BSFixedString& aNameOut) = 0;
        virtual bool CanBeCalledFromTasklets() = 0;
        virtual void SetCallableFromTasklets(bool aCallable) = 0;
    };

    struct NativeFunctionBase : IFunction
    {
        BSFixedString name;
        BSFixedString objectName;
        BSFixedString stateName;
        BSFixedString documentation;
        Variable::Type returnType;
        uint32_t flags;
        bool isStatic;
        bool isCallableFromTask;
        uint32_t paramCount;

        virtual ~NativeFunctionBase() {}

        BSFixedString& GetName() override { return name; }
        BSFixedString& GetObjectTypeName() override { return objectName; }
        BSFixedString& GetStateName() override { return stateName; }
        Variable::Type& GetReturnType() override { return returnType; }
        uint32_t GetParamCount() override { return paramCount; }
        void GetParam(uint32_t aIndex, BSFixedString& apNameOut, Variable::Type& aTypeOut) override {}
        uint32_t GetStackFrameSize() override { return 0; }
        bool GetIsNative() override { return true; }
        bool GetIsStatic() override { return isStatic; }
        bool GetIsEmpty() override { return false; }
        void* GetFunctionType() override { return nullptr; }
        uint32_t GetUserFlags() override { return flags; }
        BSFixedString& GetDocString() override { return documentation; }
        void InsertLocals(StackFrame*) override {}
        void Call(Stack*, void*, IVirtualMachine*, bool) override {}
        BSFixedString& GetSourceFilename() override { static BSFixedString s("<native>"); return s; }
        bool TranslateIPToLineNumber(uint32_t, uint32_t& aLineNumberOut) override { aLineNumberOut = 0; return false; }
        bool GetVarNameForStackIndex(uint32_t, BSFixedString& aNameOut) override { aNameOut = ""; return false; }
        bool CanBeCalledFromTasklets() override { return isCallableFromTask; }
        void SetCallableFromTasklets(bool aCallable) override { isCallableFromTask = aCallable; }
    };

    // Fallout-specific native function implementations
    struct IsRemotePlayerFunc : NativeFunctionBase
    {
        using FunctionType = bool(*)(Actor*);

        FunctionType pFunction;

        IsRemotePlayerFunc(const char* apFunctionName, const char* apClassName, FunctionType aFunction, Variable::Type aType);

        bool MarshallAndDispatch(Variable* apBaseVar, IVirtualMachine* apVm, uint32_t aStackID, Variable* apResult, StackFrame* apStackFrame);
    };

    struct IsPlayerFunc : NativeFunctionBase
    {
        using FunctionType = bool(*)(Actor*);

        FunctionType pFunction;

        IsPlayerFunc(const char* apFunctionName, const char* apClassName, FunctionType aFunction, Variable::Type aType);

        bool MarshallAndDispatch(Variable* apBaseVar, IVirtualMachine* apVm, uint32_t aStackID, Variable* apResult, StackFrame* apStackFrame);
    };

    struct DidLaunchSkyrimTogetherFunc : NativeFunctionBase
    {
        using FunctionType = bool(*)();

        FunctionType pFunction;

        DidLaunchSkyrimTogetherFunc(const char* apFunctionName, const char* apClassName, FunctionType aFunction, Variable::Type aType);

        bool MarshallAndDispatch(Variable* apBaseVar, IVirtualMachine* apVm, uint32_t aStackID, Variable* apResult, StackFrame* apStackFrame);
    };
};

template <> void BSScript::Variable::Set(int32_t aValue) noexcept;
template <> void BSScript::Variable::Set(float aValue) noexcept;
template <> void BSScript::Variable::Set(bool aValue) noexcept;
template <> void BSScript::Variable::Set(const char* acpValue) noexcept;

#endif
