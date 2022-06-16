//
// Created by theer on 24.05.2022.
//
#include "../Hpp/Creature.hpp"
#include "../Hpp/Fight.hpp"
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
    auto Creature::attack(std::shared_ptr<Creature> &other) -> int {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0, 1);
        std::uniform_int_distribution<int> dis2(1, 5);
        if (dis(gen) > other->agility_) {
            int damage = (power_ + dis2(gen)) * Creature::getEfficiency(other);
            other->currentHealth_ -= damage;
            return damage;
        }
        return 0;
    }

    auto Creature::specialAction(std::shared_ptr<Creature> &other) -> void {
        switch (this->specialAbility_.TypeOfAbility_) {
            case AbilityType::Offensive:
                switch (this->getType()) {
                    case CreatureType::Water:
                        other->currentHealth_ -= power_ * 1.2 * Creature::getEfficiency(other);
                        break;
                    case CreatureType::Earth:
                        other->currentHealth_ -= power_ * 1.2 * Creature::getEfficiency(other);
                        break;
                    case CreatureType::Air:
                        other->currentHealth_ -= power_ * 1.2 * Creature::getEfficiency(other);
                        break;
                    case CreatureType::Fire:
                        other->currentHealth_ -= power_ * 1.2 * Creature::getEfficiency(other);
                        break;
                    case CreatureType::Ice:
                        other->currentHealth_ -= power_ * 1.2 * Creature::getEfficiency(other);
                        break;
                    case CreatureType::Steel:
                        other->currentHealth_ -= power_ * 1.2 * Creature::getEfficiency(other);
                        break;
                }
            case AbilityType::Defensive:
                switch (this->getType()) {
                    case CreatureType::Water:
                        this->currentHealth_ += 50;
                        if(this->currentHealth_ > this->health_)
                            this->currentHealth_ = this->health_;
                        this->Exp_ += 100 * Creature::getEfficiency(other);
                        break;
                    case CreatureType::Earth:
                        this->currentHealth_ += 50;
                        if(this->currentHealth_ > this->health_)
                            this->currentHealth_ = this->health_;
                        this->Exp_ += 100 * Creature::getEfficiency(other);
                        break;
                    case CreatureType::Air:
                        this->currentHealth_ += 50;
                        if(this->currentHealth_ > this->health_)
                            this->currentHealth_ = this->health_;
                        this->Exp_ += 100 * Creature::getEfficiency(other);
                        break;
                    case CreatureType::Fire:
                        this->currentHealth_ += 50;
                        if(this->currentHealth_ > this->health_)
                            this->currentHealth_ = this->health_;
                        this->Exp_ += 100 * Creature::getEfficiency(other);
                        break;
                    case CreatureType::Ice:
                        this->currentHealth_ += 50;
                        if(this->currentHealth_ > this->health_)
                            this->currentHealth_ = this->health_;
                        this->Exp_ += 100 * Creature::getEfficiency(other);
                        break;
                    case CreatureType::Steel:
                        this->currentHealth_ += 50;
                        if(this->currentHealth_ > this->health_)
                            this->currentHealth_ = this->health_;
                        this->Exp_ += 100 * Creature::getEfficiency(other);
                        break;
                }
        }
    }

// evolve function
    auto Creature::evolve() -> void {
        if (Exp_ >= ExpNeededToEvolve_) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(-5, 20);
            Name_ = "Evolved " + Name_;
            Exp_ = 0;
            ExpNeededToEvolve_ = std::uniform_int_distribution<>(1000, 2225)(gen);
            int i = 1;
            while (i <= 2) {
                std::cout << "Type " << i << ". attribute you want to upgrade:"
                          << '\n';
                std::cout << "(1) Power, (2) Agility, (3) Health" << '\n';

                std::string choiceString{};
                std::cin >> choiceString;

                auto choice = std::stoi(choiceString);

                switch (choice) {
                    case 1:
                        power_ += dis(gen);
                        i++;
                        break;
                    case 2:
                        agility_ += std::uniform_real_distribution<float>(-0.1, 0.2)(gen);
                        i++;
                        break;
                    case 3:
                        health_ += dis(gen);
                        i++;
                        break;
                    default:
                        std::cerr << "Wrong atribute number" << '\n';
                        continue;
                }
            }
        } else {
            std::cout << "You need more exp to evolve" <<
                      std::endl;
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
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 2);
        int random = dis(gen);

        switch (creatureType) {
            case CreatureType::Water:
                switch (random) {
                    case 1:
                        return SpecialAbility{"Water Attack", AbilityType::Offensive, "Attack with water", 2,0};
                    case 2:
                        return SpecialAbility{"Water Defence", AbilityType::Defensive, "Defence with water", 2,0};
                    default:
                        assert(false);
                }
            case CreatureType::Fire:
                switch (random) {
                    case 1:
                        return SpecialAbility{"Fire Attack", AbilityType::Offensive, "Attack with Fire", 2,0};
                    case 2:
                        return SpecialAbility{"Fire Defence", AbilityType::Defensive, "Defence with Fire", 2,0};
                    default:
                        assert(false);
                }
            case CreatureType::Earth:
                switch (random) {
                    case 1:
                        return SpecialAbility{"Earth Attack", AbilityType::Offensive, "Attack with Earth", 2,0};
                    case 2:
                        return SpecialAbility{"Earth Defence", AbilityType::Defensive, "Defence with Earth", 2,0};
                    default:
                        assert(false);
                }
            case CreatureType::Air:
                switch (random) {
                    case 1:
                        return SpecialAbility{"Air Attack", AbilityType::Offensive, "Attack with Air", 2,0};
                    case 2:
                        return SpecialAbility{"Air Defence", AbilityType::Defensive, "Defence with Air", 2,0};
                    default:
                        assert(false);
                }
            case CreatureType::Ice:
                switch (random) {
                    case 1:
                        return SpecialAbility{"Ice Attack", AbilityType::Offensive, "Attack with Ice", 2,0};
                    case 2:
                        return SpecialAbility{"Ice Defence", AbilityType::Defensive, "Defence with Ice", 2,0};
                    default:
                        assert(false);
                }
            case CreatureType::Steel:
                switch (random) {
                    case 1:
                        return SpecialAbility{"Steel Attack", AbilityType::Offensive, "Attack with Steel", 2,0};
                    case 2:
                        return SpecialAbility{"Steel Defence", AbilityType::Defensive, "Defence with Steel", 2,0};
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

    auto Creature::createRandomCreature() -> std::shared_ptr<Creature> {
        std::shared_ptr<Creature> creature;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 5);
        int random = dis(gen);
        switch (random) {
            case 0:
                creature = std::make_shared<WaterCreature>();
                creature->specialAbility_ = generateSpecialAbility(CreatureType::Water);
                break;
            case 1:
                creature = std::make_shared<FireCreature>();
                creature->specialAbility_ = generateSpecialAbility(CreatureType::Fire);
                break;
            case 2:
                creature = std::make_shared<EarthCreature>();
                creature->specialAbility_ = generateSpecialAbility(CreatureType::Earth);
                break;
            case 3:
                creature = std::make_shared<AirCreature>();
                creature->specialAbility_ = generateSpecialAbility(CreatureType::Air);
                break;
            case 4:
                creature = std::make_shared<IceCreature>();
                creature->specialAbility_ = generateSpecialAbility(CreatureType::Ice);
                break;
            case 5:
                creature = std::make_shared<SteelCreature>();
                creature->specialAbility_ = generateSpecialAbility(CreatureType::Steel);
                break;
            default:
                assert(false);
        }
        creature->Name_ = generateName(creature->getType());
        creature->health_ = std::uniform_int_distribution<>(80, 100)(gen);
        creature->currentHealth_ = creature->health_;
        creature->power_ = std::uniform_int_distribution<>(1, 50)(gen); // zmienci na mniej
        creature->agility_ = std::uniform_real_distribution<float>(0.3, 0.7)(gen);
        creature->Exp_ = 0;
        creature->ExpNeededToEvolve_ = std::uniform_int_distribution<>(500, 1000)(gen);
        return creature;
    }

    auto Creature::useSpecialAbility(Fight &fight) -> void {
        specialAbility_.applyAbility(fight);
        specialAbility_.maxNumberOfUses_--;
    }

    auto Creature::getCurrentHealth() const -> int {
        return currentHealth_;
    }

    auto Creature::getShortStats() const -> void {
        std::cout << "Name || Current Health/Health | Power || Agility" << '\n';
        std::cout << Name_ << " || " << currentHealth_ << " / " << health_ << " || " << power_ << " || " <<
                  agility_ << " ||" << '\n';
    }


// enum to string
    auto enumCreatureTypeToString(CreatureType type) -> std::string {
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