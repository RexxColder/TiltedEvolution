#include <TiltedOnlinePCH.h>

#include <Misc/BSFixedString.h>

BSFixedString::BSFixedString()
    : data(nullptr)
{
}

BSFixedString::BSFixedString(const char* acpData)
{
    data = const_cast<char*>(acpData);
}

BSFixedString::~BSFixedString()
{
}

void BSFixedString::Set(const char* acpData)
{
    data = const_cast<char*>(acpData);
}

void BSFixedString::Release() noexcept
{
    data = nullptr;
}
