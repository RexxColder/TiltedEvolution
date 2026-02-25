#pragma once

#include <Games/Primitives.h>

#if TP_FALLOUT4

struct NiNode;
struct NiObject;
struct NiCamera;
struct TESCameraState;

struct TESCamera
{
    virtual ~TESCamera(){};

    virtual void SetNode(NiNode* node){};
    virtual void Update(){};

    NiCamera* GetNiCamera() { return nullptr; }

    float rotZ;
    float rotX;
    void* pos;
    float zoom;
    NiNode* cameraNode;
    TESCameraState* state;
    bool unk;
};

#endif
