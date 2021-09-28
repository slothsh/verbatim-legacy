// Stefan "SoulXP" Olivier
// File: validatettml.cpp
// Description: Prototype code for building a TTML tree for run time structure validation

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "../../include/config.hpp"
#endif

// Standard headers
#include <iostream>
#include <concepts>
#include <type_traits>

// Third-party headers

// Project headers
#include "../../include/prototype/validatettml.hpp"

// TTML dictionary helpers ---------------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

template<class>
struct is_tuple : std::false_type
{};

template<class... Ts>
struct is_tuple<std::tuple<Ts...>> : std::true_type
{};

template<class T>
concept tuple_c = is_tuple<std::decay_t<T>>::value;



// ------------------------------------------------------------|END|-----------------------------------------------------------|

int main(int argc, char** argv)
{
	using namespace vt::prototype;

    static_assert(MAGIC_ENUM_RANGE_MIN == 0);
    static_assert(MAGIC_ENUM_RANGE_MAX == 256);

    static_assert(mge::enum_integer(NS::none) == MAGIC_ENUM_RANGE_MAX);
    static_assert(mge::enum_integer(Tag::none) == MAGIC_ENUM_RANGE_MAX);
    static_assert(mge::enum_integer(Attribute::none) == MAGIC_ENUM_RANGE_MAX);
    static_assert(mge::enum_integer(ValueExpression::none) == MAGIC_ENUM_RANGE_MAX);
    static_assert(mge::enum_integer(GenericData::none) == MAGIC_ENUM_RANGE_MAX);

    static_assert(mge::enum_integer(NS::IS_NS) == MAGIC_ENUM_RANGE_MIN);
    static_assert(mge::enum_integer(Tag::IS_TAG) == MAGIC_ENUM_RANGE_MIN);
    static_assert(mge::enum_integer(Attribute::IS_ATTRIBUTE) == MAGIC_ENUM_RANGE_MIN);
    static_assert(mge::enum_integer(ValueExpression::IS_VALUE_EXPRESSION) == MAGIC_ENUM_RANGE_MIN);
    static_assert(mge::enum_integer(GenericData::IS_DATA) == MAGIC_ENUM_RANGE_MIN);

    constexpr std::tuple a{ 1, 2, 3, 4 };
    // constexpr ValueExpressionNode b{ NS::tt, ValueExpression::alpha, "hello", 0, 1, ValueExpressionNode{ NS::tt, ValueExpression::alpha, "bye", 0, 1 } };
    ValueExpressionNode b{ NS::tt, ValueExpression::alpha, std::string_view{"hello"}, 0, 1, NS::tt, ValueExpression::alpha, std::string_view{"hello"}, 0, 1, NS::tt, ValueExpression::alpha, std::string_view{"hello"}, 0, 1 };

    std::cout << "\nend\n";
    return 0;
}