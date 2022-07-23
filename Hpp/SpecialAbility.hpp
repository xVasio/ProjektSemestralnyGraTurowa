#pragma once

#include <string>
#include <functional>


namespace vasio {
    /**
     * Enum for the different types of abilities
     */
    enum class AbilityType {
        Offensive, Defensive
    };

    /**
     * @param type the type of ability from enum class AbilityType
     * @return the string representation of enum AbilityType
     */
    auto abilityTypeToString(AbilityType type) -> std::string;

    class Fight;

    /**
     * Class representing Special ability and its attributes
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
         * Default constructor
         */
        SpecialAbility() = default;

        /**
         *
         * @param nameOfAbility
         * @param typeOfAbility
         * @param descriptionOfAbility
         * @param maxNumberOfUses
         * @param numberOfUses
         */
        SpecialAbility(const std::string &nameOfAbility, AbilityType typeOfAbility,
                       const std::string &descriptionOfAbility, unsigned int maxNumberOfUses,
                       unsigned int numberOfUses);

        /**
         * Function for applying the special ability in the fight object
         * @param fight reference to fight object
         */
        auto applyAbility(Fight &fight) -> void;

        /**
         * Function for getting the name of the ability
         * @return name of the ability
         */
        auto getNameOfAbility() const -> std::string;

        /**
         * Function for getting the type of the ability
         * @return type of the ability as a string
         */
        auto getTypeOfAbility() const -> std::string;

        /**
         * Function that displays all special ability attributes
         */
        auto showSpecialAbility() const -> void;
    };
}