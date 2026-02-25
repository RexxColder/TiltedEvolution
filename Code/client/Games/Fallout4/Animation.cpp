#include <TiltedOnlinePCH.h>

#include <Games/References.h>

#include <Forms/BGSAction.h>
#include <Forms/TESIdleForm.h>

#include <Structs/ActionEvent.h>

#include <Games/Animation/ActorMediator.h>
#include <Games/Animation/TESActionData.h>

#include <Misc/BSFixedString.h>

#include <World.h>

#if TP_FALLOUT4

TP_THIS_FUNCTION(TPerformAction, uint8_t, ActorMediator, TESActionData* apAction);
static TPerformAction* RealPerformAction;

thread_local bool g_forceAnimation = false;

uint8_t TP_MAKE_THISCALL(HookPerformAction, ActorMediator, TESActionData* apAction)
{
    auto pActor = apAction->actor;
    const auto pExtension = pActor->GetExtension();

    if (!pExtension->IsRemote() || g_forceAnimation)
    {
        ActionEvent action;
        action.State1 = pActor->actorState.flags04;
        action.State2 = pActor->actorState.flags08;
        action.Type = apAction->unkInput | (apAction->someFlag ? 0x4 : 0);
        action.Tick = World::Get().GetTick();
        action.ActorId = pActor->formID;
        action.ActionId = apAction->action->formID;
        action.TargetId = apAction->target ? apAction->target->formID : 0;

        pActor->SaveAnimationVariables(action.Variables);

        const auto res = TiltedPhoques::ThisCall(RealPerformAction, apThis, apAction);

        if (apAction->someFlag == 1 || g_forceAnimation)
            return res;

        action.EventName = apAction->eventName.AsAscii();
        action.TargetEventName = apAction->targetEventName.AsAscii();
        action.IdleId = apAction->idleForm ? apAction->idleForm->formID : 0;

        if (res)
        {
            pExtension->LatestAnimation = action;
        }

        World::Get().GetRunner().Trigger(action);

        return res;
    }

    return 0;
}

ActorMediator* ActorMediator::Get() noexcept
{
    POINTER_FALLOUT4(ActorMediator*, s_actorMediator, 0x1234567);
    return *(s_actorMediator.Get());
}

bool ActorMediator::PerformAction(TESActionData* apAction) noexcept
{
    const auto res = TiltedPhoques::ThisCall(RealPerformAction, this, apAction);
    return res != 0;
}

bool ActorMediator::ForceAction(TESActionData* apAction) noexcept
{
    return false;
}

ActionInput::ActionInput(uint32_t aParam1, Actor* apActor, BGSAction* apAction, TESObjectREFR* apTarget)
{
    actor = apActor;
    target = apTarget;
    action = apAction;
    unkInput = aParam1;
}

void ActionInput::Release()
{
    actor.Release();
    target.Release();
}

ActionOutput::ActionOutput()
    : eventName("")
    , targetEventName("")
{
    result = 0;
    targetIdleForm = nullptr;
    idleForm = nullptr;
    unk1 = 0;
}

void ActionOutput::Release()
{
    eventName.Release();
    targetEventName.Release();
}

BGSActionData::BGSActionData(uint32_t aParam1, Actor* apActor, BGSAction* apAction, TESObjectREFR* apTarget)
    : ActionInput(aParam1, apActor, apAction, apTarget)
{
    someFlag = 0;
}

TESActionData::TESActionData(uint32_t aParam1, Actor* apActor, BGSAction* apAction, TESObjectREFR* apTarget)
    : BGSActionData(aParam1, apActor, apAction, apTarget)
{
    POINTER_FALLOUT4(void*, s_vtbl, 0x1234568);
    someFlag = false;
    *reinterpret_cast<void**>(this) = s_vtbl.Get();
}

TESActionData::~TESActionData()
{
    ActionOutput::Release();
    ActionInput::Release();
}

static TiltedPhoques::Initializer s_animationHook(
    []()
    {
        POINTER_FALLOUT4(TPerformAction, performAction, 0x1234569);
        RealPerformAction = performAction.Get();
        TP_HOOK(&RealPerformAction, HookPerformAction);
    });

#endif
