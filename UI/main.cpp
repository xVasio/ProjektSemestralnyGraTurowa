#include <iostream>
#include <vector>
#include "../Creature/Creature.hpp"
#include <memory>

auto main() -> int {

    std::cout << "========================================" << '\n';
    std::cout << "Welcome to turn-based pokemon-like game!" << '\n';
    std::cout << "========================================" << '\n';

    std::vector<std::unique_ptr<Creature>> creatures;

    for (int i = 0; i < 15; i++) {
        creatures.push_back(Creature::createRandomCreature());
    }

    for (auto &creature : creatures) {
        std::cout << *creature << '\n';
    }



    return 0;
}
