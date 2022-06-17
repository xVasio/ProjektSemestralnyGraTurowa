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
    for (int i = 0; i < 30; i++) {
        creatures.push_back(Creature::createRandomCreature());
    }

    Game game(creatures);
    Game::gameControl(game);

    return 0;
}
