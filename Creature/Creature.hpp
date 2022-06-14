//
// Created by theer on 24.05.2022.
//
#pragma once

#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <ostream>
#include <iomanip>
#include "../SpecialAbility/SpecialAbility.hpp"

namespace vasio {
    enum class CreatureType {
        Water, Earth, Air, Fire, Ice, Steel
    };

    class Fight;

    auto enumToString(CreatureType type) -> std::string;


    class Creature {
        ///dodac special ability i uzależnić je od CreatureType, losować z predefiniowanej puli
        std::string Name_;
        int power_;
        float agility_;
        int health_;
        int currentHealth_;
        int Exp_;
        int ExpNeededToEvolve_;
        SpecialAbility specialAbility_;
        constexpr inline static float interactionTable[6][6] = {
                {0.5, 1.5, 1,   1.5, 1,   1},
                {1,   1,   0.5, 1.5, 1.5, 1.5},
                {1,   1,   0.5, 1,   2,   0.5},
                {0.5, 0.5, 1,   1,   1,   1.5},
                {0.5, 1.5, 1,   0.5, 1,   1},
                {1.5, 1,   1.5, 0.5, 1,   0.5}
        };


    public:
        virtual auto getType() const -> CreatureType = 0;


        friend std::ostream &operator<<(std::ostream &os, const Creature &creature) {
            os <<"NAME: " << creature.Name_ << " PWR: " << creature.power_ << " AGL: " << std::setprecision(2) << creature.agility_
               << " HP: " << creature.health_ << " CHP: " << creature.currentHealth_ << " EXP: " << creature.Exp_ << " EXPN: "
               << creature.ExpNeededToEvolve_ << " TYPE: " << enumToString(creature.getType()) << " AB NAME: " << creature.specialAbility_.NameOfAbility_;
            return os;
        }

        auto getEfficiency(const Creature &creature) const -> float {
            return interactionTable[static_cast<int>(getType())][static_cast<int>(creature.getType())];
        }

        auto static createRandomCreature() -> std::unique_ptr<Creature>;

        auto useSpecialAbility(Fight &fight) -> void;

        auto getName() const -> std::string;

        auto evolve() -> void;

        auto addExp(int exp) -> void;

        auto getExp() const -> int;

        Creature() = default;

        Creature(const std::string &name, int power, float agility, int health, int currentHealth, int exp, int expNeededToEvolve, SpecialAbility specialAbility);

        auto attack(Creature &other) -> bool;

        virtual ~Creature() = default;
    };

    class WaterCreature : public Creature {
    public:
        using Creature::Creature;

        auto getType() const -> CreatureType override {
            return CreatureType::Water;
        }
    };

    class EarthCreature : public Creature {
    public:
        using Creature::Creature;

        auto getType() const -> CreatureType override {
            return CreatureType::Earth;
        }
    };

    class AirCreature : public Creature {
    public:
        using Creature::Creature;

        auto getType() const -> CreatureType override {
            return CreatureType::Air;
        }
    };

    class FireCreature : public Creature {
    public:
        using Creature::Creature;

        auto getType() const -> CreatureType override {
            return CreatureType::Fire;
        }
    };

    class IceCreature : public Creature {
    public:
        using Creature::Creature;

        auto getType() const -> CreatureType override {
            return CreatureType::Ice;
        }
    };

    class SteelCreature : public Creature {
    public:
        using Creature::Creature;

        auto getType() const -> CreatureType override {
            return CreatureType::Steel;
        }
    };
}


