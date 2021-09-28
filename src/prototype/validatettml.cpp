// Stefan "SoulXP" Olivier
// File: validatettml.cpp
// Description: Prototype code for building a TTML tree for run time structure validation

// Standard headers
#include <iostream>

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "../../include/config.hpp"
#endif

// Project headers
#include "../../include/dictionarynodes.hpp"
#include "../../include/ttml1dictionary.hpp"

int main(int argc, char** argv)
{
	using namespace vt::dictionary;

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

    TTMLDictionary ttml_dictionary;
    std::cout << "Total bytes: " << sizeof(ttml_dictionary.entries) << " bytes" << '\n';
    std::cout << "Total entries: " << ttml_dictionary.size << '\n';

    // const auto find = vt::dictionary::FindTTMLDictionaryNode(std::pair{ NS::tt, Tag::div });
    // if (find) std::cout << "div found!";
    // else std::cout << "div NOT found!";

    // const auto index = ttml_dictionary.GetIndex(1);

    std::cout << "\nend\n";
    return 0;
}