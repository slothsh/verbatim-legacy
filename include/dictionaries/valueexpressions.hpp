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
    constexpr inline auto CreateValueExpressionNode(const Tns&& ns, const Tvexpr&& vexpr,
                                                    const std::string_view&& value = "",
                                                    const size_t&& condition = magic_enum::enum_integer(constants::NodeCondition::none),
                                                    const size_t&& documents = magic_enum::enum_integer(constants::TTMLDocument::w3c_ttml1|constants::TTMLDocument::w3c_ttml2|constants::TTMLDocument::w3c_ttml3|constants::TTMLDocument::ebu_ttml1|constants::TTMLDocument::smpte_ttml1))
    {   
        using ns_t                  = decltype(ns);
        using element_t             = decltype(vexpr);
        using value_t               = decltype(value);
        using document_t            = decltype(documents);
        using condition_t           = decltype(condition);
        using vexpression_t         = ValueExpressionNode<NS, ValueExpression>;

        return vexpression_t{ 
            std::forward<ns_t>(ns),
            std::forward<element_t>(vexpr),
            std::forward<value_t>(value),
            std::forward<condition_t>(condition),
            std::forward<document_t>(documents)
        };
    }
}

#endif // VTVALUEEXPR_HEADER