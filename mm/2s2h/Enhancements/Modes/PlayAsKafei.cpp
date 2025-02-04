#include <libultraship/libultraship.h>
#include "2s2h/GameInteractor/GameInteractor.h"
#include "2s2h/ShipInit.hpp"

extern "C" {
#include "variables.h"
#include "objects/object_link_child/object_link_child.h"
#include "objects/object_test3/object_test3.h"

void ResourceMgr_PatchGfxByName(const char* path, const char* patchName, int index, Gfx instruction);
void ResourceMgr_UnpatchGfxByName(const char* path, const char* patchName);
extern TexturePtr sPlayerEyesTextures[PLAYER_FORM_MAX][PLAYER_EYES_MAX];
extern TexturePtr sPlayerMouthTextures[PLAYER_FORM_MAX][PLAYER_MOUTH_MAX];
}

static SkeletonHeader gLinkHumanSkelBackup;
static SkeletonHeader gKafeiSkelBackup;

#define CVAR_NAME "gModes.PlayAsKafei"
#define CVAR CVarGetInteger(CVAR_NAME, 0)

void UpdatePlayAsKafei() {
    if (CVAR) {
        auto gLinkHumanSkelResource = Ship::Context::GetInstance()->GetResourceManager()->LoadResource(gLinkHumanSkel);
        SkeletonHeader* gLinkHumanSkelPtr = (SkeletonHeader*)gLinkHumanSkelResource->GetRawPointer();
        memcpy(gLinkHumanSkelPtr, &gKafeiSkelBackup, sizeof(SkeletonHeader));

        ResourceMgr_PatchGfxByName(gLinkHumanWaistDL, "gLinkHumanWaistDL0", 0,
                                   gsSPDisplayListOTRFilePath(gKafeiWaistDL));
        ResourceMgr_PatchGfxByName(gLinkHumanWaistDL, "gLinkHumanWaistDL1", 1, gsSPEndDisplayList());

        sPlayerEyesTextures[PLAYER_FORM_HUMAN][0] = (TexturePtr)gKafeiEyesOpenTex;
        sPlayerEyesTextures[PLAYER_FORM_HUMAN][1] = (TexturePtr)gKafeiEyesHalfTex;
        sPlayerEyesTextures[PLAYER_FORM_HUMAN][2] = (TexturePtr)gKafeiEyesClosedTex;
        sPlayerEyesTextures[PLAYER_FORM_HUMAN][3] = (TexturePtr)gKafeiEyesRollRightTex;
        sPlayerEyesTextures[PLAYER_FORM_HUMAN][4] = (TexturePtr)gKafeiEyesRollLeftTex;
        sPlayerEyesTextures[PLAYER_FORM_HUMAN][5] = (TexturePtr)gKafeiEyesRollUpTex;
        sPlayerEyesTextures[PLAYER_FORM_HUMAN][6] = (TexturePtr)gKafeiEyesRollDownTex;
        sPlayerEyesTextures[PLAYER_FORM_HUMAN][7] = (TexturePtr)object_test3_Tex_006680;

        sPlayerMouthTextures[PLAYER_FORM_HUMAN][0] = (TexturePtr)gKafeiMouthClosedTex;
        sPlayerMouthTextures[PLAYER_FORM_HUMAN][1] = (TexturePtr)gKafeiMouthTeethTex;
        sPlayerMouthTextures[PLAYER_FORM_HUMAN][2] = (TexturePtr)gKafeiMouthAngryTex;
        sPlayerMouthTextures[PLAYER_FORM_HUMAN][3] = (TexturePtr)gKafeiMouthHappyTex;
    } else {
        auto gLinkHumanSkelResource = Ship::Context::GetInstance()->GetResourceManager()->LoadResource(gLinkHumanSkel);
        SkeletonHeader* gLinkHumanSkelPtr = (SkeletonHeader*)gLinkHumanSkelResource->GetRawPointer();
        memcpy(gLinkHumanSkelPtr, &gLinkHumanSkelBackup, sizeof(SkeletonHeader));

        ResourceMgr_UnpatchGfxByName(gLinkHumanWaistDL, "gLinkHumanWaistDL0");
        ResourceMgr_UnpatchGfxByName(gLinkHumanWaistDL, "gLinkHumanWaistDL1");

        sPlayerEyesTextures[PLAYER_FORM_HUMAN][0] = (TexturePtr)gLinkHumanEyesOpenTex;
        sPlayerEyesTextures[PLAYER_FORM_HUMAN][1] = (TexturePtr)gLinkHumanEyesHalfTex;
        sPlayerEyesTextures[PLAYER_FORM_HUMAN][2] = (TexturePtr)gLinkHumanEyesClosedTex;
        sPlayerEyesTextures[PLAYER_FORM_HUMAN][3] = (TexturePtr)gLinkHumanEyesRollRightTex;
        sPlayerEyesTextures[PLAYER_FORM_HUMAN][4] = (TexturePtr)gLinkHumanEyesRollLeftTex;
        sPlayerEyesTextures[PLAYER_FORM_HUMAN][5] = (TexturePtr)gLinkHumanEyesRollUpTex;
        sPlayerEyesTextures[PLAYER_FORM_HUMAN][6] = (TexturePtr)gLinkHumanEyesRollDownTex;
        sPlayerEyesTextures[PLAYER_FORM_HUMAN][7] = (TexturePtr)object_link_child_Tex_003800;

        sPlayerMouthTextures[PLAYER_FORM_HUMAN][0] = (TexturePtr)gLinkHumanMouthClosedTex;
        sPlayerMouthTextures[PLAYER_FORM_HUMAN][1] = (TexturePtr)gLinkHumanMouthTeethTex;
        sPlayerMouthTextures[PLAYER_FORM_HUMAN][2] = (TexturePtr)gLinkHumanMouthAngryTex;
        sPlayerMouthTextures[PLAYER_FORM_HUMAN][3] = (TexturePtr)gLinkHumanMouthHappyTex;
    }
}

void RegisterPlayAsKafei() {
    // Even though this isn't run when a cvar is changed, it can still run if ShipInit::InitAll(); is called again,
    // likely in the case of setting a preset or something. So we need to make sure this only runs once.
    static bool initialized = false;
    if (initialized) {
        return;
    }
    initialized = true;

    auto gLinkHumanSkelResource = Ship::Context::GetInstance()->GetResourceManager()->LoadResource(gLinkHumanSkel);
    auto gKafeiSkelResource = Ship::Context::GetInstance()->GetResourceManager()->LoadResource(gKafeiSkel);

    SkeletonHeader* gLinkHumanSkelPtr = (SkeletonHeader*)gLinkHumanSkelResource->GetRawPointer();
    SkeletonHeader* gKafeiSkelPtr = (SkeletonHeader*)gKafeiSkelResource->GetRawPointer();

    memcpy(&gLinkHumanSkelBackup, gLinkHumanSkelPtr, sizeof(SkeletonHeader));
    memcpy(&gKafeiSkelBackup, gKafeiSkelPtr, sizeof(SkeletonHeader));

    UpdatePlayAsKafei();

    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnPlayDestroy>([]() { UpdatePlayAsKafei(); });
}

// We only want this running at boot, we don't want this running when the cvar is changed, only on scene destroy
static RegisterShipInitFunc initFunc(RegisterPlayAsKafei, {});
