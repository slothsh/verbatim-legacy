// Stefan "SoulXP" Olivier
// File: node_tt_head.hpp
// Description: TTML dictionary entry for tt:head tag

#ifndef VTVALUEEXPR_HEADER
#define VTVALUEEXPR_HEADER

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "../config.hpp"
#endif

// Project headers
#include "../node.hpp"

// CreateAttributeNode Templates ------------------------------------------------------------------------------------- 1 of 1 -|
// ============================================================================================================================|

namespace vt::dictionary::detail
{
    using namespace magic_enum::bitwise_operators;

    template<class Tns = NS, class Tvexpr = ValueExpression> // TODO: Concept for XMLNodeTree
    constexpr inline auto CreateValueExpressionNode(Tns&& ns, Tvexpr&& vexpr,
                                                    std::string_view&& value = "",
                                                    size_t&& quantifier = 0,
                                                    size_t&& documents = magic_enum::enum_integer(constants::TTMLDocument::w3c_ttml1|constants::TTMLDocument::w3c_ttml2|constants::TTMLDocument::w3c_ttml3|constants::TTMLDocument::ebu_ttml1|constants::TTMLDocument::smpte_ttml1))
    {   
        using vexpression_t         = ValueExpressionNode<NS, ValueExpression>;
        return vexpression_t{ std::move(ns), std::move(vexpr), std::move(value), std::move(quantifier), std::move(documents) };
    }
}

#endif // VTVALUEEXPR_HEADER