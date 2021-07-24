// Stefan "SoulXP" Olivier
// File: ttmldictionary.cpp
// Description: Prototype code for TTML dictionary templates

// Standard headers
#include <iostream>

// Project headers
#include "../../include/node.hpp"

int main()
{
	using namespace vt::dictionary;
	
    constexpr XMLNode<NS, Tag, Attribute, ValueExpression, AttributeOption, Content,
            1, 1, 1, 1> a{};
    constexpr XMLNode<NS, Tag, Attribute, ValueExpression, AttributeOption, Content,
            2, 2, 2, 2> b{};
    constexpr XMLNode<NS, Tag, Attribute, ValueExpression, AttributeOption, Content,
            3, 3, 3, 3> c{};
    constexpr XMLNode<NS, Tag, Attribute, ValueExpression, AttributeOption, Content,
            4, 4, 4, 4> d{};
    constexpr XMLNode<NS, Tag, Attribute, ValueExpression, AttributeOption, Content,
            5, 5, 5, 5> e{};

    // constexpr XMLDictionary<decltype(a), decltype(b), decltype(c)> dict{};
    // const XMLDictionary<decltype(a), decltype(b), decltype(c), decltype(d)> dict(a,b,c,d);
    constexpr XMLDictionary<decltype(a), decltype(b), decltype(c), decltype(d)> dict(a,b,c,d);
    dict.get<1>();
    dict.get<2>();
    dict.get<3>();

    std::cout << "end\n";
    return 0;
}