#pragma once

#include "Creature.hpp"
#include <vector>


namespace vasio {


    class Game;

    enum class GameDifficulty;


    /**
     * Class representing single fight between players
     */
    class Fight {
    public:
        bool player1Turn_ = true;
        std::shared_ptr<Game> game_ptr;
        std::shared_ptr<Creature> currentPlayer1Pokemon;
        std::shared_ptr<Creature> currentPlayer2Pokemon;
        bool isWon;

        /**
         * Constructor for Fight class
         * @param player1Creatures - vector of creatures of player 1
         * @param player2Creatures - vector of creatures of player 2 (AI)
         */
        Fight(std::shared_ptr<Game> game_ptr, std::shared_ptr<Creature> currentPlayer1Pokemon,
              std::shared_ptr<Creature> currentPlayer2Pokemon);

        /**
         * Function that implements attack move during fight
         * @param creatureAttackerIndex - index of creature that attacks
         * @param creatureAttackedIndex - index of creature that is attacked
         */
        auto attack() -> void;

        /**
         * Function that implements special ability move during fight
         */
        auto useSpecialAbility() -> void;

        /**
         * Function that implements evolution move during fight
         */
        auto evolveCreature() -> void;

        /**
         * Function that implements switch creature move during fight
         */
        auto switchCreature() -> void;

        /**
         * Function that implements switch creature move during fight for player 2 (AI)
         */
        auto enemySwitchCreature() -> void;

        /**
         * Function that implements displaying special ability attributes during fight
         */
        auto showPlayerSpecialAbility() const -> void;

        /**
         * Function that implements changing turn during fight
         */
        auto changeTurn() -> void;

        /**
         * Function checing if all creatures of player 1 are alive
         * @return true if all creatures of player 1 are alive, false otherwise
         */
        auto checkIfPlayerTeamIsAlive() const -> bool;

        /**
         * Function checing if all creatures of player 2 (AI) are alive
         * @return true if all creatures of player 2 (AI) are alive, false otherwise
         */
        auto checkIfEnemyTeamIsAlive() const -> bool;


        /**
         * Static function that implements checking if given creature is alive
         * @param creature - creature to check if it is alive
         * @return true if creature is alive, false otherwise
         */
        static auto isCreatureAlive(const std::shared_ptr<Creature> &creature) -> bool;

        /**
         * Function that implements player 1 turn mechanics
         */
        auto player1Turn() -> void;

        /**
         * Function that implements player 2 (AI) turn mechanics
         */
        auto player2Turn() -> void;

        /**
         * Function that implements beginning of fight, displaying creatures of both players and managing turns
         */
        auto startFight() -> void;
    };
}