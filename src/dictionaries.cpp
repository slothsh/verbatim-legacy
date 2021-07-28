// Stefan "SoulXP" Olivier
// File: dictionaries.cpp
// Description: External linkage header for various tables & dictionaries

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "../include/config.hpp"
#endif

// Standard headers
#include <iostream>
#include <type_traits>
#include <utility>
#include <concepts>

// Project headers
#include "../include/node.hpp"
#include "../include/dictionaries.hpp"

using namespace vt::dictionary;
using namespace magic_enum;

// constexpr inline auto vt::dictionary::MakeTTMLNodes()
// {
//     // Make attributes for prototype enumerations
//     comp_attribute_t<NS, Attribute> proto_attr1;
//     using vexpr_t = detail::vexpression_t<NS, ValueExpression>;
//     constexpr vexpr_t proto_vexpr1{ NS::one, ValueExpression::one , 0};
//     constexpr vexpr_t proto_vexpr2{ NS::one, ValueExpression::two, 0};
//     constexpr vexpr_t proto_vexpr3{ NS::one, ValueExpression::four, 0};

//     using attropt_t = detail::attroption_t<NS, AttributeOption>;
//     constexpr attropt_t proto_attropt1{ { NS::two, AttributeOption::one }, "Hello", 0};
//     constexpr attropt_t proto_attropt2{ { NS::two, AttributeOption::two }, "World", 0};
//     constexpr attropt_t proto_attropt3{ { NS::two, AttributeOption::four }, "Bye", 0};

//     using content_t = detail::content_t<NS, Content>;
//     constexpr content_t proto_data1{ { NS::three, Content::one }, 0, 0};
//     constexpr content_t proto_data2{ { NS::three, Content::two }, 0, 0};
//     constexpr content_t proto_data3{ { NS::three, Content::four }, 0, 0};


//     return detail::EntryCollector<vexpr_t, vexpr_t, vexpr_t>
//         (
//             std::move(proto_vexpr1),
//             std::move(proto_vexpr2),
//             std::move(proto_vexpr3)
//         );
// }