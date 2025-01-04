#include <libultraship/libultraship.h>
#include "2s2h/GameInteractor/GameInteractor.h"
#include "2s2h/ShipInit.hpp"

#include "2s2h/Rando/Logic/Logic.h"

using namespace Rando::Logic;

// clang-format off
static RegisterShipInitFunc initFunc([]() {
    // Ocean Spider House
    Regions[RR_OCEAN_SPIDER_HOUSE_CENTRAL_ROOM] = RandoRegion{ .name = "Central Room", .sceneId = SCENE_KINDAN2,
        .checks = {
            CHECK(RC_OCEAN_SKULLTULA_2ND_ROOM_BEHIND_SKULL_1, HAS_ITEM(ITEM_HOOKSHOT) || CAN_BE_ZORA),
            CHECK(RC_OCEAN_SKULLTULA_2ND_ROOM_BEHIND_SKULL_2, HAS_ITEM(ITEM_HOOKSHOT) || CAN_BE_ZORA),
            CHECK(RC_OCEAN_SKULLTULA_2ND_ROOM_CEILING_PLANK, HAS_ITEM(ITEM_HOOKSHOT) || CAN_BE_ZORA),
            CHECK(RC_OCEAN_SKULLTULA_2ND_ROOM_CEILING_EDGE, HAS_ITEM(ITEM_HOOKSHOT) || CAN_BE_ZORA),
            CHECK(RC_OCEAN_SKULLTULA_2ND_ROOM_WEBBED_HOLE, CAN_LIGHT_TORCH_NEAR_ANOTHER && HAS_ITEM(ITEM_HOOKSHOT)),
            CHECK(RC_OCEAN_SKULLTULA_2ND_ROOM_UPPER_POT, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_OCEAN_SKULLTULA_2ND_ROOM_LOWER_POT, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_OCEAN_SKULLTULA_2ND_ROOM_WEBBED_POT, CAN_LIGHT_TORCH_NEAR_ANOTHER),
            CHECK(RC_OCEAN_SKULLTULA_2ND_ROOM_JAR, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_OCEAN_SPIDER_HOUSE_POT_MAIN_ROOM_1, true),
            CHECK(RC_OCEAN_SPIDER_HOUSE_POT_MAIN_ROOM_2, true),
            CHECK(RC_OCEAN_SPIDER_HOUSE_POT_MAIN_ROOM_WEB, true),
            CHECK(RC_OCEAN_SPIDER_HOUSE_POT_MAIN_ROOM_BOE, true),
        },
        .connections = {
            CONNECTION(RR_OCEAN_SPIDER_HOUSE_ENTRANCE_LOWER, HAS_ITEM(ITEM_HOOKSHOT)),
            CONNECTION(RR_OCEAN_SPIDER_HOUSE_LIBRARY_ROOM, CAN_LIGHT_TORCH_NEAR_ANOTHER),
            CONNECTION(RR_OCEAN_SPIDER_HOUSE_MEETING_ROOM, true),
            CONNECTION(RR_OCEAN_SPIDER_HOUSE_STORAGE_ROOM, CAN_LIGHT_TORCH_NEAR_ANOTHER)
        }
    };
    Regions[RR_OCEAN_SPIDER_HOUSE_ENTRANCE_LOWER] = RandoRegion{ .name = "Entrance Lower", .sceneId = SCENE_KINDAN2,
        .checks = {
            CHECK(RC_OCEAN_SKULLTULA_ENTRANCE_LEFT_WALL, HAS_ITEM(ITEM_HOOKSHOT) || CAN_BE_ZORA || (CAN_USE_PROJECTILE && CAN_BE_GORON)),
            CHECK(RC_OCEAN_SKULLTULA_ENTRANCE_RIGHT_WALL, HAS_ITEM(ITEM_HOOKSHOT) || CAN_BE_ZORA),
            CHECK(RC_OCEAN_SKULLTULA_ENTRANCE_WEB, HAS_ITEM(ITEM_BOW) && HAS_ITEM(ITEM_HOOKSHOT)),
            CHECK(RC_OCEAN_SPIDER_HOUSE_POT_ENTRANCE_1, true),
            CHECK(RC_OCEAN_SPIDER_HOUSE_POT_ENTRANCE_2, true),
            CHECK(RC_OCEAN_SPIDER_HOUSE_POT_ENTRANCE_3, true),
            CHECK(RC_OCEAN_SPIDER_HOUSE_POT_ENTRANCE_4, true)
        },
        .connections = {
            CONNECTION(RR_OCEAN_SPIDER_HOUSE_ENTRANCE_UPPER, CAN_BE_GORON),
            CONNECTION(RR_OCEAN_SPIDER_HOUSE_CENTRAL_ROOM, HAS_ITEM(ITEM_HOOKSHOT))
        }
    };
    Regions[RR_OCEAN_SPIDER_HOUSE_ENTRANCE_UPPER] = RandoRegion{ .name = "Entrance Upper", .sceneId = SCENE_KINDAN2,
        .checks = {
            CHECK(RC_OCEAN_SPIDER_HOUSE_WALLET, Inventory_GetSkullTokenCount(SCENE_KINDAN2) >= 30),
        },
        .exits = { //     TO                                         FROM
            EXIT(ENTRANCE(GREAT_BAY_COAST, 8),          ENTRANCE(OCEANSIDE_SPIDER_HOUSE, 0), true)
        },
        .connections = {
            CONNECTION(RR_OCEAN_SPIDER_HOUSE_ENTRANCE_LOWER, CAN_USE_EXPLOSIVE && CAN_BE_GORON),
        }
    };
    Regions[RR_OCEAN_SPIDER_HOUSE_LIBRARY_ROOM] = RandoRegion{ .name = "Library Room", .sceneId = SCENE_KINDAN2,
        .checks = {
            CHECK(RC_OCEAN_SKULLTULA_LIBRARY_HOLE_BEHIND_CABINET, HAS_ITEM(ITEM_HOOKSHOT)),
            CHECK(RC_OCEAN_SKULLTULA_LIBRARY_BEHIND_PICTURE, CAN_USE_PROJECTILE),
            CHECK(RC_OCEAN_SKULLTULA_LIBRARY_CEILING_EDGE, HAS_ITEM(ITEM_HOOKSHOT) || CAN_BE_ZORA),
            CHECK(RC_OCEAN_SKULLTULA_LIBRARY_HOLE_BEHIND_PICTURE, HAS_ITEM(ITEM_HOOKSHOT)),
            CHECK(RC_OCEAN_SKULLTULA_LIBRARY_ON_CORNER_BOOKSHELF, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_OCEAN_SKULLTULA_LIBRARY_BEHIND_BOOKCASE_1, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_OCEAN_SKULLTULA_LIBRARY_BEHIND_BOOKCASE_2, CAN_KILL_CURSED_SKULLTULA),
        },
        .connections = {
            CONNECTION(RR_OCEAN_SPIDER_HOUSE_CENTRAL_ROOM, true)
        }
    };
    Regions[RR_OCEAN_SPIDER_HOUSE_MEETING_ROOM] = RandoRegion{ .name = "Meeting Room", .sceneId = SCENE_KINDAN2,
        .checks = {
            CHECK(RC_OCEAN_SKULLTULA_COLORED_SKULLS_CEILING_EDGE, HAS_ITEM(ITEM_HOOKSHOT) || CAN_BE_ZORA),
            CHECK(RC_OCEAN_SKULLTULA_COLORED_SKULLS_CHANDELIER_1, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_OCEAN_SKULLTULA_COLORED_SKULLS_CHANDELIER_2, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_OCEAN_SKULLTULA_COLORED_SKULLS_CHANDELIER_3, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_OCEAN_SKULLTULA_COLORED_SKULLS_POT, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_OCEAN_SKULLTULA_COLORED_SKULLS_BEHIND_PICTURE, HAS_ITEM(ITEM_HOOKSHOT) || CAN_BE_ZORA),
            CHECK(RC_OCEAN_SPIDER_HOUSE_CHEST_HP, HAS_ITEM(ITEM_BOW) && HAS_ITEM(ITEM_MASK_CAPTAIN)),
            CHECK(RC_OCEAN_SPIDER_HOUSE_POT_COLORED_SKULLS_1, true),
            CHECK(RC_OCEAN_SPIDER_HOUSE_POT_COLORED_SKULLS_2, true),
        },
        .connections = {
            CONNECTION(RR_OCEAN_SPIDER_HOUSE_CENTRAL_ROOM, true)
        }
    };
    Regions[RR_OCEAN_SPIDER_HOUSE_STORAGE_ROOM] = RandoRegion{ .name = "Storage Room", .sceneId = SCENE_KINDAN2,
        .checks = {
            CHECK(RC_OCEAN_SKULLTULA_STORAGE_ROOM_BEHIND_BOAT, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_OCEAN_SKULLTULA_STORAGE_ROOM_BEHIND_CRATE, HAS_ITEM(ITEM_HOOKSHOT) || CAN_BE_ZORA),
            CHECK(RC_OCEAN_SKULLTULA_STORAGE_ROOM_CEILING_WEB, CAN_USE_MAGIC_ARROW(FIRE) && (HAS_ITEM(ITEM_HOOKSHOT) || CAN_BE_ZORA)),
            CHECK(RC_OCEAN_SKULLTULA_STORAGE_ROOM_CRATE, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_OCEAN_SKULLTULA_STORAGE_ROOM_JAR, HAS_ITEM(ITEM_HOOKSHOT)),
            CHECK(RC_OCEAN_SPIDER_HOUSE_POT_STORAGE_1, true),
            CHECK(RC_OCEAN_SPIDER_HOUSE_POT_STORAGE_2, true),
            CHECK(RC_OCEAN_SPIDER_HOUSE_POT_STORAGE_3, true),
            CHECK(RC_OCEAN_SPIDER_HOUSE_POT_STORAGE_4, true),
            CHECK(RC_OCEAN_SPIDER_HOUSE_POT_STORAGE_TOP_1, HAS_ITEM(ITEM_HOOKSHOT)),
            CHECK(RC_OCEAN_SPIDER_HOUSE_POT_STORAGE_TOP_2, HAS_ITEM(ITEM_HOOKSHOT)),
            CHECK(RC_OCEAN_SPIDER_HOUSE_POT_STORAGE_TOP_3, HAS_ITEM(ITEM_HOOKSHOT)),
        },
        .connections = {
            CONNECTION(RR_OCEAN_SPIDER_HOUSE_CENTRAL_ROOM, true)
        }
    };

    // Swamp Spider House
    Regions[RR_SWAMP_SPIDER_HOUSE_BIG_POT_ROOM_LOWER] = RandoRegion{ .name = "Lower Big Pot Room", .sceneId = SCENE_KINSTA1,
        .checks = {
            CHECK(RC_SWAMP_SKULLTULA_POT_ROOM_HIVE_1, CAN_USE_PROJECTILE),
            CHECK(RC_SWAMP_SKULLTULA_POT_ROOM_HIVE_2, CAN_USE_PROJECTILE),
            CHECK(RC_SWAMP_SKULLTULA_POT_ROOM_JAR, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_SWAMP_SKULLTULA_POT_ROOM_POT_1, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_SWAMP_SKULLTULA_POT_ROOM_POT_2, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_SWAMP_SKULLTULA_POT_ROOM_BEHIND_VINES, CAN_USE_HUMAN_SWORD), // Double check this later.
            CHECK(RC_SWAMP_SPIDER_HOUSE_POT_JAR_ROOM_1, true),
            CHECK(RC_SWAMP_SPIDER_HOUSE_POT_JAR_ROOM_2, true),
            CHECK(RC_SWAMP_SPIDER_HOUSE_POT_JAR_ROOM_3, true),
            CHECK(RC_SWAMP_SPIDER_HOUSE_POT_JAR_ROOM_4, true),
            CHECK(RC_SWAMP_SPIDER_HOUSE_POT_JAR_ROOM_5, true),
        },
        .connections = {
            CONNECTION(RR_SWAMP_SPIDER_HOUSE_CENTER_ROOM_LOWER, true),
            CONNECTION(RR_SWAMP_SPIDER_HOUSE_BIG_POT_ROOM_UPPER, CAN_BE_DEKU && CAN_PLAY_SONG(SONATA))
        }
    };
    Regions[RR_SWAMP_SPIDER_HOUSE_BIG_POT_ROOM_UPPER] = RandoRegion{ .name = "Upper Big Pot Room", .sceneId = SCENE_KINSTA1,
        .checks = {
            CHECK(RC_SWAMP_SKULLTULA_POT_ROOM_WALL, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_SWAMP_SPIDER_HOUSE_POT_JAR_ROOM_6, true),
            CHECK(RC_SWAMP_SPIDER_HOUSE_POT_JAR_ROOM_7, true),
        },
        .connections = {
            CONNECTION(RR_SWAMP_SPIDER_HOUSE_CENTER_ROOM_UPPER, true),
            CONNECTION(RR_SWAMP_SPIDER_HOUSE_BIG_POT_ROOM_LOWER, true),
            CONNECTION(RR_SWAMP_SPIDER_HOUSE_GOLD_ROOM_UPPER, true)
        },
        .events = {
            EVENT_ACCESS(RANDO_ACCESS_BUGS, true),
        },
    };
    Regions[RR_SWAMP_SPIDER_HOUSE_CENTER_ROOM_LOWER] = RandoRegion{ .name = "Lower Center Room", .sceneId = SCENE_KINSTA1,
        .checks = {
            CHECK(RC_SWAMP_SKULLTULA_MAIN_ROOM_JAR, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_SWAMP_SKULLTULA_MAIN_ROOM_LOWER_LEFT_SOFT_SOIL, HAS_BOTTLE && CAN_ACCESS(BUGS) && CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_SWAMP_SKULLTULA_MAIN_ROOM_LOWER_RIGHT_SOFT_SOIL, HAS_BOTTLE && CAN_ACCESS(BUGS) && CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_SWAMP_SKULLTULA_MAIN_ROOM_PILLAR, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_SWAMP_SKULLTULA_MAIN_ROOM_WATER, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_SWAMP_SPIDER_HOUSE_POT_MAIN_ROOM_LOWER_1, true),
            CHECK(RC_SWAMP_SPIDER_HOUSE_POT_MAIN_ROOM_LOWER_2, true),
            CHECK(RC_SWAMP_SPIDER_HOUSE_POT_MAIN_ROOM_LOWER_3, true),
        },
        .connections = {
            CONNECTION(RR_SWAMP_SPIDER_HOUSE_ENTRANCE, true),
            CONNECTION(RR_SWAMP_SPIDER_HOUSE_MONUMENT_ROOM, true),
            CONNECTION(RR_SWAMP_SPIDER_HOUSE_GOLD_ROOM_LOWER, true),
            CONNECTION(RR_SWAMP_SPIDER_HOUSE_BIG_POT_ROOM_LOWER, true),
        },
        .events = {
            EVENT_ACCESS(RANDO_ACCESS_SPRING_WATER, true),
        },
    };
    Regions[RR_SWAMP_SPIDER_HOUSE_CENTER_ROOM_UPPER] = RandoRegion{ .name = "Upper Center Room", .sceneId = SCENE_KINSTA1,
        .checks = {
            CHECK(RC_SWAMP_SKULLTULA_MAIN_ROOM_UPPER_PILLAR, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_SWAMP_SKULLTULA_MAIN_ROOM_UPPER_SOFT_SOIL, HAS_BOTTLE && CAN_ACCESS(BUGS) && CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_SWAMP_SKULLTULA_MAIN_ROOM_NEAR_CEILING, HAS_ITEM(ITEM_HOOKSHOT) || CAN_BE_ZORA || CAN_BE_DEKU),
            CHECK(RC_SWAMP_SPIDER_HOUSE_POT_MAIN_ROOM_UPPER_LEFT_1, true),
            CHECK(RC_SWAMP_SPIDER_HOUSE_POT_MAIN_ROOM_UPPER_LEFT_2, true),
            CHECK(RC_SWAMP_SPIDER_HOUSE_POT_MAIN_ROOM_UPPER_RIGHT_1, true),
            CHECK(RC_SWAMP_SPIDER_HOUSE_POT_MAIN_ROOM_UPPER_RIGHT_2, true),
        },
        .connections = {
            CONNECTION(RR_SWAMP_SPIDER_HOUSE_MONUMENT_ROOM, true),
            CONNECTION(RR_SWAMP_SPIDER_HOUSE_CENTER_ROOM_LOWER, true), // Drop down from top
            CONNECTION(RR_SWAMP_SPIDER_HOUSE_BIG_POT_ROOM_UPPER, true),
        }
    };
    Regions[RR_SWAMP_SPIDER_HOUSE_ENTRANCE] = RandoRegion{ .name = "Entrance", .sceneId = SCENE_KINSTA1,
        .checks = {
            CHECK(RC_SWAMP_SPIDER_HOUSE_MASK_OF_TRUTH, Inventory_GetSkullTokenCount(SCENE_KINSTA1) >= 30),
        },
        .exits = { //     TO                                         FROM
            EXIT(ENTRANCE(SOUTHERN_SWAMP_POISONED, 8),      ENTRANCE(SWAMP_SPIDER_HOUSE, 0), true),
        },
        .connections = {
            CONNECTION(RR_SWAMP_SPIDER_HOUSE_CENTER_ROOM_LOWER, true)
        },
        .events = {
            EVENT_ACCESS(RANDO_ACCESS_BUGS, true),
        },
    };
    Regions[RR_SWAMP_SPIDER_HOUSE_GOLD_ROOM_LOWER] = RandoRegion{ .name = "Lower Gold Room", .sceneId = SCENE_KINSTA1,
        .checks = {
            CHECK(RC_SWAMP_SKULLTULA_GOLD_ROOM_HIVE, CAN_USE_PROJECTILE),
            CHECK(RC_SWAMP_SKULLTULA_GOLD_ROOM_PILLAR, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_SWAMP_SKULLTULA_GOLD_ROOM_WALL, (Flags_GetSceneSwitch(SCENE_KINSTA1, 0x0d) && CAN_USE_PROJECTILE || HAS_ITEM(ITEM_BOMBCHU)) || (HAS_ITEM(ITEM_HOOKSHOT) || CAN_BE_ZORA)),
            CHECK(RC_SWAMP_SPIDER_HOUSE_POT_GOLD_ROOM_LOWER_1, true),
            CHECK(RC_SWAMP_SPIDER_HOUSE_POT_GOLD_ROOM_LOWER_2, true),
        },
        .connections = {
            CONNECTION(RR_SWAMP_SPIDER_HOUSE_CENTER_ROOM_LOWER, true),
            CONNECTION(RR_SWAMP_SPIDER_HOUSE_GOLD_ROOM_UPPER, Flags_GetSceneSwitch(SCENE_KINSTA1, 0x0d))
        }
    };
    Regions[RR_SWAMP_SPIDER_HOUSE_GOLD_ROOM_UPPER] = RandoRegion{ .name = "Upper Gold Room", .sceneId = SCENE_KINSTA1,
        .checks = {
            CHECK(RC_SWAMP_SKULLTULA_GOLD_ROOM_NEAR_CEILING, HAS_ITEM(ITEM_HOOKSHOT) || CAN_BE_ZORA || CAN_GROW_BEAN_PLANT),
            CHECK(RC_SWAMP_SPIDER_HOUSE_POT_GOLD_ROOM_UPPER_1, true),
            CHECK(RC_SWAMP_SPIDER_HOUSE_POT_GOLD_ROOM_UPPER_2, true),
            CHECK(RC_SWAMP_SPIDER_HOUSE_POT_GOLD_ROOM_UPPER_3, true),
            CHECK(RC_SWAMP_SPIDER_HOUSE_POT_GOLD_ROOM_UPPER_4, true),
        },
        .connections = {
            CONNECTION(RR_SWAMP_SPIDER_HOUSE_BIG_POT_ROOM_UPPER, true),
            CONNECTION(RR_SWAMP_SPIDER_HOUSE_GOLD_ROOM_LOWER, true),
            CONNECTION(RR_SWAMP_SPIDER_HOUSE_TREE_ROOM, true)
        },
        .events = {
            EVENT( // Spawn Ladder in Gold Room
                "Spawn Ladder in Gold Room", 
                Flags_GetSceneSwitch(SCENE_KINSTA1, 0x0d),
                Flags_SetSceneSwitch(SCENE_KINSTA1, 0x0d),
                Flags_ClearSceneSwitch(SCENE_KINSTA1, 0x0d), 
                true
            ),
        }
    };
    Regions[RR_SWAMP_SPIDER_HOUSE_MONUMENT_ROOM] = RandoRegion{ .name = "Monument Room", .sceneId = SCENE_KINSTA1,
        .checks = {
            CHECK(RC_SWAMP_SKULLTULA_MONUMENT_ROOM_CRATE_1, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_SWAMP_SKULLTULA_MONUMENT_ROOM_CRATE_2, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_SWAMP_SKULLTULA_MONUMENT_ROOM_LOWER_WALL, HAS_ITEM(ITEM_HOOKSHOT) || CAN_BE_ZORA || ((CAN_USE_EXPLOSIVE || CAN_BE_GORON) && CAN_KILL_CURSED_SKULLTULA && CAN_GROW_BEAN_PLANT)),
            CHECK(RC_SWAMP_SKULLTULA_MONUMENT_ROOM_ON_MONUMENT, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_SWAMP_SKULLTULA_MONUMENT_ROOM_TORCH, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_SWAMP_SPIDER_HOUSE_POT_MONUMENT_ROOM_1, true),
            CHECK(RC_SWAMP_SPIDER_HOUSE_POT_MONUMENT_ROOM_2, true),
            CHECK(RC_SWAMP_SPIDER_HOUSE_MONUMENT_ROOM_LARGE_CRATE_01, true),
            CHECK(RC_SWAMP_SPIDER_HOUSE_MONUMENT_ROOM_LARGE_CRATE_02, true),
            CHECK(RC_SWAMP_SPIDER_HOUSE_MONUMENT_ROOM_LARGE_CRATE_03, true),
            CHECK(RC_SWAMP_SPIDER_HOUSE_MONUMENT_ROOM_LARGE_CRATE_04, true),
            CHECK(RC_SWAMP_SPIDER_HOUSE_MONUMENT_ROOM_LARGE_CRATE_05, true),
            CHECK(RC_SWAMP_SPIDER_HOUSE_MONUMENT_ROOM_LARGE_CRATE_06, true),
        },
        .connections = {
            CONNECTION(RR_SWAMP_SPIDER_HOUSE_ENTRANCE, true),
            CONNECTION(RR_SWAMP_SPIDER_HOUSE_CENTER_ROOM_UPPER, true),
        }
    };
    Regions[RR_SWAMP_SPIDER_HOUSE_TREE_ROOM] = RandoRegion{ .name = "Tree Room", .sceneId = SCENE_KINSTA1,
        .checks = {
            CHECK(RC_SWAMP_SKULLTULA_TREE_ROOM_GRASS_1, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_SWAMP_SKULLTULA_TREE_ROOM_GRASS_2, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_SWAMP_SKULLTULA_TREE_ROOM_HIVE, CAN_USE_PROJECTILE),
            CHECK(RC_SWAMP_SKULLTULA_TREE_ROOM_TREE_1, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_SWAMP_SKULLTULA_TREE_ROOM_TREE_2, CAN_KILL_CURSED_SKULLTULA),
            CHECK(RC_SWAMP_SKULLTULA_TREE_ROOM_TREE_3, CAN_KILL_CURSED_SKULLTULA)
        },
        .connections = {
            CONNECTION(RR_SWAMP_SPIDER_HOUSE_GOLD_ROOM_UPPER, true)
        },
        .events = {
            EVENT_ACCESS(RANDO_ACCESS_BUGS, true),
        },
    };
}, {});
// clang-format on
