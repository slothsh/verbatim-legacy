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
    static_assert(mge::enum_integer(StyleExpression::none) == MAGIC_ENUM_RANGE_MAX);
    static_assert(mge::enum_integer(TimeExpression::none) == MAGIC_ENUM_RANGE_MAX);
    static_assert(mge::enum_integer(AttributeOption::none) == MAGIC_ENUM_RANGE_MAX);
    static_assert(mge::enum_integer(GenericData::none) == MAGIC_ENUM_RANGE_MAX);

    static_assert(mge::enum_integer(NS::IS_NS) == MAGIC_ENUM_RANGE_MIN);
    static_assert(mge::enum_integer(Tag::IS_TAG) == MAGIC_ENUM_RANGE_MIN);
    static_assert(mge::enum_integer(Attribute::IS_ATTRIBUTE) == MAGIC_ENUM_RANGE_MIN);
    static_assert(mge::enum_integer(StyleExpression::IS_VALUE_EXPRESSION) == MAGIC_ENUM_RANGE_MIN);
    static_assert(mge::enum_integer(TimeExpression::IS_VALUE_EXPRESSION) == MAGIC_ENUM_RANGE_MIN);
    static_assert(mge::enum_integer(AttributeOption::IS_ATTRIBUTE_OPTION) == MAGIC_ENUM_RANGE_MIN);
    static_assert(mge::enum_integer(GenericData::IS_DATA) == MAGIC_ENUM_RANGE_MIN);

    using attroption_t = AttributeOptionsNode<NS, AttributeOption>;
    using vexpression_t = ValueExpressionNode<NS, StyleExpression>;
    using content_data_t = ContentNode<NS, GenericData>;
    using content_tag_t = ContentNode<NS, Tag>;

    // Value expressions
    using vexpr_1_t = XMLNodeTree<vexpression_t, vexpression_t, vexpression_t, vexpression_t>;
    vexpr_1_t vexpr1 {
        vexpression_t(NS::tt, StyleExpression::digit, 0),
        vexpression_t(NS::tt, StyleExpression::digit, 0),
        vexpression_t(NS::tt, StyleExpression::digit, 0),
        vexpression_t(NS::tt, StyleExpression::digit, 0)
    };

    // Attribute options
    using attropts_1_t = XMLNodeTree<attroption_t, attroption_t, attroption_t, attroption_t>;
    attropts_1_t attropts1 {
        attroption_t(NS::tt, AttributeOption::one, "Value", 0),
        attroption_t(NS::tt, AttributeOption::one, "Value", 0),
        attroption_t(NS::tt, AttributeOption::one, "Value", 0),
        attroption_t(NS::tt, AttributeOption::one, "Value", 0)
    };

    // Attribute
    using attribute_1_t = AttributeNode<NS, Attribute, vexpr_1_t, attropts_1_t>;
    attribute_1_t attribute_1 {
        0, 0, 0,
        NS::tt, Attribute::display,
        vexpr1, attropts1
    };

    // Content
    using content_1_t = XMLNodeTree<content_data_t, content_tag_t>;
    content_1_t content_1 {
        content_data_t(NS::tt, GenericData::PCDATA, 0, 0),
        content_tag_t(NS::tt, Tag::div, 0, 0)
    };

    // Node
    using node_1_t = XMLNode<NS, Tag, attribute_1_t, content_1_t>;
    node_1_t node_1 {
        0,
        NS::tt, Tag::div,
        attribute_1, content_1
    };

    XMLDictionary
        <node_1_t>
    dictionary (
        node_1
    );

    std::cout << "\nend\n";
    return 0;
}