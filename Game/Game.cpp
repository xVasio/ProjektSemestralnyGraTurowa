//
// Created by theer on 14.06.2022.
//
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
            std::string choice;

            std::cout << "Choose your team!" << '\n';
            std::cout << "Type -h or --help for additional instructions!" << '\n';

            showTeam(creaturesInGame);
            std::cout << "You can choose 6 creatures" << '\n';

            while (counter != player1TeamSize) {
                std::cin >> choice;
                auto choiceInt = std::stoi(choice);
                if (choice == "-h" || choice == "--help") {
                    std::cout << "Manual: " << '\n';
                } else if (choiceInt <= creaturesInGame.size()) {
                    player1Creatures.push_back(creaturesInGame[choiceInt]);
                    std::cout << creaturesInGame[choiceInt]->Name_ << " added to your team!" << '\n';
                }
                counter++;
            }
        }
    auto Game::generateEnemyTeam() -> void {
        constexpr int player2TeamSize = 4;
        int counter = 0;
        while (counter != player2TeamSize) {
            auto randomCreature = std::rand() % creaturesInGame.size();
            if (std::find(player1Creatures.begin(), player1Creatures.end(), creaturesInGame[randomCreature]) ==
                player1Creatures.end()) {
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
}


