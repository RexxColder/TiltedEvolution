#pragma once
#pragma pack(push, 1)

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;

#if TP_FALLOUT4

struct ViewportConfig
{
    char pad[8];
    void* handle;
    void* wndProc;
    void* hIcon;
    const char* name;
};

struct WindowConfig
{
    int32_t iSizeW;
    int32_t iSizeH;
    int32_t iLocationX;
    int32_t iLocationY;
    char pad[8];
    bool bFullScreenDisplay;
    bool bBorderlessDisplay;
    char pad2[22 - 16];
    bool bForce;
};

struct BGSRenderer
{
    static BGSRenderer* Get();
    static ID3D11Device* GetDevice();

    char pad[28];
    uint32_t unk;
    bool unk2;
    bool isWindowedMode;
    char pad0[4];
    uint32_t syncInterval;
    char pad1[14];
    ID3D11Device* pD3dDevice;
    ID3D11DeviceContext* pD3dContext;
    void* windowHandle;
    char pad2[8];
    uint32_t windowWidth;
    uint32_t windowHeight;
    IDXGISwapChain* pSwapChain;
};

#endif

#pragma pack(pop)
