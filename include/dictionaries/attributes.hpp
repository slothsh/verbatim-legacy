// Stefan "SoulXP" Olivier
// File: node_tt_head.hpp
// Description: TTML dictionary entry for tt:head tag

#ifndef VTNODEATTR_HEADER
#define VTNODEATTR_HEADER

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
    // Base template type
    template<NS Tns = NS::none, Attribute Tattr = Attribute::none>
    constexpr inline auto CreateAttributeNode() { static_assert(Tns != NS::none && Tattr != Attribute::none, "Invalid AttributeNode type\n"); }


    // [ttp:cellResolution]  ------------------------------------------------------ Specialization -|
    template<>
    constexpr inline auto CreateAttributeNode<NS::ttp, Attribute::cellResolution>()
    {
        using namespace magic_enum::bitwise_operators;
        using magic_enum::enum_integer;

        using attroption_t          = AttributeOptionsNode<NS, AttributeOption>;
        using vexpression_t         = ValueExpressionNode<NS, ValueExpression>;
        using content_data_t        = ContentNode<NS, GenericData>;
        using content_tag_t         = ContentNode<NS, Tag>;

        using grp = constants::ByteGroup;
        using doc = constants::TTMLDocument;
        using cnd = constants::NodeCondition;
        using qty = constants::NodeQuantifier;

        // [ttp:cellResolution] ------------------------------------------------ Value expressions -|

        using vexpr_ttp_cellResolution_t                                   = XMLNodeTree<vexpression_t>;
        constexpr vexpr_ttp_cellResolution_t vexpr_ttp_cellResolution
        = detail::CreateValueExpressionNode<vexpression_t>
        ({ 
            {{ NS::none,          ValueExpression::digit,        ":32 15|<digit>+!pred:ne=0; <digit>+!pred:ne=0;",        0,           enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        // -----------------------------------------------------------------------------------------|



        // [ttp:cellResolution] ------------------------------------------------ Attribute Options -|
        
        using attropt_ttp_cellResolution_t                                  = XMLNodeTree<attroption_t>;
        constexpr attropt_ttp_cellResolution_t attropt_ttp_cellResolution
        = detail::CreateValueExpressionNode<attroption_t>
        ({ 
            {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        // -----------------------------------------------------------------------------------------|



        // [ttp:cellResolution] --------------------------------------------------- Attribute Node -|

        using attr_ttp_cellResolution_t = AttributeNode<NS, Attribute, vexpr_ttp_cellResolution_t, attropt_ttp_cellResolution_t>;
        attr_ttp_cellResolution_t attr_ttp_cellResolution {
            enum_integer(cnd::none),
            enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two),
            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1),
            NS::ttp, Attribute::cellResolution,
            vexpr_ttp_cellResolution, attropt_ttp_cellResolution
        };

        // -----------------------------------------------------------------------------------------|

        return attr_ttp_cellResolution;
    }
}

#endif // VTNODEATTR_HEADER