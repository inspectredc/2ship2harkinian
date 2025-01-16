#include "ActorBehavior.h"
#include <libultraship/libultraship.h>

extern "C" {
#include "variables.h"
#include "overlays/actors/ovl_En_Shn/z_en_shn.h"

void Player_TalkWithPlayer(PlayState* play, Actor* actor);
void func_80837B60(PlayState* play, Player* player);
s32 func_80832558(PlayState* play, Player* player, PlayerFuncD58 arg2);
}

void Rando::ActorBehavior::InitEnShnBehavior() {
    // Scripted Actors
    COND_VB_SHOULD(VB_EXEC_MSG_EVENT, IS_RANDO, {
        u32 cmdId = va_arg(args, u32);
        Actor* actor = va_arg(args, Actor*);
        MsgScript* script = va_arg(args, MsgScript*);
        Player* player = GET_PLAYER(gPlayState);
        static std::vector<u8> skipCmds = {};

        if (actor->id != ACTOR_EN_SHN) {
            return;
        }

        if (cmdId == MSCRIPT_CMD_06) { // MSCRIPT_OFFER_ITEM
            func_80832558(gPlayState, player, func_80837B60);
            *should = false;
            skipCmds.clear();
            skipCmds.push_back(MSCRIPT_CMD_07);
            skipCmds.push_back(MSCRIPT_CMD_12);
            return;
        }

        if (skipCmds.empty()) {
            return;
        }

        if (cmdId == skipCmds[0]) {
            skipCmds.erase(skipCmds.begin());
            *should = false;
        }
    });
}
