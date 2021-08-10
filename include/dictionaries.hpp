// Stefan "SoulXP" Olivier
// File: dictionaries.hpp
// Description: Definitions for various tables and dictionaries

#ifndef VTDICTIONARIES_HEADER
#define VTDICTIONARIES_HEADER

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "config.hpp"
#endif

// Standard headers
#include <iostream>
#include <type_traits>
#include <utility>
#include <concepts>

// Project headers
#include "node.hpp"
#include "functor.hpp"
#include "./dictionaries/nodes.hpp"
#include "./dictionaries/attributes.hpp"

// Master TTML definition function ----------------------------------------------------------------------------------- 1 of 1 -|
// ============================================================================================================================|

namespace vt::dictionary
{
    static constexpr auto CreateTTMLDictionary()
    {
        using namespace magic_enum::bitwise_operators;
        using namespace vt::functional;
        using magic_enum::enum_integer;

        using grp = constants::ByteGroup;
        using doc = constants::TTMLDocument;
        using cnd = constants::NodeCondition;
        using qty = constants::NodeQuantifier;

        constexpr size_t default_vexpr_condition    = enum_integer(cnd::none);
        constexpr size_t default_vexpr_quantifier   = enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two);
        constexpr size_t default_vexpr_document     = enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1);
        constexpr size_t default_node_document      = enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1);

        constexpr std::tuple attr_xml_id{ NS::xml, Attribute::id };
        constexpr std::tuple flags{ default_vexpr_condition, default_vexpr_quantifier, default_vexpr_document };
        constexpr std::tuple value_expressions { 
            std::tuple { NS::tt, ValueExpression::string, "<string1>", 0, 0 },
            std::tuple { NS::tt, ValueExpression::string, "<string2>", 0, 0 },
            std::tuple { NS::tt, ValueExpression::string, "<string3>", 0, 0 }
        };

        constexpr auto fnc_tt_tt_attribute = []
        <class Telem, class Ttup, class Tflags, size_t Stup = std::tuple_size_v<Ttup>>
        (const Telem&& element, const Ttup&& value_expressions, const Tflags&& flags) {
            using vexpr_t = decltype(value_expressions);
            using flags_t = decltype(flags);

            return std::tuple {
                detail::CreateAttributeNode(
                    std::move(std::get<0>(element)),
                    std::move(std::get<1>(element)),
                    std::forward<flags_t>(flags),
                    std::forward<vexpr_t>(value_expressions),
                    std::make_index_sequence<Stup>{}
                )
            };
        };

        constexpr auto fnc_tt_tt_content = []() { return 1; };

        constexpr std::tuple nodes {
            std::tuple{ std::move(default_node_document), NS::tt, Tag::tt, attr_xml_id, value_expressions, flags, VTFunctor{std::move(fnc_tt_tt_attribute)}, VTFunctor{std::move(fnc_tt_tt_content)} },
            std::tuple{ std::move(default_node_document), NS::tt, Tag::tt, attr_xml_id, value_expressions, flags, VTFunctor{std::move(fnc_tt_tt_attribute)}, VTFunctor{std::move(fnc_tt_tt_content)} }
        };

        return detail::CreateTTMLNodes(std::move(nodes), std::make_index_sequence<std::tuple_size_v<decltype(nodes)>>{});
    }
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif // VTDICTIONARIES_HEADER