//
// Created by theer on 04.06.2022.
//

#include "Fight.hpp"
#include <random>

namespace vasio {
    Fight::Fight(const std::vector<std::unique_ptr<Creature>> &player1Creatures,
                 const std::vector<std::unique_ptr<Creature>> &player2Creatures) {
    }


    auto Fight::attack(unsigned int creatureAttackerIndex, unsigned int creatureAttackedIndex) -> void {
        auto &creatureAttacker = *(player1Turn_ ? player1Creatures_ : player2Creatures_).at(creatureAttackerIndex);
        auto &creatureAttacked = *(player1Turn_ ? player2Creatures_ : player1Creatures_).at(creatureAttackedIndex);

        creatureAttacker.attack(creatureAttacked);
        Fight::changeTurn();
    }
    auto Fight::useSpecialAbility(unsigned int creatureUsingAbilityIndex) -> void {

    }
    auto Fight::changeTurn() -> void {
        player1Turn_ = !player1Turn_;
    }

    auto Fight::getPlayer1CreatureInfo(std::vector<std::unique_ptr<Creature>> &player1Creatures) -> std::vector<std::string> {
        std::vector<std::string> creatureInfo;
        for (auto &creature : player1Creatures) {
            creatureInfo.push_back(creature->getName());
        }
        return creatureInfo;
    }
}