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
     * Enum for the different types of creatures
     */
    enum class CreatureType {
        Water, Earth, Air, Fire, Ice, Steel
    };

    class Fight;

    /**
     * @param type
     * @return the string representation of enum CreatureType
     */
    auto enumCreatureTypeToString(CreatureType type) -> std::string;

    /**
     *
     * Class representing basic creature and its attributes
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
                {1,   0.5, 1,   1,   2,   0.5},
                {0.5, 0.5, 1,   1,   1.5, 1.5},
                {0.5, 1.5, 1,   0.5, 0.5, 1},
                {1.5, 1,   1.5, 0.5, 1,   0.5}
        };

        /**
         * Virtual function for polymorphism returning the type of creature
         * @return object of enum class CreatureType
         */
        virtual auto getType() const -> CreatureType = 0;

        /**
         * Friend function for printing the creature to an output stream
         * @param os
         * @param creature;
         * @return the ostream os with the creature information
         */
        friend std::ostream &operator<<(std::ostream &os, const Creature &creature) {
            os << "NAME: " << creature.Name_ << "|PWR: " << creature.power_ << "|AGL: " << std::setprecision(2)
               << creature.agility_
               << "|CHP/HP " << creature.currentHealth_ << "/" << creature.health_ << "|EXP: " << creature.Exp_
               << "|EXPN: " << creature.ExpNeededToEvolve_ << " TYPE: " << enumCreatureTypeToString(creature.getType())
               << "|AB NAME: "
               << creature.specialAbility_.NameOfAbility_ << '\n' << "|AB TYPE: "
               << creature.specialAbility_.getTypeOfAbility();
            return os;
        }

        /**
         * Function to get the interaction value between two creatures
         *
         * @param creature
         * @return float value representing the damage multiplier (0.5 - 2)
         */
        auto getEfficiency(const std::shared_ptr<Creature> &creature) const -> float {
            return interactionTable[static_cast<int>(getType())][static_cast<int>(creature->getType())];
        }

        /**
         * Creates a random creature with random attributes
         * @return an object of class Creature
         */
        auto static createRandomCreature() -> std::shared_ptr<Creature>;

        /**
         *
         * @return the name of the creature
         */
        auto getName() const -> std::string;

        /**
         * function implementing evolution of the creature
         */
        auto evolve() -> void;

        /**
         *
         * function implementing evolution of the creature for AI
         */
        auto enemyEvolve() -> void;


        /**
         * Function adding experience to the creature
         * @param exp the amount of exp to add to the creature
         */
        auto addExp(int exp) -> void;

        /**
         * Function displaying the creature information in shorter form than os stream
         */
        auto getShortStats() const -> void;

        /**
         * Default constructor
         */
        Creature() = default;

        /**
         *
         * @param name
         * @param power
         * @param agility
         * @param health
         * @param exp
         * @param expNeededToEvolve
         * @param SpecialAbility
         *
         * Constructor with parameters
         */
        Creature(const std::string &name, double power, float agility, int health, int currentHealth, int exp,
                 int expNeededToEvolve, SpecialAbility specialAbility);

        /**
         * Function implementing attack mechanism
         * @param other means the another creature object that is being attacked
         * @return damage given by the creature to the other creature
         */
        auto attack(std::shared_ptr<Creature> &other) const -> int;

        /**
         * Function implementing special ability effect mechanism
         * @param other
         * function implementing the use of special ability of the creature
         */
        auto specialAction(std::shared_ptr<Creature> &other) -> void;

        /**
         * Destructor
         */
        virtual ~Creature() = default;
    };

    class WaterCreature : public Creature {
    public:
        using Creature::Creature;

        /**
         * Overriding virtual function getType() for this derived class
         * @return object of enum class CreatureType Water
         */
        auto getType() const -> CreatureType override {
            return CreatureType::Water;
        }
    };

    class EarthCreature : public Creature {
    public:
        using Creature::Creature;

        /**
         * Overriding virtual function getType() for this derived class
         * @return object of enum class CreatureType Earth
         */
        auto getType() const -> CreatureType override {
            return CreatureType::Earth;
        }
    };

    class AirCreature : public Creature {
    public:
        using Creature::Creature;

        /**
         * Overriding virtual function getType() for this derived class
         * @return object of enum class CreatureType Air
         */
        auto getType() const -> CreatureType override {
            return CreatureType::Air;
        }
    };

    class FireCreature : public Creature {
    public:
        using Creature::Creature;

        /**
         * Overriding virtual function getType() for this derived class
         * @return object of enum class CreatureType Fire
         */
        auto getType() const -> CreatureType override {
            return CreatureType::Fire;
        }
    };

    class IceCreature : public Creature {
    public:
        using Creature::Creature;

        /**
         * Overriding virtual function getType() for this derived class
         * @return object of enum class CreatureType Ice
         */
        auto getType() const -> CreatureType override {
            return CreatureType::Ice;
        }
    };

    class SteelCreature : public Creature {
    public:
        using Creature::Creature;

        /**
         * Overriding virtual function getType() for this derived class
         * @return object of enum class CreatureType Steel
         */
        auto getType() const -> CreatureType override {
            return CreatureType::Steel;
        }
    };
}


