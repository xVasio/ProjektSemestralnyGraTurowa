//
// Created by theer on 07.06.2022.
//

#pragma once

#include <string>
#include <functional>
#include "../Fight/Fight.hpp"

namespace vasio {
    class SpecialAbility {
        std::string NameOfAbility_;
        std::string DescriptionOfAbility_;
        unsigned int currentNumberOfUses_;
        unsigned int maxNumberOfUses_;
    };
}


