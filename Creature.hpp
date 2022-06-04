//
// Created by theer on 24.05.2022.
//
#pragma once

#include <string>
#include <vector>
#include <functional>

enum class CreatureType {
    Water, Earth, Air, Fire, Ice, Steel
};


class Creature {
    using SpecialAbility =  std::function<Creature&(Creature&)>;
    std::string Name;
    int power;
    int agility;
    int health;
    int Exp;
    CreatureType type;
    SpecialAbility specialAbility;
    constexpr inline static int interactionTable[6][6] = {
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0}
    };
public:
    virtual auto getType() const -> CreatureType = 0;


    Creature(const std::string &name, int power, int agility, int health, int exp, SpecialAbility const &specialAbility)
            : Name(name), power(power), agility(agility), health(health), Exp(exp), specialAbility(specialAbility) {}

};

class WaterCreature : Creature {
public:
    using Creature::Creature;
    CreatureType getType() const override {
        return CreatureType::Water;
    }
};

class EarthCreature : Creature {
public:
    using Creature::Creature;
    CreatureType getType() const override {
        return CreatureType::Earth;
    }
};

class AirCreature : Creature {
public:
    using Creature::Creature;
    CreatureType getType() const override {
        return CreatureType::Air;
    }
};

class FireCreature : Creature {
public:
    using Creature::Creature;
    CreatureType getType() const override {
        return CreatureType::Fire;
    }
};
class IceCreature : Creature {
public:
    using Creature::Creature;
    CreatureType getType() const override {
        return CreatureType::Ice;
    }
};
class SteelCreature : Creature {
public:
    using Creature::Creature;
    CreatureType getType() const override {
        return CreatureType::Steel;
    }
};



