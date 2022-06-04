//
// Created by theer on 24.05.2022.
//
#include "Creature.hpp"
#include <string>
#include <vector>

enum class CreatureType {
    Water, Earth, Air, Fire, Ice, Steel
};
// make an interaction table for every type, water is less efective against water, fire is more effective against water and so on
// the table is a 2d array, the first index is the attacker type, the second index is the defender type
// the value is the effectiveness
const int interactionTable[6][6] = {
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0}
};



class SpecialAbility {
    /// TODO: add special abilities
};



auto getEffectiveness(Creature &attacker, Creature &defender) -> int {
    /// TODO implement the interaction table
}











