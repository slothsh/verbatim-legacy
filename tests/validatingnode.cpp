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
#include <utility>
#include <string_view>

// Third-party headers
#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

// Project headers
#include "../include/prototype/validatettml.hpp"


// ValidatingNode Value Expressions
TEST_CASE("ValidatingNode for value expressions initialization and move semantics", "[ValidatingNode : Value Expressions] [Initialization & Move Semantics]")
{
    using namespace vt::prototype;

    // Control variables
    std::string value;
    constexpr ValidatingNode vn_1 { NS::tt, ValueExpression::alpha, "node_1", 1, 2 };
    constexpr ValidatingNode vn_2 {
        NS::tts, ValueExpression::color, "node_1", 3, 4,
        NS::xml, ValueExpression::duration, "node_2", 5, 6
    };

    ValidatingNode vn_3 {
        NS::tt, ValueExpression::alpha, "node_1", 1, 2,
        NS::xml, ValueExpression::any_uri, "node_2", 3, 4
    };
    ValidatingNode vn_4 {
        NS::tts, ValueExpression::color, "node_3", 5, 6,
        NS::ttp, ValueExpression::duration, "node_4", 7, 8
    };

    // ------------------------------------------------------------------------------------------------|
    
    // Initialization : single entry
    REQUIRE(vn_1.data.node.ns.id == NS::tt);
    value = vn_1.data.node.ns.value;
    REQUIRE(value == "tt"); value = "";

    REQUIRE(vn_1.data.node.element.id == ValueExpression::alpha);
    value = vn_1.data.node.element.value;
    REQUIRE(value == "alpha"); value = "";

    value = vn_1.data.value;
    REQUIRE(value == "node_1"); value = "";

    REQUIRE(vn_1.data.conditions == 1);
    REQUIRE(vn_1.data.documents == 2);

    // Initialization : multiple entries
    // Entry 1
    REQUIRE(vn_2.data.node.ns.id == NS::tts);
    value = vn_2.data.node.ns.value;
    REQUIRE(value == "tts"); value = "";

    REQUIRE(vn_2.data.node.element.id == ValueExpression::color);
    value = vn_2.data.node.element.value;
    REQUIRE(value == "color"); value = "";

    value = vn_2.data.value;
    REQUIRE(value == "node_1"); value = "";

    REQUIRE(vn_2.data.conditions == 3);
    REQUIRE(vn_2.data.documents == 4);

    // Entry 2
    REQUIRE(vn_2.next.data.node.ns.id == NS::xml);
    value = vn_2.next.data.node.ns.value;
    REQUIRE(value == "xml"); value = "";

    REQUIRE(vn_2.next.data.node.element.id == ValueExpression::duration);
    value = vn_2.next.data.node.element.value;
    REQUIRE(value == "duration"); value = "";

    value = vn_2.next.data.value;
    REQUIRE(value == "node_2"); value = "";

    REQUIRE(vn_2.next.data.conditions == 5);
    REQUIRE(vn_2.next.data.documents == 6);

    // ------------------------------------------------------------------------------------------------|
    
    // std::swap : single entry

    // ------------------------------------------------------------------------------------------------|
    
    // std::swap : multiple entries
    std::swap(vn_3, vn_4);

    // vn_3 : Entry 1
    REQUIRE(vn_3.data.node.ns.id == NS::tts);
    value = vn_3.data.node.ns.value;
    REQUIRE(value == "tts"); value = "";

    REQUIRE(vn_3.data.node.element.id == ValueExpression::color);
    value = vn_3.data.node.element.value;
    REQUIRE(value == "color"); value = "";

    value = vn_3.data.value;
    REQUIRE(value == "node_3"); value = "";

    REQUIRE(vn_3.data.conditions == 5);
    REQUIRE(vn_3.data.documents == 6);

    // vn_3 : Entry 2
    REQUIRE(vn_3.next.data.node.ns.id == NS::ttp);
    value = vn_3.next.data.node.ns.value;
    REQUIRE(value == "ttp"); value = "";

    REQUIRE(vn_3.next.data.node.element.id == ValueExpression::duration);
    value = vn_3.next.data.node.element.value;
    REQUIRE(value == "duration"); value = "";

    value = vn_3.next.data.value;
    REQUIRE(value == "node_4"); value = "";

    REQUIRE(vn_3.next.data.conditions == 7);
    REQUIRE(vn_3.next.data.documents == 8);

    // vn_4 : Entry 1
    REQUIRE(vn_4.data.node.ns.id == NS::tt);
    value = vn_4.data.node.ns.value;
    REQUIRE(value == "tt"); value = "";

    REQUIRE(vn_4.data.node.element.id == ValueExpression::alpha);
    value = vn_4.data.node.element.value;
    REQUIRE(value == "alpha"); value = "";

    value = vn_4.data.value;
    REQUIRE(value == "node_1"); value = "";

    REQUIRE(vn_4.data.conditions == 1);
    REQUIRE(vn_4.data.documents == 2);

    // vn_4 : Entry 2
    REQUIRE(vn_4.next.data.node.ns.id == NS::xml);
    value = vn_4.next.data.node.ns.value;
    REQUIRE(value == "xml"); value = "";

    REQUIRE(vn_4.next.data.node.element.id == ValueExpression::any_uri);
    value = vn_4.next.data.node.element.value;
    REQUIRE(value == "any_uri"); value = "";

    value = vn_4.next.data.value;
    REQUIRE(value == "node_2"); value = "";

    REQUIRE(vn_4.next.data.conditions == 3);
    REQUIRE(vn_4.next.data.documents == 4);

    // ------------------------------------------------------------------------------------------------|
}

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
    for (const auto& e : vn_1) {
        ++count;
        name = e.value;
    }
    
    CHECK(count == 1);        count = 0;
    CHECK(name == "node_1");  name = "";

    // ------------------------------------------------------------------------------------------------|

    // Multiple entries
    for (const auto& e : vn_2) {
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

    // for_each : single entry
    std::for_each(vn_1.begin(), vn_1.end(), [&count, &name](const auto& _node) {
        ++count;
        name = _node.value;
    });

    REQUIRE(count == 1);        count = 0;
    REQUIRE(name == "node_1");  name = "";
    
    // ------------------------------------------------------------------------------------------------|

    // for_each : multiple entries
    std::for_each(vn_2.begin(), vn_2.end(), [&count, &name](const auto& _node) {
        ++count;
        name = _node.value;
    });

    REQUIRE(count == 10);        count = 0;
    REQUIRE(name == "node_10");  name = "";

    // ------------------------------------------------------------------------------------------------|

    // for_each_n : single entry
    std::for_each_n(vn_1.begin(), 1, [&count, &name](const auto& _node) {
        ++count;
        name = _node.value;
    });

    REQUIRE(count == 1);        count = 0;
    REQUIRE(name == "node_1");  name = "";
    
    // ------------------------------------------------------------------------------------------------|

    // for_each_n : multiple entries
    std::for_each_n(vn_2.begin(), 5, [&count, &name](const auto& _node) {
        ++count;
        name = _node.value;
    });

    REQUIRE(count == 5);         count = 0;
    REQUIRE(name == "node_5");   name = "";

    // ------------------------------------------------------------------------------------------------|
}