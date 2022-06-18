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

    /**
     * enum class representing difficulty of game
     */
    enum class GameDifficulty {
        Undefined,
        Easy,
        Medium,
        Hard
    };

    /**
     * Class representing whole game and fights in
     */
    class Game {

    public:
        std::vector<Fight> fights;
        std::vector<std::shared_ptr<Creature>> creaturesInGame;
        std::vector<std::shared_ptr<Creature>> player1Creatures;
        std::vector<std::shared_ptr<Creature>> player2Creatures;
        GameDifficulty difficulty;

        /**
         * Constructor for Game class
         * @param creaturesInGame - vector of all creatures in game
         * @param player1Creatures - vector of creatures of player 1
         * @param player2Creatures - vector of creatures of player 2 (AI)
         * @param difficulty - difficulty of game
         */
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

        auto createFight() -> void;

        static auto gameControl(Game &game) -> void;

    };
}
