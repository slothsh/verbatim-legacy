// Stefan "SoulXP" Olivier
// File: tupleaccess.cpp
// Description: Prototype code for accessing tuples at runtime

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "../../include/config.hpp"
#endif

// Standard headers
#include <iostream>
#include <utility>
#include <tuple>
#include <string_view>

// Project headers
#include "../../include/prototype/tupleaccess.hpp"
#include "../../include/dictionarynodes.hpp"
#include "../../include/ttml1dictionary.hpp"

int main()
{
    using namespace vt::prototype;
    using namespace vt::dictionary;
    
    TTMLDictionary ttml_dictionary;
    using type_t = typename std::tuple_element_t<0, TTMLDictionary::dictionary_t>;

    auto& node = std::get<0>(TTMLDictionary::entries);

    auto& node_1 = std::get<0>(TTMLDictionary::entries);

    auto print_dictionary = overload_unref (
        [](const type_t& node) { std::cout << "Conditions: " << node.documents << '\n'; }
    );

    // for (const auto& e : to_range(TTMLDictionary::entries)) {
    //     std::visit(print_dictionary, e);
    // }

    // std::tuple tup{ 42, std::string_view{"foo"}, 3.14 };
    // auto print_elem = overload_unref (
    //     [](int i) { std::cout << "int: " << i << '\n'; },
    //     [](std::string_view const& s) { std::cout << "string_view: " << s << '\n'; },
    //     [](double d) { std::cout << "double: " << d << '\n'; }
    // );

    // for (auto const& elem : to_range(tup)) { 
    //     std::visit(print_elem, elem);
    // }

    return 0;
}