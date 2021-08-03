// Stefan "SoulXP" Olivier
// File: ttmldictionary.cpp
// Description: Prototype code for TTML dictionary templates

// Standard headers
#include <iostream>

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "../../include/config.hpp"
#endif

// Project headers
#include "../../include/node.hpp"
#include "../../include/dictionaries.hpp"

int main()
{
	using namespace vt::dictionary;

    // SECTION 1
    // constexpr XMLNode<NS, Tag, NS, Attribute, ValueExpression, AttributeOption, NS, Content,
    //         1, 1, 1, 1> a{};
    // constexpr XMLNode<NS, Tag, Attribute, ValueExpression, AttributeOption, Content,
    //         2, 2, 2, 2> b{};
    // constexpr XMLNode<NS, Tag, Attribute, ValueExpression, AttributeOption, Content,
    //         3, 3, 3, 3> c{};
    // constexpr XMLNode<NS, Tag, Attribute, ValueExpression, AttributeOption, Content,
    //         4, 4, 4, 4> d{};
    // constexpr XMLNode<NS, Tag, Attribute, ValueExpression, AttributeOption, Content,
    //         5, 5, 5, 5> e{};

    // constexpr XMLDictionary<decltype(a), decltype(b), decltype(c)> dict{};
    // const XMLDictionary<decltype(a), decltype(b), decltype(c), decltype(d)> dict(a,b,c,d);
    // constexpr XMLDictionary<decltype(a), decltype(b), decltype(c), decltype(d)> dict(a,b,c,d);
    // dict.get<1>();
    // dict.get<2>();
    // dict.get<3>();

	// std::cout << std::boolalpha << magic_enum::enum_contains<NS>(NS::none) << '\n';

    // SECTION 2
    // vt::dictionary::detail::EntryCollector<size_t, size_t, size_t, size_t> a{1,2,3,4};

    // auto r = a.GetSize();
    // std::cout << "Accumulate total: " << vt::dictionary::detail::accumulate_t::total << '\n';
    // std::cout << "Total entries: " << r << '\n';

    // SECTION 3
    static_assert(MAGIC_ENUM_RANGE_MIN == 0);
    static_assert(MAGIC_ENUM_RANGE_MAX == 256);

    static_assert(mge::enum_integer(NS::none) == MAGIC_ENUM_RANGE_MAX);
    static_assert(mge::enum_integer(Tag::none) == MAGIC_ENUM_RANGE_MAX);
    static_assert(mge::enum_integer(Attribute::none) == MAGIC_ENUM_RANGE_MAX);
    static_assert(mge::enum_integer(ValueExpression::none) == MAGIC_ENUM_RANGE_MAX);
    static_assert(mge::enum_integer(AttributeOption::none) == MAGIC_ENUM_RANGE_MAX);
    static_assert(mge::enum_integer(GenericData::none) == MAGIC_ENUM_RANGE_MAX);

    static_assert(mge::enum_integer(NS::IS_NS) == MAGIC_ENUM_RANGE_MIN);
    static_assert(mge::enum_integer(Tag::IS_TAG) == MAGIC_ENUM_RANGE_MIN);
    static_assert(mge::enum_integer(Attribute::IS_ATTRIBUTE) == MAGIC_ENUM_RANGE_MIN);
    static_assert(mge::enum_integer(ValueExpression::IS_VALUE_EXPRESSION) == MAGIC_ENUM_RANGE_MIN);
    static_assert(mge::enum_integer(AttributeOption::IS_ATTRIBUTE_OPTION) == MAGIC_ENUM_RANGE_MIN);
    static_assert(mge::enum_integer(GenericData::IS_DATA) == MAGIC_ENUM_RANGE_MIN);

    constexpr auto node = CreateTTMLDictionary();

    std::cout << "\nend\n";
    return 0;
}