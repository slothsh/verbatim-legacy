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
#include "valueexpressions.hpp"

// Base Template for CreateAttributeNode ----------------------------------------------------------------------------- 1 of 1 -|
// ============================================================================================================================|

namespace vt::dictionary::detail
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

    // Base template type
    template<NS Tns = NS::none, Attribute Tattr = Attribute::none>
    constexpr inline auto CreateAttributeNode(size_t&& condition = enum_integer(cnd::none),
                                                size_t&& quantity = enum_integer(qty::kleene_asterisk) | (0 << grp::one) | (0 << grp::two),
                                                size_t&& documents = enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1))
    { static_assert(Tns != NS::none && Tattr != Attribute::none, "Invalid AttributeNode type\n"); }
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// Namespace XML -------------------------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

namespace vt::dictionary::detail
{
    // [xml:id]  ------------------------------------------------------------------ Specialization -|
    template<>
    constexpr inline auto CreateAttributeNode<NS::xml, Attribute::id>
    (size_t&& condition, size_t&& quantity, size_t&& documents)
    {
        // <tt:tt/> [xml:id] --------------------------------------------------- Value expressions -|

        constexpr auto vexpr_tt_tt_xml_id
        = detail::CreateXMLNodeTree<vexpression_t> 
        ({ 
            { CreateValueExpressionNode(NS::none,          ValueExpression::string,        "<id>") }
        });

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> [xml:id] --------------------------------------------------- Attribute Options -|
    
        constexpr auto attropt_tt_tt_xml_id
        = detail::CreateXMLNodeTree<attroption_t>
        ({ 
            {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> [xml:id] ------------------------------------------------------ Attribute Node -|

        using attr_tt_tt_xml_id_t
                        = AttributeNode<NS, Attribute, decltype(vexpr_tt_tt_xml_id), decltype(attropt_tt_tt_xml_id)>;

        return attr_tt_tt_xml_id_t {
            enum_integer(cnd::none),
            enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two),
            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1),
            NS::xml, Attribute::id,
            vexpr_tt_tt_xml_id, attropt_tt_tt_xml_id
        };

        // -----------------------------------------------------------------------------------------|
    }

    // [xml:lang]  ------------------------------------------------------------------ Specialization -|
    template<>
    constexpr inline auto CreateAttributeNode<NS::xml, Attribute::lang>
    (size_t&& condition, size_t&& quantity, size_t&& documents)
    {
        // <tt:tt/> [xml:lang] ------------------------------------------------- Value expressions -|

        constexpr auto vexpr_tt_tt_xml_lang
        = detail::CreateXMLNodeTree<vexpression_t> 
        ({ 
            {{ NS::none,          ValueExpression::string,        "<language>",        0,           enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> [xml:lang] ------------------------------------------------- Attribute Options -|
        
        constexpr auto attropt_tt_tt_xml_lang
        = detail::CreateXMLNodeTree<attroption_t>
        ({ 
            {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> [xml:lang] ---------------------------------------------------- Attribute Node -|

        using attr_tt_tt_xml_lang_t = AttributeNode<NS, Attribute, decltype(vexpr_tt_tt_xml_lang), decltype(attropt_tt_tt_xml_lang)>;
        return attr_tt_tt_xml_lang_t {
            std::move(condition),
            std::move(quantity),
            std::move(documents),
            NS::xml, Attribute::lang,
            vexpr_tt_tt_xml_lang, attropt_tt_tt_xml_lang
        };

        // -----------------------------------------------------------------------------------------|
    }

    // [xml:space]  ------------------------------------------------------------------ Specialization -|
    template<>
    constexpr inline auto CreateAttributeNode<NS::xml, Attribute::space>
    (size_t&& condition, size_t&& quantity, size_t&& documents)
    {
        // <tt:tt/> [xml:space] ------------------------------------------------ Value expressions -|

        constexpr auto vexpr_tt_tt_xml_space
        = detail::CreateXMLNodeTree<vexpression_t> 
        ({ 
            { CreateValueExpressionNode(NS::none,          ValueExpression::string_option,        ":default|preserve") }
        });

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> [xml:space] ------------------------------------------------ Attribute Options -|
        
        constexpr auto attropt_tt_tt_xml_space
        = detail::CreateXMLNodeTree<attroption_t>
        ({ 
            {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> [xml:space] --------------------------------------------------- Attribute Node -|

        using attr_tt_tt_xml_space_t = AttributeNode<NS, Attribute, decltype(vexpr_tt_tt_xml_space), decltype(attropt_tt_tt_xml_space)>;
        return attr_tt_tt_xml_space_t {
            enum_integer(cnd::none),
            enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two),
            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1),
            NS::xml, Attribute::space,
            vexpr_tt_tt_xml_space, attropt_tt_tt_xml_space
        };

        // -----------------------------------------------------------------------------------------|
    }
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// Namespace TTP -------------------------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

namespace vt::dictionary::detail
{
    // [ttp:cellResolution]  ------------------------------------------------------ Specialization -|
    template<>
    constexpr inline auto CreateAttributeNode<NS::ttp, Attribute::cellResolution>
    (size_t&& condition, size_t&& quantity, size_t&& documents)
    {
        // [ttp:cellResolution] ------------------------------------------------ Value expressions -|

        constexpr auto vexpr_ttp_cellResolution
        = detail::CreateXMLNodeTree
        ({ 
            { detail::CreateValueExpressionNode(NS::none, ValueExpression::digit, ":32 15|<digit>+ <digit>+") }
        });

        // -----------------------------------------------------------------------------------------|



        // [ttp:cellResolution] ------------------------------------------------ Attribute Options -|
        
        constexpr auto attropt_ttp_cellResolution
        = detail::CreateXMLNodeTree<attroption_t>
        ({ 
            {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        // -----------------------------------------------------------------------------------------|



        // [ttp:cellResolution] --------------------------------------------------- Attribute Node -|

        using attr_ttp_cellResolution_t = AttributeNode<NS, Attribute, decltype(vexpr_ttp_cellResolution), decltype(attropt_ttp_cellResolution)>;
        return attr_ttp_cellResolution_t {
            std::move(condition),
            std::move(quantity),
            std::move(documents),
            NS::ttp, Attribute::cellResolution,
            vexpr_ttp_cellResolution, attropt_ttp_cellResolution
        };

        // -----------------------------------------------------------------------------------------|
    }
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// Namespace TTS -------------------------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

namespace vt::dictionary::detail
{
    // [tts:extent]  -------------------------------------------------------------- Specialization -|
    template<>
    constexpr inline auto CreateAttributeNode<NS::tts, Attribute::extent>
    (size_t&& condition, size_t&& quantity, size_t&& documents)
    {
        // <tt:tt/> [tts:extent] ----------------------------------------------- Value expressions -|

        constexpr auto vexpr_tt_tt_tts_extent
        = detail::CreateXMLNodeTree<vexpression_t>
        ({
            { detail::CreateValueExpressionNode(NS::none,          ValueExpression::string,        ":<auto>|<length> <length>") }
        });

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> [tts:extent] ----------------------------------------------- Attribute Options -|

        constexpr auto attropt_tt_tt_tts_extent
        = detail::CreateXMLNodeTree<attroption_t>
        ({ 
            {{ NS::tt,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> [tts:extent] -------------------------------------------------- Attribute Node -|

        using attr_tt_tt_tts_extent_t
                = AttributeNode<NS, Attribute, decltype(vexpr_tt_tt_tts_extent), decltype(attropt_tt_tt_tts_extent)>;

        return attr_tt_tt_tts_extent_t {
            std::move(condition),
            std::move(quantity),
            std::move(documents),
            NS::tts, Attribute::extent,
            vexpr_tt_tt_tts_extent, attropt_tt_tt_tts_extent
        };

        // -----------------------------------------------------------------------------------------|
    }
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif // VTNODEATTR_HEADER