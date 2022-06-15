//
// Created by theer on 04.06.2022.
//
#include <random>
#include <iostream>
#include "Fight.hpp"
#include "Game.hpp"


namespace vasio {
    Fight::Fight(std::shared_ptr<Creature> currentPlayer1Creature,
                 std::shared_ptr<Creature> currentPlayer2Creature
    ) :  currentPlayer1Pokemon(currentPlayer1Creature),
        currentPlayer2Pokemon(currentPlayer2Creature) {}


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

    auto Fight::getPlayerTeamInfo(const auto& playerCreatureChoices) -> void {
        for (const auto &creature: playerCreatureChoices) {
            std::cout << creature << '\n';
        }
    }


    auto Fight::startFight() -> void {
        /// TODO couty etc

    }

    auto Fight::player1Turn() -> void {


        std::cout << "Your turn" << '\n';

    }


// bot
    auto Fight::player2Turn() -> void {

    }


}