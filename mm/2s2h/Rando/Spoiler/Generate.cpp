#include "Spoiler.h"
#include <libultraship/libultraship.h>

namespace Rando {

namespace Spoiler {

nlohmann::json GenerateFromSaveContext() {
    nlohmann::json spoiler;
    spoiler["type"] = "2S2H_RANDO_SPOILER";
    spoiler["commitHash"] = gSaveContext.save.shipSaveInfo.commitHash;
    spoiler["finalSeed"] = gSaveContext.save.shipSaveInfo.rando.finalSeed;

    spoiler["options"] = nlohmann::json::object();
    for (auto& [randoOptionId, randoStaticOption] : Rando::StaticData::Options) {
        spoiler["options"][randoStaticOption.name] = RANDO_SAVE_OPTIONS[randoOptionId];
    }

    spoiler["checks"] = nlohmann::json::object();
    for (auto& [randoCheckId, randoStaticCheck] : Rando::StaticData::Checks) {
        if (randoStaticCheck.randoCheckId == RC_UNKNOWN) {
            continue;
        }

        if (!RANDO_SAVE_CHECKS[randoCheckId].shuffled) {
            continue;
        }

        if (randoStaticCheck.randoCheckType == RCTYPE_SHOP) {
            spoiler["checks"][randoStaticCheck.name] = nlohmann::json::object();
            spoiler["checks"][randoStaticCheck.name]["randoItemId"] =
                Rando::StaticData::Items[RANDO_SAVE_CHECKS[randoCheckId].randoItemId].spoilerName;
            spoiler["checks"][randoStaticCheck.name]["price"] = RANDO_SAVE_CHECKS[randoCheckId].price;
        } else {
            spoiler["checks"][randoStaticCheck.name] =
                Rando::StaticData::Items[RANDO_SAVE_CHECKS[randoCheckId].randoItemId].spoilerName;
        }
    }

    return spoiler;
}

} // namespace Spoiler

} // namespace Rando
