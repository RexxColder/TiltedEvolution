
local function build_client(name, game)
target(name)
    set_kind("static")
    set_group("Client")
    add_includedirs(".","../../Libraries/")
    set_pcxxheader("TiltedOnlinePCH.h")

    local game_path = "Games/" .. game
    local exclude_path = game == "Skyrim" and "Games/Fallout4" or "Games/Skyrim"
    
    -- First add game-specific files
    add_files(game_path .. "/**.cpp")
    add_headerfiles(game_path .. "/**.h")
    
    -- exclude other game and shared misc files
    add_files("**.cpp|" .. exclude_path .. "/**|Games/Misc/**")
    add_headerfiles("**.h|" .. exclude_path .. "/**|Games/Misc/**")

    after_install(function(target)
        -- copy dlls
        for _, pkg_with_dlls in ipairs({"cef", "discord"}) do
            local linkdir = target:pkg(pkg_with_dlls):get("linkdirs")
            local bindir = path.join(linkdir, "..", "bin")
            os.cp(bindir, target:installdir())
        end
        -- copy ui
        local uidir = path.join(target:scriptdir(), "..", "skyrim_ui", "src")
        os.cp(path.join(uidir, "assets", "images", "cursor.dds"), path.join(target:installdir(), "bin", "assets", "images", "cursor.dds"))
        os.cp(path.join(uidir, "assets", "images", "cursor.png"), path.join(target:installdir(), "bin", "assets", "images", "cursor.png"))
        os.rm(path.join(target:installdir(), "bin", "**Tests.exe"))
    end)

    add_files(game_path .. "/**.cpp")
    add_headerfiles(game_path .. "/**.h")
    -- rather hacky:
    add_includedirs("Games")
    add_includedirs(game_path)
    
    if game == "Skyrim" then
        add_deps("SkyrimEncoding")
        add_defines("TP_SKYRIM=1", "TP_FALLOUT4=0")
        add_files("Games/Misc/Lock.cpp")
        add_files("Games/Misc/SubtitleManager.cpp")
    else
        add_deps("SkyrimEncoding")
        add_defines("TP_SKYRIM=0", "TP_FALLOUT4=1")
    end

    add_deps(
        "UiProcess",
        "CommonLib",
        "BaseLib",
        "ImGuiImpl",
        "TiltedConnect",
        "TiltedReverse",
        "TiltedHooks",
        "TiltedUi",
        {inherit = true}
    )

    add_packages(
        "tiltedcore",
        "spdlog",
        "hopscotch-map",
        "cryptopp",
        "gamenetworkingsockets",
        "discord",
        "imgui",
        "cef",
        "minhook",
        "entt",
        "glm",
        "mem",
        "xbyak")

    -- Add service implementations
    add_files("Services/Generic/**.cpp")
    add_headerfiles("Services/Generic/**.h")
    add_includedirs("Services")
    
    -- Add systems implementations
    add_files("Systems/**.cpp")
    add_headerfiles("Systems/**.h")
    add_includedirs("Systems")

    if has_config("vivox") then
        add_files("Services/Vivox/**.cpp")
        add_headerfiles("Services/Vivox/**.h")
        add_includedirs("Services/Vivox")
        add_deps("Vivox")
        add_defines("TP_VIVOX=1")
    else
        add_defines("TP_VIVOX=0")
    end

    add_syslinks(
        "version",
        "dbghelp",
        "kernel32")
end

add_requires("tiltedcore")

build_client("SkyrimTogetherClient", "Skyrim")
build_client("FalloutTogetherClient", "Fallout4")
