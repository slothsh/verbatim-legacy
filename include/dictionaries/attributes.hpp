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
                                                size_t&& quantity = enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two),
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
        constexpr auto vexpr_xml_id
        = detail::CreateXMLNodeTree<vexpression_t> 
        ({ 
            { CreateValueExpressionNode(NS::none,          ValueExpression::id,        "<id>") }
        });

        constexpr auto attropt_xml_id
        = detail::CreateXMLNodeTree<attroption_t>
        ({ 
            {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        using attr_xml_id_t
                        = AttributeNode<NS, Attribute, decltype(vexpr_xml_id), decltype(attropt_xml_id)>;

        return attr_xml_id_t {
            std::move(condition),
            std::move(quantity),
            std::move(documents),
            NS::xml, Attribute::id,
            vexpr_xml_id, attropt_xml_id
        };
    }

    // [xml:lang]  ------------------------------------------------------------------ Specialization -|
    template<>
    constexpr inline auto CreateAttributeNode<NS::xml, Attribute::lang>
    (size_t&& condition, size_t&& quantity, size_t&& documents)
    {
        constexpr auto vexpr_xml_lang
        = detail::CreateXMLNodeTree<vexpression_t> 
        ({ 
            { CreateValueExpressionNode(NS::none,          ValueExpression::language,        "<language>") }
        });
    
        constexpr auto attropt_xml_lang
        = detail::CreateXMLNodeTree<attroption_t>
        ({ 
            {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        using attr_xml_lang_t = AttributeNode<NS, Attribute, decltype(vexpr_xml_lang), decltype(attropt_xml_lang)>;
        return attr_xml_lang_t {
            std::move(condition),
            std::move(quantity),
            std::move(documents),
            NS::xml, Attribute::lang,
            vexpr_xml_lang, attropt_xml_lang
        };
    }

    // [xml:space]  ------------------------------------------------------------------ Specialization -|
    template<>
    constexpr inline auto CreateAttributeNode<NS::xml, Attribute::space>
    (size_t&& condition, size_t&& quantity, size_t&& documents)
    {
        constexpr auto vexpr_xml_space
        = detail::CreateXMLNodeTree<vexpression_t> 
        ({ 
            { CreateValueExpressionNode(NS::none,          ValueExpression::literal,        "default",           enum_integer(cnd::is_default)) },
            { CreateValueExpressionNode(NS::none,          ValueExpression::literal,        "preserve")                                         }
        });
      
        constexpr auto attropt_xml_space
        = detail::CreateXMLNodeTree<attroption_t>
        ({ 
            {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        using attr_xml_space_t = AttributeNode<NS, Attribute, decltype(vexpr_xml_space), decltype(attropt_xml_space)>;
        return attr_xml_space_t {
            std::move(condition),
            std::move(quantity),
            std::move(documents),
            NS::xml, Attribute::space,
            vexpr_xml_space, attropt_xml_space
        };
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
        constexpr auto vexpr_ttp_cellResolution
        = detail::CreateXMLNodeTree
        ({ 
            { detail::CreateValueExpressionNode(NS::none,       ValueExpression::literal,              "32 15",                enum_integer(cnd::is_default)) },
            { detail::CreateValueExpressionNode(NS::none,       ValueExpression::regex,                "<digit>+ <digit>+")                                   }
        });

        constexpr auto attropt_ttp_cellResolution
        = detail::CreateXMLNodeTree<attroption_t>
        ({ 
            {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        using attr_ttp_cellResolution_t = AttributeNode<NS, Attribute, decltype(vexpr_ttp_cellResolution), decltype(attropt_ttp_cellResolution)>;
        return attr_ttp_cellResolution_t {
            std::move(condition),
            std::move(quantity),
            std::move(documents),
            NS::ttp, Attribute::cellResolution,
            vexpr_ttp_cellResolution, attropt_ttp_cellResolution
        };
    }

    // [ttp:clockMode]  ----------------------------------------------------------- Specialization -|
    template<>
    constexpr inline auto CreateAttributeNode<NS::ttp, Attribute::clockMode>
    (size_t&& condition, size_t&& quantity, size_t&& documents)
    {
        constexpr auto vexpr_ttp_clockMode
        = detail::CreateXMLNodeTree
        ({ 
            { detail::CreateValueExpressionNode(NS::none,       ValueExpression::literal,         "local",       enum_integer(cnd::is_default)) },
            { detail::CreateValueExpressionNode(NS::none,       ValueExpression::literal,         "gps")                                        },
            { detail::CreateValueExpressionNode(NS::none,       ValueExpression::literal,         "utc")                                        }
        });
        
        constexpr auto attropt_ttp_clockMode
        = detail::CreateXMLNodeTree<attroption_t>
        ({ 
            {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        using attr_ttp_clockMode_t = AttributeNode<NS, Attribute, decltype(vexpr_ttp_clockMode), decltype(attropt_ttp_clockMode)>;
        return attr_ttp_clockMode_t {
            std::move(condition),
            std::move(quantity),
            std::move(documents),
            NS::ttp, Attribute::clockMode,
            vexpr_ttp_clockMode, attropt_ttp_clockMode
        };
    }

    // [ttp:dropMode]  ------------------------------------------------------------ Specialization -|
    template<>
    constexpr inline auto CreateAttributeNode<NS::ttp, Attribute::dropMode>
    (size_t&& condition, size_t&& quantity, size_t&& documents)
    {
        constexpr auto vexpr_ttp_dropMode
        = detail::CreateXMLNodeTree
        ({ 
            { detail::CreateValueExpressionNode(NS::none,       ValueExpression::literal,         "dropNTSC",           enum_integer(cnd::is_default)) },
            { detail::CreateValueExpressionNode(NS::none,       ValueExpression::literal,         "dropPAL")                                           },
            { detail::CreateValueExpressionNode(NS::none,       ValueExpression::literal,         "nonDrop")                                           }
        });

        constexpr auto attropt_ttp_dropMode
        = detail::CreateXMLNodeTree<attroption_t>
        ({ 
            {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        using attr_ttp_dropMode_t = AttributeNode<NS, Attribute, decltype(vexpr_ttp_dropMode), decltype(attropt_ttp_dropMode)>;
        return attr_ttp_dropMode_t {
            std::move(condition),
            std::move(quantity),
            std::move(documents),
            NS::ttp, Attribute::dropMode,
            vexpr_ttp_dropMode, attropt_ttp_dropMode
        };
    }

    // [ttp:frameRate]  ----------------------------------------------------------- Specialization -|
    template<>
    constexpr inline auto CreateAttributeNode<NS::ttp, Attribute::frameRate>
    (size_t&& condition, size_t&& quantity, size_t&& documents)
    {
        constexpr auto vexpr_ttp_frameRate
        = detail::CreateXMLNodeTree
        ({ 
            { detail::CreateValueExpressionNode(NS::none,       ValueExpression::digit,         "<digit>+",           enum_integer(cnd::is_default)) }
        });
        
        constexpr auto attropt_ttp_frameRate
        = detail::CreateXMLNodeTree<attroption_t>
        ({ 
            {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        using attr_ttp_frameRate_t = AttributeNode<NS, Attribute, decltype(vexpr_ttp_frameRate), decltype(attropt_ttp_frameRate)>;
        return attr_ttp_frameRate_t {
            std::move(condition),
            std::move(quantity),
            std::move(documents),
            NS::ttp, Attribute::frameRate,
            vexpr_ttp_frameRate, attropt_ttp_frameRate
        };
    }

    // [ttp:frameRateMultiplier]  ------------------------------------------------- Specialization -|
    template<>
    constexpr inline auto CreateAttributeNode<NS::ttp, Attribute::frameRateMultiplier>
    (size_t&& condition, size_t&& quantity, size_t&& documents)
    {
        constexpr auto vexpr_ttp_frameRateMultiplier
        = detail::CreateXMLNodeTree
        ({ 
            { detail::CreateValueExpressionNode(NS::none,       ValueExpression::regex,         "<digit>+ <digit>+",           enum_integer(cnd::is_default)) }
        });
        
        constexpr auto attropt_ttp_frameRateMultiplier
        = detail::CreateXMLNodeTree<attroption_t>
        ({ 
            {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        using attr_ttp_frameRateMultiplier_t = AttributeNode<NS, Attribute, decltype(vexpr_ttp_frameRateMultiplier), decltype(attropt_ttp_frameRateMultiplier)>;
        return attr_ttp_frameRateMultiplier_t {
            std::move(condition),
            std::move(quantity),
            std::move(documents),
            NS::ttp, Attribute::frameRateMultiplier,
            vexpr_ttp_frameRateMultiplier, attropt_ttp_frameRateMultiplier
        };
    }

    // [ttp:markerMode]  ---------------------------------------------------------- Specialization -|
    template<>
    constexpr inline auto CreateAttributeNode<NS::ttp, Attribute::markerMode>
    (size_t&& condition, size_t&& quantity, size_t&& documents)
    {
        constexpr auto vexpr_ttp_markerMode
        = detail::CreateXMLNodeTree
        ({ 
            { detail::CreateValueExpressionNode(NS::none,       ValueExpression::literal,         "continuous",           enum_integer(cnd::is_default)) },
            { detail::CreateValueExpressionNode(NS::none,       ValueExpression::literal,         "discontinuous")                                       }
        });
        
        constexpr auto attropt_ttp_markerMode
        = detail::CreateXMLNodeTree<attroption_t>
        ({ 
            {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        using attr_ttp_markerMode_t = AttributeNode<NS, Attribute, decltype(vexpr_ttp_markerMode), decltype(attropt_ttp_markerMode)>;
        return attr_ttp_markerMode_t {
            std::move(condition),
            std::move(quantity),
            std::move(documents),
            NS::ttp, Attribute::markerMode,
            vexpr_ttp_markerMode, attropt_ttp_markerMode
        };
    }

    // [ttp:pixelAspectRatio]  ---------------------------------------------------------- Specialization -|
    template<>
    constexpr inline auto CreateAttributeNode<NS::ttp, Attribute::pixelAspectRatio>
    (size_t&& condition, size_t&& quantity, size_t&& documents)
    {
        constexpr auto vexpr_ttp_pixelAspectRatio
        = detail::CreateXMLNodeTree
        ({ 
            { detail::CreateValueExpressionNode(NS::none,       ValueExpression::regex,         "<digit>+ <digit>+",           enum_integer(cnd::is_default)) }
        });
        
        constexpr auto attropt_ttp_pixelAspectRatio
        = detail::CreateXMLNodeTree<attroption_t>
        ({ 
            {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        using attr_ttp_pixelAspectRatio_t = AttributeNode<NS, Attribute, decltype(vexpr_ttp_pixelAspectRatio), decltype(attropt_ttp_pixelAspectRatio)>;
        return attr_ttp_pixelAspectRatio_t {
            std::move(condition),
            std::move(quantity),
            std::move(documents),
            NS::ttp, Attribute::pixelAspectRatio,
            vexpr_ttp_pixelAspectRatio, attropt_ttp_pixelAspectRatio
        };
    }

    // [ttp:profile]  ------------------------------------------------------------ Specialization -|
    template<>
    constexpr inline auto CreateAttributeNode<NS::ttp, Attribute::profile>
    (size_t&& condition, size_t&& quantity, size_t&& documents)
    {
        constexpr auto vexpr_ttp_profile
        = detail::CreateXMLNodeTree
        ({ 
            { detail::CreateValueExpressionNode(NS::none,       ValueExpression::any_uri,         "<anyURI>",           enum_integer(cnd::is_default)) }
        });
        
        constexpr auto attropt_ttp_profile
        = detail::CreateXMLNodeTree<attroption_t>
        ({ 
            {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        using attr_ttp_profile_t = AttributeNode<NS, Attribute, decltype(vexpr_ttp_profile), decltype(attropt_ttp_profile)>;
        return attr_ttp_profile_t {
            std::move(condition),
            std::move(quantity),
            std::move(documents),
            NS::ttp, Attribute::profile,
            vexpr_ttp_profile, attropt_ttp_profile
        };
    }
    
    // [ttp:subFrameRate]  ------------------------------------------------------- Specialization -|
    template<>
    constexpr inline auto CreateAttributeNode<NS::ttp, Attribute::subFrameRate>
    (size_t&& condition, size_t&& quantity, size_t&& documents)
    {
        constexpr auto vexpr_ttp_subFrameRate
        = detail::CreateXMLNodeTree
        ({ 
            { detail::CreateValueExpressionNode(NS::none,       ValueExpression::digit,         "<digit>+",           enum_integer(cnd::is_default)) }
        });
        
        constexpr auto attropt_ttp_subFrameRate
        = detail::CreateXMLNodeTree<attroption_t>
        ({ 
            {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        using attr_ttp_subFrameRate_t = AttributeNode<NS, Attribute, decltype(vexpr_ttp_subFrameRate), decltype(attropt_ttp_subFrameRate)>;
        return attr_ttp_subFrameRate_t {
            std::move(condition),
            std::move(quantity),
            std::move(documents),
            NS::ttp, Attribute::subFrameRate,
            vexpr_ttp_subFrameRate, attropt_ttp_subFrameRate
        };
    }

    // [ttp:tickRate]  ------------------------------------------------------------ Specialization -|
    template<>
    constexpr inline auto CreateAttributeNode<NS::ttp, Attribute::tickRate>
    (size_t&& condition, size_t&& quantity, size_t&& documents)
    {
        constexpr auto vexpr_ttp_tickRate
        = detail::CreateXMLNodeTree
        ({ 
            { detail::CreateValueExpressionNode(NS::none,       ValueExpression::digit,         "<digit>+",           enum_integer(cnd::is_default)) }
        });
        
        constexpr auto attropt_ttp_tickRate
        = detail::CreateXMLNodeTree<attroption_t>
        ({ 
            {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        using attr_ttp_tickRate_t = AttributeNode<NS, Attribute, decltype(vexpr_ttp_tickRate), decltype(attropt_ttp_tickRate)>;
        return attr_ttp_tickRate_t {
            std::move(condition),
            std::move(quantity),
            std::move(documents),
            NS::ttp, Attribute::tickRate,
            vexpr_ttp_tickRate, attropt_ttp_tickRate
        };
    }

    // [ttp:timeBase]  ------------------------------------------------------------ Specialization -|
    template<>
    constexpr inline auto CreateAttributeNode<NS::ttp, Attribute::timeBase>
    (size_t&& condition, size_t&& quantity, size_t&& documents)
    {
        constexpr auto vexpr_ttp_timeBase
        = detail::CreateXMLNodeTree
        ({ 
            { detail::CreateValueExpressionNode(NS::none,       ValueExpression::literal,         "media",           enum_integer(cnd::is_default)) },
            { detail::CreateValueExpressionNode(NS::none,       ValueExpression::literal,         "smpte")                                          },
            { detail::CreateValueExpressionNode(NS::none,       ValueExpression::literal,         "clock")                                          }
        });
        
        constexpr auto attropt_ttp_timeBase
        = detail::CreateXMLNodeTree<attroption_t>
        ({ 
            {{ NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        using attr_ttp_timeBase_t = AttributeNode<NS, Attribute, decltype(vexpr_ttp_timeBase), decltype(attropt_ttp_timeBase)>;
        return attr_ttp_timeBase_t {
            std::move(condition),
            std::move(quantity),
            std::move(documents),
            NS::ttp, Attribute::timeBase,
            vexpr_ttp_timeBase, attropt_ttp_timeBase
        };
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
        constexpr auto vexpr_tts_extent
        = detail::CreateXMLNodeTree<vexpression_t>
        ({
            { detail::CreateValueExpressionNode(NS::none,          ValueExpression::automatic,        "<auto>",               enum_integer(cnd::is_default)) },
            { detail::CreateValueExpressionNode(NS::none,          ValueExpression::regex,            "<length> <length>")                                   }
        });

        constexpr auto attropt_tts_extent
        = detail::CreateXMLNodeTree<attroption_t>
        ({ 
            {{ NS::tt,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
        });

        using attr_tts_extent_t
                = AttributeNode<NS, Attribute, decltype(vexpr_tts_extent), decltype(attropt_tts_extent)>;

        return attr_tts_extent_t {
            std::move(condition),
            std::move(quantity),
            std::move(documents),
            NS::tts, Attribute::extent,
            vexpr_tts_extent, attropt_tts_extent
        };
    }
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// Attribute Macro functions -------------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

namespace vt::dictionary::detail
{
    template<AttributeGroup Tattrgrp = AttributeGroup::none>
    constexpr inline decltype(auto) CreateAttributeGroup()
    {
        static_assert(Tattrgrp != AttributeGroup::none, "Invalid attribute group\n");
    }

    template<>
    constexpr inline decltype(auto) CreateAttributeGroup<AttributeGroup::tt_parameter>()
    {
        constexpr auto attr_ttp_cellResolution
        = CreateAttributeNode<NS::ttp, Attribute::cellResolution> ();

        constexpr auto attr_ttp_clockMode
        = CreateAttributeNode<NS::ttp, Attribute::clockMode> ();

        constexpr auto attr_ttp_dropMode
        = CreateAttributeNode<NS::ttp, Attribute::dropMode> ();

        constexpr auto attr_ttp_frameRate
        = CreateAttributeNode<NS::ttp, Attribute::frameRate> ();

        constexpr auto attr_ttp_frameRateMultiplier
        = CreateAttributeNode<NS::ttp, Attribute::frameRateMultiplier> ();

        constexpr auto attr_ttp_markerMode
        = CreateAttributeNode<NS::ttp, Attribute::markerMode> ();

        constexpr auto attr_ttp_pixelAspectRatio
        = CreateAttributeNode<NS::ttp, Attribute::pixelAspectRatio> ();

        constexpr auto attr_ttp_profile
        = CreateAttributeNode<NS::ttp, Attribute::profile> ();

        constexpr auto attr_ttp_subFrameRate
        = CreateAttributeNode<NS::ttp, Attribute::subFrameRate> ();

        constexpr auto attr_ttp_tickRate
        = CreateAttributeNode<NS::ttp, Attribute::tickRate> ();

        constexpr auto attr_ttp_timeBase
        = CreateAttributeNode<NS::ttp, Attribute::timeBase> ();

        return std::tuple <
            decltype(attr_ttp_cellResolution),
            decltype(attr_ttp_clockMode),
            decltype(attr_ttp_dropMode),
            decltype(attr_ttp_frameRate),
            decltype(attr_ttp_frameRateMultiplier),
            decltype(attr_ttp_markerMode),
            decltype(attr_ttp_pixelAspectRatio),
            decltype(attr_ttp_profile),
            decltype(attr_ttp_subFrameRate),
            decltype(attr_ttp_tickRate),
            decltype(attr_ttp_timeBase)
        >
        {
            attr_ttp_cellResolution,
            attr_ttp_clockMode,
            attr_ttp_dropMode,
            attr_ttp_frameRate,
            attr_ttp_frameRateMultiplier,
            attr_ttp_markerMode,
            attr_ttp_pixelAspectRatio,
            attr_ttp_profile,
            attr_ttp_subFrameRate,
            attr_ttp_tickRate,
            attr_ttp_timeBase
        };
    }
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif // VTNODEATTR_HEADER