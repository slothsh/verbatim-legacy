// Stefan "SoulXP" Olivier
// File: node_tt_head.hpp
// Description: TTML dictionary entry for tt:head tag

#ifndef VTNODEATTR_HEADER
#define VTNODEATTR_HEADER

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "../config.hpp"
#endif

// Standard headars
#include <tuple>

// Project headers
#include "../node.hpp"
#include "valueexpressions.hpp"

// Base Template for CreateAttributeNode ----------------------------------------------------------------------------- 1 of 1 -|
// ============================================================================================================================|

namespace vt::dictionary::detail
{
    using namespace magic_enum::bitwise_operators;
    using magic_enum::enum_integer;

    using vexpression_t         = ValueExpressionNode<NS, ValueExpression>;
    using content_data_t        = ContentNode<NS, GenericData>;
    using content_tag_t         = ContentNode<NS, Tag>;

    using grp = constants::ByteGroup;
    using doc = constants::TTMLDocument;
    using cnd = constants::NodeCondition;
    using qty = constants::NodeQuantifier;

    // Base template type
    template<class Tns = NS, class Tattr = Attribute, class Tflag, class Tvexpr, class S, S... Sseq>
    constexpr inline auto CreateAttributeNode(Tns&& ns, Tattr&& attribute, Tflag&& flags,
                                                Tvexpr&& vexprs, std::integer_sequence<S, Sseq...> sequence)
    {
        // static_assert(Vns != NS::none && Vattr != Attribute::none, "Invalid AttributeNode type\n");

        std::tuple value_expressions {
            CreateValueExpressionNode(
                std::forward<decltype(std::get<0>(std::get<Sseq>(vexprs)))>(std::get<0>(std::get<Sseq>(vexprs))),
                std::forward<decltype(std::get<1>(std::get<Sseq>(vexprs)))>(std::get<1>(std::get<Sseq>(vexprs))),
                std::forward<decltype(std::get<2>(std::get<Sseq>(vexprs)))>(std::get<2>(std::get<Sseq>(vexprs))),
                std::forward<decltype(std::get<3>(std::get<Sseq>(vexprs)))>(std::get<3>(std::get<Sseq>(vexprs))),
                std::forward<decltype(std::get<4>(std::get<Sseq>(vexprs)))>(std::get<4>(std::get<Sseq>(vexprs)))
            )
            ...
        };

        using attributes = AttributeNode<NS, Attribute, decltype(value_expressions)>;

        return attributes {
            std::move(std::get<0>(flags)),
            std::move(std::get<1>(flags)),
            std::move(std::get<2>(flags)),
            std::move(ns), std::move(attribute),
            std::move(value_expressions)
        };
    }
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif // VTNODEATTR_HEADER