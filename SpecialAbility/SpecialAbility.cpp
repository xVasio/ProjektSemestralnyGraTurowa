//
// Created by theer on 07.06.2022.
//

#include <cassert>
#include <utility>
#include "SpecialAbility.hpp"
#include "../Fight/Fight.hpp"

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

    SpecialAbility::SpecialAbility(const std::string &nameOfAbility, AbilityType typeOfAbility,
                                   const std::string &descriptionOfAbility, unsigned int maxNumberOfUses,
                                   std::function<void(Fight &)> abilityFunction) : NameOfAbility_(nameOfAbility), TypeOfAbility_(typeOfAbility), DescriptionOfAbility_(descriptionOfAbility),
                                                                                   maxNumberOfUses_(maxNumberOfUses), abilityFunction_(std::move(abilityFunction)) {}

    auto SpecialAbility::applyAbility(Fight &fight) -> void {
        abilityFunction_(fight);
    }
}

