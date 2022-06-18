#include <cassert>
#include "SpecialAbility.hpp"
#include "/Fight.hpp"
#include <iostream>

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
                                   unsigned int numberOfUses
    ) : NameOfAbility_(nameOfAbility), TypeOfAbility_(typeOfAbility), DescriptionOfAbility_(descriptionOfAbility),
        maxNumberOfUses_(maxNumberOfUses), numberOfUses_(numberOfUses) {}

    auto SpecialAbility::applyAbility(Fight &fight) -> void {
        if (fight.player1Turn_) {
            fight.currentPlayer1Pokemon->specialAction(fight.currentPlayer2Pokemon);
        } else {
            fight.currentPlayer2Pokemon->specialAction(fight.currentPlayer1Pokemon);
        }
    }


    auto SpecialAbility::getNameOfAbility() const -> std::string {
        return NameOfAbility_;
    }

    auto SpecialAbility::getTypeOfAbility() const -> std::string {
        return enumAbilityTypeToString(TypeOfAbility_);
    }


    auto SpecialAbility::showSpecialAbility() const -> void {
        std::cout << "Name of ability: " << NameOfAbility_ << std::endl;
        std::cout << "Type of ability: " << getTypeOfAbility() << std::endl;
        std::cout << "Description of ability: " << DescriptionOfAbility_ << std::endl;
        std::cout << "Number of uses: " << numberOfUses_ << std::endl;
        std::cout << "Max number of uses: " << maxNumberOfUses_ << std::endl;
    }


}

