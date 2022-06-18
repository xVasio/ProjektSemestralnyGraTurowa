#include <random>
#include <fstream>
#include "Game.hpp"

HANDLE color2 = GetStdHandle(STD_OUTPUT_HANDLE);

namespace vasio {
    auto Game::chooseDifficulty() -> void {
        std::string choice;
        Game::difficulty = GameDifficulty::Undefined;
        SetConsoleTextAttribute(color2, 14);
        while (choice != "1" && choice != "2" && choice != "3") {
            std::cout << "Choose difficulty: " << '\n';
            std::cout << "1. Easy" << '\n';
            std::cout << "2. Medium" << '\n';
            std::cout << "3. Hard" << '\n';
            std::cout << "-h or --help for manual" << '\n';

            std::cout << "Your choice: " << '\n';
            std::cin >> choice;
            if (choice == "-h" || choice == "--help") {
                std::cout
                        << "Difficulty level affects number of rounds and number of enemies. For (Easy) it is 4 rounds, 4 enemies each. For (Medium) it is 5 rounds, 5 enemies each and for (Hard) it is 6 rounds, 6 enemies each "
                        << '\n';
            } else if (choice == "1") {
                difficulty = GameDifficulty::Easy;
            } else if (choice == "2") {
                difficulty = GameDifficulty::Medium;
            } else if (choice == "3") {
                difficulty = GameDifficulty::Hard;
            } else {
                std::cout << "Invalid choice" << '\n';
            }
            SetConsoleTextAttribute(color2, 7);
        }
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
                SetConsoleTextAttribute(color2, 14);
                std::cout
                        << "You won't be able to switch creatures to new ones after this prompt. You can't have to same creatures so choose wisely"
                        << '\n';
                SetConsoleTextAttribute(color2, 7);
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
        std::uniform_int_distribution<unsigned int> dis(0, creaturesInGame.size() - 1);
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
            std::cout << '\n' << i << ". " << *(teamCreatures[i]) << '\n';
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
        file.open("./save.txt");

        for (auto &creature: player1Creatures) {
            file << *creature << '\n';
        }
    }

    auto Game::controlPanel() -> void {
        std::string choice;
        SetConsoleTextAttribute(color2, 9);
        std::cout << "U won the fight! Do you want to start the next one or save and exit?"
                  << '\n';
        while (choice != "1" && choice != "2" && choice != "3") {
            std::cout << "1. Start next fight" << '\n';
            std::cout << "2. Save and exit" << '\n';
            std::cout << "Your choice: " << '\n';
            std::cin >> choice;
        }
        SetConsoleTextAttribute(color2, 7);
        auto choiceInt = std::stoi(choice);
        switch (choiceInt) {
            case 1:
                break;
            case 2:
                std::cout << "Saving... and... Exiting..." << '\n';
                saveGame();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                exit(0);
            default:
                assert(false);
        }
    }

    auto Game::welcome() -> void {
        std::string choice;
        SetConsoleTextAttribute(color2, 14);
        while (choice != "1" && choice != "2") {
            std::cout << "Welcome to the game! " << '\n';

            std::cout << "1. Start game!" << '\n';
            std::cout << "2. Exit" << '\n';
            std::cout << "-h or --help for game instruction " << '\n';
            std::cout << "Your choice: " << '\n';
            std::cin >> choice;
            if (choice == "-h" || choice == "--help") {
                std::cout << "THIS IS BASIC INSTRUCTION FOR THE WHOLE GAME" << '\n';
                std::cout
                        << "Each option is given from the keyboard. Command -h or --help is available in some places to display more detailed instructions."
                        << '\n';
            }
        }
        SetConsoleTextAttribute(color2, 7);
        auto choiceInt = std::stoi(choice);
        switch (choiceInt) {
            case 1:
                break;
            case 2:
                SetConsoleTextAttribute(color2, 12);
                std::cout << "Exiting..." << '\n';
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                exit(0);
            default:
                assert(false);
        }
    }

    auto Game::createFight() -> void {
        fights.emplace_back(std::make_shared<Game>(*this), player1Creatures[0], player2Creatures[0]);
    }

    auto Game::gameControl(Game &game) -> void {
        vasio::Game::welcome();
        game.chooseDifficulty();
        SetConsoleTextAttribute(color2, 10);
        game.letHumanPlayerChooseCreatures();
        SetConsoleTextAttribute(color2, 2);
        vasio::Game::showTeam(game.player1Creatures);
        SetConsoleTextAttribute(color2, 7);
        switch (game.difficulty) {
            case GameDifficulty::Easy:
                game.generateEnemyTeam(4);
                SetConsoleTextAttribute(color2, 4);
                vasio::Game::showTeam(game.player2Creatures);
                SetConsoleTextAttribute(color2, 7);
                game.createFight();
                std::cout << "----------------------------------------------------" << '\n';
                std::cout <<  "Your next adversary is Enemy 1" << '\n';
                std::cout << "----------------------------------------------------" << '\n';
                game.fights[0].startFight();
                for (int i = 0; i < 4; i++) {
                    if (game.fights[i].isWon) {
                        game.controlPanel();
                        game.resetHpOfBothTeams();
                        game.generateEnemyTeam(4);
                        game.createFight();
                        std::cout << "----------------------------------------------------" << '\n';
                        std::cout << "Your next adversary is Enemy " << i + 2 << '\n';
                        std::cout << "----------------------------------------------------" << '\n';
                        game.fights[i + 1].startFight();
                    } else {
                        SetConsoleTextAttribute(color2, 4);
                        std::cout << "GAME OVER" << '\n';
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        SetConsoleTextAttribute(color2, 7);
                        std::cout << "Exiting..." << '\n';
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        exit(0);
                    }
                }
                SetConsoleTextAttribute(color2, 14);
                std::cout << "You won the game! GG!" << '\n';
                SetConsoleTextAttribute(color2, 7);
                break;
            case GameDifficulty::Medium:
                game.generateEnemyTeam(5);
                SetConsoleTextAttribute(color2, 4);
                vasio::Game::showTeam(game.player2Creatures);
                SetConsoleTextAttribute(color2, 7);
                game.createFight();
                std::cout << "----------------------------------------------------" << '\n';
                std::cout <<  "Your next adversary is Enemy 1" << '\n';
                std::cout << "----------------------------------------------------" << '\n';
                game.fights[0].startFight();
                for (int i = 0; i < 5; i++) {
                    if (game.fights[i].isWon) {
                        game.controlPanel();
                        game.resetHpOfBothTeams();
                        game.generateEnemyTeam(5);
                        game.createFight();
                        std::cout << "----------------------------------------------------" << '\n';
                        std::cout << "Your next adversary is Enemy " << i + 2 << '\n';
                        std::cout << "----------------------------------------------------" << '\n';
                        game.fights[i + 1].startFight();
                    } else {
                        SetConsoleTextAttribute(color2, 4);
                        std::cout << "GAME OVER" << '\n';
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        SetConsoleTextAttribute(color2, 7);
                        std::cout << "Exiting..." << '\n';
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        exit(0);
                    }
                }
                SetConsoleTextAttribute(color2, 14);
                std::cout << "You won the game! GG!" << '\n';
                SetConsoleTextAttribute(color2, 7);
                break;
            case GameDifficulty::Hard:
                game.generateEnemyTeam(6);
                SetConsoleTextAttribute(color2, 4);
                vasio::Game::showTeam(game.player2Creatures);
                SetConsoleTextAttribute(color2, 7);
                game.createFight();
                std::cout << "----------------------------------------------------" << '\n';
                std::cout <<  "Your next adversary is Enemy 1" << '\n';
                std::cout << "----------------------------------------------------" << '\n';
                game.fights[0].startFight();
                for (int i = 0; i < 6; i++) {
                    if (game.fights[i].isWon) {
                        game.controlPanel();
                        game.resetHpOfBothTeams();
                        game.generateEnemyTeam(6);
                        game.createFight();
                        std::cout << "----------------------------------------------------" << '\n';
                        std::cout << "Your next adversary is Enemy " << i + 2 << '\n';
                        std::cout << "----------------------------------------------------" << '\n';
                        game.fights[i + 1].startFight();
                    } else {
                        SetConsoleTextAttribute(color2, 4);
                        std::cout << "GAME OVER" << '\n';
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        SetConsoleTextAttribute(color2, 7);
                        std::cout << "Exiting..." << '\n';
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        exit(0);
                    }
                }
                SetConsoleTextAttribute(color2, 14);
                std::cout << "You won the game! GG!" << '\n';
                SetConsoleTextAttribute(color2, 7);
                break;
            case GameDifficulty::Undefined:
                assert(false);
                break;
        }
    }
}
