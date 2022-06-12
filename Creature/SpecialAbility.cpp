//
// Created by theer on 07.06.2022.
//

#include <cassert>
#include "SpecialAbility.hpp"

namespace vasio {
    auto enumAbilityTypeToString(AbilityType type) -> std::string {
        switch (type) {
            case AbilityType::Offensive:
                return "Offensive";
            case AbilityType::Defensive:
                return "Defensive";
            default:
                assert(false);
        }
    }

    SpecialAbility::SpecialAbility(std::string nameOfAbility, AbilityType typeOfAbility,
                                   std::string descriptionOfAbility, unsigned int maxNumberOfUses,
                                   std::function<void(Fight &)> abilityFunction) {}
}

