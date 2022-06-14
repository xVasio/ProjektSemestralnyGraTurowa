//
// Created by theer on 04.06.2022.
//

#include "Fight.hpp"
#include <random>
#include <iostream>

namespace vasio {
    Fight::Fight(const std::vector<std::unique_ptr<Creature>> &player1Creatures,
                 const std::vector<std::unique_ptr<Creature>> &player2Creatures) {
    }


    auto Fight::attack(unsigned int creatureAttackerIndex, unsigned int creatureAttackedIndex) -> void {
        auto &creatureAttacker = *(player1Turn_ ? player1Creatures_ : player2Creatures_).at(creatureAttackerIndex);
        auto &creatureAttacked = *(player1Turn_ ? player2Creatures_ : player1Creatures_).at(creatureAttackedIndex);

        *currentPlayer1Pokemon = (player1Turn_ ? creatureAttacker : creatureAttacked);
        *currentPlayer2Pokemon = (player1Turn_ ? creatureAttacked : creatureAttacker);

        creatureAttacker.attack(creatureAttacked);
        Fight::changeTurn();
    }


    auto Fight::useSpecialAbility(unsigned int creatureUsingAbilityIndex) -> void {
        auto &creatureUsingAbility = *(player1Turn_ ? player1Creatures_ : player2Creatures_).at(
                creatureUsingAbilityIndex);
        creatureUsingAbility.useSpecialAbility(*this);
        Fight::changeTurn();
    }

    auto Fight::changeTurn() -> void {
        player1Turn_ = !player1Turn_;
    }


    auto Fight::getPlayer1CreatureInfo(std::vector<std::unique_ptr<Creature>> &player1Creatures) -> void {
        auto creatureInfo = std::vector<std::string>(player1Creatures.size());

//        std::ranges::transform(player1Creatures.begin(), player1Creatures.end(),creatureInfo.begin(),[](){});

        for (auto &creature: player1Creatures) {
            creatureInfo.push_back(creature->getName());
        }
        for (const auto &c: creatureInfo) {
            std::cout << c << std::endl;
        }
    }
}