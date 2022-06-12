//
// Created by theer on 07.06.2022.
//

#pragma once

#include <string>
#include <functional>
#include "../Fight/Fight.hpp"

namespace vasio {
    enum class AbilityType {
        Offensive, Defensive
    };

    class SpecialAbility {
        std::string NameOfAbility_;
        AbilityType TypeOfAbility_;
        std::string DescriptionOfAbility_;
        unsigned int maxNumberOfUses_;
        std::function<void(Fight &fight)> abilityFunction_;

    public:
        SpecialAbility(std::string nameOfAbility, AbilityType typeOfAbility, std::string descriptionOfAbility,
                        unsigned int maxNumberOfUses, std::function<void(Fight &fight)> abilityFunction);

    };
}


