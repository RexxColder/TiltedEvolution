#include <Misc/BSScript.h>
#include <Misc/GameVM.h>

#if TP_FALLOUT4

uint64_t BSScript::Object::GetHandle()
{
    return 0;
}

BSScript::Variable::Variable()
{
}

BSScript::Variable::~Variable() noexcept
{
    Reset();
}

void BSScript::Variable::Reset() noexcept
{
}

void BSScript::Variable::Clear() noexcept
{
    Reset();
    type = kEmpty;
}

template <> void BSScript::Variable::Set(int32_t aValue) noexcept
{
    Reset();
    type = kInteger;
    data.i = aValue;
}

template <> void BSScript::Variable::Set(float aValue) noexcept
{
    Reset();
    type = kFloat;
    data.f = aValue;
}

template <> void BSScript::Variable::Set(bool aValue) noexcept
{
    Reset();
    type = kBoolean;
    data.b = aValue;
}

template <> void BSScript::Variable::Set(const char* acpValue) noexcept
{
    Reset();
    type = kString;
    data.s = acpValue;
}

BSScript::Object* BSScript::Variable::GetObject() const noexcept
{
    if (type > Type::kMax)
    {
        bool isArray = type & 1;
        if (isArray)
            return nullptr;
    }
    else if (type != Type::kObject)
        return nullptr;

    return data.pObj;
}

// ============================================================
// Fallout 4 Native Papyrus Function Implementations
// ============================================================

BSScript::IsRemotePlayerFunc::IsRemotePlayerFunc(const char* apFunctionName, const char* apClassName, FunctionType aFunction, Variable::Type aType)
    : NativeFunctionBase()
{
    pFunction = aFunction;
    name.Set(apFunctionName);
    objectName.Set(apClassName);
    stateName.Set("");
    returnType = aType;
    isStatic = true;
    isCallableFromTask = false;
    paramCount = 1;
}

bool BSScript::IsRemotePlayerFunc::MarshallAndDispatch(Variable* apBaseVar, IVirtualMachine* apVm, uint32_t aStackID, Variable* apResult, StackFrame* apStackFrame)
{
    // For Fallout 4, we need to extract the Actor from the stack
    // This is a simplified version - actual implementation needs proper address library
    apResult->Set<bool>(false);
    return true;
}

BSScript::IsPlayerFunc::IsPlayerFunc(const char* apFunctionName, const char* apClassName, FunctionType aFunction, Variable::Type aType)
    : NativeFunctionBase()
{
    pFunction = aFunction;
    name.Set(apFunctionName);
    objectName.Set(apClassName);
    stateName.Set("");
    returnType = aType;
    isStatic = true;
    isCallableFromTask = false;
    paramCount = 1;
}

bool BSScript::IsPlayerFunc::MarshallAndDispatch(Variable* apBaseVar, IVirtualMachine* apVm, uint32_t aStackID, Variable* apResult, StackFrame* apStackFrame)
{
    // For Fallout 4, we need to extract the Actor from the stack
    apResult->Set<bool>(false);
    return true;
}

BSScript::DidLaunchSkyrimTogetherFunc::DidLaunchSkyrimTogetherFunc(const char* apFunctionName, const char* apClassName, FunctionType aFunction, Variable::Type aType)
    : NativeFunctionBase()
{
    pFunction = aFunction;
    name.Set(apFunctionName);
    objectName.Set(apClassName);
    stateName.Set("");
    returnType = aType;
    isStatic = true;
    isCallableFromTask = false;
    paramCount = 0;
}

bool BSScript::DidLaunchSkyrimTogetherFunc::MarshallAndDispatch(Variable* apBaseVar, IVirtualMachine* apVm, uint32_t aStackID, Variable* apResult, StackFrame* apStackFrame)
{
    // Always return true - means the mod launcher was used
    apResult->Set<bool>(true);
    return true;
}

#endif
