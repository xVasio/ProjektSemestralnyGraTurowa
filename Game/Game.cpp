//
// Created by theer on 14.06.2022.
//
#include <random>
#include <chrono>
#include <thread>
#include "Game.hpp"

namespace vasio {
    auto enumGameDifficultyToString(vasio::GameDifficulty difficulty) -> std::string {
        switch (difficulty) {
            case GameDifficulty::Undefined:
                return "Undefined";
            case GameDifficulty::Easy:
                return "Easy";
            case GameDifficulty::Medium:
                return "Medium";
            case GameDifficulty::Hard:
                return "Hard";
        }
    }

    auto Game::chooseDifficulty() -> void {
        std::string choice;
        Game::difficulty = GameDifficulty::Undefined;
        do {
            std::cout << "Choose difficulty: " << '\n';
            std::cout << "1. Easy" << '\n';
            std::cout << "2. Medium" << '\n';
            std::cout << "3. Hard" << '\n';
            std::cout << "-h or -help for manual" << '\n';

            std::cout << "Your choice: " << '\n';
            std::cin >> choice;
            if (choice == "-h" || choice == "-help") {
                std::cout << "Manual" << '\n';
            } else if (choice == "1") {
                difficulty = GameDifficulty::Easy;
            } else if (choice == "2") {
                difficulty = GameDifficulty::Medium;
            } else if (choice == "3") {
                difficulty = GameDifficulty::Hard;
            } else {
                std::cout << "Invalid choice" << '\n';
            }
        } while (choice != "1" && choice != "2" && choice != "3");
    }

    auto Game::letHumanPlayerChooseCreatures() -> void {
        constexpr int player1TeamSize = 6;
        int counter = 0;
        int spaceLeft;
        std::string choice;

        std::cout << "Choose your team!" << '\n';
        std::cout << "Type -h or --help for additional instructions!" << '\n';

        showTeam(creaturesInGame);
        while (counter != player1TeamSize) {
            spaceLeft = player1TeamSize - counter;
            std::cout << "You can choose " << spaceLeft << " creatures" << '\n';
            std::cin >> choice;

            if (choice == "-h" || choice == "--help") {
                std::cout << "Manual: " << '\n';

            } else {
                unsigned int choiceInt = std::stoi(choice);
                if (choiceInt < creaturesInGame.size()) {
                    player1Creatures.push_back(creaturesInGame[choiceInt]);
                    std::cout << creaturesInGame[choiceInt]->Name_ << " added to your team!" << '\n';
                    counter++;
                } else {
                    std::cout << "Invalid choice" << '\n';
                }
            }
        }
    }

    auto Game::generateEnemyTeam() -> void {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, creaturesInGame.size() - 1);
        constexpr int player2TeamSize = 4;
        int counter = 0;
        while (counter != player2TeamSize) {
            auto randomCreature = dis(gen);
            if (std::find(player1Creatures.begin(), player1Creatures.end(), creaturesInGame[randomCreature]) ==
                player1Creatures.end()) {
                creaturesInGame[randomCreature]->Name_ = "Enemy " + creaturesInGame[randomCreature]->getName();
                player2Creatures.push_back(creaturesInGame[randomCreature]);
                counter++;
            }

        }
    }

    auto Game::showTeam(const std::vector<std::shared_ptr<Creature>> &teamCreatures) -> void {
        std::cout << "Creatures:" << '\n';
        for (int i = 0; i < teamCreatures.size(); i++) {
            std::cout << i << ". " << *(teamCreatures[i]) << '\n';
        }
    }

    auto Game::resetHp(std::vector<std::shared_ptr<Creature>> &creaturesToReset) -> void {
        for (auto &creature: creaturesToReset) {
            creature->currentHealth_ = creature->health_;
        }
    }

    auto Game::resetHpOfBothTeams() -> void {
        resetHp(player1Creatures);
        resetHp(player2Creatures);
    }

    auto Game::createFightsIfPreviousIsWon(Game &game) -> void {
        switch (game.difficulty) {
            case GameDifficulty::Easy:
                game.createFight();
                game.fights[0].startFight();
                for (int i = 0; i < 1; i++) {
                    if (game.fights[i].isWon) {
                        game.controlPanel();
                        game.resetHpOfBothTeams();
                        game.createFight();
                        game.fights[i + 1].startFight();
                    } else {
                        std::cout << "You lost! Start again!" << '\n';
                    }
                }
                break;
            case GameDifficulty::Medium:
                game.createFight();
                game.fights[0].startFight();
                game.resetHpOfBothTeams();
                game.createFight();
                game.fights[1].startFight();
                game.resetHpOfBothTeams();
                break;
            case GameDifficulty::Hard:
                game.createFight();
                game.fights[0].startFight();
                game.resetHpOfBothTeams();
                game.createFight();
                game.fights[1].startFight();
                game.resetHpOfBothTeams();
                break;
        }
    }

    auto Game::controlPanel() -> void {
        std::string choice;
        do {
            std::cout << "U won the fight! Do you want to start the next one or save and exit?" << '\n';
            std::cout << "1. Start next fight" << '\n';
            std::cout << "2. Save and exit" << '\n';
            std::cout << "Your choice: " << '\n';
            std::cin >> choice;
        } while (choice != "1" && choice != "2" && choice != "3");
        auto choiceInt = std::stoi(choice);
        switch (choiceInt) {
            case 1:
                resetHpOfBothTeams();
                createFightsIfPreviousIsWon(*this);
            case 2:
                std::cout << "Exiting... Saving un unavailable" << '\n';
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                exit(0);
        }
    }
}