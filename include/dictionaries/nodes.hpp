// Stefan "SoulXP" Olivier
// File: node_tt_tt.hpp
// Description: TTML dictionary entry for tt:tt tag

#ifndef VTNODEENTRIES_HEADER
#define VTNODEENTRIES_HEADER

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "../config.hpp"
#endif

// Project headers
#include "../node.hpp"
#include "attributes.hpp"

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
}

// ---------------------------------------------------------------------------------------------------|
// Legend                                                                                             |
//                                                                                                    |
// Tags:        <ns:tag/>                [nsentry:entry]                                              |
// Naming:      type_nstag_tag_nsentry_entry(_t | _init)                                              |
//                                                                                                    |
// ---------------------------------------------------------------------------------------------------|

// Node tt:tt Entry -------------------------------------------------------------------------------------------------- 1 of 1 -|
// ============================================================================================================================|

namespace vt::dictionary::detail
{
    template<>
    constexpr inline auto CreateTTMLNode<NS::tt, Tag::tt>()
    {
        // <tt:tt/> [tts:extent] -------------------------------------------------- Attribute Node -|

        constexpr auto attr_tt_tt_tts_extent
        = detail::CreateAttributeNode<NS::tts, Attribute::extent> ();

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> [xml:id] --------------------------------------------------- Value expressions -|

        constexpr auto attr_tt_tt_xml_id
        = detail::CreateAttributeNode<NS::xml, Attribute::id> ();

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> [xml:lang] ------------------------------------------------- Value expressions -|

        constexpr auto attr_tt_tt_xml_lang
        = CreateAttributeNode<NS::xml, Attribute::lang> (
            enum_integer(cnd::required)
        );

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> [xml:space] ------------------------------------------------ Value expressions -|

        constexpr auto attr_tt_tt_xml_space
        = CreateAttributeNode<NS::xml, Attribute::space> ();

        // -----------------------------------------------------------------------------------------|

        // TT Parameter Attributes ----------------------------------------------- Attribute Group -|

        const auto& [
            attr_tt_tt_ttp_cellResolution,
            attr_tt_tt_ttp_clockMode,
            attr_tt_tt_ttp_dropMode,
            attr_tt_tt_ttp_frameRate,
            attr_tt_tt_ttp_frameRateMultiplier,
            attr_tt_tt_ttp_markerMode,
            attr_tt_tt_ttp_pixelAspectRatio,
            attr_tt_tt_ttp_profile,
            attr_tt_tt_ttp_subFrameRate,
            attr_tt_tt_ttp_tickRate,
            attr_tt_tt_ttp_timeBase
        ] = CreateAttributeGroup<AttributeGroup::tt_parameter>();

        // -----------------------------------------------------------------------------------------|

        // <tt:tt/> --------------------------------------------------------------- Attribute Tree -|

        using attr_tt_tt_t = std::tuple <
            // Explicitly Declared
            decltype(attr_tt_tt_tts_extent),
            decltype(attr_tt_tt_xml_id),
            decltype(attr_tt_tt_xml_lang),
            decltype(attr_tt_tt_xml_space),

            // { any in TT Parameter namespace }
            decltype(attr_tt_tt_ttp_cellResolution),
            decltype(attr_tt_tt_ttp_clockMode),
            decltype(attr_tt_tt_ttp_dropMode),
            decltype(attr_tt_tt_ttp_frameRate),
            decltype(attr_tt_tt_ttp_frameRateMultiplier),
            decltype(attr_tt_tt_ttp_markerMode),
            decltype(attr_tt_tt_ttp_pixelAspectRatio),
            decltype(attr_tt_tt_ttp_profile),
            decltype(attr_tt_tt_ttp_subFrameRate),
            decltype(attr_tt_tt_ttp_tickRate),
            decltype(attr_tt_tt_ttp_timeBase)
        >;

        attr_tt_tt_t attr_tt_tt {
            attr_tt_tt_tts_extent,
            attr_tt_tt_xml_id,
            attr_tt_tt_xml_lang,
            attr_tt_tt_xml_space,
            attr_tt_tt_ttp_cellResolution,
            attr_tt_tt_ttp_clockMode,
            attr_tt_tt_ttp_dropMode,
            attr_tt_tt_ttp_frameRate,
            attr_tt_tt_ttp_frameRateMultiplier,
            attr_tt_tt_ttp_markerMode,
            attr_tt_tt_ttp_pixelAspectRatio,
            attr_tt_tt_ttp_profile,
            attr_tt_tt_ttp_subFrameRate,
            attr_tt_tt_ttp_tickRate,
            attr_tt_tt_ttp_timeBase
        };

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> ----------------------------------------------------------------- Content Node -|

        using content_tt_tt_t            = std::tuple<content_data_t, content_tag_t, content_tag_t>;

        content_tt_tt_t content_tt_tt
        {
            content_data_t( NS::none,         GenericData::PCDATA,    enum_integer(qty::kleene_asterisk) | (0 << grp::one) | (0 << grp::two),          enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1)),
            content_tag_t ( NS::tt,           Tag::head,              enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two),          enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1)),
            content_tag_t ( NS::tt,           Tag::body,              enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two),          enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1))
        };

        // -----------------------------------------------------------------------------------------|



        // <tt:tt/> --------------------------------------------------------------------- XML Node -|

        using node_tt_tt_t                         = XMLNode<NS, Tag, attr_tt_tt_t, content_tt_tt_t>;

        return node_tt_tt_t {
            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1),
            NS::tt, Tag::tt,
            attr_tt_tt, content_tt_tt
        };

        // -----------------------------------------------------------------------------------------|

    }
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// Node tt:head Entry ------------------------------------------------------------------------------------------------ 1 of 1 -|
// ============================================================================================================================|

namespace vt::dictionary::detail
{
    template<>
    constexpr inline auto CreateTTMLNode<NS::tt, Tag::head>()
    {
        // <tt:head/> [xml:id] ------------------------------------------------- Value expressions -|

        constexpr auto attr_tt_head_xml_id
        = CreateAttributeNode<NS::xml, Attribute::id> (
            enum_integer(cnd::none),
            enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two)
        );

        // -----------------------------------------------------------------------------------------|


        // <tt:head/> [xml:lang] ----------------------------------------------- Value expressions -|

        constexpr auto attr_tt_head_xml_lang
        = CreateAttributeNode<NS::xml, Attribute::lang> (
            enum_integer(cnd::none),
            enum_integer(qty::kleene_one) | (0 << grp::one) | (0 << grp::two)
        );

        // -----------------------------------------------------------------------------------------|


        // <tt:head/> [xml:space] ---------------------------------------------- Value expressions -|

        constexpr auto attr_tt_head_xml_space 
        = CreateAttributeNode<NS::xml, Attribute::space> (
            enum_integer(cnd::none),
            enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two)
        );

        // -----------------------------------------------------------------------------------------|


        
        // <tt:head/> --------------------------------------------------------------- Attribute Tree -|

        using attr_tt_head_t               = std::tuple<decltype(attr_tt_head_xml_id),decltype(attr_tt_head_xml_lang),
                                                            decltype(attr_tt_head_xml_space)>;
        attr_tt_head_t attr_tt_tt
        {
            attr_tt_head_xml_id,
            attr_tt_head_xml_lang,
            attr_tt_head_xml_space
        };

        // -----------------------------------------------------------------------------------------|



        // <tt:head/> ----------------------------------------------------------------- Content Node -|

        using content_tt_head_t
                = std::tuple<content_tag_t, content_tag_t, content_tag_t, content_tag_t, content_tag_t,
                                content_tag_t, content_tag_t, content_tag_t>;

        content_tt_head_t content_tt_head
        {
            content_tag_t ( NS::tt,           Tag::metadata,          enum_integer(qty::kleene_asterisk) | (0 << grp::one) | (0 << grp::two),          enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1)),
            content_tag_t ( NS::ttm,          Tag::agent,             enum_integer(qty::kleene_asterisk) | (0 << grp::one) | (0 << grp::two),          enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1)),
            content_tag_t ( NS::ttm,          Tag::copyright,         enum_integer(qty::kleene_asterisk) | (0 << grp::one) | (0 << grp::two),          enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1)),
            content_tag_t ( NS::ttm,          Tag::desc,              enum_integer(qty::kleene_asterisk) | (0 << grp::one) | (0 << grp::two),          enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1)),
            content_tag_t ( NS::ttm,          Tag::title,             enum_integer(qty::kleene_asterisk) | (0 << grp::one) | (0 << grp::two),          enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1)),
            content_tag_t ( NS::ttp,          Tag::profile,           enum_integer(qty::kleene_asterisk) | (0 << grp::one) | (0 << grp::two),          enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1)),
            content_tag_t ( NS::tt,           Tag::styling,           enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two),          enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1)),
            content_tag_t ( NS::tt,           Tag::layout,            enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two),          enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1))
        };

        // -----------------------------------------------------------------------------------------|



        // <tt:head/> --------------------------------------------------------------------- XML Node -|

        using node_tt_head_t                     = XMLNode<NS, Tag, attr_tt_head_t, content_tt_head_t>;

        return node_tt_head_t {
            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1),
            NS::tt, Tag::head,
            attr_tt_tt, content_tt_head
        };

        // -----------------------------------------------------------------------------------------|
    }
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif // VTNODEENTRIES_HEADER