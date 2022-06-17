//
// Created by theer on 14.06.2022.
//

#pragma once

#include <utility>
#include "Fight.hpp"
#include <iostream>
#include <windows.h>



/// Dificulty of the game
/// Start, load, exit
/// Generate creatures and let the player choose 6
namespace vasio {
    using Fight = vasio::Fight;
    using Creature = vasio::Creature;

    enum class GameDifficulty {
        Undefined,
        Easy,
        Medium,
        Hard
    };

    auto enumGameDifficultyToString(GameDifficulty difficulty) -> std::string;

    class Game {

    public:
        std::vector<Fight> fights;
        std::vector<std::shared_ptr<Creature>> creaturesInGame;
        std::vector<std::shared_ptr<Creature>> player1Creatures;
        std::vector<std::shared_ptr<Creature>> player2Creatures;
        GameDifficulty difficulty;

        Game(std::vector<std::shared_ptr<Creature>> creaturesInGame) : creaturesInGame(creaturesInGame) {
            fights = {}, player1Creatures = {}, player2Creatures = {}, difficulty = GameDifficulty::Undefined;
        }


        auto showTeam(const std::vector<std::shared_ptr<Creature>> &teamCreatures) -> void;


        auto letHumanPlayerChooseCreatures() -> void;

        auto resetHp(std::vector<std::shared_ptr<Creature>> &creaturesToReset) -> void;

        auto resetHpOfBothTeams() -> void;

        static auto createFightsIfPreviousIsWon(Game &game) -> void;

        auto controlPanel() -> void;

        auto generateEnemyTeam() -> void;

        auto chooseDifficulty() -> void;

        // per referencja zrobic eluwa
        auto createFight() -> void {
            fights.push_back(Fight(std::make_shared<Game>(*this), player1Creatures[0], player2Creatures[0]));
        }

        static auto startGame(Game &game) -> void {
            game.chooseDifficulty();
            game.letHumanPlayerChooseCreatures();
            game.showTeam(game.player1Creatures);
            game.generateEnemyTeam();
            game.showTeam(game.player2Creatures);
            createFightsIfPreviousIsWon(game);
            }
        };
    }

