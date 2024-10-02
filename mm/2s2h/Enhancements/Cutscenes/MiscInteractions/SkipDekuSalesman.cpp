#include <libultraship/bridge.h>
#include "Enhancements/GameInteractor/GameInteractor.h"

extern "C" {
#include "functions.h"
#include "variables.h"

#include "overlays/actors/ovl_En_Sellnuts/z_en_sellnuts.h"
#include "overlays/actors/ovl_En_Akindonuts/z_en_akindonuts.h"
void func_80ADC118(EnSellnuts* enSellnuts, PlayState* play);
void func_80BEF83C(EnAkindonuts* enAkindonuts, PlayState* play);
}

void RegisterSkipDekuSalesman() {
    // prevents him from doing his "fly in" animation
    GameInteractor::Instance->RegisterGameHookForID<GameInteractor::ShouldActorInit>(
        ACTOR_EN_SELLNUTS, [](Actor* actor, bool* should) {
            if (CVarGetInteger("gEnhancements.Cutscenes.SkipMiscInteractions", 0) &&
                !CHECK_WEEKEVENTREG(WEEKEVENTREG_73_04)) {
                SET_WEEKEVENTREG(WEEKEVENTREG_73_04);
            }
        });

    // Kills him when he's about to pop out of the ground for his exit animation
    GameInteractor::Instance->RegisterGameHookForID<GameInteractor::OnActorUpdate>(ACTOR_EN_SELLNUTS, [](Actor* actor) {
        EnSellnuts* enSellnuts = (EnSellnuts*)actor;

        if (CVarGetInteger("gEnhancements.Cutscenes.SkipMiscInteractions", 0) &&
            enSellnuts->actionFunc == func_80ADC118) {
            CutsceneManager_Stop(enSellnuts->csId);
            Player_SetCsActionWithHaltedActors(gPlayState, &enSellnuts->actor, PLAYER_CSACTION_END);
            Actor_Kill(&enSellnuts->actor);
        }
    });

    // Kills him when he's about to pop out of the ground for his exit animation
    GameInteractor::Instance->RegisterGameHookForID<GameInteractor::OnActorUpdate>(
        ACTOR_EN_AKINDONUTS, [](Actor* actor) {
            EnAkindonuts* enAkindonuts = (EnAkindonuts*)actor;

            if (CVarGetInteger("gEnhancements.Cutscenes.SkipMiscInteractions", 0) &&
                enAkindonuts->actionFunc == func_80BEF83C && enAkindonuts->unk_33A < 40) {
                CutsceneManager_Stop(enAkindonuts->csId);
                Player_SetCsActionWithHaltedActors(gPlayState, &enAkindonuts->actor, PLAYER_CSACTION_END);
                Actor_Kill(&enAkindonuts->actor);
            }
        });
}
