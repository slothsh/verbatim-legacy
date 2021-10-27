// Stefan "SoulXP" Olivier
// File: validatettml.cpp
// Description: Test code for building a TTML tree for run time structure validation

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "../include/config.hpp"
#endif

// Standard headers
#include <iostream>
#include <string>
#include <algorithm>

// Third-party headers
#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

// Project headers
#include "../include/prototype/validatettml.hpp"

// ValidatingNode Value Expressions
TEST_CASE("ValidatingNode range-based for-loop for TTML value expressions", "[ValidatingNode : Value Expressions] [Range-Based For-Loop]")
{
    using namespace vt::prototype;

    // Control variables
    size_t count = 0;
    std::string name = "";
    constexpr ValidatingNode vn_1 { NS::tt, ValueExpression::alpha, "node_1", 1, 2 };

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

    // ------------------------------------------------------------------------------------------------|

    // Single entry
    for (const auto e : vn_1) {
        ++count;
        name = e.value;
    }
    
    CHECK(count == 1);        count = 0;
    CHECK(name == "node_1");  name = "";

    // ------------------------------------------------------------------------------------------------|

    // Multiple entries
    for (const auto e : vn_2) {
        ++count;
        name = e.value;
    }

    CHECK(count == 10);             count = 0;
    REQUIRE(name == "node_10");     name = "";

    // ------------------------------------------------------------------------------------------------|
}

TEST_CASE("ValidatingNode STL non-modifying sequence operations for TTML value expressions", "[ValidatingNode : Value Expressions] [STL Non-Modifying]")
{
    using namespace vt::prototype;

    // Control variables
    size_t count = 0;
    std::string name = "";
    constexpr ValidatingNode vn_1 { NS::tt, ValueExpression::alpha, "node_1", 1, 2 };

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

    // ------------------------------------------------------------------------------------------------|

    // for_each : Single entry
    std::for_each(vn_1.begin(), vn_1.end(), [&count, &name](const auto& _node) {
        ++count;
        name = _node.value;
    });

    REQUIRE(count == 1);        count = 0;
    REQUIRE(name == "node_1");  name = "";
    
    // ------------------------------------------------------------------------------------------------|

    // for_each : Multiple entries
    std::for_each(vn_2.begin(), vn_2.end(), [&count, &name](const auto& _node) {
        ++count;
        name = _node.value;
    });

    REQUIRE(count == 10);        count = 0;
    REQUIRE(name == "node_10");  name = "";

    // ------------------------------------------------------------------------------------------------|

    // for_each_n : Single entry
    std::for_each_n(vn_1.begin(), 1, [&count, &name](const auto& _node) {
        ++count;
        name = _node.value;
    });

    REQUIRE(count == 1);        count = 0;
    REQUIRE(name == "node_1");  name = "";
    
    // ------------------------------------------------------------------------------------------------|

    // for_each_n : Multiple entries
    std::for_each_n(vn_2.begin(), 5, [&count, &name](const auto& _node) {
        ++count;
        name = _node.value;
    });

    REQUIRE(count == 5);         count = 0;
    REQUIRE(name == "node_5");   name = "";

    // ------------------------------------------------------------------------------------------------|
}