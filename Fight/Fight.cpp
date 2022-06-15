//
// Created by theer on 04.06.2022.
//

#include "../Hpp/Fight.hpp"
#include <random>
#include <iostream>

namespace vasio {
    Fight::Fight(std::unique_ptr<Creature> currentPlayer1Creature,
                 std::unique_ptr<Creature> currentPlayer2Creature) {
    }


    auto Fight::attack() -> void {
        if (player1Turn_) {
            currentPlayer1Pokemon->attack(currentPlayer2Pokemon);
        } else {
            currentPlayer2Pokemon->attack(currentPlayer1Pokemon);
        }
        Fight::changeTurn();
    }


    auto Fight::useSpecialAbility() -> void {
        auto &creatureUsingAbility = *(player1Turn_ ? currentPlayer1Pokemon : currentPlayer2Pokemon);
        creatureUsingAbility.useSpecialAbility(*this);
        Fight::changeTurn();
    }

    auto Fight::changeTurn() -> void {
        player1Turn_ = !player1Turn_;
    }


    auto Fight::getPlayer1CreatureInfo() -> void {
        std::cout << currentPlayer1Pokemon->getName() << std::endl;
    }

    auto Fight::getPlayer2CreatureInfo() -> void {
        std::cout << currentPlayer2Pokemon->getName() << std::endl;
    }
}