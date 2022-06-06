//
// Created by theer on 07.06.2022.
//

#include "CreatureGenerator.hpp"
#include <random>
#include <cassert>

namespace vasio {

    auto generateName(CreatureType type) -> std::string {
        switch (type) {
            case CreatureType::Water:
                static int waterNamesCounter = 1;
                return "Water Creature " + std::to_string(waterNamesCounter++);
            case CreatureType::Fire:
                static int fireNamesCounter = 1;
                return "Fire Creature " + std::to_string(fireNamesCounter++);
            case CreatureType::Earth:
                static int earthNamesCounter = 1;
                return "Earth Creature " + std::to_string(earthNamesCounter++);
            case CreatureType::Air:
                static int airNamesCounter = 1;
                return "Air Creature " + std::to_string(airNamesCounter++);
            case CreatureType::Ice:
                static int iceNamesCounter = 1;
                return "Ice Creature " + std::to_string(iceNamesCounter++);
            case CreatureType::Steel:
                static int steelNamesCounter = 1;
                return "Steel Creature " + std::to_string(steelNamesCounter++);
        }
    }

    auto createRandomCreature() -> std::unique_ptr<Creature> {
        std::unique_ptr<Creature> creature;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 5);
        int random = dis(gen);
        switch (random) {
            case 0:
                creature = std::make_unique<WaterCreature>();
                break;
            case 1:
                creature = std::make_unique<FireCreature>();
                break;
            case 2:
                creature = std::make_unique<EarthCreature>();
                break;
            case 3:
                creature = std::make_unique<AirCreature>();
                break;
            case 4:
                creature = std::make_unique<IceCreature>();
                break;
            case 5:
                creature = std::make_unique<SteelCreature>();
                break;
            default:
                assert(false);
        }
        creature->Name_ = generateName(creature->getType());
        creature->health_ = std::uniform_int_distribution<>(1, 100)(gen);
        creature->power_ = std::uniform_int_distribution<>(1, 100)(gen);
        creature->agility_ = std::uniform_real_distribution<float>(0, 0.7)(gen);
        creature->Exp_ = 0;
        creature->ExpNeededToEvolve_ = std::uniform_int_distribution<>(500, 1000)(gen);
        return creature;
    }
}