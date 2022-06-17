#include <iostream>
#include <vector>
#include "Creature.hpp"
#include "Game.hpp"
#include <memory>

auto main() -> int {
    // wywalić potem using namespace
//    using namespace vasio;
    using Creature = vasio::Creature;
    using Game = vasio::Game;



    std::vector<std::shared_ptr<Creature>> creatures;
    std::vector<std::shared_ptr<Creature>> creatures2;


    for (int i = 0; i < 15; i++) {
        creatures.push_back(Creature::createRandomCreature());
    }

    for (int i = 0; i < 15; i++) {
        creatures2.push_back(Creature::createRandomCreature());
    }

//    for (auto &creature: creatures) {
//        std::cout << *creature << '\n';
//    }
//
//    auto &creature = creatures[0];
//    auto &creature2 = creatures[1];
//
//    std::cout << '\n';
//    std::cout << *creature << '\n';
//    std::cout << *creature2 << '\n';
//
//    std::cout << creature->getEfficiency(creatures[1]) << '\n';
//    std::cout << creature2->getEfficiency(creatures[0]) << '\n';
//
//    float efficiency = creature->getEfficiency(creature2);
//    std::cout << "Efficiency: " << efficiency << '\n';
//
//    creature2->addExp(1100);
//    creature->getExp();
//    creature2->evolve();
//    std::cout << *creature2 << '\n';


    Game game(creatures);
//    game.chooseDifficulty();
//    game.letHumanPlayerChooseCreatures();
//    game.generateEnemyTeam();
//    game.showTeam(game.player1Creatures);
//    game.showTeam(game.player2Creatures);
//    game.createFight();
//    game.fights[0].startFight();
    Game::startGame(game);

    return 0;
}
