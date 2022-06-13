//
// Created by theer on 07.06.2022.
//

#pragma once

#include <string>
#include <functional>

namespace vasio {
    enum class AbilityType {
        Offensive, Defensive
    };

    class SpecialAbility {
        std::string NameOfAbility_;
        AbilityType TypeOfAbility_;
        std::string DescriptionOfAbility_;
        unsigned int maxNumberOfUses_;

    public:
        SpecialAbility() = default;

        SpecialAbility(const std::string &nameOfAbility, AbilityType typeOfAbility,
                       const std::string &descriptionOfAbility, unsigned int maxNumberOfUses);
    };
}

