#pragma once

#include <string>
#include <functional>



namespace vasio {
    /**
     *
     */
    enum class AbilityType {
        Offensive, Defensive
    };

    auto abilityTypeToString(AbilityType type) -> std::string;

    class Fight;
    /**
     *
     */
    class SpecialAbility {
    public:
        std::string NameOfAbility_;
        AbilityType TypeOfAbility_;
        std::string DescriptionOfAbility_;
        unsigned int numberOfUses_;
        unsigned int maxNumberOfUses_;
        /**
         *
         */
        SpecialAbility() = default;
        /**
         *
         * @param nameOfAbility
         * @param typeOfAbility
         * @param descriptionOfAbility
         * @param maxNumberOfUses
         */
        SpecialAbility(const std::string &nameOfAbility, AbilityType typeOfAbility,
                       const std::string &descriptionOfAbility, unsigned int maxNumberOfUses, unsigned int numberOfUses);

        /**
         *
         * @param fight
         */
        auto applyAbility(Fight &fight) -> void;

        auto getNameOfAbility() const -> std::string;

        auto getTypeOfAbility() const -> std::string;

        auto showSpecialAbility() const -> void;

    };

}