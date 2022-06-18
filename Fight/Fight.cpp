#include <random>
#include <iostream>
#include "Fight.hpp"
#include "Game.hpp"
#include <chrono>
#include <thread>
#include <utility>
#include <windows.h>


namespace vasio {
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);

    Fight::Fight(std::shared_ptr<Game> game_ptr,
                 std::shared_ptr<Creature> currentPlayer1Creature,
                 std::shared_ptr<Creature> currentPlayer2Creature
    ) : game_ptr(std::move(game_ptr)), currentPlayer1Pokemon(std::move(currentPlayer1Creature)),
        currentPlayer2Pokemon(std::move(currentPlayer2Creature)) {}

    auto Fight::attack() -> void {
        if (player1Turn_) {
            std::cout << currentPlayer1Pokemon->getName() << " attacks " << currentPlayer2Pokemon->getName() << "\n\n";
            auto damageGiven = currentPlayer1Pokemon->attack(currentPlayer2Pokemon);
            if (damageGiven > 0) {
                SetConsoleTextAttribute(color, 2);
                std::cout << "Attack was successful!" << '\n';
                SetConsoleTextAttribute(color, 7);
                std::cout << currentPlayer2Pokemon->getName() << " took " << damageGiven << " damage" << "\n\n";
                SetConsoleTextAttribute(color, 2);
                currentPlayer1Pokemon->getShortStats();
                SetConsoleTextAttribute(color, 4);
                currentPlayer2Pokemon->getShortStats();
                SetConsoleTextAttribute(color, 7);
                if (currentPlayer2Pokemon->currentHealth_ <= 0) {
                    SetConsoleTextAttribute(color, 4);
                    std::cout << '\n' << currentPlayer2Pokemon->getName() << " fainted!\n\n";
                    SetConsoleTextAttribute(color, 7);
                    int expGot = currentPlayer2Pokemon->ExpNeededToEvolve_ / 4;
                    SetConsoleTextAttribute(color, 2);
                    std::cout << currentPlayer1Pokemon->getName() << " got " << expGot << " exp" << "\n\n";
                    currentPlayer1Pokemon->addExp(expGot);
                    SetConsoleTextAttribute(color, 7);
                }
            } else {
                std::cout << currentPlayer2Pokemon->getName() << " dodged the attack!\n";

                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        } else {
            std::cout << currentPlayer2Pokemon->getName() << " attacks " << currentPlayer1Pokemon->getName() << '\n';
            auto damageGiven = currentPlayer2Pokemon->attack(currentPlayer1Pokemon);
            if (damageGiven > 0) {
                SetConsoleTextAttribute(color, 4);
                std::cout << "Attack was successful" << '\n';
                SetConsoleTextAttribute(color, 7);
                std::cout << currentPlayer1Pokemon->getName() << " took " << damageGiven << " damage" << "\n\n";
                SetConsoleTextAttribute(color, 4);
                currentPlayer2Pokemon->getShortStats();
                SetConsoleTextAttribute(color, 2);
                currentPlayer1Pokemon->getShortStats();
                SetConsoleTextAttribute(color, 7);
                if (currentPlayer1Pokemon->currentHealth_ <= 0) {
                    std::cout << currentPlayer1Pokemon->getName() << " fainted!\n\n";
                    int expGot = currentPlayer1Pokemon->ExpNeededToEvolve_ / 5;
                    std::cout << currentPlayer2Pokemon->getName() << " got " << expGot << " exp" << "\n\n";
                    currentPlayer1Pokemon->addExp(expGot);
                }
            } else {
                std::cout << currentPlayer1Pokemon->getName() << " dodged the attack!" << '\n';

                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
        Fight::changeTurn();
    }


    auto Fight::useSpecialAbility() -> void {
        auto &creatureUsingAbility = *(player1Turn_ ? currentPlayer1Pokemon : currentPlayer2Pokemon);
        if (creatureUsingAbility.specialAbility_.numberOfUses_ !=
            creatureUsingAbility.specialAbility_.maxNumberOfUses_) {
            std::cout << creatureUsingAbility.getName() << " uses "
                      << creatureUsingAbility.specialAbility_.getNameOfAbility() << '\n';

            creatureUsingAbility.specialAbility_.applyAbility(*this);
            if (currentPlayer2Pokemon->currentHealth_ <= 0) {
                std::cout << currentPlayer2Pokemon->getName() << " fainted!\n\n";
                int expGot = currentPlayer2Pokemon->ExpNeededToEvolve_ / 4;
                std::cout << currentPlayer1Pokemon->getName() << " got " << expGot << " exp" << "\n\n";
                currentPlayer1Pokemon->addExp(expGot);
            }
            creatureUsingAbility.specialAbility_.numberOfUses_++;
            unsigned int max = creatureUsingAbility.specialAbility_.maxNumberOfUses_;
            unsigned int uses = creatureUsingAbility.specialAbility_.numberOfUses_;
            unsigned int usesLeft = max - uses;
            std::cout << usesLeft << " uses of this Special Ability left" << "\n\n";
        } else {
            std::cout << "No more uses left for this ability" << '\n';
        }
        Fight::changeTurn();
    }


    auto Fight::evolveCreature() -> void {
        if (player1Turn_) {
            auto &creatureTryingToEvolve = *(currentPlayer1Pokemon);
            std::cout << creatureTryingToEvolve.getName() << " tries to evolve!" << '\n';
            creatureTryingToEvolve.evolve();
        } else {
            auto &creatureTryingToEvolve = *(currentPlayer2Pokemon);
            std::cout << creatureTryingToEvolve.getName() << " tries to evolve!" << '\n';
            creatureTryingToEvolve.enemyEvolve();
        }
        Fight::changeTurn();
    }


    auto Fight::changeTurn() -> void {
        player1Turn_ = !player1Turn_;
    }

    auto Fight::switchCreature() -> void {
        std::vector<std::shared_ptr<Creature>> creaturesToSwitchTo = game_ptr->player1Creatures;
        SetConsoleTextAttribute(color, 2);
        game_ptr->showTeam(creaturesToSwitchTo);
        SetConsoleTextAttribute(color, 7);
        std::cout << "Choose a creature to switch to: " << '\n';
        std::cout << "Your current creature is: " << "\n";
        SetConsoleTextAttribute(color, 2);
        currentPlayer1Pokemon->getShortStats();
        SetConsoleTextAttribute(color, 7);
        int creatureToSwitchToIndex;
        std::cin >> creatureToSwitchToIndex;
        while (creatureToSwitchToIndex < 0 || creatureToSwitchToIndex >= creaturesToSwitchTo.size()) {
            std::cout << "Invalid input, try again: " << '\n';
            std::cin >> creatureToSwitchToIndex;
        }
        auto &creatureToSwitch = creaturesToSwitchTo[creatureToSwitchToIndex];
        if (player1Turn_) {
            std::cout << "You switch " << currentPlayer1Pokemon->getName() << " to " << creatureToSwitch->getName()
                      << '\n';
            currentPlayer1Pokemon = creatureToSwitch;
        }
        Fight::changeTurn();
    }

    auto Fight::enemySwitchCreature() -> void {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<unsigned int> dis(0, game_ptr->player2Creatures.size() - 1);

        bool enemyTeamStatus = checkIfEnemyTeamIsAlive();

        std::vector<std::shared_ptr<Creature>> enemyCreaturesToSwitchTo = game_ptr->player2Creatures;

        int creatureToSwitchToIndex = dis(gen);
        auto &creatureToSwitch = enemyCreaturesToSwitchTo[creatureToSwitchToIndex];

        if (!player1Turn_ && creatureToSwitch->currentHealth_ > 0 && enemyTeamStatus) {
            std::cout << "Enemy switches " << currentPlayer2Pokemon->getName() << " to " << creatureToSwitch->getName()
                      << '\n';
            currentPlayer2Pokemon = creatureToSwitch;
        } else if (enemyTeamStatus) {
            SetConsoleTextAttribute(color, 4);
            std::cout << "Enemy is fainted, switching to a random creature" << '\n';
            SetConsoleTextAttribute(color, 7);
            while (!isCreatureAlive(creatureToSwitch)) {
                int creatureToSwitchIndex = dis(gen);
                creatureToSwitch = enemyCreaturesToSwitchTo[creatureToSwitchIndex];
            }
            currentPlayer2Pokemon = creatureToSwitch;
        } else {
            checkIfEnemyTeamIsAlive();
        }
        Fight::changeTurn();
    }

    auto Fight::showPlayerSpecialAbility() const -> void {
        currentPlayer1Pokemon->specialAbility_.showSpecialAbility();
    }

    auto Fight::isCreatureAlive(const std::shared_ptr<Creature> &creature) -> bool {
        if (creature->currentHealth_ <= 0) {
            return false;
        } else {
            return true;
        }
    }

    auto Fight::checkIfPlayerTeamIsAlive() const -> bool {
        unsigned sizeOfTeam = game_ptr->player1Creatures.size();
        int counter = 0;
        for (auto &creature: game_ptr->player1Creatures) {
            if (!isCreatureAlive(creature)) {
                counter++;
            } else
                counter += 0;
        }
        if (counter == sizeOfTeam) {
            return false;
        } else {
            return true;
        }
    }

    auto Fight::checkIfEnemyTeamIsAlive() const -> bool {
        unsigned int sizeOfTeam = game_ptr->player2Creatures.size();
        int counter = 0;
        for (auto &creature: game_ptr->player2Creatures) {
            if (!isCreatureAlive(creature)) {
                counter++;
            } else {
                counter += 0;
            }
        }
        if (counter == sizeOfTeam) {
            return false;
        } else {
            return true;
        }
    }

    auto Fight::startFight() -> void {
        bool playerTeamStatus = checkIfPlayerTeamIsAlive();
        bool enemyTeamStatus = checkIfEnemyTeamIsAlive();
        player1Turn_ = true;
        SetConsoleTextAttribute(color, 10);
        std::cout << '\n' << "BATTLE BEGINS!" << "\n";
        std::cout << '\n' << "FIGHT TO THE DEATH OR DIE TRYING!" << "\n\n";
        SetConsoleTextAttribute(color, 7);
        while (playerTeamStatus && enemyTeamStatus) {
            if (player1Turn_) {
                playerTeamStatus = checkIfPlayerTeamIsAlive();
                if (currentPlayer1Pokemon->currentHealth_ <= 0) {
                    Fight::switchCreature();
                } else {
                    Fight::player1Turn();
                }
            } else {
                enemyTeamStatus = checkIfEnemyTeamIsAlive();
                if (currentPlayer2Pokemon->currentHealth_ <= 0) {
                    Fight::enemySwitchCreature();
                } else {
                    Fight::player2Turn();
                }
            }
        }
        if (playerTeamStatus && !enemyTeamStatus) {
            SetConsoleTextAttribute(color, 2);
            std::cout << '\n' << "You won!" << '\n';
            SetConsoleTextAttribute(color, 7);
            isWon = true;
        } else {
            SetConsoleTextAttribute(color, 4);
            std::cout << '\n' << "You lost! Game over." << '\n';
            SetConsoleTextAttribute(color, 7);
            isWon = false;
        }
    }

    auto Fight::player1Turn() -> void {
        std::string choice;

        SetConsoleTextAttribute(color, 5);
        std::cout << '\n' << "USER TURN! " << "\n\n";
        SetConsoleTextAttribute(color, 7);

        SetConsoleTextAttribute(color, 2);
        std::cout << '\n' << "Your current creature:  " << '\n';
        currentPlayer1Pokemon->getShortStats();
        SetConsoleTextAttribute(color, 4);
        std::cout << "Enemy creature: " << '\n';
        currentPlayer2Pokemon->getShortStats();
        SetConsoleTextAttribute(color, 7);

        std::cout << '\n' << "What would you like to do? " << "\n\n";

        SetConsoleTextAttribute(color, 1);
        std::cout << "1. Attack" << '\n';
        std::cout << "2. Use special ability" << '\n';
        std::cout << "3. Evolve" << '\n';
        std::cout << "4. Switch Creature" << '\n';
        SetConsoleTextAttribute(color, 2);
        std::cout << "5. Show Team" << '\n';
        SetConsoleTextAttribute(color, 4);
        std::cout << "6. Show Enemy Team" << '\n';
        SetConsoleTextAttribute(color, 1);
        std::cout << "7. Show Special Ability" << '\n';
        SetConsoleTextAttribute(color, 7);


        std::cout << "Your choice: " << '\n';
        std::cin >> choice;
        int intChoice = std::stoi(choice);
        switch (intChoice) {
            case 1:
                SetConsoleTextAttribute(color, 2);
                std::cout << "Attack" << '\n';
                SetConsoleTextAttribute(color, 7);
                Fight::attack();
                break;
            case 2:
                SetConsoleTextAttribute(color, 2);
                std::cout << "Special Ability" << '\n';
                SetConsoleTextAttribute(color, 7);
                Fight::useSpecialAbility();
                break;
            case 3:
                SetConsoleTextAttribute(color, 2);
                std::cout << "Evolve" << '\n';
                SetConsoleTextAttribute(color, 7);
                Fight::evolveCreature();
                break;
            case 4:
                SetConsoleTextAttribute(color, 2);
                std::cout << "Switch" << '\n';
                SetConsoleTextAttribute(color, 7);
                Fight::switchCreature();
                break;
            case 5:
                SetConsoleTextAttribute(color, 2);
                game_ptr->showTeam(game_ptr->player1Creatures);
                SetConsoleTextAttribute(color, 7);
                break;
            case 6:
                SetConsoleTextAttribute(color, 4);
                game_ptr->showTeam(game_ptr->player2Creatures);
                SetConsoleTextAttribute(color, 7);
                break;
            case 7:
                SetConsoleTextAttribute(color, 2);
                std::cout << "Special Ability" << '\n';
                SetConsoleTextAttribute(color, 7);
                Fight::showPlayerSpecialAbility();
                break;
            default:
                assert(false);
        }


    }


    auto Fight::player2Turn() -> void {

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 7);

        SetConsoleTextAttribute(color, 5);
        std::cout << '\n' << "ENEMY TURN!" << "\n\n";
        SetConsoleTextAttribute(color, 7);
        if (!isCreatureAlive(currentPlayer2Pokemon)) {
            Fight::enemySwitchCreature();
            Fight::changeTurn();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        switch (dis(gen)) {
            case 1:
                Fight::attack();
                break;
            case 2:
                Fight::attack();
                break;
            case 3:
                Fight::attack();
                break;
            case 4:
                Fight::useSpecialAbility();
                break;
            case 5:
                Fight::evolveCreature();
                break;
            case 6:
                Fight::enemySwitchCreature();
                break;
            case 7:
                Fight::enemySwitchCreature();
                break;
            default:
                assert(false);
        }
    }


}