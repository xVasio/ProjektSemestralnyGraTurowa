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
    Creature::Creature(const std::string &name, int power, float agility, int health, int currentHealth, int exp,
                       int expNeededToEvolve, SpecialAbility specialAbility) : Name_(name), power_(power),
                                                                               agility_(agility),
                                                                               health_(health),
                                                                               currentHealth_(currentHealth),
                                                                               Exp_(exp),
                                                                               ExpNeededToEvolve_(expNeededToEvolve),
                                                                               specialAbility_(specialAbility) {}

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
// co jesli wyewoluujemy stworzenie podczas walki a operujeym na klonach
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

    auto Creature::getName() const -> std::string {
        return Name_;
    }

//    auto generateSpecialAbility(CreatureType creatureType, AbilityType abilityType) -> SpecialAbility {
//        switch (creatureType) {
//            case CreatureType::Water:
//                switch (abilityType) {
//                    case AbilityType::Offensive:
//                        return SpecialAbility("Water Attack","Attack with water",2, [](Fight &fight) -> void {
//
//                });
//                    case AbilityType::Defensive:
//                        return SpecialAbility("Water Shield", 10, 0.5);
//                    default:
//                        assert(false);
//                }
//            case CreatureType::Fire:
//                switch (abilityType) {
//                    case AbilityType::Offensive:
//                        return SpecialAbility("Fire Attack", 10, 0.5);
//                    case AbilityType::Defensive:
//                        return SpecialAbility("Fire Shield", 10, 0.5);
//                    default:
//                        assert(false);
//                }
//            case CreatureType::Earth:
//                switch (abilityType) {
//                    case AbilityType::Offensive:
//                        return SpecialAbility("Earth Attack", 10, 0.5);
//                    case AbilityType::Defensive:
//                        return SpecialAbility("Earth Shield", 10, 0.5);
//                    default:
//                        assert(false);
//                }
//            case CreatureType::Air:
//                switch (abilityType) {
//                    case AbilityType::Offensive:
//                        return SpecialAbility("Air Attack", 10, 0.5);
//                    case AbilityType::Defensive:
//                        return SpecialAbility("Air Shield", 10, 0.5);
//                    default:
//                        assert(false);
//                }
//            case CreatureType::Ice:
//                switch (abilityType) {
//                    case AbilityType::Offensive:
//                        return SpecialAbility("Ice Attack", 10, 0.5);
//                    case AbilityType::Defensive:
//                        return SpecialAbility("Ice Shield", 10, 0.5);
//                    default:
//                        assert(false);
//                }
//            case CreatureType::Steel:
//                switch (abilityType) {
//                    case AbilityType::Offensive:
//                        return SpecialAbility("Steel Attack", 10, 0.5);
//                    case AbilityType::Defensive:
//                        return SpecialAbility("Steel Shield", 10, 0.5);
//                    default:
//                        assert(false);
//                }
//        }


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
            creature->Name_ = generateName(creature->getType());
            creature->health_ = std::uniform_int_distribution<>(80, 100)(gen);
            creature->currentHealth_ = creature->health_;
            creature->power_ = std::uniform_int_distribution<>(1, 12)(gen);
            creature->agility_ = std::uniform_real_distribution<float>(0.3, 0.7)(gen);
            creature->Exp_ = 0;
            creature->ExpNeededToEvolve_ = std::uniform_int_distribution<>(500, 1000)(gen);
            creature->specialAbility_ = SpecialAbility();
            return creature;
        }

//    auto Creature::useSpecialAbility(Fight &fight) -> void {
//        specialAbility_.abilityFunction_(fight);
//    }


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