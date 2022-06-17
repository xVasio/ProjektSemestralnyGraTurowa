#include <iostream>
#include <vector>
#include "Creature.hpp"
#include "Game.hpp"
#include <memory>

auto main() -> int {


    std::vector<std::shared_ptr<vasio::Creature>> creatures;
    std::vector<std::shared_ptr<vasio::Creature>> creatures2;
    for (int i = 0; i < 30; i++) {
        creatures.push_back(vasio::Creature::createRandomCreature());
    }

    vasio::Game game(creatures);
    vasio::Game::gameControl(game);

    return 0;
}
