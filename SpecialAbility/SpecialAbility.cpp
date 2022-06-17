//
// Created by theer on 07.06.2022.
//

#include <cassert>
#include "../Hpp/SpecialAbility.hpp"
#include "../Hpp/Fight.hpp"

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
                                   const std::string &descriptionOfAbility, unsigned int maxNumberOfUses, unsigned int numberOfUses
    ) : NameOfAbility_(nameOfAbility), TypeOfAbility_(typeOfAbility), DescriptionOfAbility_(descriptionOfAbility),
        maxNumberOfUses_(maxNumberOfUses), numberOfUses_(numberOfUses) {}

    auto SpecialAbility::applyAbility(Fight &fight) -> void {
        if(fight.player1Turn_) {
            fight.currentPlayer1Pokemon->specialAction(fight.currentPlayer2Pokemon);
        } else {
            fight.currentPlayer2Pokemon->specialAction(fight.currentPlayer1Pokemon);
        }
    }


    auto SpecialAbility::getNameOfAbility() const -> std::string {
        return NameOfAbility_;
    }
}

