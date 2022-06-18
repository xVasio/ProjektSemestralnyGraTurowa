#pragma once

#include "Creature.hpp"
#include <vector>


namespace vasio {


    class Game;

    enum class GameDifficulty;


    /**
     *
     */

    class Fight {
    public:
        bool player1Turn_ = true;
        std::shared_ptr<Game> game_ptr;
        std::shared_ptr<Creature> currentPlayer1Pokemon;
        std::shared_ptr<Creature> currentPlayer2Pokemon;
        bool isWon;

        /**
         *
         * @param player1Creatures
         * @param player2Creatures
         */
        Fight(std::shared_ptr<Game> game_ptr, std::shared_ptr<Creature> currentPlayer1Pokemon, std::shared_ptr<Creature> currentPlayer2Pokemon);

        /**
         *
         * @param creatureAttackerIndex
         * @param creatureAttackedIndex
         */
        auto attack() -> void;

        /**
         *
         * @param creatureUsingAbilityIndex
         */
        auto useSpecialAbility() -> void;


        /**
         *
         * @param player1Creatures
         */

        auto evolveCreature() -> void;

        auto switchCreature() -> void;

        auto showPlayerSpecialAbility() const -> void;

        auto enemySwitchCreature() -> void;

        /**
         *
         */
        auto changeTurn() -> void;

        auto checkIfPlayerTeamIsAlive() const -> bool;

        auto checkIfEnemyTeamIsAlive() const -> bool;

        auto player1Turn() -> void;

        auto player2Turn() -> void;

        auto startFight() -> void;

        static auto isCreatureAlive(const std::shared_ptr<Creature> &creature) -> bool;

    };
}