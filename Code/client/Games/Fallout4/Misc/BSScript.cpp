#include <Misc/BSScript.h>

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

#endif
