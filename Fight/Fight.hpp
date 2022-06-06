//
// Created by theer on 04.06.2022.
//
#pragma once

#include "../Creature/Creature.hpp"
#include <vector>
namespace vasio {
    class Fight {
        std::vector<std::unique_ptr<Creature>> player1Creatures_;
        std::vector<std::unique_ptr<Creature>> player2Creatures_;
        bool player1Turn_ = true;

    public:
        Fight(const std::vector<std::unique_ptr<Creature>> &player1Creatures,
              const std::vector<std::unique_ptr<Creature>> &player2Creatures);

        auto attack(unsigned int creatureAttackerIndex, unsigned int creatureAttackedIndex) -> void;

        /// Funkcja zwracająca imiona pokemonów dzięki czemu będziemy znali ich indeksy w wektorze potrzebne do attack
        // auto getPlayer1CreatureInfo() -> std::vector<NAME>

        auto changeTurn() -> void;


    };

}