#pragma clang diagnostic push
#include "../Hpp/Creature.hpp"
#include "../Hpp/Fight.hpp"
#include <string>
#include <random>
#include <cassert>
#include <iostream>
#include <utility>


namespace vasio {
    Creature::Creature(const std::string &name, double power, float agility, int health, int currentHealth, int exp,
                       int expNeededToEvolve, SpecialAbility specialAbility) : Name_(name), power_(power),
                                                                               agility_(agility),
                                                                               health_(health),
                                                                               currentHealth_(currentHealth),
                                                                               Exp_(exp),
                                                                               ExpNeededToEvolve_(expNeededToEvolve),
                                                                               specialAbility_(
                                                                                       std::move(specialAbility)) {}


    auto Creature::attack(std::shared_ptr<Creature> &other) const -> int {
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
        std::random_device rd;
        std::mt19937 gen(rd());
        switch (this->specialAbility_.TypeOfAbility_) {
            case AbilityType::Offensive:
                switch (this->getType()) {
                    case CreatureType::Water:
                        other->currentHealth_ -= power_ * 1.5 * Creature::getEfficiency(other);
                        break;
                    case CreatureType::Earth:
                        other->currentHealth_ -= power_ * 1.1 * Creature::getEfficiency(other);
                        break;
                    case CreatureType::Air:
                        other->currentHealth_ -= power_ * 1.4 * Creature::getEfficiency(other);
                        break;
                    case CreatureType::Fire:
                        other->currentHealth_ -= power_ * 1.3 * Creature::getEfficiency(other);
                        break;
                    case CreatureType::Ice:
                        other->currentHealth_ -= power_ * 1.6 * Creature::getEfficiency(other);
                        break;
                    case CreatureType::Steel:
                        other->currentHealth_ -= power_ * 1.7 * Creature::getEfficiency(other);
                        break;
                    default:
                        break;
                }
            case AbilityType::Defensive:
                switch (this->getType()) {
                    case CreatureType::Water:
                        this->currentHealth_ += std::uniform_int_distribution<int>(25, 97)(gen);
                        if (this->currentHealth_ > this->health_)
                            this->currentHealth_ = this->health_;
                        break;
                    case CreatureType::Earth:
                        this->currentHealth_ += std::uniform_int_distribution<int>(25, 67)(gen);
                        if (this->currentHealth_ > this->health_)
                            this->currentHealth_ = this->health_;

                        break;
                    case CreatureType::Air:
                        this->currentHealth_ += std::uniform_int_distribution<int>(15, 80)(gen);
                        if (this->currentHealth_ > this->health_)
                            this->currentHealth_ = this->health_;
                        break;
                    case CreatureType::Fire:
                        this->currentHealth_ += std::uniform_int_distribution<int>(35, 120)(gen);
                        if (this->currentHealth_ > this->health_)
                            this->currentHealth_ = this->health_;
                        break;
                    case CreatureType::Ice:
                        this->currentHealth_ += std::uniform_int_distribution<int>(45, 90)(gen);
                        if (this->currentHealth_ > this->health_)
                            this->currentHealth_ = this->health_;
                        break;
                    case CreatureType::Steel:
                        this->currentHealth_ += std::uniform_int_distribution<int>(35, 110)(gen);
                        if (this->currentHealth_ > this->health_)
                            this->currentHealth_ = this->health_;
                        break;
                }
        }
    }

    auto Creature::evolve() -> void {
        if (Exp_ >= ExpNeededToEvolve_) {
            timesEvolved_++;
            int temp = timesEvolved_;
            std::random_device rd;
            std::mt19937 gen(rd());

            if (!isEvolved_) {
                Name_ = "Evolved " + Name_;
                isEvolved_ = true;
            } else {
                Name_ = "Evolved (" + std::to_string(temp) + ")" + Name_;
            }
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
                        power_ += std::uniform_int_distribution<int>(1, 15)(gen);
                        i++;
                        break;
                    case 2:
                        agility_ += std::uniform_real_distribution<float>(-0.1, 0.2)(gen);
                        i++;
                        break;
                    case 3:
                        health_ += std::uniform_int_distribution<int>(50, 100)(gen);
                        currentHealth_ = health_;
                        i++;
                        break;
                    default:
                        std::cerr << "Wrong attribute number" << '\n';
                        continue;
                }
            }
        } else {
            std::cout << "You need more exp to evolve" <<
                      std::endl;
        }
    }

    auto Creature::enemyEvolve() -> void {
        if (Exp_ >= ExpNeededToEvolve_) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(-5, 20);
            std::uniform_int_distribution<> dis2(1, 3);
            Name_ = "Evolved " + Name_;
            Exp_ = 0;
            ExpNeededToEvolve_ = std::uniform_int_distribution<>(1000, 2225)(gen);
            int i = 1;
            while (i <= 2) {
                switch (dis2(gen)) {
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
                        currentHealth_ = health_;
                        i++;
                        break;
                }
            }
        } else {
            std::cout << "Enemy needs more exp to evolve" << '\n';
        }
    }


    auto Creature::addExp(int exp) -> void {
        Exp_ += exp;
    }

    auto Creature::getName() const -> std::string {
        return Name_;
    }

    auto generateSpecialAbility(CreatureType creatureType) -> SpecialAbility {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 2);
        std::uniform_int_distribution<> dis2(1, 5);
        int random = dis(gen);
        unsigned int maxUses = dis2(gen);

        switch (creatureType) {
            case CreatureType::Water:
                switch (random) {
                    case 1:
                        return SpecialAbility{"Water Tornado", AbilityType::Offensive, "Creates water tornado dealing devastating damage", maxUses, 0};
                    case 2:
                        return SpecialAbility{"Water Shield", AbilityType::Defensive, "Negates effect of previous enemy attack by healing the creature", maxUses,0};
                    default:
                        assert(false);
                }
            case CreatureType::Fire:
                switch (random) {
                    case 1:
                        return SpecialAbility{"Fire Breath", AbilityType::Offensive, "Creates a deadly stream of fire burning your enemy", maxUses, 0};
                    case 2:
                        return SpecialAbility{"Fire Fenix", AbilityType::Defensive, "Summons a fenix that restores your hp", maxUses, 0};
                    default:
                        assert(false);
                }
            case CreatureType::Earth:
                switch (random) {
                    case 1:
                        return SpecialAbility{"Earthquake", AbilityType::Offensive, "Earth shakes furiously damaging everything in its area", maxUses, 0};
                    case 2:
                        return SpecialAbility{"Mud Golem", AbilityType::Defensive, "Mud golem is created to repair any damage suffered by creature", maxUses,
                                              0};
                    default:
                        assert(false);
                }
            case CreatureType::Air:
                switch (random) {
                    case 1:
                        return SpecialAbility{"Airstrike", AbilityType::Offensive, "Air is filled with thunders damaging your enemy", maxUses, 0};
                    case 2:
                        return SpecialAbility{"Healing wind", AbilityType::Defensive, "Magic wind health your creatures wounds", maxUses, 0};
                    default:
                        assert(false);
                }
            case CreatureType::Ice:
                switch (random) {
                    case 1:
                        return SpecialAbility{"Ice storm", AbilityType::Offensive, "Creates a wall of ice shards going straight into your enemy", maxUses, 0};
                    case 2:
                        return SpecialAbility{"Ice patch", AbilityType::Defensive, "Patches your wound with solid ice", maxUses, 0};
                    default:
                        assert(false);
                }
            case CreatureType::Steel:
                switch (random) {
                    case 1:
                        return SpecialAbility{"Steel sword", AbilityType::Offensive, "Deadly attack with magical steel sword cutting open your enemy", maxUses, 0};
                    case 2:
                        return SpecialAbility{"Additional armour", AbilityType::Defensive, "Your creatures wounds are filled with steel armour that stops the bleeding", maxUses,
                                              0};
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
        creature->health_ = std::uniform_int_distribution<>(80, 125)(gen);
        creature->currentHealth_ = creature->health_;
        creature->power_ = std::uniform_int_distribution<>(20, 50)(gen);
        creature->agility_ = std::uniform_real_distribution<float>(0.4, 0.75)(gen);
        creature->Exp_ = 0;
        creature->ExpNeededToEvolve_ = std::uniform_int_distribution<>(400, 700)(gen);
        return creature;
    }

    auto Creature::getShortStats() const -> void {
        std::cout << "Name || CHP/HP | Power || Agility || SA Name & Type" << '\n';
        std::cout << Name_ << " || " << currentHealth_ << " / " << health_ << " || " << power_ << " || " <<
                  agility_ << " || " << specialAbility_.NameOfAbility_ << " || " << specialAbility_.getTypeOfAbility() << '\n';
    }



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
