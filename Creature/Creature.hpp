//
// Created by theer on 24.05.2022.
//
#pragma once

#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <ostream>

enum class CreatureType {
    Water, Earth, Air, Fire, Ice, Steel
};

auto enumToString(CreatureType type) -> std::string;

class Creature {
    /// dodac evolution
    ///dodac special ability
    std::string Name_;
    int power_;
    float agility_;
    int health_;
    int Exp_;

    //table of interactions beetween types
    constexpr inline static float interactionTable[6][6] = {
            {0.5, 1.5, 1, 1.5, 1, 1},
            {1, 1, 0.5, 1.5, 1.5, 1.5},
            {1, 1, 0.5, 1, 2, 0.5},
            {0.5, 0.5, 1, 1, 1, 1.5},
            {0.5, 1.5, 1, 0.5, 1, 1},
            {1.5, 1, 1.5, 0.5, 1, 0.5}
    };


public:
    virtual auto getType() const -> CreatureType = 0;

    virtual auto cloneCreature() const -> std::unique_ptr<Creature> = 0;

    friend std::ostream &operator<<(std::ostream &os, const Creature &creature) {
        os << "Name: " << creature.Name_ << " Power: " << creature.power_ << " Agility: " << creature.agility_
           << " Health: " << creature.health_ << " Exp: " << creature.Exp_ << " Type: " << enumToString(creature.getType());
        return os;
    }

    auto getEfficiency(const Creature &creature) const -> float {
        return interactionTable[static_cast<int>(getType())][static_cast<int>(creature.getType())];
    }
    auto evolve() -> void;

    Creature() = default;

    Creature(const std::string &name, int power, float agility, int health, int exp);

    auto attack(Creature &other) -> bool;

    static auto createRandomCreature() -> std::unique_ptr<Creature>;
};

class WaterCreature : public Creature {
public:
    using Creature::Creature;
    auto getType() const -> CreatureType override {
        return CreatureType::Water;
    }
    auto cloneCreature() const -> std::unique_ptr<Creature> override {
        return std::make_unique<WaterCreature>(*this);
    }

};

class EarthCreature : public Creature {
public:
    using Creature::Creature;
    auto getType() const -> CreatureType override {
        return CreatureType::Earth;
    }
    auto cloneCreature() const -> std::unique_ptr<Creature> override {
        return std::make_unique<EarthCreature>(*this);
    }
};

class AirCreature : public Creature {
public:
    using Creature::Creature;
    auto getType() const -> CreatureType override {
        return CreatureType::Air;
    }
    auto cloneCreature() const -> std::unique_ptr<Creature> override {
        return std::make_unique<AirCreature>(*this);
    }
};

class FireCreature : public Creature {
public:
    using Creature::Creature;
    auto getType() const -> CreatureType override {
        return CreatureType::Fire;
    }
    auto cloneCreature() const -> std::unique_ptr<Creature> override {
        return std::make_unique<FireCreature>(*this);
    }
};
class IceCreature : public Creature {
public:
    using Creature::Creature;
    auto getType() const -> CreatureType override {
        return CreatureType::Ice;
    }
    auto cloneCreature() const -> std::unique_ptr<Creature> override {
        return std::make_unique<IceCreature>(*this);
    }
};
class SteelCreature : public Creature {
public:
    using Creature::Creature;
    auto getType() const -> CreatureType override {
        return CreatureType::Steel;
    }
    auto cloneCreature() const -> std::unique_ptr<Creature> override {
        return std::make_unique<SteelCreature>(*this);
    }
};



