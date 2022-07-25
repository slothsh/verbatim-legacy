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
    CHECK(vn_1.data.node.ns.id == NS::tt);
    value = vn_1.data.node.ns.value;
    CHECK(value == "tt"); value = "";

    CHECK(vn_1.data.node.element.id == ValueExpression::alpha);
    value = vn_1.data.node.element.value;
    CHECK(value == "alpha"); value = "";

    value = vn_1.data.value;
    CHECK(value == "node_1"); value = "";

    CHECK(vn_1.data.conditions == 1);
    CHECK(vn_1.data.documents == 2);

    // Initialization : multiple entries
    // Entry 1
    CHECK(vn_2.data.node.ns.id == NS::tts);
    value = vn_2.data.node.ns.value;
    CHECK(value == "tts"); value = "";

    CHECK(vn_2.data.node.element.id == ValueExpression::color);
    value = vn_2.data.node.element.value;
    CHECK(value == "color"); value = "";

    value = vn_2.data.value;
    CHECK(value == "node_1"); value = "";

    CHECK(vn_2.data.conditions == 3);
    CHECK(vn_2.data.documents == 4);

    // Entry 2
    CHECK(vn_2.next.data.node.ns.id == NS::xml);
    value = vn_2.next.data.node.ns.value;
    CHECK(value == "xml"); value = "";

    CHECK(vn_2.next.data.node.element.id == ValueExpression::duration);
    value = vn_2.next.data.node.element.value;
    CHECK(value == "duration"); value = "";

    value = vn_2.next.data.value;
    CHECK(value == "node_2"); value = "";

    CHECK(vn_2.next.data.conditions == 5);
    CHECK(vn_2.next.data.documents == 6);

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

    // Iterator default initialisation
    using data_t = typename decltype(vn_1)::data_t;
    using iterator_empty_t = detail::_validatingnode_input_iter<0, data_t>;
    using iterator_one_t = detail::_validatingnode_input_iter<1, data_t>;
    using iterator_two_t = detail::_validatingnode_input_iter<2, data_t>;
    using iterator_three_t = detail::_validatingnode_input_iter<3, data_t>;

    iterator_empty_t iter_1{};
    const iterator_empty_t iter_const_1{};
    constexpr iterator_empty_t iter_constexpr_1{};

    CHECK(iter_1.index == 0);
    CHECK(iter_1.size == 1);
    CHECK(iter_const_1.index == 0);
    CHECK(iter_const_1.size == 1);
    CHECK(iter_constexpr_1.index == 0);
    CHECK(iter_constexpr_1.size == 1);

    // ------------------------------------------------------------------------------------------------|

    // Iterator Copy Construction
    iterator_three_t iter_2{ data_t{ NS::tts, ValueExpression::duration, "node_2", 3, 4 }, vn_1 };
    iterator_three_t iter_3 { iter_2 };

    CHECK(iter_2 == iter_3);

    // ------------------------------------------------------------------------------------------------|
    
    // std::swap : single entry
    std::swap(vn_1.begin(), vn_2.begin());

    // vn_1
    CHECK((*vn_1.begin()).node.ns.id == NS::tts);
    value = (*vn_1.begin()).node.ns.value; CHECK(value == "tts");
    CHECK((*vn_1.begin()).node.element.id == ValueExpression::duration);
    value = (*vn_1.begin()).node.element.value; CHECK(value == "duration");
    value = (*vn_1.begin()).value; CHECK(value == "node_2");

    CHECK((*vn_1.begin()).node.ns.id == NS::tts);
    value = (*vn_1.begin()).node.ns.value; CHECK(value == "tts");
    CHECK((*vn_1.begin()).node.element.id == ValueExpression::duration);
    value = (*vn_1.begin()).node.element.value; CHECK(value == "duration");
    value = (*vn_1.begin()).value; CHECK(value == "node_2");

    CHECK((*vn_1.begin()).conditions == 3);
    CHECK((*vn_1.begin()).documents == 4);

    // CHECK((*vn_1.end()).value == magic_enum::enum_name(VT_ERROR_CODE::error_empty));
    CHECK((*vn_1.end()).conditions == magic_enum::enum_integer(vt::constants::NodeCondition::none));
    CHECK((*vn_1.end()).documents == magic_enum::enum_integer(vt::constants::TTMLDocument::none));

    for (const auto& n : vn_1) {
        ++count;
        value = n.value;
    }

    CHECK(count == 1);        count = 0;
    CHECK(value == "node_2"); value = "";

    // vn_2
    CHECK((*vn_2.begin()).node.ns.id == NS::tt);
    value = (*vn_2.begin()).node.ns.value; CHECK(value == "tt");
    CHECK((*vn_2.begin()).node.element.id == ValueExpression::alpha);
    value = (*vn_2.begin()).node.element.value; CHECK(value == "alpha");
    value = (*vn_2.begin()).value; CHECK(value == "node_1");

    CHECK((*vn_2.begin()).node.ns.id == NS::tt);
    value = (*vn_2.begin()).node.ns.value; CHECK(value == "tt");
    CHECK((*vn_2.begin()).node.element.id == ValueExpression::alpha);
    value = (*vn_2.begin()).node.element.value; CHECK(value == "alpha");
    value = (*vn_2.begin()).value; CHECK(value == "node_1");

    CHECK((*vn_2.begin()).conditions == 1);
    CHECK((*vn_2.begin()).documents == 2);

    CHECK((*vn_2.end()).conditions == magic_enum::enum_integer(vt::constants::NodeCondition::none));
    CHECK((*vn_2.end()).documents == magic_enum::enum_integer(vt::constants::TTMLDocument::none));

    for (const auto& n : vn_2) {
        ++count;
        value = n.value;
    }

    CHECK(count == 1);        count = 0;
    CHECK(value == "node_1"); value = "";

    // ------------------------------------------------------------------------------------------------|
    
    // std::swap : multiple entries
    std::swap(vn_3.begin(), vn_4.begin());

    // vn_2
    CHECK((*vn_3.begin()).node.ns.id == NS::ttp);
    value = (*vn_3.begin()).node.ns.value; CHECK(value == "ttp");
    CHECK((*vn_3.begin()).node.element.id == ValueExpression::color);
    value = (*vn_3.begin()).node.element.value; CHECK(value == "color");
    value = (*vn_3.begin()).value; CHECK(value == "node_3");

    CHECK((*vn_3.end()).node.ns.id == NS::none);
    value = (*vn_3.end()).node.ns.value; CHECK(value == "none");
    CHECK((*vn_3.end()).node.element.id == ValueExpression::none);
    value = (*vn_3.end()).node.element.value; CHECK(value == "none");
    value = (*vn_3.end()).value; CHECK(value == "node_4");

    CHECK((*vn_3.begin()).conditions == 7);
    CHECK((*vn_3.begin()).documents == 8);
    CHECK((*vn_3.end()).conditions == 9);
    CHECK((*vn_3.end()).documents == 10);

    for (const auto& n : vn_3) {
        ++count;
        value = n.value;
    }

    CHECK(count == 2);        count = 0;
    CHECK(value == "node_4"); value = "";

    // vn_4
    CHECK((*vn_4.begin()).node.ns.id == NS::tts);
    value = (*vn_4.begin()).node.ns.value; CHECK(value == "tts");
    CHECK((*vn_4.begin()).node.element.id == ValueExpression::alpha);
    value = (*vn_4.begin()).node.element.value; CHECK(value == "alpha");
    value = (*vn_4.begin()).value; CHECK(value == "node_1");

    CHECK((*vn_4.end()).node.ns.id == NS::none);
    value = (*vn_4.end()).node.ns.value; CHECK(value == "none");
    CHECK((*vn_4.end()).node.element.id == ValueExpression::none);
    value = (*vn_4.end()).node.element.value; CHECK(value == "none");
    value = (*vn_4.end()).value; CHECK(value == "node_2");

    CHECK((*vn_4.begin()).conditions == 3);
    CHECK((*vn_4.begin()).documents == 4);
    CHECK((*vn_4.end()).conditions == magic_enum::enum_integer(vt::constants::NodeCondition::none));
    CHECK((*vn_4.end()).documents == magic_enum::enum_integer(vt::constants::TTMLDocument::none));

    for (const auto& n : vn_4) {
        ++count;
        value = n.value;
    }

    CHECK(count == 2);        count = 0;
    CHECK(value == "node_2"); value = "";
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
    CHECK(name == "node_10");     name = "";

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

    CHECK(vn_1_all_of);

    // ------------------------------------------------------------------------------------------------|

    // all_of : single entry : constexpr unary predicate
    constexpr bool vn_1_all_of_constexpr = std::all_of(vn_1.begin(), vn_1.end(), [](const auto& _data) {
        return _data.node.ns.id == NS::tt && _data.node.ns.id != NS::tts;
    });

    CHECK(vn_1_all_of_constexpr);

    // ------------------------------------------------------------------------------------------------|
    
    // any_of : single entry : unary predicate
    bool vn_1_any_of = std::any_of(vn_1.begin(), vn_1.end(), [](const auto& _data) {
        return _data.node.ns.id == NS::tt && _data.node.ns.id != NS::tts;
    });

    CHECK(vn_1_any_of);

    // ------------------------------------------------------------------------------------------------|

    // any_of : single entry : constexpr unary predicate
    constexpr bool vn_1_any_of_constexpr = std::any_of(vn_1.begin(), vn_1.end(), [](const auto& _data) {
        return _data.node.ns.id == NS::tt && _data.node.ns.id != NS::tts;
    });

    CHECK(vn_1_any_of_constexpr);

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

    // for_each : single entry : 
    std::for_each(vn_1.begin(), vn_1.end(), [&count, &name](const auto& _data) {
        ++count;
        name = _data.value;
    });

    CHECK(count == 1);        count = 0;
    CHECK(name == "node_1");  name = "";
    
    // ------------------------------------------------------------------------------------------------|

    // for_each : multiple entries
    std::for_each(vn_3.begin(), vn_3.end(), [&count, &name](const auto& _data) {
        ++count;
        name = _data.value;
    });

    CHECK(count == 10);        count = 0;
    CHECK(name == "node_10");  name = "";

    // ------------------------------------------------------------------------------------------------|

    // for_each_n : single entry
    std::for_each_n(vn_1.begin(), 1, [&count, &name](const auto& _data) {
        ++count;
        name = _data.value;
    });

    CHECK(count == 1);        count = 0;
    CHECK(name == "node_1");  name = "";
    
    // ------------------------------------------------------------------------------------------------|

    // for_each_n : multiple entries
    std::for_each_n(vn_3.begin(), 5, [&count, &name](const auto& _data) {
        ++count;
        name = _data.value;
    });

    CHECK(count == 5);         count = 0;
    CHECK(name == "node_5");   name = "";

    // ------------------------------------------------------------------------------------------------|
}