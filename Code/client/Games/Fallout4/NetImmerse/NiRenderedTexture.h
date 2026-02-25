#pragma once

#if TP_FALLOUT4

#pragma once

#include <NetImmerse/NiTexture.h>
#include <NetImmerse/Ni2DBuffer.h>

struct NiRenderedTexture : NiTexture
{
    virtual ~NiRenderedTexture();

    Ni2DBuffer* buffer;
};


#endif
