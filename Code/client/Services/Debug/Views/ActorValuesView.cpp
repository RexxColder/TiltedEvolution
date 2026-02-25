#include <Services/DebugService.h>

#include <Forms/ActorValueInfo.h>

#include <imgui.h>

void DebugService::DrawActorValuesView()
{
    Actor* pActor = Cast<Actor>(TESForm::GetById(m_formId));
    if (!pActor)
        return;

    ImGui::Begin("Actor values");

    // for (int i = 0; i < ActorValueInfo::kActorValueCount; i++)
    {
        ActorValueOwner& actorValueOwner = pActor->actorValueOwner;
#if TP_SKYRIM
        float health[3]{actorValueOwner.GetValue(24), actorValueOwner.GetBaseValue(24), actorValueOwner.GetPermanentValue(24)};
#elif TP_FALLOUT4
        float health[3]{actorValueOwner.GetActorValue(24), actorValueOwner.GetBaseActorValue(24), actorValueOwner.GetPermanentActorValue(24)};
#endif
        ImGui::InputFloat3("Health (val/base/perm)", health, "%.3f", ImGuiInputTextFlags_ReadOnly);
    }

    ImGui::End();
}
