//
// Created by theer on 24.05.2022.
//
#include "Creature.hpp"
#include "../Fight/Fight.hpp"
#include <string>
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
            std::uniform_int_distribution<> dis(-5, 20);
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


    // no prawie działa
    auto generateSpecialAbility(CreatureType creatureType) -> SpecialAbility {
        AbilityType abilityType;
        std::unique_ptr<Creature> creature;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 2);
        int random = dis(gen);

        switch (creatureType) {
            case CreatureType::Water:
                switch (random) {
                    case 1:
                        return SpecialAbility("Water Attack", AbilityType::Offensive, "Attack with water", 2,
                                              [](Fight &fight) -> void {

                                              });
                    case 2:
                        return SpecialAbility("Water Defence", AbilityType::Defensive, "Defence with water", 2,
                                              [](Fight &fight) -> void {
                                                  std::cout << "Water Defence" << std::endl;
                                              });
                    default:
                        assert(false);
                }
            case CreatureType::Fire:
                switch (random) {
                    case 1:
                        return SpecialAbility("Fire Attack", AbilityType::Offensive, "Attack with Fire", 2,
                                              [](Fight &fight) -> void {
                                                  std::cout << "Fire Attack" << std::endl;
                                              });
                    case 2:
                        return SpecialAbility("Fire Defence", AbilityType::Defensive, "Defence with Fire", 2,
                                              [](Fight &fight) -> void {
                                                  std::cout << "Fire Defence" << std::endl;
                                              });
                    default:
                        assert(false);
                }
            case CreatureType::Earth:
                switch (random) {
                    case 1:
                        return SpecialAbility("Earth Attack", AbilityType::Offensive, "Attack with Earth", 2,
                                              [](Fight &fight) -> void {
                                                  std::cout << "Earth Attack" << std::endl;
                                              });
                    case 2:
                        return SpecialAbility("Earth Defence", AbilityType::Defensive, "Defence with Earth", 2,
                                              [](Fight &fight) -> void {
                                                  std::cout << "Earth Defence" << std::endl;
                                              });
                    default:
                        assert(false);
                }
            case CreatureType::Air:
                switch (random) {
                    case 1:
                        return SpecialAbility("Air Attack", AbilityType::Offensive, "Attack with Air", 2,
                                              [](Fight &fight) -> void {
                                                  std::cout << "Air Attack" << std::endl;
                                              });
                    case 2:
                        return SpecialAbility("Air Defence", AbilityType::Defensive, "Defence with Air", 2,
                                              [](Fight &fight) -> void {
                                                  std::cout << "Air Defence" << std::endl;
                                              });
                    default:
                        assert(false);
                }
            case CreatureType::Ice:
                switch (random) {
                    case 1:
                        return SpecialAbility("Ice Attack", AbilityType::Offensive, "Attack with Ice", 2,
                                              [](Fight &fight) -> void {
                                                  std::cout << "Ice Attack" << std::endl;
                                              });
                    case 2:
                        return SpecialAbility("Ice Defence", AbilityType::Defensive, "Defence with Ice", 2,
                                              [](Fight &fight) -> void {
                                                  std::cout << "Ice Defence" << std::endl;
                                              });
                    default:
                        assert(false);
                }
            case CreatureType::Steel:
                switch (random) {
                    case 1:
                        return SpecialAbility("Steel Attack", AbilityType::Offensive, "Attack with Steel", 2,
                                              [](Fight &fight) -> void {
                                                  std::cout << "Steel Attack" << std::endl;
                                              });
                    case 2:
                        return SpecialAbility("Steel Defence", AbilityType::Defensive, "Defence with Steel", 2,
                                              [](Fight &fight) -> void {
                                                  std::cout << "Steel Defence" << std::endl;
                                              });
                    default:
                        assert(false);
                }
            default:
                assert(false);
        }
    }

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
                creature->specialAbility_ = generateSpecialAbility(CreatureType::Water);
                break;
            case 1:
                creature = std::make_unique<FireCreature>();
                creature->specialAbility_ = generateSpecialAbility(CreatureType::Fire);
                break;
            case 2:
                creature = std::make_unique<EarthCreature>();
                creature->specialAbility_ = generateSpecialAbility(CreatureType::Earth);
                break;
            case 3:
                creature = std::make_unique<AirCreature>();
                creature->specialAbility_ = generateSpecialAbility(CreatureType::Air);
                break;
            case 4:
                creature = std::make_unique<IceCreature>();
                creature->specialAbility_ = generateSpecialAbility(CreatureType::Ice);
                break;
            case 5:
                creature = std::make_unique<SteelCreature>();
                creature->specialAbility_ = generateSpecialAbility(CreatureType::Steel);
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
        return creature;
    }

      auto Creature::useSpecialAbility(Fight &fight) -> void {
        specialAbility_.abilityFunction_(fight);
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