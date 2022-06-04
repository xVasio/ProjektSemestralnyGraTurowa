//
// Created by theer on 24.05.2022.
//

#include <string>
#include <vector>

#ifndef PROJEKTSEMESTRALNYGRATUROWA_CREATURE_HPP
#define PROJEKTSEMESTRALNYGRATUROWA_CREATURE_HPP

enum class CreatureType {
    Water, Earth, Air, Fire, Ice, Steel
};



class Creature {
    std::string Name;
    int power;
    int agility;
    int health;
    int Exp;
    CreatureType type;
    SpecialAbility& specialAbility;

    Creature(const std::string &name, int power, int agility, int health, int exp, SpecialAbility &specialAbility)
            : Name(name), power(power), agility(agility), health(health), Exp(exp), specialAbility(specialAbility) {}
};




#endif //PROJEKTSEMESTRALNYGRATUROWA_CREATURE_HPP
