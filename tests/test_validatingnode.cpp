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

TEST_CASE("ValidatingNode Templating Test", "[ValidatingNode : Templates]")
{
	using namespace vt::prototype;

    // constexpr std::tuple a_t{ NS::tt, ValueExpression::alpha, "hello", 1, 2 };
    // constexpr ValidatingNode a { 
    //     NS::tt, ValueExpression::alpha, "hello", 1, 2,
    //     NS::tt, ValueExpression::alpha, "hello", 3, 4,
    //     std::move(a_t),
    //     NS::tt, ValueExpression::alpha, "hello", 3, 4,
    //     std::move(a_t),
    //     NS::tt, ValueExpression::alpha, "hello", 3, 4,
    //     std::move(a_t)
    // };
    // constexpr vt::ValueExpressionNode b{ NS::tt, ValueExpression::alpha, "hello", 5, 6 };

    // constexpr std::tuple c_t{ NS::tt, Attribute::opacity, "hello", 0, 1, 2 };
    // constexpr ValidatingNode c { 
    //     NS::tt, Attribute::opacity, "hello", 0, 1, 2,
    //     std::move(c_t),
    //     NS::tt, Attribute::opacity, "hello", 0, 1, 2,
    //     std::move(c_t),
    //     std::move(c_t),
    //     NS::tt, Attribute::opacity, "hello", 0, 1, 2,
    //     NS::tt, Attribute::opacity, "hello", 0, 1, 2
    // };

    // constexpr ValidatingNode d{ NS::tt, Attribute::opacity, "hello", 1, 2, 3 };

    // constexpr std::tuple e_t{ NS::tt, GenericData::PCDATA, 1, 2 };
    // constexpr ValidatingNode e { 
    //     std::move(e_t)
    // };

    // vt::ContentNode f{ NS::tt, GenericData::PCDATA, 1, 2 };

    // constexpr ValidatingNode g { 
    //     NS::tt, Tag::tt, std::move(c), std::move(e), 1,
    //     NS::tt, Tag::tt, std::move(c), std::move(e), 1,
    //     NS::tt, Tag::tt, std::move(c), std::move(e), 1,
    //     NS::tt, Tag::tt, std::move(c), std::move(e), 1,
    //     NS::tt, Tag::tt, std::move(c), std::move(e), 1
    // };

    // constexpr ValidatingNode h{ NS::tt, Tag::tt, std::move(d), std::move(e), 3 };

    // constexpr std::tuple j_t1{ NS::tt, Tag::tt, std::move(c), std::move(e), 3 };
    // constexpr std::tuple j_t2{ NS::tt, Tag::tt, std::move(c), std::move(e), 3 };
    // constexpr ValidatingNode j_1{ NS::tt, Tag::tt, std::move(d), std::move(e), 3 };
    // constexpr ValidatingNode j_2{ NS::tt, Tag::tt, std::move(d), std::move(e), 3, std::tuple{ NS::tt, Tag::tt, std::move(d), std::move(e), 3 }, std::tuple{ NS::tt, Tag::tt, std::move(d), std::move(e), 3 } };

    REQUIRE(true);
}

TEST_CASE("ValidatingNode Iterator Test", "[ValidatingNode : Iterators]")
{
    using namespace vt::prototype;
    const ValidatingNode vn_1{ NS::tt, ValueExpression::alpha, "node_1", 1, 2, NS::tt, ValueExpression::alpha, "node_1", 1, 2 };

    // for (auto e : vn_1)
    // {
    //     std::cout << "Hello\n";
    // }
}