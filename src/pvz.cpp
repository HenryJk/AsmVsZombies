//
// Created by henryj on 2/7/2021.
//

#include <cstdint>
#include "pvz.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

enum class pvz::ZombieType: uint32_t {
    kZombie = 0,
    kFlagZombie = 1,
    kConeheadZombie = 2,
    kPoleVaultingZombie = 3,
    kBucketheadZombie = 4,
    kNewspaperZombie = 5,
    kScreenDoorZombie = 6,
    kFootballZombie = 7,
    kDancingZombie = 8,
    kBackupDancer = 9,
    kDuckyTubeZombie = 10,
    kSnorkelZombie = 11,
    kZomboni = 12,
    kZombieBobsledTeam = 13,
    kDolphinRiderZombie = 14,
    kJackInTheBoxZombie = 15,
    kBalloonZombie = 16,
    kDiggerZombie = 17,
    kPogoZombie = 18,
    kZombieYeti = 19,
    kBungeeZombie = 20,
    kLadderZombie = 21,
    kCatapultZombie = 22,
    kGargantuar = 23,
    kImp = 24,
    kDrZomboss = 25,
    kPeashooterZombie = 26,
    kWallNutZombie = 27,
    kJalapenoZombie = 28,
    kGatlingPeaZombie = 29,
    kSquashZombie = 30,
    kTallNutZombie = 31,
    kGigaGargantuar = 32,
};

enum class pvz::HelmetType: uint32_t {
    kNone = 0,
    kCone = 1,
    kBucket = 2,
    kRugby = 3,
    kMiner = 4,
    kSled = 7,
    kWallNut = 8,
    kTallNut = 9,
};

enum class pvz::ShieldType: uint32_t {
    kNone = 0,
    kScreenDoor = 1,
    kNewspaper = 2,
    kLadder = 3,
    kPickaxe = 4,
};

enum class pvz::PlantType: uint32_t {
    kPeashooter = 0,
    kSunflower = 1,
    kCherryBomb = 2,
    kWallNut = 3,
    kPotatoMine = 4,
    kSnowPea = 5,
    kChomper = 6,
    kRepeater = 7,
    kPuffShroom = 8,
    kSunShroom = 9,
    kFumeShroom = 10,
    kGraveBuster = 11,
    kHypnoShroom = 12,
    kScaredyShroom = 13,
    kIceShroom = 14,
    kDoomShroom = 15,
    kLilyPad = 16,
    kSquash = 17,
    kThreepeater = 18,
    kTangleKelp = 19,
    kJalapeno = 20,
    kSpikeweed = 21,
    kTorchwood = 22,
    kTallNut = 23,
    kSeaShroom = 24,
    kPlantern = 25,
    kCactus = 26,
    kBlover = 27,
    kSplitPea = 28,
    kStarFruit = 29,
    kPumpkin = 30,
    kMagnetShroom = 31,
    kCabbagePult = 32,
    kFlowerPot = 33,
    kKernelPult = 34,
    kCoffeeBean = 35,
    kGarlic = 36,
    kUmbrellaLeaf = 37,
    kMarigold = 38,
    kMelonPult = 39,
    kGatlingPea = 40,
    kTwinSunflower = 41,
    kGloomShroom = 42,
    kCattail = 43,
    kWinterMelon = 44,
    kGoldMagnet = 45,
    kSpikerock = 46,
    kCobCannon = 47,
    kImitater = 48,
};

enum class pvz::FloatingItemType: uint32_t {
    kNone = 0,
    kSilverCoin = 1,
    kGoldCoin = 2,
    kDiamond = 3,
    kSun = 4,
    kSmallSun = 5,
    kBigSun = 6,
    kTrophy = 8,
    kSeedPacket = 16,
    kZenGardenPlant = 17,
};

enum class pvz::GridItemType: uint32_t {
    kNone = 0,
    kGrave = 1,
    kCrater = 2,
    kLadder = 3,
    kRake = 11,
    kBrain = 12,
};

enum class pvz::CursorItem: uint32_t {
    kNone = 0,
    kPlant = 1,
    kShovel = 6,
    kMallet = 7,
    kCannonTarget = 8,
    kWateringCan = 9,
    kFertilizer = 10,
    kBugSpray = 11,
    kPhonograph = 12,
    kChocolate = 13,
    kGardeningGlove = 14,
    kSellPlant = 15,
    kWheelBarrow = 16,
    kTreeFood = 17,
};

enum class pvz::TerrainType: uint32_t {
    kLand = 1,
    kUnsodded = 2,
    kWater = 3,
};

#pragma clang diagnostic pop

#pragma GCC push_options
#pragma GCC optimize ("O0")
#pragma GCC pop_options
