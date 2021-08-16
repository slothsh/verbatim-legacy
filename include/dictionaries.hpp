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

        // Aliases for readability
        using grp = constants::ByteGroup;
        using doc = constants::TTMLDocument;
        using cnd = constants::NodeCondition;
        using qty = constants::NodeQuantifier;

        // Default expressions
        constexpr size_t cnd_vexpr_isDefault        = enum_integer(cnd::is_default);
        constexpr size_t cnd_vexpr_none             = enum_integer(cnd::none);
        constexpr size_t cnd_node_none              = enum_integer(cnd::none);
        constexpr size_t cnd_node_required          = enum_integer(cnd::required);

        constexpr size_t qty_node_zeroOrOne         = enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two);
        constexpr size_t qty_node_zeroOrMore        = enum_integer(qty::kleene_asterisk) | (0 << grp::one) | (0 << grp::two);
        constexpr size_t qty_vexpr_zeroOrOne        = enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two);

        constexpr size_t doc_node_all               = enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1);
        constexpr size_t doc_vexpr_all              = enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1);

        // Value Expression Entries
        // ---------------------------------------------------------------------------------------------------|

        // XML Namespace -------------------------------------------------|

        // [xml:id]
        constexpr std::tuple vexpr_xml_id {
            std::tuple { NS::none,       ValueExpression::id,               "<id>",                         cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [xml:lang]
        constexpr std::tuple vexpr_xml_lang {
            std::tuple { NS::none,       ValueExpression::language,         "<language>",                   cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [xml:space]
        constexpr std::tuple vexpr_xml_space {
            std::tuple { NS::none,       ValueExpression::literal,          "default",                      cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "preserve",                     cnd_vexpr_none,                         doc_vexpr_all }
        };

        constexpr std::tuple vexpr_xml {
            vexpr_xml_id,
            vexpr_xml_lang,
            vexpr_xml_space 
        };

        // TT Namespace --------------------------------------------------|

        // [tt:style]
        constexpr std::tuple vexpr_tt_style {
            std::tuple { NS::none,       ValueExpression::idrefs,           "<idrefs>",                     cnd_vexpr_isDefault,                    doc_vexpr_all }
        };

        // [tt:begin]
        constexpr std::tuple vexpr_tt_begin {
            std::tuple { NS::none,       ValueExpression::timeExpression,   "<timeExpression>",             cnd_vexpr_isDefault,                    doc_vexpr_all }
        };

        // [tt:end]
        constexpr std::tuple vexpr_tt_end {
            std::tuple { NS::none,       ValueExpression::timeExpression,   "<timeExpression>",             cnd_vexpr_isDefault,                    doc_vexpr_all }
        };

        // [tt:dur]
        constexpr std::tuple vexpr_tt_dur {
            std::tuple { NS::none,       ValueExpression::timeExpression,   "<timeExpression>",             cnd_vexpr_isDefault,                    doc_vexpr_all }
        };

        // [tt:region]
        constexpr std::tuple vexpr_tt_region {
            std::tuple { NS::none,       ValueExpression::idref,            "<idref>",                      cnd_vexpr_isDefault,                    doc_vexpr_all }
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
            std::tuple { NS::none,       ValueExpression::idrefs,           "<idrefs>",                                                cnd_vexpr_isDefault,               doc_vexpr_all },
        };

        // [ttm:actor]
        constexpr std::tuple vexpr_ttm_actor {
            std::tuple { NS::none,       ValueExpression::literal,          "action",                                                  cnd_vexpr_isDefault,               doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "caption",                                                 cnd_vexpr_none,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "description",                                             cnd_vexpr_none,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "dialog",                                                  cnd_vexpr_none,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "expletive",                                               cnd_vexpr_none,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "kinesic",                                                 cnd_vexpr_none,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "lyrics",                                                  cnd_vexpr_none,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "music",                                                   cnd_vexpr_none,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "narration",                                               cnd_vexpr_none,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "quality",                                                 cnd_vexpr_none,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "sound",                                                   cnd_vexpr_none,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "source",                                                  cnd_vexpr_none,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "suppressed",                                              cnd_vexpr_none,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "reproduction",                                            cnd_vexpr_none,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "thought",                                                 cnd_vexpr_none,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "title",                                                   cnd_vexpr_none,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "transcription",                                           cnd_vexpr_none,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::token_char,       "<extenstionRole>",                                        cnd_vexpr_none,                    doc_vexpr_all }
        };

        constexpr std::tuple vexpr_ttm {
            vexpr_ttm_agent,
            vexpr_ttm_actor
        };

        // TTP Namespace -------------------------------------------------|

        // [ttp:cellResolution]
        constexpr std::tuple vexpr_ttp_cellResolution {
            std::tuple { NS::none,       ValueExpression::literal,          "32 15",                        cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::digit,            "<digit>+ <digit>+",            cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [ttp:clockMode]
        constexpr std::tuple vexpr_ttp_clockMode {
            std::tuple { NS::none,       ValueExpression::literal,          "local",                        cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "gps",                          cnd_vexpr_none,                         doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "utc",                          cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [ttp:dropMode]
        constexpr std::tuple vexpr_ttp_dropMode {
            std::tuple { NS::none,       ValueExpression::literal,          "dropNTSC",                     cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "dropPAL",                      cnd_vexpr_none,                         doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "nonDrop",                      cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [ttp:frameRate]
        constexpr std::tuple vexpr_ttp_frameRate {
            std::tuple { NS::none,       ValueExpression::digit,            "<digit>+",                     cnd_vexpr_isDefault,                    doc_vexpr_all }
        };

        // [ttp:frameRateMultiplier]
        constexpr std::tuple vexpr_ttp_frameRateMultiplier {
            std::tuple { NS::none,       ValueExpression::digit,            "<digit>+ <digit>+",            cnd_vexpr_isDefault,                    doc_vexpr_all }
        };

        // [ttp:markerMode]
        constexpr std::tuple vexpr_ttp_markerMode {
            std::tuple { NS::none,       ValueExpression::literal,          "continuous",                   cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "discontinuous",                cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [ttp:pixelAspectRatio]
        constexpr std::tuple vexpr_ttp_pixelAspectRatio {
            std::tuple { NS::none,       ValueExpression::digit,            "<digit>+ <digit>+",            cnd_vexpr_isDefault,                    doc_vexpr_all }
        };

        // [ttp:profile]
        constexpr std::tuple vexpr_ttp_profile {
            std::tuple { NS::none,       ValueExpression::any_uri,          "<anyURI>",                     cnd_vexpr_isDefault,                    doc_vexpr_all }
        };

        // [ttp:subFrameRate]
        constexpr std::tuple vexpr_ttp_subFrameRate {
            std::tuple { NS::none,       ValueExpression::digit,            "<digit>+",                     cnd_vexpr_isDefault,                    doc_vexpr_all }
        };

        // [ttp:tickRate]
        constexpr std::tuple vexpr_ttp_tickRate {
            std::tuple { NS::none,       ValueExpression::digit,            "<digit>+",                     cnd_vexpr_isDefault,                    doc_vexpr_all }
        };

        // [ttp:timeBase]
        constexpr std::tuple vexpr_ttp_timeBase {
            std::tuple { NS::none,       ValueExpression::literal,          "media",                        cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "smpte",                        cnd_vexpr_none,                         doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "clock",                        cnd_vexpr_none,                         doc_vexpr_all }
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
            std::tuple { NS::none,       ValueExpression::color,            "<color>",                                                 cnd_vexpr_isDefault,                    doc_vexpr_all },
        };

        // [tts:color]
        constexpr std::tuple vexpr_tts_color {
            std::tuple { NS::none,       ValueExpression::color,            "<color>",                                                 cnd_vexpr_isDefault,                    doc_vexpr_all },
        };

        // [tts:direction]
        constexpr std::tuple vexpr_tts_direction {
            std::tuple { NS::none,       ValueExpression::literal,          "ltr",                                                     cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "rtl",                                                     cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [tts:display]
        constexpr std::tuple vexpr_tts_display {
            std::tuple { NS::none,       ValueExpression::literal,          "auto",                                                    cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "none",                                                    cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [tts:displayAlign]
        constexpr std::tuple vexpr_tts_displayAlign {
            std::tuple { NS::none,       ValueExpression::literal,          "before",                                                  cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "center",                                                  cnd_vexpr_none,                         doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "after",                                                   cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [tts:extent]
        constexpr std::tuple vexpr_tts_extent {
            std::tuple { NS::none,       ValueExpression::literal,          "auto",                                                    cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::length,           "<length> <length>",                                       cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [tts:fontFamily]
        constexpr std::tuple vexpr_tts_fontFamily {
            std::tuple { NS::none,       ValueExpression::literal,          "default",                                                 cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::font,             "<familyName>|<genericFamilyName>*",                       cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [tts:fontSize]
        constexpr std::tuple vexpr_tts_fontSize {
            std::tuple { NS::none,       ValueExpression::literal,          "1c",                                                      cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::length,           "<length> <length>?",                                      cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [tts:fontSyle]
        constexpr std::tuple vexpr_tts_fontSyle {
            std::tuple { NS::none,       ValueExpression::literal,          "normal",                                                  cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "italic",                                                  cnd_vexpr_none,                         doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "oblique",                                                 cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [tts:fontWeight]
        constexpr std::tuple vexpr_tts_fontWeight {
            std::tuple { NS::none,       ValueExpression::literal,          "normal",                                                  cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "bold",                                                    cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [tts:lineHeight]
        constexpr std::tuple vexpr_tts_lineHeight {
            std::tuple { NS::none,       ValueExpression::literal,          "normal",                                                  cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::length,           "<length>",                                                cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [tts:opacity]
        constexpr std::tuple vexpr_tts_opacity {
            std::tuple { NS::none,       ValueExpression::literal,          "1.0",                                                     cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::alpha,            "<alpha>",                                                 cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [tts:origin]
        constexpr std::tuple vexpr_tts_origin {
            std::tuple { NS::none,       ValueExpression::literal,          "auto",                                                    cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::length,           "<length> <length>",                                       cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [tts:overflow]
        constexpr std::tuple vexpr_tts_overflow {
            std::tuple { NS::none,       ValueExpression::literal,          "visible",                                                 cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "hidden",                                                  cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [tts:padding]
        constexpr std::tuple vexpr_tts_padding {
            std::tuple { NS::none,       ValueExpression::literal,          "0px",                                                     cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::length,           "<length>",                                                cnd_vexpr_none,                         doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::length,           "<length> <length>",                                       cnd_vexpr_none,                         doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::length,           "<length> <length> <length>",                              cnd_vexpr_none,                         doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::length,           "<length> <length> <length> <length>",                     cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [tts:showBackground]
        constexpr std::tuple vexpr_tts_showBackground {
            std::tuple { NS::none,       ValueExpression::literal,          "always",                                                  cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "whenActive",                                              cnd_vexpr_none,                         doc_vexpr_all }
        };
        
        // [tts:textAlign]
        constexpr std::tuple vexpr_tts_textAlign {
            std::tuple { NS::none,       ValueExpression::literal,          "start",                                                   cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "left",                                                    cnd_vexpr_none,                         doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "center",                                                  cnd_vexpr_none,                         doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "right",                                                   cnd_vexpr_none,                         doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "end",                                                     cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [tts:textDecoration]
        constexpr std::tuple vexpr_tts_textDecoration {
            std::tuple { NS::none,       ValueExpression::literal,          "none",                                                                                 cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::string,           "underline|noUnderline||lineThrough|noLineThrough||overline|noOverline",                cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [tts:textOutline]
        constexpr std::tuple vexpr_tts_textOutline {
            std::tuple { NS::none,       ValueExpression::literal,          "none",                                                    cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::compound,         "<color>? <length> <length>?",                             cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [tts:unicodeBidi]
        constexpr std::tuple vexpr_tts_unicodeBidi {
            std::tuple { NS::none,       ValueExpression::literal,          "none",                                                    cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "embed",                                                   cnd_vexpr_none,                         doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "bidiOverride",                                            cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [tts:visibility]
        constexpr std::tuple vexpr_tts_visibility {
            std::tuple { NS::none,       ValueExpression::literal,          "visible",                                                 cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "hidden",                                                  cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [tts:wrapOption]
        constexpr std::tuple vexpr_tts_wrapOption {
            std::tuple { NS::none,       ValueExpression::literal,          "wrap",                                                    cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "noWrap",                                                  cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [tts:writingMode]
        constexpr std::tuple vexpr_tts_writingMode {
            std::tuple { NS::none,       ValueExpression::literal,          "lrtb",                                                    cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "rltb",                                                    cnd_vexpr_none,                         doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "tbrl",                                                    cnd_vexpr_none,                         doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "tblr",                                                    cnd_vexpr_none,                         doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "lr",                                                      cnd_vexpr_none,                         doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "rl",                                                      cnd_vexpr_none,                         doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::literal,          "tb",                                                      cnd_vexpr_none,                         doc_vexpr_all }
        };

        // [tts:zIndex]
        constexpr std::tuple vexpr_tts_zIndex {
            std::tuple { NS::none,       ValueExpression::literal,          "auto",                                                    cnd_vexpr_isDefault,                    doc_vexpr_all },
            std::tuple { NS::none,       ValueExpression::integer,          "<integer>",                                               cnd_vexpr_none,                         doc_vexpr_all }
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

        // Attribute Elements
        // ---------------------------------------------------------------------------------------------------|

        // XML Core
        constexpr std::tuple attrelem_xml_id    { NS::xml,          Attribute::id    };
        constexpr std::tuple attrelem_xml_lang  { NS::xml,          Attribute::lang  };
        constexpr std::tuple attrelem_xml_space { NS::xml,          Attribute::space };
        constexpr std::tuple attrelem_xml_base  { NS::xml,          Attribute::base  };

        // TT Core
        constexpr std::tuple attrelem_tt_tt            { NS::tt,           Attribute::tt            };
        constexpr std::tuple attrelem_tt_ttm           { NS::tt,           Attribute::ttm           };
        constexpr std::tuple attrelem_tt_ttp           { NS::tt,           Attribute::ttp           };
        constexpr std::tuple attrelem_tt_tts           { NS::tt,           Attribute::tts           };
        constexpr std::tuple attrelem_tt_style         { NS::tt,           Attribute::style         };
        constexpr std::tuple attrelem_tt_region        { NS::tt,           Attribute::region        };
        constexpr std::tuple attrelem_tt_begin         { NS::tt,           Attribute::begin         };
        constexpr std::tuple attrelem_tt_dur           { NS::tt,           Attribute::dur           };
        constexpr std::tuple attrelem_tt_end           { NS::tt,           Attribute::end           };
        constexpr std::tuple attrelem_tt_timeContainer { NS::tt,           Attribute::timeContainer };

        // TT Metadata
        constexpr std::tuple attrelem_ttm_agent { NS::ttm,            Attribute::agent };
        constexpr std::tuple attrelem_ttm_role  { NS::ttm,            Attribute::role  };

        // TT Parameter
        constexpr std::tuple attrelem_ttp_profile             { NS::ttp,          Attribute::profile             };
        constexpr std::tuple attrelem_ttp_cellResolution      { NS::ttp,          Attribute::cellResolution      };
        constexpr std::tuple attrelem_ttp_clockMode           { NS::ttp,          Attribute::clockMode           };
        constexpr std::tuple attrelem_ttp_dropMode            { NS::ttp,          Attribute::dropMode            };
        constexpr std::tuple attrelem_ttp_frameRate           { NS::ttp,          Attribute::frameRate           };
        constexpr std::tuple attrelem_ttp_frameRateMultiplier { NS::ttp,          Attribute::frameRateMultiplier };
        constexpr std::tuple attrelem_ttp_markerMode          { NS::ttp,          Attribute::markerMode          };
        constexpr std::tuple attrelem_ttp_pixelAspectRatio    { NS::ttp,          Attribute::pixelAspectRatio    };
        constexpr std::tuple attrelem_ttp_subFrameRate        { NS::ttp,          Attribute::subFrameRate        };
        constexpr std::tuple attrelem_ttp_tickRate            { NS::ttp,          Attribute::tickRate            };
        constexpr std::tuple attrelem_ttp_timeBase            { NS::ttp,          Attribute::timeBase            };

        // TT Style
        constexpr std::tuple attrelem_tts_backgroundColor { NS::tts,         Attribute::backgroundColor };
        constexpr std::tuple attrelem_tts_color           { NS::tts,         Attribute::color           };
        constexpr std::tuple attrelem_tts_direction       { NS::tts,         Attribute::direction       };
        constexpr std::tuple attrelem_tts_display         { NS::tts,         Attribute::display         };
        constexpr std::tuple attrelem_tts_displayAlign    { NS::tts,         Attribute::displayAlign    };
        constexpr std::tuple attrelem_tts_extent          { NS::tts,         Attribute::extent          };
        constexpr std::tuple attrelem_tts_fontFamily      { NS::tts,         Attribute::fontFamily      };
        constexpr std::tuple attrelem_tts_fontSize        { NS::tts,         Attribute::fontSize        };
        constexpr std::tuple attrelem_tts_fontStyle       { NS::tts,         Attribute::fontStyle       };
        constexpr std::tuple attrelem_tts_fontWeight      { NS::tts,         Attribute::fontWeight      };
        constexpr std::tuple attrelem_tts_lineHeight      { NS::tts,         Attribute::lineHeight      };
        constexpr std::tuple attrelem_tts_opacity         { NS::tts,         Attribute::opacity         };
        constexpr std::tuple attrelem_tts_origin          { NS::tts,         Attribute::origin          };
        constexpr std::tuple attrelem_tts_overflow        { NS::tts,         Attribute::overflow        };
        constexpr std::tuple attrelem_tts_padding         { NS::tts,         Attribute::padding         };
        constexpr std::tuple attrelem_tts_showBackground  { NS::tts,         Attribute::showBackground  };
        constexpr std::tuple attrelem_tts_textAlign       { NS::tts,         Attribute::textAlign       };
        constexpr std::tuple attrelem_tts_textDecoration  { NS::tts,         Attribute::textDecoration  };
        constexpr std::tuple attrelem_tts_textOutline     { NS::tts,         Attribute::textOutline     };
        constexpr std::tuple attrelem_tts_unicodeBidi     { NS::tts,         Attribute::unicodeBidi     };
        constexpr std::tuple attrelem_tts_visibility      { NS::tts,         Attribute::visibility      };
        constexpr std::tuple attrelem_tts_wrapOption      { NS::tts,         Attribute::wrapOption      };
        constexpr std::tuple attrelem_tts_writingMode     { NS::tts,         Attribute::writingMode     };
        constexpr std::tuple attrelem_tts_zIndex          { NS::tts,         Attribute::zIndex          };

        // Attribute Node Entries
        // ---------------------------------------------------------------------------------------------------|

        // TTP group attribute factory
        constexpr auto attr_join_parameters = []
        <class Tattr, class Tparam, class Telem, class S, S... Sseq>
        (const Tattr&& value_expressions, const Tparam&& parameters, const Telem&& element, std::integer_sequence<S, Sseq...> sequence) {
            return std::tuple {
                std::tuple{ 
                    std::get<0>(parameters),
                    std::get<1>(parameters),
                    std::get<2>(parameters),
                    element,
                    std::get<Sseq>(value_expressions)
                }
                ...
            };
        };

        // TT Namespace -------------------------------------------------|

        // <tt:tt/>
        constexpr std::tuple attrgrp_tt_tt_main {
            std::tuple {
                cnd_node_none, qty_node_zeroOrOne, doc_node_all,
                attrelem_tt_tt,
                vexpr_xml_id
            },

            std::tuple {
                cnd_node_required, qty_node_zeroOrOne, doc_node_all,
                attrelem_tt_tt,
                vexpr_xml_lang
            },

            std::tuple {
                cnd_node_none, qty_node_zeroOrOne, doc_node_all,
                attrelem_tt_tt,
                vexpr_xml_space
            },

            std::tuple {
                cnd_node_none, qty_node_zeroOrOne, doc_node_all,
                attrelem_tt_tt,
                vexpr_tts_extent
            }
        };

        constexpr std::tuple attrgrp_tt_tt_ttp = attr_join_parameters (
            std::move(vexpr_ttp),
            std::tuple{ cnd_node_none, qty_node_zeroOrMore, doc_node_all },
            std::move(attrelem_tt_tt),
            std::make_index_sequence<std::tuple_size_v<decltype(vexpr_ttp)>>{}
        );

        // TODO: {any attribute not in default or any TT namespace}

        constexpr std::tuple attr_tt_tt = std::tuple_cat(
            attrgrp_tt_tt_main,
            attrgrp_tt_tt_ttp
        );

        return attr_tt_tt;

        // TTM Namespace -------------------------------------------------|
        // TTP Namespace -------------------------------------------------|
        // TTS Namespace -------------------------------------------------|

        // Old Value Expressions
        constexpr std::tuple flags{ cnd_vexpr_none, qty_vexpr_zeroOrOne, doc_vexpr_all };
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

        // constexpr auto fnc_create_content = []() { return 1; };

        // constexpr std::tuple nodes {
        //     std::tuple{ std::move(doc_node_all), NS::tt, Tag::tt, attr_xml_id, value_expressions, flags, VTFunctor{ std::move(fnc_create_attribute) }, VTFunctor{ std::move(fnc_create_content) } },
        //     std::tuple{ std::move(doc_node_all), NS::tt, Tag::tt, attr_xml_id, value_expressions, flags, VTFunctor{ std::move(fnc_create_attribute) }, VTFunctor{ std::move(fnc_create_content) } }
        // };

        // return detail::CreateTTMLNodeList(std::move(nodes), detail::tuple_seq<decltype(nodes)>{});
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