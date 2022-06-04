//
// Created by theer on 04.06.2022.
//
#include "Creature.hpp"
#include <memory>
#include <random>
#include <cassert>

#pragma once

auto createRandomCreature() -> std::unique_ptr<Creature> {
    std::unique_ptr<Creature> creature;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 6);
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
}