
#include <TiltedOnlineApp.h>
#include <TiltedOnlinePCH.h>

#include <Commctrl.h>
#include <Windows.h>

#include <spdlog/spdlog.h>
#include <base/dialogues/win/TaskDialog.h>

std::unique_ptr<TiltedOnlineApp> g_appInstance{nullptr};

extern HICON g_SharedWindowIcon;

static void ShowAddressLibraryError(const wchar_t* apGamePath)
{
    const wchar_t* gameName = L"Skyrim";
    const wchar_t* libraryName = L"Skyrim Address Library";
    const wchar_t* troubleshootingUrl = LR"(https://wiki.tiltedphoques.com/tilted-online/guides/troubleshooting/address-library-error)";
    const wchar_t* modPageUrl = LR"(https://www.nexusmods.com/skyrimspecialedition/mods/32444?tab=files)";

#if TP_FALLOUT4
    gameName = L"Fallout 4";
    libraryName = L"Fallout 4 Address Library";
    modPageUrl = LR"(https://www.nexusmods.com/fallout4/mods/47327?tab=files)";
#endif

    auto errorDetail = fmt::format(L"Looking for it here: {}\\Data\\SKSE\\Plugins", apGamePath);
#if TP_FALLOUT4
    errorDetail = fmt::format(L"Looking for it here: {}\\Data\\F4SE\\Plugins", apGamePath);
#endif

    Base::TaskDialog dia(g_SharedWindowIcon, L"Error", fmt::format(L"Failed to load {}", libraryName).c_str(), L"Make sure you have the correct Address Library installed.", errorDetail.c_str());

    dia.AppendButton(0xBEED, L"Visit troubleshooting page on wiki.tiltedphoques.com");
    dia.AppendButton(0xBEEF, L"Visit Address Library modpage on nexusmods.com");
    const int result = dia.Show();
    if (result == 0xBEEF)
    {
        ShellExecuteW(nullptr, L"open", modPageUrl, nullptr, nullptr, SW_SHOWNORMAL);
    }
    else if (result == 0xBEED)
    {
        ShellExecuteW(nullptr, L"open", troubleshootingUrl, nullptr, nullptr, SW_SHOWNORMAL);
    }

    exit(4);
}

void RunTiltedInit(const std::filesystem::path& acGamePath, const String& aExeVersion)
{
    spdlog::info("RunTiltedInit: Starting...");
    spdlog::info("Game path: {}", acGamePath.string());
    spdlog::info("Exe version: {}", aExeVersion.c_str());

    if (!VersionDb::Get().Load(acGamePath, aExeVersion))
    {
        spdlog::error("VersionDb::Load failed!");
        ShowAddressLibraryError(acGamePath.c_str());
    }

    spdlog::info("VersionDb loaded successfully");

    // VersionDb::Get().DumpToTextFile(R"(S:\Work\Tilted\fallout\_addresslib.txt)");

    spdlog::info("Creating TiltedOnlineApp...");
    g_appInstance = std::make_unique<TiltedOnlineApp>();

    spdlog::info("Installing hooks...");
    TiltedOnlineApp::InstallHooks2();
    TP_HOOK_COMMIT;

    spdlog::info("Hooks installed, init complete!");
}

void RunTiltedApp()
{
    spdlog::info("RunTiltedApp: Starting main...");
    g_appInstance->BeginMain();
}
