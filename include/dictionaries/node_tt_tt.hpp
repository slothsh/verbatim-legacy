// Stefan "SoulXP" Olivier
// File: node_tt_tt.hpp
// Description: TTML dictionary entry for tt:tt tag

#ifndef VTNODEENTRY_TT_TT_HEADER
#define VTNODEENTRY_TT_TT_HEADER

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "../config.hpp"
#endif

// Project headers
#include "../node.hpp"
#include "attributes.hpp"

// Node tt:tt Entry -------------------------------------------------------------------------------------------------- 1 of 1 -|
// ============================================================================================================================|

namespace vt::dictionary::detail
{
    template<>
    constexpr inline auto CreateTTMLNode<NS::tt, Tag::tt>()
    {
        // ---------------------------------------------------------------------------------------------------|
        // Legend                                                                                             |
        //                                                                                                    |
        // Tags:        <ns:tag/>                [nsentry:entry]                                              |
        // Naming:      type_nstag_tag_nsentry_entry(_t | _init)                                              |
        //                                                                                                    |
        // ---------------------------------------------------------------------------------------------------|

        // SECTION: <tt:tt/> ---------------------------------------------------------------------------------|
        // ===================================================================================================|

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

        // <tt:tt/> [tts:extent] ----------------------------------------------- Value expressions -|

        using vexpr_tt_tt_tts_extent_t                                  = XMLNodeTree<vexpression_t>;
        
        constexpr vexpr_tt_tt_tts_extent_t vexpr_tt_tt_tts_extent
        = detail::CreateValueExpressionNode<vexpression_t>
        ({
            {{ NS::none,          ValueExpression::string,        ":<auto>|<length> <length>",        0,         enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> [tts:extent] ----------------------------------------------- Attribute Options -|
        
        using attropt_tt_tt_tts_extent_t                                 = XMLNodeTree<attroption_t>;

        constexpr attropt_tt_tt_tts_extent_t attropt_tt_tt_tts_extent
        = detail::CreateValueExpressionNode<attroption_t>
        ({ 
            {{ NS::tt,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> [tts:extent] -------------------------------------------------- Attribute Node -|

        using attr_tt_tt_tts_extent_t
                = AttributeNode<NS, Attribute, vexpr_tt_tt_tts_extent_t, attropt_tt_tt_tts_extent_t>;

        attr_tt_tt_tts_extent_t attr_tt_tt_tts_extent {
            enum_integer(cnd::none),
            enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two),
            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1),
            NS::tts, Attribute::extent,
            vexpr_tt_tt_tts_extent, attropt_tt_tt_tts_extent
        };

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> [xml:id] --------------------------------------------------- Value expressions -|

        using vexpr_tt_tt_xml_id_t                                      = XMLNodeTree<vexpression_t>;
        constexpr vexpr_tt_tt_xml_id_t vexpr_tt_tt_xml_id
        = detail::CreateValueExpressionNode<vexpression_t> 
        ({ 
            {{ NS::none,          ValueExpression::string,        "<id>",        0,                             enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }},
        });

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> [xml:id] --------------------------------------------------- Attribute Options -|
        
        using attropt_tt_tt_xml_id_t                                     = XMLNodeTree<attroption_t>;
        constexpr attropt_tt_tt_xml_id_t attropt_tt_tt_xml_id
        = detail::CreateValueExpressionNode<attroption_t>
        ({ 
            {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> [xml:id] ------------------------------------------------------ Attribute Node -|

        using attr_tt_tt_xml_id_t
                        = AttributeNode<NS, Attribute, vexpr_tt_tt_xml_id_t, attropt_tt_tt_xml_id_t>;

        attr_tt_tt_xml_id_t attr_tt_tt_xml_id {
            enum_integer(cnd::none),
            enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two),
            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1),
            NS::xml, Attribute::id,
            vexpr_tt_tt_xml_id, attropt_tt_tt_xml_id
        };

        // -----------------------------------------------------------------------------------------|


        // <tt:tt/> [xml:lang] ------------------------------------------------- Value expressions -|

        using vexpr_tt_tt_xml_lang_t                                    = XMLNodeTree<vexpression_t>;
        constexpr vexpr_tt_tt_xml_lang_t vexpr_tt_tt_xml_lang
        = detail::CreateValueExpressionNode<vexpression_t> 
        ({ 
            {{ NS::none,          ValueExpression::string,        "<language>",        0,           enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> [xml:lang] ------------------------------------------------- Attribute Options -|
        
        using attropt_tt_tt_xml_lang_t                                   = XMLNodeTree<attroption_t>;
        constexpr attropt_tt_tt_xml_lang_t attropt_tt_tt_xml_lang
        = detail::CreateValueExpressionNode<attroption_t>
        ({ 
            {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> [xml:lang] ---------------------------------------------------- Attribute Node -|

        using attr_tt_tt_xml_lang_t = AttributeNode<NS, Attribute, vexpr_tt_tt_xml_lang_t, attropt_tt_tt_xml_lang_t>;
        attr_tt_tt_xml_lang_t attr_tt_tt_xml_lang {
            enum_integer(cnd::required),
            enum_integer(qty::kleene_one) | (0 << grp::one) | (0 << grp::two),
            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1),
            NS::xml, Attribute::lang,
            vexpr_tt_tt_xml_lang, attropt_tt_tt_xml_lang
        };

        // -----------------------------------------------------------------------------------------|


        // <tt:tt/> [xml:space] ------------------------------------------------ Value expressions -|

        using vexpr_tt_tt_xml_space_t                                   = XMLNodeTree<vexpression_t>;
        constexpr vexpr_tt_tt_xml_space_t vexpr_tt_tt_xml_space
        = detail::CreateValueExpressionNode<vexpression_t> 
        ({ 
            {{ NS::none,          ValueExpression::string_option,        ":default|preserve",        0,           enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> [xml:space] ------------------------------------------------ Attribute Options -|
        
        using attropt_tt_tt_xml_space_t                                  = XMLNodeTree<attroption_t>;
        constexpr attropt_tt_tt_xml_space_t attropt_tt_tt_xml_space
        = detail::CreateValueExpressionNode<attroption_t>
        ({ 
            {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> [xml:space] --------------------------------------------------- Attribute Node -|

        using attr_tt_tt_xml_space_t = AttributeNode<NS, Attribute, vexpr_tt_tt_xml_space_t, attropt_tt_tt_xml_space_t>;
        attr_tt_tt_xml_space_t attr_tt_tt_xml_space {
            enum_integer(cnd::none),
            enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two),
            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1),
            NS::xml, Attribute::space,
            vexpr_tt_tt_xml_space, attropt_tt_tt_xml_space
        };

        // -----------------------------------------------------------------------------------------|


        
        // <tt:tt/> --------------------------------------------------------------- Attribute Tree -|

        using attr_tt_tt_t                = XMLNodeTree<attr_tt_tt_tts_extent_t, attr_tt_tt_xml_id_t,
                                                    attr_tt_tt_xml_lang_t, attr_tt_tt_xml_space_t>;
        attr_tt_tt_t attr_tt_tt
        {
            attr_tt_tt_tts_extent,
            attr_tt_tt_xml_id,
            attr_tt_tt_xml_lang,
            attr_tt_tt_xml_space
        };

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> ----------------------------------------------------------------- Content Node -|

        using content_tt_tt_t            = XMLNodeTree<content_data_t, content_tag_t, content_tag_t>;
        content_tt_tt_t content_tt_tt
        {
            content_data_t( NS::none,         GenericData::PCDATA,    enum_integer(qty::kleene_asterisk) | (0 << grp::one) | (0 << grp::two),          enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1)),
            content_tag_t ( NS::tt,           Tag::head,              enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two),          enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1)),
            content_tag_t ( NS::tt,           Tag::body,              enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two),          enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1))
        };

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> --------------------------------------------------------------------- XML Node -|

        using node_tt_tt_t                         = XMLNode<NS, Tag, attr_tt_tt_t, content_tt_tt_t>;
        node_tt_tt_t node_tt_tt {
            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1),
            NS::tt, Tag::tt,
            attr_tt_tt, content_tt_tt
        };

        // -----------------------------------------------------------------------------------------|


        return node_tt_tt;
    }
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif // VTNODEENTRY_TT_TT_HEADER