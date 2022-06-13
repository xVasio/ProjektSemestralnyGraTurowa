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


    SpecialAbility::SpecialAbility(const std::string &nameOfAbility, AbilityType typeOfAbility,
                                   const std::string &descriptionOfAbility, unsigned int maxNumberOfUses)
            : NameOfAbility_(nameOfAbility), TypeOfAbility_(typeOfAbility), DescriptionOfAbility_(descriptionOfAbility),
              maxNumberOfUses_(maxNumberOfUses) {};
}

