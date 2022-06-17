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
#include "SpecialAbility.hpp"

namespace vasio {
    /**
     *
     */
    enum class CreatureType {
        Water, Earth, Air, Fire, Ice, Steel
    };

    class Fight;

    /**
     * @param type
     * @return
     */
    auto enumCreatureTypeToString(CreatureType type) -> std::string;

    /**
     *
     */
    class Creature {
    public:
        std::string Name_{};
        double power_{};
        float agility_{};
        int health_{};
        int currentHealth_{};
        int Exp_{};
        int ExpNeededToEvolve_{};
        bool isEvolved_{};
        bool isEnemy_{};
        int timesEvolved_{};
        SpecialAbility specialAbility_;
        constexpr inline static float interactionTable[6][6] = {
                {0.5, 1.5, 1,   1.5, 1,   1},
                {1,   1,   0.5, 1.5, 1.5, 1.5},
                {1,   1,   0.5, 1,   2,   0.5},
                {0.5, 0.5, 1,   1,   1,   1.5},
                {0.5, 1.5, 1,   0.5, 1,   1},
                {1.5, 1,   1.5, 0.5, 1,   0.5}
        };

        /**
         *
         * @return
         */
        virtual auto getType() const -> CreatureType = 0;

        /**
         *
         * @param os
         * @param creature;
         * @return
         */
        friend std::ostream &operator<<(std::ostream &os, const Creature &creature) {
            os << "NAME: " << creature.Name_ << " PWR: " << creature.power_ << " AGL: " << std::setprecision(2)
               << creature.agility_
               << " HP: " << creature.health_ << " CHP: " << creature.currentHealth_ << " EXP: " << creature.Exp_
               << " EXPN: "
               << creature.ExpNeededToEvolve_ << " TYPE: " << enumCreatureTypeToString(creature.getType()) << " AB NAME: "
               << creature.specialAbility_.NameOfAbility_;
            return os;
        }

        /**
         *
         * @param creature
         * @return
         */
        auto getEfficiency(const std::shared_ptr<Creature> &creature) const -> float {
            return interactionTable[static_cast<int>(getType())][static_cast<int>(creature->getType())];
        }

        /**
         *
         * @return
         */
        auto static createRandomCreature() -> std::shared_ptr<Creature>;

        /**
         *
         * @param fight
         */
        auto useSpecialAbility(Fight &fight) -> void;

        /**
         *
         * @return
         */
        auto getName() const -> std::string;

        /**
         *
         */
        auto evolve() -> void;

        auto enemyEvolve() -> void;


        /**
         *
         * @param exp
         */
        auto addExp(int exp) -> void;

        /**
         *
         * @return
         */

        auto getCurrentHealth() const -> int;

        auto getShortStats() const -> void;

        auto getExp() const -> int;

        /**
         *
         */
        Creature() = default;

        /**
         *
         * @param name
         * @param power
         * @param agility
         * @param health
         * @param currentHealth
         * @param exp
         * @param expNeededToEvolve
         * @param specialAbility
         */
        Creature(const std::string &name, double power, float agility, int health, int currentHealth, int exp,
                 int expNeededToEvolve, SpecialAbility specialAbility);

        /**
         *
         * @param other
         * @return
         */
        auto attack(std::shared_ptr<Creature>& other) -> int;

        /**
         *
         * @param other
         */
        auto specialAction(std::shared_ptr<Creature> &other) -> void;

        /**
         *
         */
        virtual ~Creature() = default;
    };

    class WaterCreature : public Creature {
    public:
        using Creature::Creature;

        /**
         *
         * @return
         */
        auto getType() const -> CreatureType override {
            return CreatureType::Water;
        }
    };

    class EarthCreature : public Creature {
    public:
        using Creature::Creature;

        /**
         *
         * @return
         */
        auto getType() const -> CreatureType override {
            return CreatureType::Earth;
        }
    };

    class AirCreature : public Creature {
    public:
        using Creature::Creature;

        /**
         *
         * @return
         */
        auto getType() const -> CreatureType override {
            return CreatureType::Air;
        }
    };

    class FireCreature : public Creature {
    public:
        using Creature::Creature;

        /**
         *
         * @return
         */
        auto getType() const -> CreatureType override {
            return CreatureType::Fire;
        }
    };

    class IceCreature : public Creature {
    public:
        using Creature::Creature;

        /**
         *
         * @return
         */
        auto getType() const -> CreatureType override {
            return CreatureType::Ice;
        }
    };

    class SteelCreature : public Creature {
    public:
        using Creature::Creature;

        /**
         *
         * @return
         */
        auto getType() const -> CreatureType override {
            return CreatureType::Steel;
        }
    };
}


