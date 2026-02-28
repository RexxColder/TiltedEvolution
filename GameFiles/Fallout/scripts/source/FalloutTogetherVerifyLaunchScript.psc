ScriptName FalloutTogetherVerifyLaunchScript extends Quest Native Hidden

bool Function DidLaunchSkyrimTogether() global native

Event OnInit()
    VerifyLaunch()
EndEvent

Function VerifyLaunch()
    If (!DidLaunchSkyrimTogether())
        Utility.Wait(1)
        Debug.MessageBox("Fallout Together Error\n\n" \
                       + "Fallout Together is not running!\n" \
                       + "To play Fallout Together and access multiplayer features, " \
                       + "launch FalloutTogether.exe located in your game folder.")
    EndIf
EndFunction
