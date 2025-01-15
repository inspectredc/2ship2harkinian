#ifndef SHIP_UTILS_H
#define SHIP_UTILS_H

#include <libultraship/libultraship.h>
#include "PR/ultratypes.h"

#ifdef __cplusplus

void LoadGuiTextures();
std::string convertEnumToReadableName(const std::string& input);
extern std::vector<const char*> digitList;

extern "C" {
#endif

struct PlayState;
struct Actor;

f32 Ship_GetExtendedAspectRatioMultiplier();
void Ship_ExtendedCullingActorAdjustProjectedZ(Actor* actor);
void Ship_ExtendedCullingActorAdjustProjectedX(Actor* actor);
void Ship_ExtendedCullingActorRestoreProjectedPos(PlayState* play, Actor* actor);
const char* Ship_GetSceneName(s16 sceneId);
bool Ship_IsCStringEmpty(const char* str);
void Ship_CreateQuadVertexGroup(Vtx* vtxList, s32 xStart, s32 yStart, s32 width, s32 height, u8 flippedH);
f32 Ship_GetCharFontWidthNES(u8 character);
TexturePtr Ship_GetCharFontTextureNES(u8 character);
void Ship_Random_Seed(u32 seed);
s32 Ship_Random(s32 min, s32 max);

#ifdef __cplusplus
}
#endif

#endif // SHIP_UTILS_H
