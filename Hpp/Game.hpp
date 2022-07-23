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
     *
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

        /**
         * Static function that displays given team
         * @param teamCreatures - vector of creatures to display
         */
        auto static showTeam(const std::vector<std::shared_ptr<Creature>> &teamCreatures) -> void;

        /**
         * Function that allows player to choose his team
         */
        auto letHumanPlayerChooseCreatures() -> void;

        /**
         * Function that resets currentHealth and Special Ability uses for given vector of creatures
         * @param creaturesToReset - vector of creatures to reset
         */
        static auto resetHpAndSAUses(std::vector<std::shared_ptr<Creature>> &creaturesToReset) -> void;

        /**
         * Function that resets currentHealth and Special Ability uses for player 1 team and player 2 team
         */
        auto resetHpOfBothTeams() -> void;

        /**
         * Function that saves game progress to text file
         */
        auto saveGame() -> void;

        /**
         * Function that enables player to start game
         */
        auto static welcome() -> void;

        /**
         * Function that enables player to continue game or exit after winning fight
         */
        auto controlPanel() -> void;

        /**
         * Function that generates enemy team of given size
         * @param TeamSize - size of enemy team to be generated
         */
        auto generateEnemyTeam(int TeamSize) -> void;

        /**
         * Function that enables player to choose difficulty of game
         */
        auto chooseDifficulty() -> void;

        /**
         * Function that creates single fight between two teams and puts it into vector of fights
         */
        auto createFight() -> void;

        /**
         * Function that manages game, it contains main loop of game, choosing difficulty, creating fights, and ending game
         * @param game - reference to game object
         */
        static auto gameControl(Game &game) -> void;
    };
}
