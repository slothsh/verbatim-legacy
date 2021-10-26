// Stefan "SoulXP" Olivier
// File: validatettml.cpp
// Description: Test code for building a TTML tree for run time structure validation

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "../include/config.hpp"
#endif

// Standard headers
#include <iostream>
#include <concepts>
#include <type_traits>

// Third-party headers
#include <catch2/catch_test_macros.hpp>

// Project headers
#include "../include/prototype/validatettml.hpp"

// Value Expressions
TEST_CASE("[ValidatingNode : Iterators]", "[ValidatingNode : Iterators]")
{
    using namespace vt::prototype;

    // Single entry
    constexpr ValidatingNode vn_1 { NS::tt, ValueExpression::alpha, "node_1", 1, 2 };

    for (const auto e : vn_1)
    {
        std::cout << e.value << '\n';
    }

    // Multiple entries
    constexpr ValidatingNode vn_2 {
        NS::tt, ValueExpression::alpha, "node_1", 1, 2,
        NS::xml, ValueExpression::alpha, "node_2", 1, 2,
        NS::xml, ValueExpression::alpha, "node_3", 1, 2,
        NS::xml, ValueExpression::alpha, "node_4", 1, 2,
        NS::xml, ValueExpression::alpha, "node_5", 1, 2,
        NS::xml, ValueExpression::alpha, "node_6", 1, 2,
        NS::xml, ValueExpression::alpha, "node_7", 1, 2,
        NS::xml, ValueExpression::alpha, "node_8", 1, 2,
        NS::xml, ValueExpression::alpha, "node_9", 1, 2,
        NS::xml, ValueExpression::alpha, "node_10", 1, 2,
    };

    for (const auto e : vn_2)
    {
        std::cout << e.value << '\n';
    }
}