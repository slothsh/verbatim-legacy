// Stefan "SoulXP" Olivier
// File: node_tt_head.hpp
// Description: TTML dictionary entry for tt:head tag

#ifndef VTNODEENTRY_TT_HEAD_HEADER
#define VTNODEENTRY_TT_HEAD_HEADER

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "../config.hpp"
#endif

// Project headers
#include "../node.hpp"

// Node tt:tt Entry -------------------------------------------------------------------------------------------------- 1 of 1 -|
// ============================================================================================================================|

namespace vt
{
    namespace dictionary
    {
        namespace detail
        {
            template<>
            constexpr inline auto CreateTTMLNode<NS::tt, Tag::head>()
            {
                // ---------------------------------------------------------------------------------------------------|
                // Legend                                                                                             |
                //                                                                                                    |
                // Tags:        <ns:tag/>                [nsentry:entry]                                              |
                // Naming:      type_nstag_tag_nsentry_entry(_t | _init)                                              |
                //                                                                                                    |
                // ---------------------------------------------------------------------------------------------------|

                // SECTION: <tt:head/> -------------------------------------------------------------------------------|
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

                // <tt:head/> [xml:id] ------------------------------------------------- Value expressions -|

                using vexpr_tt_head_xml_id_t                                    = XMLNodeTree<vexpression_t>;

                constexpr vexpr_tt_head_xml_id_t vexpr_tt_head_xml_id
                = detail::CreateValueExpressionNode<vexpression_t> 
                ({ 
                    {{ NS::none,          ValueExpression::string,        "<id>",        0,                             enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }},
                });

                // -----------------------------------------------------------------------------------------|



                // <tt:head/> [xml:id] ------------------------------------------------- Attribute Options -|
                
                using attropt_tt_head_xml_id_t                                   = XMLNodeTree<attroption_t>;

                constexpr attropt_tt_head_xml_id_t attropt_tt_head_xml_id
                = detail::CreateValueExpressionNode<attroption_t>
                ({ 
                    {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
                });

                // -----------------------------------------------------------------------------------------|



                // <tt:head/> [xml:id] ---------------------------------------------------- Attribute Node -|

                using attr_tt_head_xml_id_t
                            = AttributeNode<NS, Attribute, vexpr_tt_head_xml_id_t, attropt_tt_head_xml_id_t>;

                attr_tt_head_xml_id_t attr_tt_head_xml_id {
                    enum_integer(cnd::none),
                    enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two),
                    enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1),
                    NS::xml, Attribute::id,
                    vexpr_tt_head_xml_id, attropt_tt_head_xml_id
                };

                // -----------------------------------------------------------------------------------------|


                // <tt:head/> [xml:lang] ----------------------------------------------- Value expressions -|

                using vexpr_tt_head_xml_lang_t                                  = XMLNodeTree<vexpression_t>;

                constexpr vexpr_tt_head_xml_lang_t vexpr_tt_head_xml_lang
                = detail::CreateValueExpressionNode<vexpression_t> 
                ({ 
                    {{ NS::none,          ValueExpression::string,        "<language>",        0,           enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
                });

                // -----------------------------------------------------------------------------------------|



                // <tt:head/> [xml:lang] ----------------------------------------------- Attribute Options -|
                
                using attropt_tt_head_xml_lang_t                                 = XMLNodeTree<attroption_t>;

                constexpr attropt_tt_head_xml_lang_t attropt_tt_head_xml_lang
                = detail::CreateValueExpressionNode<attroption_t>
                ({ 
                    {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
                });

                // -----------------------------------------------------------------------------------------|



                // <tt:head/> [xml:lang] -------------------------------------------------- Attribute Node -|

                using attr_tt_head_xml_lang_t
                        = AttributeNode<NS, Attribute, vexpr_tt_head_xml_lang_t, attropt_tt_head_xml_lang_t>;

                attr_tt_head_xml_lang_t attr_tt_head_xml_lang {
                    enum_integer(cnd::required),
                    enum_integer(qty::kleene_one) | (0 << grp::one) | (0 << grp::two),
                    enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1),
                    NS::xml, Attribute::lang,
                    vexpr_tt_head_xml_lang, attropt_tt_head_xml_lang
                };

                // -----------------------------------------------------------------------------------------|


                // <tt:head/> [xml:space] ---------------------------------------------- Value expressions -|

                using vexpr_tt_head_xml_space_t                                 = XMLNodeTree<vexpression_t>;

                constexpr vexpr_tt_head_xml_space_t vexpr_tt_head_xml_space
                = detail::CreateValueExpressionNode<vexpression_t> 
                ({ 
                    {{ NS::none,          ValueExpression::string_option,        ":default|preserve",        0,           enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
                });

                // -----------------------------------------------------------------------------------------|



                // <tt:head/> [xml:space] ---------------------------------------------- Attribute Options -|
                
                using attropt_tt_head_xml_space_t                                = XMLNodeTree<attroption_t>;

                constexpr attropt_tt_head_xml_space_t attropt_tt_head_xml_space
                = detail::CreateValueExpressionNode<attroption_t>
                ({ 
                    {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
                });

                // -----------------------------------------------------------------------------------------|



                // <tt:head/> [xml:space] --------------------------------------------------- Attribute Node -|

                using attr_tt_head_xml_space_t
                        = AttributeNode<NS, Attribute, vexpr_tt_head_xml_space_t, attropt_tt_head_xml_space_t>;

                attr_tt_head_xml_space_t attr_tt_head_xml_space {
                    enum_integer(cnd::none),
                    enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two),
                    enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1),
                    NS::xml, Attribute::space,
                    vexpr_tt_head_xml_space, attropt_tt_head_xml_space
                };

                // -----------------------------------------------------------------------------------------|


                
                // <tt:head/> --------------------------------------------------------------- Attribute Tree -|

                using attr_tt_head_t               = XMLNodeTree<attr_tt_head_xml_id_t,attr_tt_head_xml_lang_t,
                                                                    attr_tt_head_xml_space_t>;
                attr_tt_head_t attr_tt_tt
                {
                    attr_tt_head_xml_id,
                    attr_tt_head_xml_lang,
                    attr_tt_head_xml_space
                };

                // -----------------------------------------------------------------------------------------|



                // <tt:head/> ----------------------------------------------------------------- Content Node -|

                using content_tt_head_t            = XMLNodeTree<content_data_t, content_tag_t, content_tag_t>;

                content_tt_head_t content_tt_head
                {
                    content_data_t( NS::none,         GenericData::PCDATA,    enum_integer(qty::kleene_asterisk) | (0 << grp::one) | (0 << grp::two),          enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1)),
                    content_tag_t ( NS::tt,           Tag::head,              enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two),          enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1)),
                    content_tag_t ( NS::tt,           Tag::body,              enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two),          enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1))
                };

                // -----------------------------------------------------------------------------------------|



                // <tt:head/> --------------------------------------------------------------------- XML Node -|

                using node_tt_head_t                     = XMLNode<NS, Tag, attr_tt_head_t, content_tt_head_t>;
                
                node_tt_head_t node_tt_head {
                    enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1),
                    NS::tt, Tag::head,
                    attr_tt_tt, content_tt_head
                };

                // -----------------------------------------------------------------------------------------|

                return node_tt_head;
            }
        }
    }
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif // VTNODEENTRY_TT_HEAD_HEADER