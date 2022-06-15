//
// Created by theer on 04.06.2022.
//
#pragma once

#include "Creature.hpp"
#include <vector>

namespace vasio {
    /**
     *
     */
    class Fight {
        bool player1Turn_ = true;

    public:
        std::unique_ptr<Creature> currentPlayer1Pokemon;
        std::unique_ptr<Creature> currentPlayer2Pokemon;

        /**
         *
         * @param player1Creatures
         * @param player2Creatures
         */
        Fight(std::unique_ptr<Creature> player1Creatures,
              std::unique_ptr<Creature> player2Creatures);

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

        /**
         *
         * @param player2Creatures
         */
        auto getPlayer2CreatureInfo() -> void;

        /**
         *
         */
        auto changeTurn() -> void;
    };
}