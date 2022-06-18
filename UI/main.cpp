#include <vector>
#include "Game.hpp"

auto main() -> int {
    std::vector<std::shared_ptr<vasio::Creature>> creatures;
    creatures.reserve(30);
    for (int i = 0; i < 30; i++) {
        creatures.push_back(vasio::Creature::createRandomCreature());
    }
    vasio::Game game(creatures);
    vasio::Game::gameControl(game);
    return 0;
}
