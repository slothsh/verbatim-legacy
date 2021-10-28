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
TEST_CASE("ValidatingNode structure initialization & move semantics", "[ValidatingNode : Value Expressions] [Initialization & Move Semantics]")
{
    using namespace vt::prototype;

    // Control variables
    std::string value;
    constexpr ValidatingNode vn_1 { NS::tt, ValueExpression::alpha, "node_1", 1, 2 };
    constexpr ValidatingNode vn_2 {
        NS::tts, ValueExpression::color, "node_1", 3, 4,
        NS::xml, ValueExpression::duration, "node_2", 5, 6
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
}

TEST_CASE("ValidatingNode iterator initialization & move semantics", "[ValidatingNode : Value Expressions] [Iterator Initialization]")
{
    using namespace vt::prototype;

    // Control varibales
    size_t count = 0;
    std::string value;
    ValidatingNode vn_1 { NS::tt, ValueExpression::alpha, "node_1", 1, 2 };
    ValidatingNode vn_2 { NS::tts, ValueExpression::duration, "node_2", 3, 4 };

    ValidatingNode vn_3 {
        NS::tts, ValueExpression::alpha, "node_1", 3, 4,
        NS::xml, ValueExpression::any_uri, "node_2", 5, 6
    };

    ValidatingNode vn_4 {
        NS::ttp, ValueExpression::color, "node_3", 7, 8,
        NS::ttm, ValueExpression::duration, "node_4", 9, 10
    };

    // ------------------------------------------------------------------------------------------------|
    
    // std::swap : single entry
    std::swap(vn_1.begin(), vn_2.begin());

    // vn_1
    REQUIRE((*vn_1.begin()).node.ns.id == NS::tts);
    value = (*vn_1.begin()).node.ns.value; REQUIRE(value == "tts");
    REQUIRE((*vn_1.begin()).node.element.id == ValueExpression::duration);
    value = (*vn_1.begin()).node.element.value; REQUIRE(value == "duration");
    value = (*vn_1.begin()).value; REQUIRE(value == "node_2");

    REQUIRE((*vn_1.begin()).node.ns.id == NS::tts);
    value = (*vn_1.begin()).node.ns.value; REQUIRE(value == "tts");
    REQUIRE((*vn_1.begin()).node.element.id == ValueExpression::duration);
    value = (*vn_1.begin()).node.element.value; REQUIRE(value == "duration");
    value = (*vn_1.begin()).value; REQUIRE(value == "node_2");

    REQUIRE((*vn_1.begin()).conditions == 3);
    REQUIRE((*vn_1.begin()).documents == 4);
    REQUIRE((*vn_1.end()).conditions == 3);
    REQUIRE((*vn_1.end()).documents == 4);

    for (const auto& n : vn_1) {
        ++count;
        value = n.value;
    }

    REQUIRE(count == 1);        count = 0;
    REQUIRE(value == "node_2"); value = "";

    // vn_2
    REQUIRE((*vn_2.begin()).node.ns.id == NS::tt);
    value = (*vn_2.begin()).node.ns.value; REQUIRE(value == "tt");
    REQUIRE((*vn_2.begin()).node.element.id == ValueExpression::alpha);
    value = (*vn_2.begin()).node.element.value; REQUIRE(value == "alpha");
    value = (*vn_2.begin()).value; REQUIRE(value == "node_1");

    REQUIRE((*vn_2.begin()).node.ns.id == NS::tt);
    value = (*vn_2.begin()).node.ns.value; REQUIRE(value == "tt");
    REQUIRE((*vn_2.begin()).node.element.id == ValueExpression::alpha);
    value = (*vn_2.begin()).node.element.value; REQUIRE(value == "alpha");
    value = (*vn_2.begin()).value; REQUIRE(value == "node_1");

    REQUIRE((*vn_2.begin()).conditions == 1);
    REQUIRE((*vn_2.begin()).documents == 2);
    REQUIRE((*vn_2.end()).conditions == 1);
    REQUIRE((*vn_2.end()).documents == 2);

    for (const auto& n : vn_2) {
        ++count;
        value = n.value;
    }

    REQUIRE(count == 1);        count = 0;
    REQUIRE(value == "node_1"); value = "";

    // ------------------------------------------------------------------------------------------------|
    
    // std::swap : multiple entries
    std::swap(vn_3.begin(), vn_4.begin());

    // vn_2
    REQUIRE((*vn_3.begin()).node.ns.id == NS::ttp);
    value = (*vn_3.begin()).node.ns.value; REQUIRE(value == "ttp");
    REQUIRE((*vn_3.begin()).node.element.id == ValueExpression::color);
    value = (*vn_3.begin()).node.element.value; REQUIRE(value == "color");
    value = (*vn_3.begin()).value; REQUIRE(value == "node_3");

    REQUIRE((*vn_3.end()).node.ns.id == NS::ttm);
    value = (*vn_3.end()).node.ns.value; REQUIRE(value == "ttm");
    REQUIRE((*vn_3.end()).node.element.id == ValueExpression::duration);
    value = (*vn_3.end()).node.element.value; REQUIRE(value == "duration");
    value = (*vn_3.end()).value; REQUIRE(value == "node_4");

    REQUIRE((*vn_3.begin()).conditions == 7);
    REQUIRE((*vn_3.begin()).documents == 8);
    REQUIRE((*vn_3.end()).conditions == 9);
    REQUIRE((*vn_3.end()).documents == 10);

    for (const auto& n : vn_3) {
        ++count;
        value = n.value;
    }

    REQUIRE(count == 2);        count = 0;
    REQUIRE(value == "node_4"); value = "";

    // vn_4
    REQUIRE((*vn_4.begin()).node.ns.id == NS::tts);
    value = (*vn_4.begin()).node.ns.value; REQUIRE(value == "tts");
    REQUIRE((*vn_4.begin()).node.element.id == ValueExpression::alpha);
    value = (*vn_4.begin()).node.element.value; REQUIRE(value == "alpha");
    value = (*vn_4.begin()).value; REQUIRE(value == "node_1");

    REQUIRE((*vn_4.end()).node.ns.id == NS::xml);
    value = (*vn_4.end()).node.ns.value; REQUIRE(value == "xml");
    REQUIRE((*vn_4.end()).node.element.id == ValueExpression::any_uri);
    value = (*vn_4.end()).node.element.value; REQUIRE(value == "any_uri");
    value = (*vn_4.end()).value; REQUIRE(value == "node_2");

    REQUIRE((*vn_4.begin()).conditions == 3);
    REQUIRE((*vn_4.begin()).documents == 4);
    REQUIRE((*vn_4.end()).conditions == 5);
    REQUIRE((*vn_4.end()).documents == 6);

    for (const auto& n : vn_4) {
        ++count;
        value = n.value;
    }

    REQUIRE(count == 2);        count = 0;
    REQUIRE(value == "node_2"); value = "";
}

TEST_CASE("ValidatingNode structure range-based for-loop", "[ValidatingNode : Value Expressions] [Range-Based For-Loop]")
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

TEST_CASE("ValidatingNode structure STL non-modifying sequence operations", "[ValidatingNode : Value Expressions] [STL Non-Modifying]")
{
    using namespace vt::prototype;

    // Control variables
    size_t count = 0;
    std::string name = "";
    constexpr ValidatingNode vn_1 { NS::tt, ValueExpression::alpha, "node_1", 1, 2 };
    ValidatingNode vn_2 { NS::tt, ValueExpression::alpha, "node_1", 1, 2 };

    constexpr ValidatingNode vn_3 {
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

    ValidatingNode vn_4 {
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

    // all_of : single entry : unary predicate
    bool vn_1_all_of = std::all_of(vn_1.begin(), vn_1.end(), [](const auto& _data) {
        return _data.node.ns.id == NS::tt && _data.node.ns.id != NS::tts;
    });

    REQUIRE(vn_1_all_of);

    // ------------------------------------------------------------------------------------------------|

    // all_of : single entry : constexpr unary predicate
    constexpr bool vn_1_all_of_constexpr = std::all_of(vn_1.begin(), vn_1.end(), [](const auto& _data) {
        return _data.node.ns.id == NS::tt && _data.node.ns.id != NS::tts;
    });

    REQUIRE(vn_1_all_of_constexpr);

    // ------------------------------------------------------------------------------------------------|
    
    // any_of : single entry : unary predicate
    bool vn_1_any_of = std::any_of(vn_1.begin(), vn_1.end(), [](const auto& _data) {
        return _data.node.ns.id == NS::tt && _data.node.ns.id != NS::tts;
    });

    REQUIRE(vn_1_any_of);

    // ------------------------------------------------------------------------------------------------|

    // any_of : single entry : constexpr unary predicate
    constexpr bool vn_1_any_of_constexpr = std::any_of(vn_1.begin(), vn_1.end(), [](const auto& _data) {
        return _data.node.ns.id == NS::tt && _data.node.ns.id != NS::tts;
    });

    REQUIRE(vn_1_any_of_constexpr);

    // ------------------------------------------------------------------------------------------------|
    
    // none_of : single entry : unary predicate
    bool vn_1_none_of = std::none_of(vn_1.begin(), vn_1.end(), [](const auto& _data) {
        return _data.node.ns.id == NS::tt && _data.node.ns.id != NS::tts;
    });

    REQUIRE_FALSE(vn_1_none_of);

    // ------------------------------------------------------------------------------------------------|

    // none_of : single entry : constexpr unary predicate
    constexpr bool vn_1_none_of_constexpr = std::none_of(vn_1.begin(), vn_1.end(), [](const auto& _data) {
        return _data.node.ns.id == NS::tt && _data.node.ns.id != NS::tts;
    });

    REQUIRE_FALSE(vn_1_none_of_constexpr);

    // ------------------------------------------------------------------------------------------------|

    // for_each : single entry
    std::for_each(vn_1.begin(), vn_1.end(), [&count, &name](const auto& _data) {
        ++count;
        name = _data.value;
    });

    REQUIRE(count == 1);        count = 0;
    REQUIRE(name == "node_1");  name = "";
    
    // ------------------------------------------------------------------------------------------------|

    // for_each : multiple entries
    std::for_each(vn_3.begin(), vn_3.end(), [&count, &name](const auto& _data) {
        ++count;
        name = _data.value;
    });

    REQUIRE(count == 10);        count = 0;
    REQUIRE(name == "node_10");  name = "";

    // ------------------------------------------------------------------------------------------------|

    // for_each_n : single entry
    std::for_each_n(vn_1.begin(), 1, [&count, &name](const auto& _data) {
        ++count;
        name = _data.value;
    });

    REQUIRE(count == 1);        count = 0;
    REQUIRE(name == "node_1");  name = "";
    
    // ------------------------------------------------------------------------------------------------|

    // for_each_n : multiple entries
    std::for_each_n(vn_3.begin(), 5, [&count, &name](const auto& _data) {
        ++count;
        name = _data.value;
    });

    REQUIRE(count == 5);         count = 0;
    REQUIRE(name == "node_5");   name = "";

    // ------------------------------------------------------------------------------------------------|
}