#pragma once

#if TP_FALLOUT4

#include <Camera/TESCamera.h>

struct PlayerCamera : public TESCamera
{
    static PlayerCamera* Get() noexcept;

    bool IsFirstPerson() noexcept;
    void ForceFirstPerson() noexcept;
    void ForceThirdPerson() noexcept;

    float rotZ;
    float rotX;
    NiPoint3 pos;
    float zoom;
    NiNode* cameraNode;
    TESCameraState* state;
    bool unk;
};

#endif
