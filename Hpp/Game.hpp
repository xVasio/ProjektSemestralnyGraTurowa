#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
#pragma once

#include <utility>
#include "Fight.hpp"
#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>
#include <cassert>

namespace vasio {
    using Fight = vasio::Fight;
    using Creature = vasio::Creature;

    enum class GameDifficulty {
        Undefined,
        Easy,
        Medium,
        Hard
    };

    class Game {

    public:
        std::vector<Fight> fights;
        std::vector<std::shared_ptr<Creature>> creaturesInGame;
        std::vector<std::shared_ptr<Creature>> player1Creatures;
        std::vector<std::shared_ptr<Creature>> player2Creatures;
        GameDifficulty difficulty;

        Game(std::vector<std::shared_ptr<Creature>> creaturesInGame) : creaturesInGame(std::move(creaturesInGame)) {
            fights = {}, player1Creatures = {}, player2Creatures = {}, difficulty = GameDifficulty::Undefined;
        }


        auto static showTeam(const std::vector<std::shared_ptr<Creature>> &teamCreatures) -> void;

        auto letHumanPlayerChooseCreatures() -> void;

        static auto resetHpAndSAUses(std::vector<std::shared_ptr<Creature>> &creaturesToReset) -> void;

        auto resetHpOfBothTeams() -> void;

        auto saveGame() -> void;

        auto static welcome() -> void;

        auto controlPanel() -> void;

        auto generateEnemyTeam(int TeamSize) -> void;

        auto chooseDifficulty() -> void;

        auto createFight() -> void {
            fights.emplace_back(std::make_shared<Game>(*this), player1Creatures[0], player2Creatures[0]);
        }

        static auto gameControl(Game &game) -> void {
            vasio::Game::welcome();
            game.chooseDifficulty();
            game.letHumanPlayerChooseCreatures();
            vasio::Game::showTeam(game.player1Creatures);
            game.generateEnemyTeam(4);
            vasio::Game::showTeam(game.player2Creatures);
            switch (game.difficulty) {
                case GameDifficulty::Easy:
                    game.createFight();
                    std::cout << '\n' << "Your next adversary is Enemy 1" << '\n';
                    game.fights[0].startFight();
                    for (int i = 0; i < 2; i++) {
                        if (game.fights[i].isWon) {
                            game.controlPanel();
                            game.resetHpOfBothTeams();
                            game.generateEnemyTeam(4);
                            game.createFight();
                            std::cout << "Your next adversary is Enemy " << i + 2 << '\n';
                            game.fights[i + 1].startFight();
                        } else {
                            std::cout << "You lost! Start again!" << '\n';
                            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                            std::cout << "Exiting..." << '\n';
                            std::this_thread::sleep_for(std::chrono::milliseconds(500));
                            exit(0);

                        }
                        std::cout << "You won the game! GG!" << '\n';
                    }
                    break;
                case GameDifficulty::Medium:
                    game.createFight();
                    std::cout << '\n' << "Your next adversary is Enemy 1" << '\n';
                    game.fights[0].startFight();
                    for (int i = 0; i < 6; i++) {
                        if (game.fights[i].isWon) {
                            std::string choice;
                            do {
                                std::cout << "U won the fight! Do you want to start the next one or save and exit?"
                                          << '\n';
                                std::cout << "1. Start next fight" << '\n';
                                std::cout << "2. Save and exit" << '\n';
                                std::cout << "Your choice: " << '\n';
                                std::cin >> choice;
                            } while (choice != "1" && choice != "2" && choice != "3");
                            auto choiceInt = std::stoi(choice);
                            switch (choiceInt) {
                                case 1:
                                    break;
                                case 2:
                                    std::cout << "Saving... and... Exiting..." << '\n';
                                    game.saveGame();
                                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                                    exit(0);
                                default:
                                    std::cout << "Invalid choice!" << '\n';
                                    break;
                            }
                            game.resetHpOfBothTeams();
                            game.generateEnemyTeam(5);
                            game.createFight();
                            game.fights[i + 1].startFight();
                        } else {
                            std::cout << "You lost! Start again!" << '\n';
                            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                            std::cout << "Exiting..." << '\n';
                            std::this_thread::sleep_for(std::chrono::milliseconds(500));
                            exit(0);

                        }
                        std::cout << "You won the game! GG!" << '\n';
                    }
                    break;
                case GameDifficulty::Hard:
                    game.createFight();
                    std::cout << '\n' << "Your next adversary is Enemy 1" << '\n';
                    game.fights[0].startFight();
                    for (int i = 0; i < 7; i++) {
                        if (game.fights[i].isWon) {
                            std::string choice;
                            do {
                                std::cout << "U won the fight! Do you want to start the next one or save and exit?"
                                          << '\n';
                                std::cout << "1. Start next fight" << '\n';
                                std::cout << "2. Save and exit" << '\n';
                                std::cout << "Your choice: " << '\n';
                                std::cin >> choice;
                            } while (choice != "1" && choice != "2" && choice != "3");
                            auto choiceInt = std::stoi(choice);
                            switch (choiceInt) {
                                case 1:
                                    break;
                                case 2:
                                    std::cout << "Saving... and... Exiting..." << '\n';
                                    game.saveGame();
                                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                                    exit(0);
                                default:
                                    std::cout << "Invalid choice!" << '\n';
                                    break;
                            }
                            game.resetHpOfBothTeams();
                            game.generateEnemyTeam(6);
                            game.createFight();
                            game.fights[i + 1].startFight();
                        } else {
                            std::cout << "You lost! Start again!" << '\n';
                            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                            std::cout << "Exiting..." << '\n';
                            std::this_thread::sleep_for(std::chrono::milliseconds(500));
                            exit(0);

                        }
                        std::cout << "You won the game! GG!" << '\n';
                    }
                    break;
                case GameDifficulty::Undefined:
                    assert(false);
                    break;
            }
        }
    };
}
