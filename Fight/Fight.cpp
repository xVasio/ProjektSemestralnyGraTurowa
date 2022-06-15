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
            std:: cout << currentPlayer1Pokemon->getName() << " attacks " << currentPlayer2Pokemon->getName() << '\n';
            auto damageGiven = currentPlayer1Pokemon->attack(currentPlayer2Pokemon);
            if(damageGiven > 0) {
                std::cout << " Attack was successful" << '\n';
                std::cout << " " << currentPlayer2Pokemon->getName() << " took " << damageGiven << " damage" << '\n';
            } else {
                std::cout << currentPlayer2Pokemon->getName() << " doged the attack!\n";
            }
        } else {
            std:: cout << currentPlayer2Pokemon->getName() << "attacks " << currentPlayer1Pokemon->getName() << '\n';
            auto damageGiven = currentPlayer2Pokemon->attack(currentPlayer1Pokemon);
            if(damageGiven > 0) {
                std::cout << " Attack was successful" << '\n';
                std::cout << " " << currentPlayer1Pokemon->getName() << " took " << damageGiven << " damage" << '\n';
            } else {
                std::cout << currentPlayer1Pokemon->getName() << " doged the attack!" << '\n';
            }
        }
        Fight::changeTurn();
    }


    auto Fight::useSpecialAbility() -> void {
        auto &creatureUsingAbility = *(player1Turn_ ? currentPlayer1Pokemon : currentPlayer2Pokemon);
        std::cout << creatureUsingAbility.getName() << " uses " << creatureUsingAbility.specialAbility_.getNameOfAbility() << '\n';
        creatureUsingAbility.useSpecialAbility(*this);
        Fight::changeTurn();
    }

    auto Fight::evolveCreature() -> void {
        auto &creatureTryingToEvolve = *(player1Turn_ ? currentPlayer1Pokemon : currentPlayer2Pokemon);
        std::cout << creatureTryingToEvolve.getName() << " tries to evolve!" << '\n';
        creatureTryingToEvolve.evolve();
    }

    auto Fight::changeTurn() -> void {
        player1Turn_ = !player1Turn_;
    }

    auto Fight::switchCreature() -> void {

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
        player1Turn_ = true;
        std::cout << "Fight to the death or die trying! << \n";
        while (currentPlayer1Pokemon->getCurrentHealth() > 0 && currentPlayer2Pokemon->getCurrentHealth() > 0) {
            if (player1Turn_) {
                Fight::player1Turn();
            } else {
                Fight::player2Turn();
            }
        }
    }

    auto Fight::player1Turn() -> void {
        std::string choice;

        std::cout << "Your turn: " << '\n';

        std::cout << "1. Attack" << '\n';
        std::cout << "2. Use special ability" << '\n';
        std::cout << "3. Evolve" << '\n';
        std::cout << "4. Switch creature" << '\n';


        std::cout << "Your choice: ";
        std::cin >> choice;
        int intChoice = std::stoi(choice);
        switch(intChoice) {
            case 1:
                Fight::attack();
                break;
            case 2:
                Fight::useSpecialAbility();
                break;
            case 3:
                Fight::evolveCreature();
                break;
            case 4:
                Fight::switchCreature();
                break;
        }


    }


// bot
    auto Fight::player2Turn() -> void {
    }




}