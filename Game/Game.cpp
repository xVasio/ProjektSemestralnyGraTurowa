//
// Created by theer on 14.06.2022.
//
#include <random>
#include <fstream>
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
                    if (std::find(player1Creatures.begin(), player1Creatures.end(), creaturesInGame[choiceInt]) ==
                        player1Creatures.end()) {
                        std::cout << creaturesInGame[choiceInt]->Name_ << " added to your team!" << '\n';
                        player1Creatures.push_back(creaturesInGame[choiceInt]);
                        counter++;
                    } else {
                        std::cout << "This creature is already in your team! Choose another!" << '\n';
                    }
                } else {
                    std::cout << "Invalid choice" << '\n';
                }
            }
        }
    }

    auto Game::generateEnemyTeam(int teamSize) -> void {
        player2Creatures.clear();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, creaturesInGame.size() - 1);
        int player2TeamSize = teamSize;
        int counter = 0;
        while (counter != player2TeamSize) {
            auto randomCreature = dis(gen);
            if (std::find(player1Creatures.begin(), player1Creatures.end(), creaturesInGame[randomCreature]) ==
                player1Creatures.end() && std::find(player2Creatures.begin(), player2Creatures.end(),
                                                    creaturesInGame[randomCreature]) == player2Creatures.end()) {
                if (!creaturesInGame[randomCreature]->isEnemy_) {
                    creaturesInGame[randomCreature]->Name_ = "Enemy " + creaturesInGame[randomCreature]->getName();
                    player2Creatures.push_back(creaturesInGame[randomCreature]);
                    creaturesInGame[randomCreature]->isEnemy_ = true;
                    counter++;
                } else {
                    player2Creatures.push_back(creaturesInGame[randomCreature]);
                    counter++;
                }
            }

        }
    }

    auto Game::showTeam(const std::vector<std::shared_ptr<Creature>> &teamCreatures) -> void {
        std::cout << "Creatures:" << '\n';
        for (int i = 0; i < teamCreatures.size(); i++) {
            std::cout << i << ". " << *(teamCreatures[i]) << '\n';
        }
    }

    auto Game::resetHpAndSAUses(std::vector<std::shared_ptr<Creature>> &creaturesToReset) -> void {
        for (auto &creature: creaturesToReset) {
            creature->currentHealth_ = creature->health_;
            creature->specialAbility_.numberOfUses_ = 0;
        }
    }

    auto Game::resetHpOfBothTeams() -> void {
        resetHpAndSAUses(player1Creatures);
        resetHpAndSAUses(player2Creatures);
    }

    auto Game::saveGame() -> void {
        std::ofstream file;
        file.open("save.txt");

        for (auto &creature: player1Creatures) {
            file << *creature << '\n';
        }
    }
}
