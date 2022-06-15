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
        std::vector<std::unique_ptr<Creature>> player1Creatures_;
        std::vector<std::unique_ptr<Creature>> player2Creatures_;
        bool player1Turn_ = true;

    public:
        std::unique_ptr<Creature> currentPlayer1Pokemon;
        std::unique_ptr<Creature> currentPlayer2Pokemon;
        /**
         *
         * @param player1Creatures
         * @param player2Creatures
         */
        Fight(const std::vector<std::unique_ptr<Creature>> &player1Creatures,
              const std::vector<std::unique_ptr<Creature>> &player2Creatures);
        /**
         *
         * @param creatureAttackerIndex
         * @param creatureAttackedIndex
         */
        auto attack(unsigned int creatureAttackerIndex, unsigned int creatureAttackedIndex) -> void;
        /**
         *
         * @param creatureUsingAbilityIndex
         */
        auto useSpecialAbility(unsigned int creatureUsingAbilityIndex) -> void;
        /**
         *
         * @param player1Creatures
         */
        static auto getPlayer1CreatureInfo(std::vector<std::unique_ptr<Creature>> &player1Creatures) -> void;
        /**
         *
         * @param player2Creatures
         */
        static auto getPlayer2CreatureInfo(std::vector<std::unique_ptr<Creature>> &player2Creatures) -> void;
        /**
         *
         */
        auto changeTurn() -> void;
    };
}