//
// Created by theer on 24.05.2022.
//
#include "Creature.hpp"
#include <string>
#include <vector>
#include <random>
#include <cassert>

// constructor
Creature::Creature(const std::string &name, int power, float agility, int health, int exp) : Name_(
        name), power_(power), agility_(agility), health_(health), Exp_(exp) {}

// attack move with doging
auto Creature::attack(Creature &other) -> bool {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0, 1);

    if (dis(gen) < other.agility_) {
        other.health_ -= power_;
        return true;
    }
    return false;
}

// Generates random creatures
auto Creature::createRandomCreature() -> std::unique_ptr<Creature> {
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
    creature->Name_ = "Creature " + std::to_string(1);
    creature->health_ = std::uniform_int_distribution<>(1, 100)(gen);
    creature->power_ = std::uniform_int_distribution<>(1, 100)(gen);
    creature->agility_ = std::uniform_real_distribution<float>(0, 1)(gen);
    creature->Exp_ = 0;


    return creature;
}
// evolve function
auto Creature::evolve() -> void {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-5, 50);
    power_ += dis(gen);
    /// ETC
}

// effectivnes against other creature type
auto getEffectiveness(Creature &attacker, Creature &defender) -> int {
    /// TODO implement the interaction table
}

// enum to string
auto enumToString(CreatureType type) -> std::string {
    switch (type) {
        case CreatureType::Water:
            return "Water";
        case CreatureType::Fire:
            return "Fire";
        case CreatureType::Earth:
            return "Earth";
        case CreatureType::Air:
            return "Air";
        case CreatureType::Ice:
            return "Ice";
        case CreatureType::Steel:
            return "Steel";
        default:
            assert(false);
    }
}
