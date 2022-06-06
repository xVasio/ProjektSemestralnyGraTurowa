//
// Created by theer on 24.05.2022.
//
#include "Creature.hpp"
#include <string>
#include <vector>
#include <random>
#include <cassert>
#include <iostream>

namespace vasio {
// constructor
    Creature::Creature(const std::string &name, int power, float agility, int health, int exp, int expNeededToEvolve)
            : Name_(
            name), power_(power), agility_(agility), health_(health), Exp_(exp),
              ExpNeededToEvolve_(expNeededToEvolve) {}

// attack move with doging
    auto Creature::attack(Creature &other) -> bool {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0, 1); //zmienic wartości

        if (dis(gen) < other.agility_) {
            other.health_ -= power_ * Creature::getEfficiency(other);
            return true;
        }
        return false;
    }

// evolve function
    auto Creature::evolve() -> void {
        if (Exp_ >= ExpNeededToEvolve_) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(-5, 50);
            Name_ = "Evloved " + Name_;
            power_ += dis(gen);
            agility_ += std::uniform_real_distribution<float>(-0.1, 0.2)(gen);
            health_ += dis(gen);
            Exp_ = 0;
            ExpNeededToEvolve_ = std::uniform_int_distribution<>(1000, 2225)(gen);
        } else {
            std::cout << "You need more exp to evolve" << std::endl;
        }
    }

    auto Creature::addExp(int exp) -> void {
        Exp_ += exp;
    }

    auto Creature::getExp() const -> int {
        return Exp_;
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
}