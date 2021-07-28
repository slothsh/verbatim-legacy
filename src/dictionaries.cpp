// Stefan "SoulXP" Olivier
// File: dictionaries.cpp
// Description: External linkage header for various tables & dictionaries

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "../include/config.hpp"
#endif

// Standard headers
#include <iostream>
#include <type_traits>
#include <utility>
#include <concepts>

// Project headers
#include "../include/node.hpp"
#include "../include/dictionaries.hpp"

using namespace vt::dictionary;
using namespace magic_enum;

namespace vt
{
    namespace dictionary
    {
        constexpr inline auto MakeTTMLNodes()
        {
            // Make tags for prototype enumerations
            component_t a(NS::one, Tag::one);
            attribute_t b(NS::one, Attribute::one);
            vexpression_t c(NS::one, ValueExpression::one);
            attroption_t d(NS::one, AttributeOption::one);
            content_t e(NS::one, Content::one);

            
        }
    }
}