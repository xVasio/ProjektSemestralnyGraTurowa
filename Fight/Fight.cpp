//
// Created by theer on 04.06.2022.
//

#include "Fight.hpp"
#include <random>


Fight::Fight(const std::vector<Creature*> &player1Creatures, const std::vector<Creature*> &player2Creatures) {
    for (auto creature : player1Creatures) {
        player1Creatures_.push_back(creature->cloneCreature());
    }
    for (auto creature : player2Creatures) {
        player2Creatures_.push_back(creature->cloneCreature());
    }
}

auto Fight::attack(unsigned int creatureAttackerIndex, unsigned int creatureAttackedIndex) -> void {
    auto &creatureAttacker = *(player1Turn_ ? player1Creatures_ : player2Creatures_).at(creatureAttackerIndex);
    auto &creatureAttacked = *(player1Turn_ ? player2Creatures_ : player1Creatures_).at(creatureAttackedIndex);

    creatureAttacker.attack(creatureAttacked);

}
