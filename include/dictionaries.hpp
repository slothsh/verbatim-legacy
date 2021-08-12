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
    namespace detail
    {
        template<class T>
        using tuple_seq = std::make_index_sequence<std::tuple_size_v<T>>;
    }

    static constexpr auto CreateTTMLDictionary()
    {
        using namespace magic_enum::bitwise_operators;
        using namespace vt::functional;
        using magic_enum::enum_integer;

        using grp = constants::ByteGroup;
        using doc = constants::TTMLDocument;
        using cnd = constants::NodeCondition;
        using qty = constants::NodeQuantifier;

        // Default expressions
        constexpr size_t default_vexpr_isDefault    = enum_integer(cnd::is_default);
        constexpr size_t default_vexpr_none         = enum_integer(cnd::none);
        constexpr size_t default_vexpr_quantifier   = enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two);
        constexpr size_t default_node_document      = enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1);
        constexpr size_t default_vexpr_document     = enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1);

        // Attribute Elements
        // ---------------------------------------------------------------------------------------------------|

        // XML Core
        constexpr std::tuple attr_xml_id    { NS::xml,          Attribute::id    };
        constexpr std::tuple attr_xml_lang  { NS::xml,          Attribute::lang  };
        constexpr std::tuple attr_xml_space { NS::xml,          Attribute::space };
        constexpr std::tuple attr_xml_base  { NS::xml,          Attribute::base  };

        // TT Core
        constexpr std::tuple attr_tt_tt            { NS::tt,           Attribute::tt            };
        constexpr std::tuple attr_tt_ttm           { NS::tt,           Attribute::ttm           };
        constexpr std::tuple attr_tt_ttp           { NS::tt,           Attribute::ttp           };
        constexpr std::tuple attr_tt_tts           { NS::tt,           Attribute::tts           };
        constexpr std::tuple attr_tt_style         { NS::tt,           Attribute::style         };
        constexpr std::tuple attr_tt_region        { NS::tt,           Attribute::region        };
        constexpr std::tuple attr_tt_begin         { NS::tt,           Attribute::begin         };
        constexpr std::tuple attr_tt_dur           { NS::tt,           Attribute::dur           };
        constexpr std::tuple attr_tt_end           { NS::tt,           Attribute::end           };
        constexpr std::tuple attr_tt_timeContainer { NS::tt,           Attribute::timeContainer };

        // TT Metadata
        constexpr std::tuple attr_ttm_agent { NS::ttm,            Attribute::agent };
        constexpr std::tuple attr_ttm_role  { NS::ttm,            Attribute::role  };

        // TT Parameter
        constexpr std::tuple attr_ttp_profile             { NS::ttp,          Attribute::profile             };
        constexpr std::tuple attr_ttp_cellResolution      { NS::ttp,          Attribute::cellResolution      };
        constexpr std::tuple attr_ttp_clockMode           { NS::ttp,          Attribute::clockMode           };
        constexpr std::tuple attr_ttp_dropMode            { NS::ttp,          Attribute::dropMode            };
        constexpr std::tuple attr_ttp_frameRate           { NS::ttp,          Attribute::frameRate           };
        constexpr std::tuple attr_ttp_frameRateMultiplier { NS::ttp,          Attribute::frameRateMultiplier };
        constexpr std::tuple attr_ttp_markerMode          { NS::ttp,          Attribute::markerMode          };
        constexpr std::tuple attr_ttp_pixelAspectRatio    { NS::ttp,          Attribute::pixelAspectRatio    };
        constexpr std::tuple attr_ttp_subFrameRate        { NS::ttp,          Attribute::subFrameRate        };
        constexpr std::tuple attr_ttp_tickRate            { NS::ttp,          Attribute::tickRate            };
        constexpr std::tuple attr_ttp_timeBase            { NS::ttp,          Attribute::timeBase            };

        // TT Style
        constexpr std::tuple attr_tts_backgroundColor { NS::tts,         Attribute::backgroundColor };
        constexpr std::tuple attr_tts_color           { NS::tts,         Attribute::color           };
        constexpr std::tuple attr_tts_direction       { NS::tts,         Attribute::direction       };
        constexpr std::tuple attr_tts_display         { NS::tts,         Attribute::display         };
        constexpr std::tuple attr_tts_displayAlign    { NS::tts,         Attribute::displayAlign    };
        constexpr std::tuple attr_tts_extent          { NS::tts,         Attribute::extent          };
        constexpr std::tuple attr_tts_fontFamily      { NS::tts,         Attribute::fontFamily      };
        constexpr std::tuple attr_tts_fontSize        { NS::tts,         Attribute::fontSize        };
        constexpr std::tuple attr_tts_fontStyle       { NS::tts,         Attribute::fontStyle       };
        constexpr std::tuple attr_tts_fontWeight      { NS::tts,         Attribute::fontWeight      };
        constexpr std::tuple attr_tts_lineHeight      { NS::tts,         Attribute::lineHeight      };
        constexpr std::tuple attr_tts_opacity         { NS::tts,         Attribute::opacity         };
        constexpr std::tuple attr_tts_origin          { NS::tts,         Attribute::origin          };
        constexpr std::tuple attr_tts_overflow        { NS::tts,         Attribute::overflow        };
        constexpr std::tuple attr_tts_padding         { NS::tts,         Attribute::padding         };
        constexpr std::tuple attr_tts_showBackground  { NS::tts,         Attribute::showBackground  };
        constexpr std::tuple attr_tts_textAlign       { NS::tts,         Attribute::textAlign       };
        constexpr std::tuple attr_tts_textDecoration  { NS::tts,         Attribute::textDecoration  };
        constexpr std::tuple attr_tts_textOutline     { NS::tts,         Attribute::textOutline     };
        constexpr std::tuple attr_tts_unicodeBidi     { NS::tts,         Attribute::unicodeBidi     };
        constexpr std::tuple attr_tts_visibility      { NS::tts,         Attribute::visibility      };
        constexpr std::tuple attr_tts_wrapOption      { NS::tts,         Attribute::wrapOption      };
        constexpr std::tuple attr_tts_writingMode     { NS::tts,         Attribute::writingMode     };
        constexpr std::tuple attr_tts_zIndex          { NS::tts,         Attribute::zIndex          };

        // Value Expression Entries
        // ---------------------------------------------------------------------------------------------------|

        // XML Namespace -------------------------------------------------|

        // [xml:id]
        constexpr std::tuple vexpr_xml_id {
            std::tuple { NS::none,       ValueExpression::id,               "<id>",                         default_vexpr_none,                         default_vexpr_document }
        };

        // [xml:lang]
        constexpr std::tuple vexpr_xml_lang {
            std::tuple { NS::none,       ValueExpression::language,         "<language>",                   default_vexpr_none,                         default_vexpr_document }
        };

        // [xml:space]
        constexpr std::tuple vexpr_xml_space {
            std::tuple { NS::none,       ValueExpression::literal,          "default",                      default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "preserve",                     default_vexpr_none,                         default_vexpr_document }
        };

        constexpr std::tuple vexpr_xml {
            vexpr_xml_id,
            vexpr_xml_lang,
            vexpr_xml_space 
        };

        // TT Namespace --------------------------------------------------|

        // [tt:style]
        constexpr std::tuple vexpr_tt_style {
            std::tuple { NS::none,       ValueExpression::idrefs,           "<idrefs>",                     default_vexpr_isDefault,                    default_vexpr_document }
        };

        // [tt:begin]
        constexpr std::tuple vexpr_tt_begin {
            std::tuple { NS::none,       ValueExpression::timeExpression,   "<timeExpression>",             default_vexpr_isDefault,                    default_vexpr_document }
        };

        // [tt:end]
        constexpr std::tuple vexpr_tt_end {
            std::tuple { NS::none,       ValueExpression::timeExpression,   "<timeExpression>",             default_vexpr_isDefault,                    default_vexpr_document }
        };

        // [tt:dur]
        constexpr std::tuple vexpr_tt_dur {
            std::tuple { NS::none,       ValueExpression::timeExpression,   "<timeExpression>",             default_vexpr_isDefault,                    default_vexpr_document }
        };

        // [tt:region]
        constexpr std::tuple vexpr_tt_region {
            std::tuple { NS::none,       ValueExpression::idref,            "<idref>",                      default_vexpr_isDefault,                    default_vexpr_document }
        };

        constexpr std::tuple vexpr_tt {
            vexpr_tt_style,
            vexpr_tt_begin,
            vexpr_tt_end,
            vexpr_tt_dur,
            vexpr_tt_region
        };

        // TTM Namespace -------------------------------------------------|

        // [ttm:agent]
        constexpr std::tuple vexpr_ttm_agent {
            std::tuple { NS::none,       ValueExpression::idrefs,           "<idrefs>",                                                default_vexpr_isDefault,               default_vexpr_document },
        };

        // [ttm:actor]
        constexpr std::tuple vexpr_ttm_actor {
            std::tuple { NS::none,       ValueExpression::literal,          "action",                                                  default_vexpr_isDefault,               default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "caption",                                                 default_vexpr_none,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "description",                                             default_vexpr_none,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "dialog",                                                  default_vexpr_none,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "expletive",                                               default_vexpr_none,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "kinesic",                                                 default_vexpr_none,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "lyrics",                                                  default_vexpr_none,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "music",                                                   default_vexpr_none,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "narration",                                               default_vexpr_none,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "quality",                                                 default_vexpr_none,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "sound",                                                   default_vexpr_none,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "source",                                                  default_vexpr_none,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "suppressed",                                              default_vexpr_none,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "reproduction",                                            default_vexpr_none,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "thought",                                                 default_vexpr_none,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "title",                                                   default_vexpr_none,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "transcription",                                           default_vexpr_none,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::token_char,       "<extenstionRole>",                                        default_vexpr_none,                    default_vexpr_document }
        };

        constexpr std::tuple vexpr_ttm {
            vexpr_ttm_agent,
            vexpr_ttm_actor
        };

        // TTP Namespace -------------------------------------------------|

        // [ttp:cellResolution]
        constexpr std::tuple vexpr_ttp_cellResolution {
            std::tuple { NS::none,       ValueExpression::literal,          "32 15",                        default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::digit,            "<digit>+ <digit>+",            default_vexpr_none,                         default_vexpr_document }
        };

        // [ttp:clockMode]
        constexpr std::tuple vexpr_ttp_clockMode {
            std::tuple { NS::none,       ValueExpression::literal,          "local",                        default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "gps",                          default_vexpr_none,                         default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "utc",                          default_vexpr_none,                         default_vexpr_document }
        };

        // [ttp:dropMode]
        constexpr std::tuple vexpr_ttp_dropMode {
            std::tuple { NS::none,       ValueExpression::literal,          "dropNTSC",                     default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "dropPAL",                      default_vexpr_none,                         default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "nonDrop",                      default_vexpr_none,                         default_vexpr_document }
        };

        // [ttp:frameRate]
        constexpr std::tuple vexpr_ttp_frameRate {
            std::tuple { NS::none,       ValueExpression::digit,            "<digit>+",                     default_vexpr_isDefault,                    default_vexpr_document }
        };

        // [ttp:frameRateMultiplier]
        constexpr std::tuple vexpr_ttp_frameRateMultiplier {
            std::tuple { NS::none,       ValueExpression::digit,            "<digit>+ <digit>+",            default_vexpr_isDefault,                    default_vexpr_document }
        };

        // [ttp:markerMode]
        constexpr std::tuple vexpr_ttp_markerMode {
            std::tuple { NS::none,       ValueExpression::literal,          "continuous",                   default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "discontinuous",                default_vexpr_none,                         default_vexpr_document }
        };

        // [ttp:pixelAspectRatio]
        constexpr std::tuple vexpr_ttp_pixelAspectRatio {
            std::tuple { NS::none,       ValueExpression::digit,            "<digit>+ <digit>+",            default_vexpr_isDefault,                    default_vexpr_document }
        };

        // [ttp:profile]
        constexpr std::tuple vexpr_ttp_profile {
            std::tuple { NS::none,       ValueExpression::any_uri,          "<anyURI>",                     default_vexpr_isDefault,                    default_vexpr_document }
        };

        // [ttp:subFrameRate]
        constexpr std::tuple vexpr_ttp_subFrameRate {
            std::tuple { NS::none,       ValueExpression::digit,            "<digit>+",                     default_vexpr_isDefault,                    default_vexpr_document }
        };

        // [ttp:tickRate]
        constexpr std::tuple vexpr_ttp_tickRate {
            std::tuple { NS::none,       ValueExpression::digit,            "<digit>+",                     default_vexpr_isDefault,                    default_vexpr_document }
        };

        // [ttp:timeBase]
        constexpr std::tuple vexpr_ttp_timeBase {
            std::tuple { NS::none,       ValueExpression::literal,          "media",                        default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "smpte",                        default_vexpr_none,                         default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "clock",                        default_vexpr_none,                         default_vexpr_document }
        };

        constexpr std::tuple vexpr_ttp {
            vexpr_ttp_cellResolution,
            vexpr_ttp_clockMode,
            vexpr_ttp_dropMode,
            vexpr_ttp_frameRate,
            vexpr_ttp_frameRateMultiplier,
            vexpr_ttp_markerMode,
            vexpr_ttp_pixelAspectRatio,
            vexpr_ttp_profile,
            vexpr_ttp_subFrameRate,
            vexpr_ttp_tickRate,
            vexpr_ttp_timeBase
        };

        // TTS Namespace -------------------------------------------------|

        // [tts:backgroundColor]
        constexpr std::tuple vexpr_tts_backgroundColor {
            std::tuple { NS::none,       ValueExpression::color,            "<color>",                                                 default_vexpr_isDefault,                    default_vexpr_document },
        };

        // [tts:color]
        constexpr std::tuple vexpr_tts_color {
            std::tuple { NS::none,       ValueExpression::color,            "<color>",                                                 default_vexpr_isDefault,                    default_vexpr_document },
        };

        // [tts:direction]
        constexpr std::tuple vexpr_tts_direction {
            std::tuple { NS::none,       ValueExpression::literal,          "ltr",                                                     default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "rtl",                                                     default_vexpr_none,                         default_vexpr_document }
        };

        // [tts:display]
        constexpr std::tuple vexpr_tts_display {
            std::tuple { NS::none,       ValueExpression::literal,          "auto",                                                    default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "none",                                                    default_vexpr_none,                         default_vexpr_document }
        };

        // [tts:displayAlign]
        constexpr std::tuple vexpr_tts_displayAlign {
            std::tuple { NS::none,       ValueExpression::literal,          "before",                                                  default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "center",                                                  default_vexpr_none,                         default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "after",                                                   default_vexpr_none,                         default_vexpr_document }
        };

        // [tts:extent]
        constexpr std::tuple vexpr_tts_extent {
            std::tuple { NS::none,       ValueExpression::literal,          "auto",                                                    default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::length,           "<length> <length>",                                       default_vexpr_none,                         default_vexpr_document }
        };

        // [tts:fontFamily]
        constexpr std::tuple vexpr_tts_fontFamily {
            std::tuple { NS::none,       ValueExpression::literal,          "default",                                                 default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::font,             "<familyName>|<genericFamilyName>*",                       default_vexpr_none,                         default_vexpr_document }
        };

        // [tts:fontSize]
        constexpr std::tuple vexpr_tts_fontSize {
            std::tuple { NS::none,       ValueExpression::literal,          "1c",                                                      default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::length,           "<length> <length>?",                                      default_vexpr_none,                         default_vexpr_document }
        };

        // [tts:fontSyle]
        constexpr std::tuple vexpr_tts_fontSyle {
            std::tuple { NS::none,       ValueExpression::literal,          "normal",                                                  default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "italic",                                                  default_vexpr_none,                         default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "oblique",                                                 default_vexpr_none,                         default_vexpr_document }
        };

        // [tts:fontWeight]
        constexpr std::tuple vexpr_tts_fontWeight {
            std::tuple { NS::none,       ValueExpression::literal,          "normal",                                                  default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "bold",                                                    default_vexpr_none,                         default_vexpr_document }
        };

        // [tts:lineHeight]
        constexpr std::tuple vexpr_tts_lineHeight {
            std::tuple { NS::none,       ValueExpression::literal,          "normal",                                                  default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::length,           "<length>",                                                default_vexpr_none,                         default_vexpr_document }
        };

        // [tts:opacity]
        constexpr std::tuple vexpr_tts_opacity {
            std::tuple { NS::none,       ValueExpression::literal,          "1.0",                                                     default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::alpha,            "<alpha>",                                                 default_vexpr_none,                         default_vexpr_document }
        };

        // [tts:origin]
        constexpr std::tuple vexpr_tts_origin {
            std::tuple { NS::none,       ValueExpression::literal,          "auto",                                                    default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::length,           "<length> <length>",                                       default_vexpr_none,                         default_vexpr_document }
        };

        // [tts:overflow]
        constexpr std::tuple vexpr_tts_overflow {
            std::tuple { NS::none,       ValueExpression::literal,          "visible",                                                 default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "hidden",                                                  default_vexpr_none,                         default_vexpr_document }
        };

        // [tts:padding]
        constexpr std::tuple vexpr_tts_padding {
            std::tuple { NS::none,       ValueExpression::literal,          "0px",                                                     default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::length,           "<length>",                                                default_vexpr_none,                         default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::length,           "<length> <length>",                                       default_vexpr_none,                         default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::length,           "<length> <length> <length>",                              default_vexpr_none,                         default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::length,           "<length> <length> <length> <length>",                     default_vexpr_none,                         default_vexpr_document }
        };

        // [tts:showBackground]
        constexpr std::tuple vexpr_tts_showBackground {
            std::tuple { NS::none,       ValueExpression::literal,          "always",                                                  default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "whenActive",                                              default_vexpr_none,                         default_vexpr_document }
        };
        
        // [tts:textAlign]
        constexpr std::tuple vexpr_tts_textAlign {
            std::tuple { NS::none,       ValueExpression::literal,          "start",                                                   default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "left",                                                    default_vexpr_none,                         default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "center",                                                  default_vexpr_none,                         default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "right",                                                   default_vexpr_none,                         default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "end",                                                     default_vexpr_none,                         default_vexpr_document }
        };

        // [tts:textDecoration]
        constexpr std::tuple vexpr_tts_textDecoration {
            std::tuple { NS::none,       ValueExpression::literal,          "none",                                                                                 default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::string,           "underline|noUnderline||lineThrough|noLineThrough||overline|noOverline",                default_vexpr_none,                         default_vexpr_document }
        };

        // [tts:textOutline]
        constexpr std::tuple vexpr_tts_textOutline {
            std::tuple { NS::none,       ValueExpression::literal,          "none",                                                    default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::compound,         "<color>? <length> <length>?",                             default_vexpr_none,                         default_vexpr_document }
        };

        // [tts:unicodeBidi]
        constexpr std::tuple vexpr_tts_unicodeBidi {
            std::tuple { NS::none,       ValueExpression::literal,          "none",                                                    default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "embed",                                                   default_vexpr_none,                         default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "bidiOverride",                                            default_vexpr_none,                         default_vexpr_document }
        };

        // [tts:visibility]
        constexpr std::tuple vexpr_tts_visibility {
            std::tuple { NS::none,       ValueExpression::literal,          "visible",                                                 default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "hidden",                                                  default_vexpr_none,                         default_vexpr_document }
        };

        // [tts:wrapOption]
        constexpr std::tuple vexpr_tts_wrapOption {
            std::tuple { NS::none,       ValueExpression::literal,          "wrap",                                                    default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "noWrap",                                                  default_vexpr_none,                         default_vexpr_document }
        };

        // [tts:writingMode]
        constexpr std::tuple vexpr_tts_writingMode {
            std::tuple { NS::none,       ValueExpression::literal,          "lrtb",                                                    default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "rltb",                                                    default_vexpr_none,                         default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "tbrl",                                                    default_vexpr_none,                         default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "tblr",                                                    default_vexpr_none,                         default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "lr",                                                      default_vexpr_none,                         default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "rl",                                                      default_vexpr_none,                         default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::literal,          "tb",                                                      default_vexpr_none,                         default_vexpr_document }
        };

        // [tts:zIndex]
        constexpr std::tuple vexpr_tts_zIndex {
            std::tuple { NS::none,       ValueExpression::literal,          "auto",                                                    default_vexpr_isDefault,                    default_vexpr_document },
            std::tuple { NS::none,       ValueExpression::integer,          "<integer>",                                               default_vexpr_none,                         default_vexpr_document }
        };

        constexpr std::tuple vexpr_tts {
            vexpr_tts_backgroundColor,
            vexpr_tts_color,
            vexpr_tts_direction,
            vexpr_tts_display,
            vexpr_tts_displayAlign,
            vexpr_tts_extent,
            vexpr_tts_fontFamily,
            vexpr_tts_fontSize,
            vexpr_tts_fontSyle,
            vexpr_tts_fontWeight,
            vexpr_tts_lineHeight,
            vexpr_tts_opacity,
            vexpr_tts_origin,
            vexpr_tts_overflow,
            vexpr_tts_padding,
            vexpr_tts_showBackground,
            vexpr_tts_textAlign,
            vexpr_tts_textDecoration,
            vexpr_tts_textOutline,
            vexpr_tts_unicodeBidi,
            vexpr_tts_visibility,
            vexpr_tts_wrapOption,
            vexpr_tts_writingMode,
            vexpr_tts_zIndex
        };

        // Attribute Node Entries
        // ---------------------------------------------------------------------------------------------------|

        

        // Old Value Expressions
        constexpr std::tuple flags{ default_vexpr_none, default_vexpr_quantifier, default_vexpr_document };
        constexpr std::tuple value_expressions { 
            std::tuple { NS::tt, ValueExpression::string, "<string1>", 0, 0 },
            std::tuple { NS::tt, ValueExpression::string, "<string2>", 0, 0 },
            std::tuple { NS::tt, ValueExpression::string, "<string3>", 0, 0 }
        };

        constexpr auto fnc_create_attribute = [] <class Telem, class Ttup, class Tflags, size_t Stup = std::tuple_size_v<Ttup>>
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

        constexpr auto fnc_create_content = []() { return 1; };

        constexpr std::tuple nodes {
            std::tuple{ std::move(default_node_document), NS::tt, Tag::tt, attr_xml_id, value_expressions, flags, VTFunctor{ std::move(fnc_create_attribute) }, VTFunctor{ std::move(fnc_create_content) } },
            std::tuple{ std::move(default_node_document), NS::tt, Tag::tt, attr_xml_id, value_expressions, flags, VTFunctor{ std::move(fnc_create_attribute) }, VTFunctor{ std::move(fnc_create_content) } }
        };

        return detail::CreateTTMLNodeList(std::move(nodes), detail::tuple_seq<decltype(nodes)>{});
    }

    template<class Tdict = decltype(CreateTTMLDictionary())>
    struct TTMLDictionary
    {
        using dictionary_t = Tdict;

        constexpr TTMLDictionary()
            : entries(CreateTTMLDictionary())
        {}

        Tdict entries;
    };
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif // VTDICTIONARIES_HEADER