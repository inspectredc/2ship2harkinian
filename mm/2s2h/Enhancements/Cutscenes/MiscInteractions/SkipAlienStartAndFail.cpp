#include <libultraship/bridge.h>
#include "2s2h/GameInteractor/GameInteractor.h"
#include "2s2h/ShipInit.hpp"

extern "C" {
#include "variables.h"
}

#define CVAR_NAME "gEnhancements.Cutscenes.SkipMiscInteractions"
#define CVAR CVarGetInteger(CVAR_NAME, 0)

void RegisterSkipAlienStartAndFail() {
    COND_VB_SHOULD(VB_PLAY_TRANSITION_CS, CVAR, {
        if (gSaveContext.save.cutsceneIndex == 0xFFF3 && gSaveContext.save.entrance == ENTRANCE(ROMANI_RANCH, 0)) {
            gSaveContext.save.cutsceneIndex = 0;
            gSaveContext.save.entrance = ENTRANCE(ROMANI_RANCH, 9);
        }
    });

    COND_VB_SHOULD(VB_START_CUTSCENE, CVAR, {
        s16* csId = va_arg(args, s16*);
        if (gPlayState->sceneId == SCENE_F01) {
            // 15 is aliens spawning in, 16 is aliens retreating
            // not skipping 16 because you can leave the scene during the the time
            // the cutscene would have been playing and miss the reward
            if (*csId == 15) {
                *should = false;
            }
        }
    });
}

static RegisterShipInitFunc initFunc(RegisterSkipAlienStartAndFail, { CVAR_NAME });
