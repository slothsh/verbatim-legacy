// Stefan "SoulXP" Olivier
// File: validatettml.cpp
// Description: Test code for building a TTML tree for run time structure validation

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "../../include/config.hpp"
#endif

// Standard headers
#include <iostream>
#include <string>
#include <algorithm>

// Third-party headers

// Project headers
#include "../../include/prototype/validatettml.hpp"

int main(int argc, char** argv)
{
    using namespace vt::prototype;

    constexpr ValidatingNode vn_1 { NS::tt, ValueExpression::alpha, "vn_1_node_1", 1, 2 };

    for (const auto& e : vn_1)
    {
        std::clog << e.value << '\n';
    }

    std::clog << "-------------------------------------------------------\n";
    constexpr ValidatingNode vn_2 {
        NS::tt, ValueExpression::alpha, "vn_2_node_1", 1, 2,
        NS::xml, ValueExpression::alpha, "vn_2_node_2", 1, 2,
        NS::xml, ValueExpression::alpha, "vn_2_node_3", 1, 2,
        NS::xml, ValueExpression::alpha, "vn_2_node_4", 1, 2,
        NS::xml, ValueExpression::alpha, "vn_2_node_5", 1, 2,
        NS::xml, ValueExpression::alpha, "vn_2_node_6", 1, 2,
        NS::xml, ValueExpression::alpha, "vn_2_node_7", 1, 2,
        NS::xml, ValueExpression::alpha, "vn_2_node_8", 1, 2,
        NS::xml, ValueExpression::alpha, "vn_2_node_9", 1, 2,
        NS::xml, ValueExpression::alpha, "vn_2_node_10", 1, 2
    };

    for (const auto& e : vn_2)
    {
        std::clog << e.value << '\n';
    }

    std::clog << "-------------------------------------------------------\n";
    constexpr ValidatingNode vn_3 {
        NS::tt, ValueExpression::alpha, "vn_3_node_1", 1, 2,
        NS::xml, ValueExpression::alpha, "vn_3_node_2", 1, 2,
        NS::xml, ValueExpression::alpha, "vn_3_node_3", 1, 2,
        NS::xml, ValueExpression::alpha, "vn_3_node_4", 1, 2,
        NS::xml, ValueExpression::alpha, "vn_3_node_5", 1, 2
    };

    std::for_each(vn_2.begin(), vn_2.end(), [](const auto& _node) {
        std::clog << _node.value << '\n';
    });

    std::clog << "-------------------------------------------------------\n";
    std::clog << "size of vn_1: " << sizeof(vn_1) << '\n';
    std::clog << "size of vn_2: " << sizeof(vn_2) << '\n';
    std::clog << "size of vn_3: " << sizeof(vn_3) << '\n';
}