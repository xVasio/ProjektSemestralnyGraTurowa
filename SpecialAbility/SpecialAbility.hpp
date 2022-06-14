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

    class Fight;

    class SpecialAbility {
    public:
        std::string NameOfAbility_;
        AbilityType TypeOfAbility_;
        std::string DescriptionOfAbility_;
        unsigned int maxNumberOfUses_;
//        std::function<void(Fight &fight)> abilityFunction_;

        SpecialAbility() = default;

        SpecialAbility(const std::string &nameOfAbility, AbilityType typeOfAbility,
                       const std::string &descriptionOfAbility, unsigned int maxNumberOfUses
        );

        auto applyAbility(Fight &fight) -> void;

    };

}