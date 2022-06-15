//
// Created by theer on 04.06.2022.
//
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
        bool player1Turn_ = true;

    public:
        std::shared_ptr<Creature> currentPlayer1Pokemon;
        std::shared_ptr<Creature> currentPlayer2Pokemon;

        /**
         *
         * @param player1Creatures
         * @param player2Creatures
         */
        Fight(
                std::shared_ptr<Creature> currentPlayer1Creature,
                std::shared_ptr<Creature> currentPlayer2Creature
        );

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
        auto getPlayer1CreatureInfo() -> void;

        auto getPlayerTeamInfo(const auto &playerChoices) -> void;

        /**
         *
         * @param player2Creatures
         */
        auto getPlayer2CreatureInfo() -> void;

        /**
         *
         */
        auto changeTurn() -> void;

        auto player1Turn() -> void;

        auto player2Turn() -> void;

        auto startFight() -> void;
    };
}