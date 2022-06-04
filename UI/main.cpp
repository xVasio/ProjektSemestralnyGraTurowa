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


    auto& creature = creatures[0];
    auto& creature2 = creatures[1];

    std::cout << '\n';
    std::cout << *creature << '\n';
    std::cout << *creature2 << '\n';

    std::cout << creature->getEfficiency(*creatures[1]) << '\n';
    std::cout << creature2->getEfficiency(*creatures[0]) << '\n';

    float efficiency = creature->getEfficiency(*creature2);
    std::cout << "Efficiency: " << efficiency << '\n';

    return 0;
}
