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
#include <variant>
#include <string_view>

// Project headers
#include "../../include/prototype/tupleaccess.hpp"
#include "../../include/dictionarynodes.hpp"
#include "../../include/ttml1dictionary.hpp"

int main()
{
    using namespace vt::prototype;
    using namespace vt::dictionary;

    constexpr std::tuple vexpr_xml_id {
        ValueExpressionNode { NS::none,       ValueExpression::id,               "<id>",                         0,                         0 }
    };

    constexpr std::tuple vexpr_xml_space {
        ValueExpressionNode { NS::none,       ValueExpression::language,         "<language>",                   0,                         0 }
    };

    constexpr std::tuple content_tt_tt = std::tuple_cat (
        std::tuple {
            ContentNode   { 0,               0,                NS::tt,             Tag::head                                             },
            ContentNode   { 0,               0,                NS::tt,             Tag::body                                             }
        }
    );

    constexpr std::tuple attrgrp_tt_tt = std::tuple_cat (
        std::tuple {
            AttributeNode   { 0,         0,         0,           std::tuple{ NS::xml, Attribute::id },            vexpr_xml_id                           },
            AttributeNode   { 0,         0,         0,           std::tuple{ NS::xml, Attribute::space },         vexpr_xml_space                        }
        }
    );

    // <ttm:title/>
    constexpr std::tuple attrgrp_ttm_title = std::tuple_cat (
        std::tuple {
            AttributeNode   { 0,         0,         0,           std::tuple{ NS::xml, Attribute::id },            vexpr_xml_id                           }
        }
    );

    std::tuple dictionary {
        DictionaryNode { 1,              NS::tt,             Tag::tt,                  attrgrp_tt_tt,                content_tt_tt       }
    };

    // using type0_t = std::tuple_element_t<0, decltype(dictionary)>;
    // using type1_t = std::tuple_element_t<1, decltype(dictionary)>;

    TTMLDictionary ttml_dictionary;
    using type0_t = std::tuple_element_t<0, decltype(ttml_dictionary.entries)>;
    using type1_t = std::tuple_element_t<1, decltype(ttml_dictionary.entries)>;
    using type2_t = std::tuple_element_t<2, decltype(ttml_dictionary.entries)>;
    using type3_t = std::tuple_element_t<3, decltype(ttml_dictionary.entries)>;
    using type4_t = std::tuple_element_t<4, decltype(ttml_dictionary.entries)>;
    using type5_t = std::tuple_element_t<5, decltype(ttml_dictionary.entries)>;
    using type6_t = std::tuple_element_t<6, decltype(ttml_dictionary.entries)>;
    using type7_t = std::tuple_element_t<7, decltype(ttml_dictionary.entries)>;
    using type8_t = std::tuple_element_t<8, decltype(ttml_dictionary.entries)>;
    using type9_t = std::tuple_element_t<9, decltype(ttml_dictionary.entries)>;
    using type10_t = std::tuple_element_t<10, decltype(ttml_dictionary.entries)>;
    using type11_t = std::tuple_element_t<11, decltype(ttml_dictionary.entries)>;
    using type12_t = std::tuple_element_t<12, decltype(ttml_dictionary.entries)>;
    using type13_t = std::tuple_element_t<13, decltype(ttml_dictionary.entries)>;
    using type14_t = std::tuple_element_t<14, decltype(ttml_dictionary.entries)>;
    using type15_t = std::tuple_element_t<15, decltype(ttml_dictionary.entries)>;
    using type16_t = std::tuple_element_t<16, decltype(ttml_dictionary.entries)>;
    using type17_t = std::tuple_element_t<17, decltype(ttml_dictionary.entries)>;

    // using type1_t = std::tuple_element_t<0, decltype(std::get<0>(ttml_dictionary.entries).attributes)>;
    // const auto print_attributes = overload_unref { 
    //     [](const type1_t& node) { std::cout << "Value Expressions: " << node.condition << '\n'; }
    // };

    const auto print_dictionary = overload_unref {
        [](const type0_t& node) { std::cout << "Entry 1\n";  },
        [](const type1_t& node) { std::cout << "Entry 2\n";  }
        // [](const type1_t& node) { std::cout << "Documents 2: " << node.documents << '\n'; }
        // [](const type2_t& node) { std::cout << "Documents: " << node.documents << '\n'; },
        // [](const type3_t& node) { std::cout << "Documents: " << node.documents << '\n'; },
        // [](const type4_t& node) { std::cout << "Documents: " << node.documents << '\n'; },
        // [](const type5_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
        // [](const type6_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
        // [](const type7_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
        // [](const type8_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
        // [](const type9_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
        // [](const type10_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
        // [](const type11_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
        // [](const type12_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
        // [](const type13_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
        // [](const type14_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
        // [](const type15_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
        // [](const type16_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
        // [](const type17_t& node) { std::cout << "Conditions: " << node.documents << '\n'; }
        // [](const type18_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
        // [](const type19_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
        // [](const type20_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
        // [](const type21_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
        // [](const type22_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
        // [](const type23_t& node) { std::cout << "Conditions: " << node.documents << '\n'; }
    };

    // const auto print_dictionary = overload_unref (
    //     [](const type0_t& node) { std::cout << "Documents 1: " << node.documents << '\n'; },
    //     [](const type0_t& node) { std::cout << "Documents 2: " << node.documents << '\n'; }
    // );

    // for (const auto& e : to_range(ttml_dictionary.entries)) {
    //     // std::visit(print_dictionary, e);
    //     // std::cout << "Documents: " << std::get<0>(std::get<0>(e).get() << '\n'; 
    //     // std::cout << "Hello World\n";
    // }
    
    // TTMLDictionary ttml_dictionary;

    // using type0_t = std::tuple_element_t<0, decltype(ttml_dictionary.entries)>;
    // using type1_t = std::tuple_element_t<1, decltype(ttml_dictionary.entries)>;
    // using type2_t = std::tuple_element_t<2, decltype(ttml_dictionary.entries)>;
    // using type3_t = std::tuple_element_t<3, decltype(ttml_dictionary.entries)>;
    // using type4_t = std::tuple_element_t<4, decltype(ttml_dictionary.entries)>;
    // // using type5_t = std::tuple_element_t<5, decltype(ttml_dictionary.entries)>;
    // // using type6_t = std::tuple_element_t<6, decltype(ttml_dictionary.entries)>;
    // // using type7_t = std::tuple_element_t<7, decltype(ttml_dictionary.entries)>;
    // // using type8_t = std::tuple_element_t<8, decltype(ttml_dictionary.entries)>;
    // // using type9_t = std::tuple_element_t<9, decltype(ttml_dictionary.entries)>;
    // // using type10_t = std::tuple_element_t<10, decltype(ttml_dictionary.entries)>;
    // // using type11_t = std::tuple_element_t<11, decltype(ttml_dictionary.entries)>;
    // // using type12_t = std::tuple_element_t<12, decltype(ttml_dictionary.entries)>;
    // // using type13_t = std::tuple_element_t<13, decltype(ttml_dictionary.entries)>;
    // // using type14_t = std::tuple_element_t<14, decltype(ttml_dictionary.entries)>;
    // // using type15_t = std::tuple_element_t<15, decltype(ttml_dictionary.entries)>;
    // // using type16_t = std::tuple_element_t<16, decltype(ttml_dictionary.entries)>;
    // // using type17_t = std::tuple_element_t<17, decltype(ttml_dictionary.entries)>;
    // // using type18_t = std::tuple_element_t<18, decltype(ttml_dictionary.entries)>;
    // // using type19_t = std::tuple_element_t<19, decltype(ttml_dictionary.entries)>;
    // // using type20_t = std::tuple_element_t<20, decltype(ttml_dictionary.entries)>;
    // // using type21_t = std::tuple_element_t<21, decltype(ttml_dictionary.entries)>;
    // // using type22_t = std::tuple_element_t<22, decltype(ttml_dictionary.entries)>;
    // // using type23_t = std::tuple_element_t<23, decltype(ttml_dictionary.entries)>;

    // const auto print_dictionary = overload_unref {
    //     [](const type0_t& node) { std::cout << "Documents: " << node.documents << '\n'; },
    //     [](const type1_t& node) { std::cout << "Documents: " << node.documents << '\n'; },
    //     [](const type2_t& node) { std::cout << "Documents: " << node.documents << '\n'; },
    //     [](const type3_t& node) { std::cout << "Documents: " << node.documents << '\n'; },
    //     [](const type4_t& node) { std::cout << "Documents: " << node.documents << '\n'; }/*,
    //     [](const type5_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
    //     [](const type6_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
    //     [](const type7_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
    //     [](const type8_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
    //     [](const type9_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
    //     [](const type10_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
    //     [](const type11_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
    //     [](const type12_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
    //     [](const type13_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
    //     [](const type14_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
    //     [](const type15_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
    //     [](const type16_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
    //     [](const type17_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
    //     [](const type18_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
    //     [](const type19_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
    //     [](const type20_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
    //     [](const type21_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
    //     [](const type22_t& node) { std::cout << "Conditions: " << node.documents << '\n'; },
    //     [](const type23_t& node) { std::cout << "Conditions: " << node.documents << '\n'; } */
    // };

    // for (const auto e : to_range(ttml_dictionary.entries)) {
    //     // std::visit(print_dictionary, e);
    //     // std::cout << "Hello World!\n";
    // }

    std::tuple tup{ 42, std::tuple{ 1, 2, 3 }, 3.14 };
    auto print_elem = overload_unref (
        [](const int& i) { std::cout << "int: " << i << '\n'; },
        [](const std::tuple<int, int, int>& s) { 
            std::cout << "\tValue: " << std::get<0>(s) << '\n';
            std::cout << "\tValue: " << std::get<1>(s) << '\n';
            std::cout << "\tValue: " << std::get<2>(s) << '\n';
         },
        [](const double& d) { std::cout << "double: " << d << '\n'; }
    );

    for (auto const& elem : to_range(tup)) { 
        std::visit(print_elem, elem);
    }

    return 0;
}