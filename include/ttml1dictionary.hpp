// Stefan "SoulXP" Olivier
// File: dictionaries.hpp
// Description: Definitions for various tables and dictionaries

#ifndef VTTTML1DICTIONARY_HEADER
#define VTTTML1DICTIONARY_HEADER

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "config.hpp"
#endif

// Standard headers
#include <iostream>
#include <type_traits>
#include <utility>
#include <concepts>
#include <optional>
#include <variant>

// Project headers
#include "dictionarynodes.hpp"

// Master TTML definition function ----------------------------------------------------------------------------------- 1 of 1 -|
// ============================================================================================================================|

namespace vt::dictionary
{
    namespace detail
    {
        static constexpr auto CreateTTMLDictionary()
        {
            using namespace magic_enum::bitwise_operators;
            using magic_enum::enum_integer;

            // Aliases for readability
            using grp = constants::ByteGroup;
            using doc = constants::TTMLDocument;
            using cnd = constants::NodeCondition;
            using qty = constants::NodeQuantifier;

            // Default expressions
            constexpr size_t cnd_vexpr_isDefault        = enum_integer(cnd::is_default);
            constexpr size_t cnd_vexpr_dependent        = enum_integer(cnd::element_dependent);
            constexpr size_t cnd_vexpr_none             = enum_integer(cnd::none);
            constexpr size_t cnd_attr_none              = enum_integer(cnd::none);
            constexpr size_t cnd_attr_required          = enum_integer(cnd::required);
            constexpr size_t cnd_element_required       = enum_integer(cnd::required);

            constexpr size_t qty_vexpr_zeroOrOne        = enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two);
            constexpr size_t qty_attr_zeroOrOne         = enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two);
            constexpr size_t qty_attr_one               = enum_integer(qty::kleene_one) | (0 << grp::one) | (0 << grp::two);
            constexpr size_t qty_content_none           = enum_integer(qty::none) | (0 << grp::one) | (0 << grp::two);
            constexpr size_t qty_content_zeroOrMore     = enum_integer(qty::kleene_asterisk) | (0 << grp::one) | (0 << grp::two);
            constexpr size_t qty_content_zeroOrOne      = enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::two);
            constexpr size_t qty_element_zeroOrMore     = enum_integer(qty::kleene_asterisk) | (0 << grp::one) | (0 << grp::two);

            constexpr size_t doc_attr_all               = enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1);
            constexpr size_t doc_vexpr_all              = enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1);
            constexpr size_t doc_content_all            = enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1);
            constexpr size_t doc_element_all            = enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1);

            constexpr std::tuple attrparams_default     { cnd_attr_none, qty_attr_zeroOrOne, doc_attr_all };

            // Value Expression Entries
            // ---------------------------------------------------------------------------------------------------|

            // XML Namespace -------------------------------------------------|

            // [xml:id]
            constexpr std::tuple vexpr_xml_id {
                ValueExpressionNode { NS::none,       ValueExpression::id,               "<id>",                         cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [xml:lang]
            constexpr std::tuple vexpr_xml_lang {
                ValueExpressionNode { NS::none,       ValueExpression::language,         "<language>",                   cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [xml:space]
            constexpr std::tuple vexpr_xml_space {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "default",                      cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "preserve",                     cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [xml:base]
            constexpr std::tuple vexpr_xml_base {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "[ttp:features]{http://www.w3.org/ns/ttml/feature/}",       cnd_vexpr_isDefault | cnd_vexpr_dependent,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "[ttp:extensions]{http://www.w3.org/ns/ttml/extension/}",   cnd_vexpr_isDefault | cnd_vexpr_dependent,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::any_uri,          "<anyURI>",                                                 cnd_vexpr_none,                                               doc_vexpr_all }
            };

            constexpr std::tuple vexpr_xml {
                vexpr_xml_id,
                vexpr_xml_lang,
                vexpr_xml_space 
            };

            // TT Namespace --------------------------------------------------|

            // [tt:style]
            constexpr std::tuple vexpr_tt_style {
                ValueExpressionNode { NS::none,       ValueExpression::idrefs,           "<idrefs>",                     cnd_vexpr_isDefault,                    doc_vexpr_all }
            };

            // [tt:begin]
            constexpr std::tuple vexpr_tt_begin {
                ValueExpressionNode { NS::none,       ValueExpression::timeExpression,   "<timeExpression>",             cnd_vexpr_isDefault,                    doc_vexpr_all }
            };

            // [tt:end]
            constexpr std::tuple vexpr_tt_end {
                ValueExpressionNode { NS::none,       ValueExpression::timeExpression,   "<timeExpression>",             cnd_vexpr_isDefault,                    doc_vexpr_all }
            };

            // [tt:dur]
            constexpr std::tuple vexpr_tt_dur {
                ValueExpressionNode { NS::none,       ValueExpression::timeExpression,   "<timeExpression>",             cnd_vexpr_isDefault,                    doc_vexpr_all }
            };

            // [tt:region]
            constexpr std::tuple vexpr_tt_region {
                ValueExpressionNode { NS::none,       ValueExpression::idref,            "<idref>",                      cnd_vexpr_isDefault,                    doc_vexpr_all }
            };

            // [tt:timeContainer]
            constexpr std::tuple vexpr_tt_timeContainer {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "par",                          cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "seq",                          cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [tt:type]
            constexpr std::tuple vexpr_tt_type {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "[ttm:agent]{person}",          cnd_vexpr_dependent,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "[ttm:agent]{character}",       cnd_vexpr_dependent,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "[ttm:agent]{group}",           cnd_vexpr_dependent,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "[ttm:agent]{organization}",    cnd_vexpr_dependent,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "[ttm:agent]{other}",           cnd_vexpr_dependent,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "[ttm:name]{full}",             cnd_vexpr_dependent,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "[ttm:name]{family}",           cnd_vexpr_dependent,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "[ttm:name]{given}",            cnd_vexpr_dependent,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "[ttm:name]{alias}",            cnd_vexpr_dependent,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "[ttm:name]{other}",            cnd_vexpr_dependent,                    doc_vexpr_all }
            };

            // [tt:use]
            constexpr std::tuple vexpr_tt_use {
                ValueExpressionNode { NS::none,       ValueExpression::any_uri,          "<anyURI>",                     cnd_vexpr_isDefault,                    doc_vexpr_all }
            };

            // [tt:value]
            constexpr std::tuple vexpr_tt_value {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "[ttp:feature]{required}",          cnd_vexpr_isDefault | cnd_vexpr_dependent,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "[ttp:extension]{required}",        cnd_vexpr_isDefault | cnd_vexpr_dependent,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "[ttp:feature]{optional}",          cnd_vexpr_dependent,                                          doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "[ttp:feature]{use}",               cnd_vexpr_dependent,                                          doc_vexpr_all }
            };

            constexpr std::tuple vexpr_tt {
                vexpr_tt_style,
                vexpr_tt_begin,
                vexpr_tt_end,
                vexpr_tt_dur,
                vexpr_tt_region,
                vexpr_tt_timeContainer
            };

            constexpr std::tuple vexpr_tt_timing {
                vexpr_tt_begin,
                vexpr_tt_end,
                vexpr_tt_dur,
                vexpr_tt_timeContainer
            };

            constexpr std::tuple vexpr_tt_layout {
                vexpr_tt_style,
                vexpr_tt_region
            };

            // TTM Namespace -------------------------------------------------|

            // [ttm:agent]
            constexpr std::tuple vexpr_ttm_agent {
                ValueExpressionNode { NS::none,       ValueExpression::idrefs,           "<idrefs>",                                                cnd_vexpr_isDefault,               doc_vexpr_all },
            };

            // [ttm:actor]
            constexpr std::tuple vexpr_ttm_role {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "action",                                                  cnd_vexpr_isDefault,               doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "caption",                                                 cnd_vexpr_none,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "description",                                             cnd_vexpr_none,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "dialog",                                                  cnd_vexpr_none,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "expletive",                                               cnd_vexpr_none,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "kinesic",                                                 cnd_vexpr_none,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "lyrics",                                                  cnd_vexpr_none,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "music",                                                   cnd_vexpr_none,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "narration",                                               cnd_vexpr_none,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "quality",                                                 cnd_vexpr_none,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "sound",                                                   cnd_vexpr_none,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "source",                                                  cnd_vexpr_none,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "suppressed",                                              cnd_vexpr_none,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "reproduction",                                            cnd_vexpr_none,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "thought",                                                 cnd_vexpr_none,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "title",                                                   cnd_vexpr_none,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "transcription",                                           cnd_vexpr_none,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::token_char,       "<extenstionRole>",                                        cnd_vexpr_none,                    doc_vexpr_all }
            };

            constexpr std::tuple vexpr_ttm {
                vexpr_ttm_agent,
                vexpr_ttm_role
            };

            // TTP Namespace -------------------------------------------------|

            // [ttp:cellResolution]
            constexpr std::tuple vexpr_ttp_cellResolution {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "32 15",                        cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::digit,            "<digit>+ <digit>+",            cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [ttp:clockMode]
            constexpr std::tuple vexpr_ttp_clockMode {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "local",                        cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "gps",                          cnd_vexpr_none,                         doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "utc",                          cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [ttp:dropMode]
            constexpr std::tuple vexpr_ttp_dropMode {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "dropNTSC",                     cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "dropPAL",                      cnd_vexpr_none,                         doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "nonDrop",                      cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [ttp:frameRate]
            constexpr std::tuple vexpr_ttp_frameRate {
                ValueExpressionNode { NS::none,       ValueExpression::digit,            "<digit>+",                     cnd_vexpr_isDefault,                    doc_vexpr_all }
            };

            // [ttp:frameRateMultiplier]
            constexpr std::tuple vexpr_ttp_frameRateMultiplier {
                ValueExpressionNode { NS::none,       ValueExpression::digit,            "<digit>+ <digit>+",            cnd_vexpr_isDefault,                    doc_vexpr_all }
            };

            // [ttp:markerMode]
            constexpr std::tuple vexpr_ttp_markerMode {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "continuous",                   cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "discontinuous",                cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [ttp:pixelAspectRatio]
            constexpr std::tuple vexpr_ttp_pixelAspectRatio {
                ValueExpressionNode { NS::none,       ValueExpression::digit,            "<digit>+ <digit>+",            cnd_vexpr_isDefault,                    doc_vexpr_all }
            };

            // [ttp:profile]
            constexpr std::tuple vexpr_ttp_profile {
                ValueExpressionNode { NS::none,       ValueExpression::any_uri,          "<anyURI>",                     cnd_vexpr_isDefault,                    doc_vexpr_all }
            };

            // [ttp:subFrameRate]
            constexpr std::tuple vexpr_ttp_subFrameRate {
                ValueExpressionNode { NS::none,       ValueExpression::digit,            "<digit>+",                     cnd_vexpr_isDefault,                    doc_vexpr_all }
            };

            // [ttp:tickRate]
            constexpr std::tuple vexpr_ttp_tickRate {
                ValueExpressionNode { NS::none,       ValueExpression::digit,            "<digit>+",                     cnd_vexpr_isDefault,                    doc_vexpr_all }
            };

            // [ttp:timeBase]
            constexpr std::tuple vexpr_ttp_timeBase {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "media",                        cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "smpte",                        cnd_vexpr_none,                         doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "clock",                        cnd_vexpr_none,                         doc_vexpr_all }
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
                ValueExpressionNode { NS::none,       ValueExpression::color,            "<color>",                                                 cnd_vexpr_isDefault,                    doc_vexpr_all },
            };

            // [tts:color]
            constexpr std::tuple vexpr_tts_color {
                ValueExpressionNode { NS::none,       ValueExpression::color,            "<color>",                                                 cnd_vexpr_isDefault,                    doc_vexpr_all },
            };

            // [tts:direction]
            constexpr std::tuple vexpr_tts_direction {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "ltr",                                                     cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "rtl",                                                     cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [tts:display]
            constexpr std::tuple vexpr_tts_display {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "auto",                                                    cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "none",                                                    cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [tts:displayAlign]
            constexpr std::tuple vexpr_tts_displayAlign {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "before",                                                  cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "center",                                                  cnd_vexpr_none,                         doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "after",                                                   cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [tts:extent]
            constexpr std::tuple vexpr_tts_extent {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "auto",                                                    cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::length,           "<length> <length>",                                       cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [tts:fontFamily]
            constexpr std::tuple vexpr_tts_fontFamily {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "default",                                                 cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::font,             "<familyName>|<genericFamilyName>*",                       cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [tts:fontSize]
            constexpr std::tuple vexpr_tts_fontSize {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "1c",                                                      cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::length,           "<length> <length>?",                                      cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [tts:fontSyle]
            constexpr std::tuple vexpr_tts_fontSyle {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "normal",                                                  cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "italic",                                                  cnd_vexpr_none,                         doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "oblique",                                                 cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [tts:fontWeight]
            constexpr std::tuple vexpr_tts_fontWeight {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "normal",                                                  cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "bold",                                                    cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [tts:lineHeight]
            constexpr std::tuple vexpr_tts_lineHeight {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "normal",                                                  cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::length,           "<length>",                                                cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [tts:opacity]
            constexpr std::tuple vexpr_tts_opacity {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "1.0",                                                     cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::alpha,            "<alpha>",                                                 cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [tts:origin]
            constexpr std::tuple vexpr_tts_origin {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "auto",                                                    cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::length,           "<length> <length>",                                       cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [tts:overflow]
            constexpr std::tuple vexpr_tts_overflow {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "visible",                                                 cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "hidden",                                                  cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [tts:padding]
            constexpr std::tuple vexpr_tts_padding {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "0px",                                                     cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::length,           "<length>",                                                cnd_vexpr_none,                         doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::length,           "<length> <length>",                                       cnd_vexpr_none,                         doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::length,           "<length> <length> <length>",                              cnd_vexpr_none,                         doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::length,           "<length> <length> <length> <length>",                     cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [tts:showBackground]
            constexpr std::tuple vexpr_tts_showBackground {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "always",                                                  cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "whenActive",                                              cnd_vexpr_none,                         doc_vexpr_all }
            };
            
            // [tts:textAlign]
            constexpr std::tuple vexpr_tts_textAlign {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "start",                                                   cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "left",                                                    cnd_vexpr_none,                         doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "center",                                                  cnd_vexpr_none,                         doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "right",                                                   cnd_vexpr_none,                         doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "end",                                                     cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [tts:textDecoration]
            constexpr std::tuple vexpr_tts_textDecoration {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "none",                                                                                 cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::string,           "underline|noUnderline||lineThrough|noLineThrough||overline|noOverline",                cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [tts:textOutline]
            constexpr std::tuple vexpr_tts_textOutline {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "none",                                                    cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::compound,         "<color>? <length> <length>?",                             cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [tts:unicodeBidi]
            constexpr std::tuple vexpr_tts_unicodeBidi {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "none",                                                    cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "embed",                                                   cnd_vexpr_none,                         doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "bidiOverride",                                            cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [tts:visibility]
            constexpr std::tuple vexpr_tts_visibility {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "visible",                                                 cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "hidden",                                                  cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [tts:wrapOption]
            constexpr std::tuple vexpr_tts_wrapOption {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "wrap",                                                    cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "noWrap",                                                  cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [tts:writingMode]
            constexpr std::tuple vexpr_tts_writingMode {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "lrtb",                                                    cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "rltb",                                                    cnd_vexpr_none,                         doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "tbrl",                                                    cnd_vexpr_none,                         doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "tblr",                                                    cnd_vexpr_none,                         doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "lr",                                                      cnd_vexpr_none,                         doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "rl",                                                      cnd_vexpr_none,                         doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "tb",                                                      cnd_vexpr_none,                         doc_vexpr_all }
            };

            // [tts:zIndex]
            constexpr std::tuple vexpr_tts_zIndex {
                ValueExpressionNode { NS::none,       ValueExpression::literal,          "auto",                                                    cnd_vexpr_isDefault,                    doc_vexpr_all },
                ValueExpressionNode { NS::none,       ValueExpression::integer,          "<integer>",                                               cnd_vexpr_none,                         doc_vexpr_all }
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

            constexpr std::tuple attrelem_xml {
                attrelem_xml_id,
                attrelem_xml_lang,
                attrelem_xml_space
            };

            // TT Core
            constexpr std::tuple attrelem_tt_tt            { NS::tt,           Attribute::tt            };
            constexpr std::tuple attrelem_tt_ttm           { NS::tt,           Attribute::ttm           };
            constexpr std::tuple attrelem_tt_ttp           { NS::tt,           Attribute::ttp           };
            constexpr std::tuple attrelem_tt_tts           { NS::tt,           Attribute::tts           };
            constexpr std::tuple attrelem_tt_style         { NS::tt,           Attribute::style         };
            constexpr std::tuple attrelem_tt_type          { NS::tt,           Attribute::type          };
            constexpr std::tuple attrelem_tt_use           { NS::tt,           Attribute::use           };
            constexpr std::tuple attrelem_tt_value         { NS::tt,           Attribute::value         };
            constexpr std::tuple attrelem_tt_region        { NS::tt,           Attribute::region        };
            constexpr std::tuple attrelem_tt_begin         { NS::tt,           Attribute::begin         };
            constexpr std::tuple attrelem_tt_dur           { NS::tt,           Attribute::dur           };
            constexpr std::tuple attrelem_tt_end           { NS::tt,           Attribute::end           };
            constexpr std::tuple attrelem_tt_timeContainer { NS::tt,           Attribute::timeContainer };

            constexpr std::tuple attrelem_tt {
                attrelem_tt_tt,
                attrelem_tt_ttm,
                attrelem_tt_ttp,
                attrelem_tt_tts,
                attrelem_tt_style,
                attrelem_tt_region,
                attrelem_tt_begin,
                attrelem_tt_dur,
                attrelem_tt_end,
                attrelem_tt_timeContainer
            };

            constexpr std::tuple attrelem_tt_timing {
                attrelem_tt_begin,
                attrelem_tt_dur,
                attrelem_tt_end,
                attrelem_tt_timeContainer
            };

            constexpr std::tuple attrelem_tt_layout {
                attrelem_tt_style,
                attrelem_tt_region
            };

            // TT Metadata
            constexpr std::tuple attrelem_ttm_agent { NS::ttm,            Attribute::agent };
            constexpr std::tuple attrelem_ttm_role  { NS::ttm,            Attribute::role  };

            constexpr std::tuple attrelem_ttm {
                attrelem_ttm_agent,
                attrelem_ttm_role
            };

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

            constexpr std::tuple attrelem_ttp {
                attrelem_ttp_profile,
                attrelem_ttp_cellResolution,
                attrelem_ttp_clockMode,
                attrelem_ttp_dropMode,
                attrelem_ttp_frameRate,
                attrelem_ttp_frameRateMultiplier,
                attrelem_ttp_markerMode,
                attrelem_ttp_pixelAspectRatio,
                attrelem_ttp_subFrameRate,
                attrelem_ttp_tickRate,
                attrelem_ttp_timeBase
            };

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

            constexpr std::tuple attrelem_tts {
                attrelem_tts_backgroundColor,
                attrelem_tts_color, 
                attrelem_tts_direction,
                attrelem_tts_display,
                attrelem_tts_displayAlign,
                attrelem_tts_extent,
                attrelem_tts_fontFamily,
                attrelem_tts_fontSize,
                attrelem_tts_fontStyle,
                attrelem_tts_fontWeight,
                attrelem_tts_lineHeight,
                attrelem_tts_opacity,
                attrelem_tts_origin,
                attrelem_tts_overflow,
                attrelem_tts_padding,
                attrelem_tts_showBackground,
                attrelem_tts_textAlign,
                attrelem_tts_textDecoration,
                attrelem_tts_textOutline,
                attrelem_tts_unicodeBidi,
                attrelem_tts_visibility,
                attrelem_tts_wrapOption,
                attrelem_tts_writingMode,
                attrelem_tts_zIndex
            };

            // Data type elements
            constexpr std::tuple contentelem_pcdata { NS::none,         GenericData::PCDATA };

            // Tag elements
            constexpr std::tuple tagelem_tt_div           { NS::tt,           Tag::div           };
            constexpr std::tuple tagelem_tt_p             { NS::tt,           Tag::p             };
            constexpr std::tuple tagelem_tt_span          { NS::tt,           Tag::span          };
            constexpr std::tuple tagelem_tt_br            { NS::tt,           Tag::br            };
            constexpr std::tuple tagelem_tt_set           { NS::tt,           Tag::set           };
            constexpr std::tuple tagelem_tt_metadata      { NS::tt,           Tag::metadata      };

            constexpr std::tuple tagelem_ttm_agent        { NS::ttm,           Tag::agent        };
            constexpr std::tuple tagelem_ttm_copyright    { NS::ttm,           Tag::copyright    };
            constexpr std::tuple tagelem_ttm_desc         { NS::ttm,           Tag::desc         };
            constexpr std::tuple tagelem_ttm_title        { NS::ttm,           Tag::title        };

            constexpr std::tuple tagelem_ttp_profile      { NS::ttp,           Tag::profile      };

            // Element Groups
            using singlegrp_entry_t = std::tuple<std::tuple<NS, Tag>>;

            constexpr singlegrp_entry_t elemgrp_animation     { tagelem_tt_set                                                                                                         };
            constexpr std::tuple elemgrp_block                { tagelem_tt_div,          tagelem_tt_p                                                                                  };
            constexpr std::tuple elemgrp_inline               { tagelem_tt_span,         tagelem_tt_br,         contentelem_pcdata                                                     };
            constexpr std::tuple elemgrp_metadata             { tagelem_tt_metadata,     tagelem_ttm_agent,     tagelem_ttm_copyright,       tagelem_ttm_desc,       tagelem_ttm_title };
            constexpr singlegrp_entry_t elemgrp_parameters    { tagelem_ttp_profile                                                                                                    };

            // Attribute Node Parameters
            // ---------------------------------------------------------------------------------------------------|
            constexpr std::tuple attrparams_xml {
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // xml_id
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // xml_lang
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // xml_space
            };

            constexpr std::tuple attrparams_tt {
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tt_style
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tt_begin
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tt_end
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tt_dur
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tt_region
            };

            constexpr std::tuple attrparams_ttm {
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // ttm_agent
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all }      // ttm_actor
            };

            constexpr std::tuple attrparams_ttp {
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },      // ttp_cellResolution
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },      // ttp_clockMode
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },      // ttp_dropMode
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },      // ttp_frameRate
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },      // ttp_frameRateMultiplier
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },      // ttp_markerMode
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },      // ttp_pixelAspectRatio
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },      // ttp_profile
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },      // ttp_subFrameRate
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },      // ttp_tickRate
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all }       // ttp_timeBase
            };

            constexpr std::tuple attrparams_tts {
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tts_backgroundColor
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tts_color
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tts_direction
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tts_display
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tts_displayAlign
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tts_extent
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tts_fontFamily
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tts_fontSize
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tts_fontSyle
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tts_fontWeight
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tts_lineHeight
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tts_opacity
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tts_origin
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tts_overflow
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tts_padding
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tts_showBackground
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tts_textAlign
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tts_textDecoration
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tts_textOutline
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tts_unicodeBidi
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tts_visibility
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tts_wrapOption
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all },     // tts_writingMode
                std::tuple { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all }      // tts_zIndex
            };

            // Content Node Parameters
            // ---------------------------------------------------------------------------------------------------|
            
            using single_entry_t = std::tuple<std::tuple<size_t, size_t>>;

            constexpr single_entry_t contentparams_animation {
                std::tuple { qty_content_zeroOrMore,        doc_content_all }
            };

            constexpr std::tuple contentparams_block {
                std::tuple { qty_content_zeroOrMore,        doc_content_all },
                std::tuple { qty_content_zeroOrMore,        doc_content_all }
            };

            constexpr std::tuple contentparams_inline {
                std::tuple { qty_content_zeroOrMore,        doc_content_all },
                std::tuple { qty_content_zeroOrMore,        doc_content_all },
                std::tuple { qty_content_zeroOrMore,        doc_content_all }
            };

            constexpr std::tuple contentparams_metadata {
                std::tuple { qty_content_zeroOrMore,        doc_content_all },
                std::tuple { qty_content_zeroOrMore,        doc_content_all },
                std::tuple { qty_content_zeroOrMore,        doc_content_all },
                std::tuple { qty_content_zeroOrMore,        doc_content_all },
                std::tuple { qty_content_zeroOrMore,        doc_content_all }
            };

            constexpr single_entry_t contentparams_parameters {
                std::tuple { qty_content_zeroOrMore,        doc_content_all }
            };

            // ---------------------------------------------------------------------------------------------------|

            // Attribute Node Entries
            // ---------------------------------------------------------------------------------------------------|

            // Helper functions for generating attribute nodes
            constexpr auto CreateAttributeNode = []
            <class Tattr, class Tparam, class Telem, class S, S... Sseq>
            (const Tattr& value_expressions, const Tparam& parameters, const Telem& element, std::integer_sequence<S, Sseq...> sequence)
            {
                using params_t = std::tuple<size_t, size_t, size_t>;
                if constexpr (std::is_same_v<params_t, Tparam>) {
                    return std::tuple {
                        AttributeNode { 
                            std::move(std::get<0>(parameters)),
                            std::move(std::get<1>(parameters)),
                            std::move(std::get<2>(parameters)),
                            std::move(std::get<Sseq>(element)),
                            std::move(std::get<Sseq>(value_expressions))
                        }
                        ...
                    };
                } else if constexpr (!std::conjunction_v<std::is_same<params_t, decltype(std::get<Sseq>(parameters))> ... >) {
                    return std::tuple {
                        AttributeNode { 
                            std::move(std::get<0>(std::get<Sseq>(parameters))),
                            std::move(std::get<1>(std::get<Sseq>(parameters))),
                            std::move(std::get<2>(std::get<Sseq>(parameters))),
                            std::move(std::get<Sseq>(element)),
                            std::move(std::get<Sseq>(value_expressions))
                        }
                        ...
                    };
                }
            };

            constexpr auto CreateContentNode = []
            <class Tparam, class Telem, class S, S... Sseq>
            (const Tparam& parameters, const Telem& element, std::integer_sequence<S, Sseq...> sequence)
            {
                using params_t = std::tuple<size_t, size_t>;
                if constexpr (std::is_same_v<params_t, Tparam>) {
                    return std::tuple {
                        ContentNode { 
                            std::move(std::get<0>(parameters)),
                            std::move(std::get<1>(parameters)),
                            std::move(std::get<Sseq>(element))
                        }
                        ...
                    };
                } else if constexpr (!std::conjunction_v<std::is_same<params_t, decltype(std::get<Sseq>(parameters))> ... >) {
                    return std::tuple {
                        ContentNode { 
                            std::move(std::get<0>(std::get<Sseq>(parameters))),
                            std::move(std::get<1>(std::get<Sseq>(parameters))),
                            std::move(std::get<Sseq>(element))
                        }
                        ...
                    };
                }
            };

            // TT Namespace -------------------------------------------------|

            // <tt:tt/>
            constexpr std::tuple attrgrp_tt_tt = std::tuple_cat (
                std::tuple {
                    AttributeNode   { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all,           attrelem_xml_id,            vexpr_xml_id                           },
                    AttributeNode   { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all,           attrelem_xml_space,         vexpr_xml_space                        },
                    AttributeNode   { cnd_attr_required,     qty_attr_one,               doc_attr_all,           attrelem_xml_lang,          vexpr_xml_lang                         },
                    AttributeNode   { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all,           attrelem_tts_extent,        vexpr_tts_extent                       },
                },
                CreateAttributeNode ( vexpr_ttp,             attrparams_ttp,             attrelem_ttp,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_ttp)>>{} )
                // TODO: {any attribute not in default or any TT namespace}
            );

            // <tt:head/>
            constexpr std::tuple attrgrp_tt_head = std::tuple_cat (
                CreateAttributeNode ( vexpr_xml,             attrparams_xml,             attrelem_xml,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_xml)>>{} )
                // TODO: {any attribute not in default or any TT namespace}
            );

            // <tt:body/>
            constexpr std::tuple attrgrp_tt_body = std::tuple_cat (
                CreateAttributeNode ( vexpr_xml,             attrparams_xml,             attrelem_xml,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_xml)>>{}       ),
                CreateAttributeNode ( vexpr_tt_timing,       attrparams_default,         attrelem_tt_timing,     std::make_index_sequence<std::tuple_size_v<decltype(vexpr_tt_timing)>>{} ),
                CreateAttributeNode ( vexpr_tt_layout,       attrparams_default,         attrelem_tt_layout,     std::make_index_sequence<std::tuple_size_v<decltype(vexpr_tt_layout)>>{} ),
                CreateAttributeNode ( vexpr_ttm,             attrparams_ttm,             attrelem_ttm,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_ttm)>>{}       ),
                CreateAttributeNode ( vexpr_tts,             attrparams_tts,             attrelem_tts,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_tts)>>{}       )
                // TODO: {any attribute not in default or any TT namespace}
            );
            
            // <tt:div/>
            constexpr std::tuple attrgrp_tt_div = std::tuple_cat (
                CreateAttributeNode ( vexpr_xml,             attrparams_xml,             attrelem_xml,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_xml)>>{}       ),
                CreateAttributeNode ( vexpr_tt_timing,       attrparams_default,         attrelem_tt_timing,     std::make_index_sequence<std::tuple_size_v<decltype(vexpr_tt_timing)>>{} ),
                CreateAttributeNode ( vexpr_tt_layout,       attrparams_default,         attrelem_tt_layout,     std::make_index_sequence<std::tuple_size_v<decltype(vexpr_tt_layout)>>{} ),
                CreateAttributeNode ( vexpr_ttm,             attrparams_ttm,             attrelem_ttm,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_ttm)>>{}       ),
                CreateAttributeNode ( vexpr_tts,             attrparams_tts,             attrelem_tts,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_tts)>>{}       )
                // TODO: {any attribute not in default or any TT namespace}
            );

            // <tt:p/>
            constexpr std::tuple attrgrp_tt_p = std::tuple_cat (
                CreateAttributeNode ( vexpr_xml,             attrparams_xml,             attrelem_xml,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_xml)>>{}       ),
                CreateAttributeNode ( vexpr_tt_timing,       attrparams_default,         attrelem_tt_timing,     std::make_index_sequence<std::tuple_size_v<decltype(vexpr_tt_timing)>>{} ),
                CreateAttributeNode ( vexpr_tt_layout,       attrparams_default,         attrelem_tt_layout,     std::make_index_sequence<std::tuple_size_v<decltype(vexpr_tt_layout)>>{} ),
                CreateAttributeNode ( vexpr_ttm,             attrparams_ttm,             attrelem_ttm,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_ttm)>>{}       ),
                CreateAttributeNode ( vexpr_tts,             attrparams_tts,             attrelem_tts,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_tts)>>{}       )
                // TODO: {any attribute not in default or any TT namespace}
            );

            // <tt:span/>
            constexpr std::tuple attrgrp_tt_span = std::tuple_cat (
                CreateAttributeNode ( vexpr_xml,             attrparams_xml,             attrelem_xml,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_xml)>>{}       ),
                CreateAttributeNode ( vexpr_tt_timing,       attrparams_default,         attrelem_tt_timing,     std::make_index_sequence<std::tuple_size_v<decltype(vexpr_tt_timing)>>{} ),
                CreateAttributeNode ( vexpr_tt_layout,       attrparams_default,         attrelem_tt_layout,     std::make_index_sequence<std::tuple_size_v<decltype(vexpr_tt_layout)>>{} ),
                CreateAttributeNode ( vexpr_ttm,             attrparams_ttm,             attrelem_ttm,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_ttm)>>{}       ),
                CreateAttributeNode ( vexpr_tts,             attrparams_tts,             attrelem_tts,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_tts)>>{}       )
                // TODO: {any attribute not in default or any TT namespace}
            );

            // <tt:br/>
            constexpr std::tuple attrgrp_tt_br = std::tuple_cat (
                std::tuple {
                    AttributeNode   { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all,           attrelem_tt_style,            vexpr_tt_style                             }
                },
                CreateAttributeNode ( vexpr_xml,             attrparams_xml,             attrelem_xml,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_xml)>>{}       ),
                CreateAttributeNode ( vexpr_ttm,             attrparams_ttm,             attrelem_ttm,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_ttm)>>{}       ),
                CreateAttributeNode ( vexpr_tts,             attrparams_tts,             attrelem_tts,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_tts)>>{}       )
                // TODO: {any attribute not in default or any TT namespace}
            );

            // <tt:metadata/>
            constexpr std::tuple attrgrp_tt_metadata = std::tuple_cat (
                CreateAttributeNode ( vexpr_xml,             attrparams_xml,             attrelem_xml,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_xml)>>{}       )
                // TODO: {any attribute not in default or any TT namespace}
            );

            // <tt:layout/>
            constexpr std::tuple attrgrp_tt_layout = std::tuple_cat (
                CreateAttributeNode ( vexpr_xml,             attrparams_xml,             attrelem_xml,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_xml)>>{}       )
                // TODO: {any attribute not in default or any TT namespace}
            );

            // <tt:region/>
            constexpr std::tuple attrgrp_tt_region = std::tuple_cat (
                std::tuple { 
                    AttributeNode   { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all,           attrelem_ttm_role,            vexpr_ttm_role                             },
                    AttributeNode   { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all,           attrelem_tt_style,            vexpr_tt_style                             }
                },
                CreateAttributeNode ( vexpr_xml,             attrparams_xml,             attrelem_xml,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_xml)>>{}       ),
                CreateAttributeNode ( vexpr_tts,             attrparams_tts,             attrelem_tts,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_tts)>>{}       ),
                CreateAttributeNode ( vexpr_tt_timing,       attrparams_default,         attrelem_tt_timing,     std::make_index_sequence<std::tuple_size_v<decltype(vexpr_tt_timing)>>{} )
                // TODO: {any attribute not in default or any TT namespace}
            );

            // <tt:set/>
            constexpr std::tuple attrgrp_tt_set = std::tuple_cat (
                std::tuple {
                    AttributeNode   { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all,           attrelem_tt_begin,            vexpr_tt_begin                       },
                    AttributeNode   { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all,           attrelem_tt_dur,              vexpr_tt_dur                         },
                    AttributeNode   { cnd_attr_none,         qty_attr_zeroOrOne,         doc_attr_all,           attrelem_tt_end,              vexpr_tt_end                         }
                },
                CreateAttributeNode ( vexpr_xml,             attrparams_xml,             attrelem_xml,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_xml)>>{} )
                // TODO: {any attribute not in default or any TT namespace}
            );

            // <tt:styling/>
            constexpr std::tuple attrgrp_tt_styling = std::tuple_cat (
                CreateAttributeNode ( vexpr_xml,            attrparams_xml,              attrelem_xml,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_xml)>>{} )
                // TODO: {any attribute not in default or any TT namespace}
            );

            // <tt:style/>
            constexpr std::tuple attrgrp_tt_style = std::tuple_cat (
                std::tuple {
                    AttributeNode   { cnd_attr_none,          qty_attr_zeroOrOne,             doc_attr_all,           attrelem_tt_style,          vexpr_tt_style                         }
                },
                CreateAttributeNode ( vexpr_xml,              attrparams_xml,                 attrelem_xml,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_xml)>>{} ),
                CreateAttributeNode ( vexpr_tts,              attrparams_tts,                 attrelem_tts,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_tts)>>{} )
                // TODO: {any attribute not in default or any TT namespace}
            );

            // TTM Namespace -------------------------------------------------|

            // <ttm:title/>
            constexpr std::tuple attrgrp_ttm_title = std::tuple_cat (
                CreateAttributeNode ( vexpr_xml,              attrparams_xml,       attrelem_xml,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_xml)>>{} )
                // TODO: {any attribute not in default or any TT namespace}
            );

            // <ttm:desc/>
            constexpr std::tuple attrgrp_ttm_desc = std::tuple_cat (
                CreateAttributeNode ( vexpr_xml,              attrparams_xml,       attrelem_xml,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_xml)>>{} )
                // TODO: {any attribute not in default or any TT namespace}
            );

            // <ttm:copyright/>
            constexpr std::tuple attrgrp_ttm_copyright = std::tuple_cat (
                CreateAttributeNode ( vexpr_xml,              attrparams_xml,       attrelem_xml,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_xml)>>{} )
                // TODO: {any attribute not in default or any TT namespace}
            );

            // <ttm:agent/>
            constexpr std::tuple attrgrp_ttm_agent = std::tuple_cat (
                std::tuple {
                    AttributeNode   { cnd_attr_required,      qty_attr_one,         doc_attr_all,           attrelem_tt_type,           vexpr_tt_type                          }
                },
                CreateAttributeNode ( vexpr_xml,              attrparams_xml,       attrelem_xml,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_xml)>>{} )
                // TODO: {any attribute not in default or any TT namespace}
            );

            // <ttm:name/>
            constexpr std::tuple attrgrp_ttm_name = std::tuple_cat (
                std::tuple {
                    AttributeNode   { cnd_attr_required,      qty_attr_one,         doc_attr_all,           attrelem_tt_type,           vexpr_tt_type                          }
                },
                CreateAttributeNode ( vexpr_xml,              attrparams_xml,       attrelem_xml,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_xml)>>{} )
                // TODO: {any attribute not in default or any TT namespace}
            );

            // <ttm:actor/>
            constexpr std::tuple attrgrp_ttm_actor = std::tuple_cat (
                std::tuple {
                    AttributeNode   { cnd_attr_required,      qty_attr_one,         doc_attr_all,           attrelem_ttm_agent,         vexpr_ttm_agent                        }
                },
                CreateAttributeNode ( vexpr_xml,              attrparams_xml,       attrelem_xml,           std::make_index_sequence<std::tuple_size_v<decltype(vexpr_xml)>>{} )
                // TODO: {any attribute not in default or any TT namespace}
            );

            // TTP Namespace -------------------------------------------------|

            // <ttp:profile/>
            constexpr std::tuple attrgrp_ttp_profile = std::tuple_cat (
                std::tuple {
                    AttributeNode   { cnd_attr_none,      qty_attr_zeroOrOne,         doc_attr_all,           attrelem_xml_id,            vexpr_xml_id                         },
                    AttributeNode   { cnd_attr_none,      qty_attr_zeroOrOne,         doc_attr_all,           attrelem_tt_use,            vexpr_tt_use                         }
                }
                // TODO: {any attribute not in default or any TT namespace}
            );

            // <ttp:features/>
            constexpr std::tuple attrgrp_ttp_features = std::tuple_cat (
                std::tuple {
                    AttributeNode   { cnd_attr_none,      qty_attr_zeroOrOne,         doc_attr_all,           attrelem_xml_id,            vexpr_xml_id                         },
                    AttributeNode   { cnd_attr_none,      qty_attr_zeroOrOne,         doc_attr_all,           attrelem_xml_base,          vexpr_xml_base                       }
                }
                // TODO: {any attribute not in default or any TT namespace}
            );

            // <ttp:feature/>
            constexpr std::tuple attrgrp_ttp_feature = std::tuple_cat (
                std::tuple {
                    AttributeNode   { cnd_attr_none,      qty_attr_zeroOrOne,         doc_attr_all,           attrelem_xml_id,            vexpr_xml_id                         },
                    AttributeNode   { cnd_attr_none,      qty_attr_zeroOrOne,         doc_attr_all,           attrelem_tt_value,          vexpr_tt_value                       }
                }
                // TODO: {any attribute not in default or any TT namespace}
            );

            // <ttp:extensions/>
            constexpr std::tuple attrgrp_ttp_extensions = std::tuple_cat (
                std::tuple {
                    AttributeNode   { cnd_attr_none,      qty_attr_zeroOrOne,         doc_attr_all,           attrelem_xml_id,            vexpr_xml_id                         },
                    AttributeNode   { cnd_attr_none,      qty_attr_zeroOrOne,         doc_attr_all,           attrelem_xml_base,          vexpr_xml_base                       }
                }
                // TODO: {any attribute not in default or any TT namespace}
            );

            // <ttp:extension/>
            constexpr std::tuple attrgrp_ttp_extension = std::tuple_cat (
                std::tuple {
                    AttributeNode   { cnd_attr_none,      qty_attr_zeroOrOne,         doc_attr_all,           attrelem_xml_id,            vexpr_xml_id                         },
                    AttributeNode   { cnd_attr_none,      qty_attr_zeroOrOne,         doc_attr_all,           attrelem_tt_value,          vexpr_tt_value                       }
                }
                // TODO: {any attribute not in default or any TT namespace}
            );

            // Content Node Entries
            // ---------------------------------------------------------------------------------------------------|

            // TT Namespace --------------------------------------------------|

            // <tt:tt/>
            constexpr std::tuple content_tt_tt = std::tuple_cat (
                std::tuple {
                    ContentNode   { qty_content_zeroOrOne,               doc_content_all,                NS::tt,             Tag::head                                             },
                    ContentNode   { qty_content_zeroOrOne,               doc_content_all,                NS::tt,             Tag::body                                             }
                }
            );

            // <tt:head/>
            constexpr std::tuple content_tt_head = std::tuple_cat (
                std::tuple {
                    ContentNode   { qty_content_zeroOrOne,               doc_content_all,                NS::tt,             Tag::styling                                            },
                    ContentNode   { qty_content_zeroOrOne,               doc_content_all,                NS::tt,             Tag::layout                                             }
                },
                CreateContentNode ( contentparams_metadata,              elemgrp_metadata,               std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_metadata)>>{}   ),
                CreateContentNode ( contentparams_parameters,            elemgrp_parameters,             std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_parameters)>>{} )
            );

            // <tt:body/>
            constexpr std::tuple content_tt_body = std::tuple_cat (
                std::tuple {
                    ContentNode   { qty_content_zeroOrMore,               doc_content_all,               NS::tt,             Tag::div                                               }
                },
                CreateContentNode ( contentparams_animation,             elemgrp_animation,              std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_animation)>>{} ),
                CreateContentNode ( contentparams_metadata,              elemgrp_metadata,               std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_metadata)>>{}  )
            );

            // <tt:div/>
            constexpr std::tuple content_tt_div = std::tuple_cat (
                CreateContentNode ( contentparams_animation,             elemgrp_animation,              std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_animation)>>{} ),
                CreateContentNode ( contentparams_metadata,              elemgrp_metadata,               std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_metadata)>>{}  ),
                CreateContentNode ( contentparams_block,                 elemgrp_block,                  std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_block)>>{}     )
            );

            // <tt:p/>
            constexpr std::tuple content_tt_p = std::tuple_cat (
                CreateContentNode ( contentparams_animation,             elemgrp_animation,              std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_animation)>>{} ),
                CreateContentNode ( contentparams_metadata,              elemgrp_metadata,               std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_metadata)>>{}  ),
                CreateContentNode ( contentparams_inline,                 elemgrp_inline,                std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_inline)>>{}    )
            );

            // <tt:span/>
            constexpr std::tuple content_tt_span = std::tuple_cat (
                CreateContentNode ( contentparams_animation,             elemgrp_animation,              std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_animation)>>{} ),
                CreateContentNode ( contentparams_metadata,              elemgrp_metadata,               std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_metadata)>>{}  ),
                CreateContentNode ( contentparams_inline,                 elemgrp_inline,                std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_inline)>>{}    )
            );

            // <tt:br/>
            constexpr std::tuple content_tt_br = std::tuple_cat (
                CreateContentNode ( contentparams_animation,             elemgrp_animation,              std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_animation)>>{} ),
                CreateContentNode ( contentparams_metadata,              elemgrp_metadata,               std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_metadata)>>{}  )
            );

            // <tt:styling/>
            constexpr std::tuple content_tt_styling = std::tuple_cat (
                std::tuple {
                    ContentNode   { qty_content_zeroOrMore,              doc_content_all,                NS::tt,             Tag::style                                             }
                },
                CreateContentNode ( contentparams_metadata,              elemgrp_metadata,               std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_metadata)>>{}  )
            );

            // <tt:style/>
            constexpr std::tuple content_tt_style = std::tuple_cat (
                std::tuple {
                    ContentNode   { qty_content_none,                    doc_content_all,                NS::none,           Tag::none                                              }
                }
            );

            // <tt:layout/>
            constexpr std::tuple content_tt_layout = std::tuple_cat (
                std::tuple {
                    ContentNode   { qty_content_zeroOrMore,              doc_content_all,                NS::tt,             Tag::region                                            }
                },
                CreateContentNode ( contentparams_metadata,              elemgrp_metadata,               std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_metadata)>>{}  )
            );

            // <tt:region/>
            constexpr std::tuple content_tt_region = std::tuple_cat (
                std::tuple {
                    ContentNode   { qty_content_zeroOrMore,              doc_content_all,                NS::tt,             Tag::style                                             }
                },
                CreateContentNode ( contentparams_animation,             elemgrp_animation,              std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_animation)>>{} ),
                CreateContentNode ( contentparams_metadata,              elemgrp_metadata,               std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_metadata)>>{}  )
            );

            // <tt:set/>
            constexpr std::tuple content_tt_set = std::tuple_cat (
                CreateContentNode ( contentparams_metadata,              elemgrp_metadata,               std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_metadata)>>{}  )
            );

            // <tt:metadata/>
            constexpr std::tuple content_tt_metadata = std::tuple_cat (
                CreateContentNode ( contentparams_metadata,              elemgrp_metadata,               std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_metadata)>>{}  )
                // TODO: Content: ({any element in TT Metadata namespace}|{any element not in any TT namespace})*
            );

            // TTM Namespace -------------------------------------------------|

            // <ttm:title/>
            constexpr std::tuple content_ttm_title = std::tuple_cat (
                std::tuple {
                    ContentNode   { qty_content_zeroOrMore,              doc_content_all,                 NS::none,             GenericData::PCDATA                                 }
                }
            );

            // <ttm:desc/>
            constexpr std::tuple content_ttm_desc = std::tuple_cat (
                std::tuple {
                    ContentNode   { qty_content_zeroOrMore,              doc_content_all,                 NS::none,             GenericData::PCDATA                                 }
                }
            );

            // <ttm:copyright/>
            constexpr std::tuple content_ttm_copyright = std::tuple_cat (
                std::tuple {
                    ContentNode   { qty_content_zeroOrMore,              doc_content_all,                 NS::none,             GenericData::PCDATA                                 }
                }
            );

            // <ttm:agent/>
            constexpr std::tuple content_ttm_agent = std::tuple_cat (
                std::tuple {
                    ContentNode   { qty_content_zeroOrMore,              doc_content_all,                 NS::ttm,            Tag::name                                             },
                    ContentNode   { qty_content_zeroOrOne,               doc_content_all,                 NS::ttm,            Tag::actor                                            }
                }
            );

            // <ttm:name/>
            constexpr std::tuple content_ttm_name = std::tuple_cat (
                std::tuple {
                    ContentNode   { qty_content_zeroOrMore,              doc_content_all,                NS::none,             GenericData::PCDATA                                  }
                }
            );

            // <ttm:actor/>
            constexpr std::tuple content_ttm_actor = std::tuple_cat (
                std::tuple {
                    ContentNode   { qty_content_none,                    doc_content_all,                NS::none,           Tag::none                                              }
                }
            );

            // TTP Namespace -------------------------------------------------|

            // <ttp:profile/>
            constexpr std::tuple content_ttp_profile = std::tuple_cat (
                std::tuple {
                    ContentNode   { qty_content_zeroOrMore,              doc_content_all,                NS::ttp,            Tag::features                                          },
                    ContentNode   { qty_content_zeroOrMore,              doc_content_all,                NS::ttp,            Tag::extensions                                        }
                },
                CreateContentNode ( contentparams_metadata,              elemgrp_metadata,               std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_metadata)>>{}  )
            );

            // <ttp:features/>
            constexpr std::tuple content_ttp_features = std::tuple_cat (
                std::tuple {
                    ContentNode   { qty_content_zeroOrMore,              doc_content_all,                NS::ttp,            Tag::feature                                           }
                },
                CreateContentNode ( contentparams_metadata,              elemgrp_metadata,               std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_metadata)>>{}  )
            );

            // <ttp:feature/>
            constexpr std::tuple content_ttp_feature = std::tuple_cat (
                std::tuple {
                    ContentNode   { qty_content_zeroOrMore,              doc_content_all,                NS::none,             GenericData::PCDATA                                  }
                }
            );

            // <ttp:extensions/>
            constexpr std::tuple content_ttp_extensions = std::tuple_cat (
                std::tuple {
                    ContentNode   { qty_content_zeroOrMore,              doc_content_all,                NS::ttp,            Tag::extension                                         }
                },
                CreateContentNode ( contentparams_metadata,              elemgrp_metadata,               std::make_index_sequence<std::tuple_size_v<decltype(elemgrp_metadata)>>{}  )
            );

            // <ttp:extension/>
            constexpr std::tuple content_ttp_extension = std::tuple_cat (
                std::tuple {
                    ContentNode   { qty_content_zeroOrMore,              doc_content_all,                NS::none,             GenericData::PCDATA                                  }
                }
            );

            // Element Node Entries
            // ---------------------------------------------------------------------------------------------------|

            // TT Namespace --------------------------------------------------|
            constexpr DictionaryNode element_tt_tt       { doc_element_all,              NS::tt,             Tag::tt,                  attrgrp_tt_tt,                content_tt_tt       };
            constexpr DictionaryNode element_tt_head     { doc_element_all,              NS::tt,             Tag::head,                attrgrp_tt_head,              content_tt_head     };
            constexpr DictionaryNode element_tt_body     { doc_element_all,              NS::tt,             Tag::body,                attrgrp_tt_body,              content_tt_body     };
            constexpr DictionaryNode element_tt_div      { doc_element_all,              NS::tt,             Tag::div,                 attrgrp_tt_div,               content_tt_div      };
            constexpr DictionaryNode element_tt_p        { doc_element_all,              NS::tt,             Tag::p,                   attrgrp_tt_p,                 content_tt_p        };
            constexpr DictionaryNode element_tt_span     { doc_element_all,              NS::tt,             Tag::span,                attrgrp_tt_span,              content_tt_span     };
            constexpr DictionaryNode element_tt_br       { doc_element_all,              NS::tt,             Tag::br,                  attrgrp_tt_br,                content_tt_br       };
            constexpr DictionaryNode element_tt_styling  { doc_element_all,              NS::tt,             Tag::styling,             attrgrp_tt_styling,           content_tt_styling  };
            constexpr DictionaryNode element_tt_style    { doc_element_all,              NS::tt,             Tag::style,               attrgrp_tt_style,             content_tt_style    };
            constexpr DictionaryNode element_tt_layout   { doc_element_all,              NS::tt,             Tag::layout,              attrgrp_tt_layout,            content_tt_layout   };
            constexpr DictionaryNode element_tt_region   { doc_element_all,              NS::tt,             Tag::region,              attrgrp_tt_region,            content_tt_region   };
            constexpr DictionaryNode element_tt_set      { doc_element_all,              NS::tt,             Tag::set,                 attrgrp_tt_set,               content_tt_set      };
            constexpr DictionaryNode element_tt_metadata { doc_element_all,              NS::tt,             Tag::metadata,            attrgrp_tt_metadata,          content_tt_metadata };

            // TTM Namespace -------------------------------------------------|
            constexpr DictionaryNode element_ttm_title     { doc_element_all,          NS::ttm,              Tag::title,             attrgrp_ttm_title,                    content_ttm_title     };
            constexpr DictionaryNode element_ttm_desc      { doc_element_all,          NS::ttm,              Tag::desc,              attrgrp_ttm_desc,                     content_ttm_desc      };
            constexpr DictionaryNode element_ttm_copyright { doc_element_all,          NS::ttm,              Tag::copyright,         attrgrp_ttm_copyright,                content_ttm_copyright };
            constexpr DictionaryNode element_ttm_agent     { doc_element_all,          NS::ttm,              Tag::agent,             attrgrp_ttm_agent,                    content_ttm_agent     };
            constexpr DictionaryNode element_ttm_name      { doc_element_all,          NS::ttm,              Tag::name,              attrgrp_ttm_name,                     content_ttm_name      };
            constexpr DictionaryNode element_ttm_actor     { doc_element_all,          NS::ttm,              Tag::actor,             attrgrp_ttm_actor,                    content_ttm_actor     };

            // TTP Namespace -------------------------------------------------|
            constexpr DictionaryNode element_ttp_profile       { doc_element_all,          NS::ttp,              Tag::profile,                attrgrp_ttp_profile,             content_ttp_profile    };
            constexpr DictionaryNode element_ttp_features      { doc_element_all,          NS::ttp,              Tag::features,               attrgrp_ttp_features,            content_ttp_features   };
            constexpr DictionaryNode element_ttp_feature       { doc_element_all,          NS::ttp,              Tag::feature,                attrgrp_ttp_feature,             content_ttp_feature    };
            constexpr DictionaryNode element_ttp_extensions    { doc_element_all,          NS::ttp,              Tag::extensions,             attrgrp_ttp_extensions,          content_ttp_extensions };
            constexpr DictionaryNode element_ttp_extension     { doc_element_all,          NS::ttp,              Tag::extension,              attrgrp_ttp_extension,           content_ttp_extension  };

            // The TTML table is complete
            return std::tuple {
                // TT namespace
                element_tt_tt,
                element_tt_head,
                element_tt_body,
                element_tt_div,
                element_tt_p,
                element_tt_span,
                element_tt_br,
                element_tt_styling,
                element_tt_style,
                element_tt_layout,
                element_tt_region,
                element_tt_set,
                element_tt_metadata,

                // TTM namespace
                element_ttm_title,
                element_ttm_desc,
                element_ttm_copyright,
                element_ttm_agent,
                element_ttm_name,
                element_ttm_actor,

                // TTP namespace
                element_ttp_profile,
                element_ttp_features,
                element_ttp_feature,
                element_ttp_extensions,
                element_ttp_extension
            };
        }
    }

    namespace detail
    {
        template<size_t I, class Tdictionary, class Fnc>
        struct TraverseTTMLDictionary;

        template<class Tdictionary, class Fnc>
        struct TraverseTTMLDictionary<0, Tdictionary, Fnc>
        {
            using entry_t = std::tuple_element_t<0, Tdictionary>;
            static constexpr bool TraverseWithPredicate(const Tdictionary& dictionary, const Fnc& fnc)
            {
                return fnc(std::get<0>(dictionary));
            }
        };

        template<size_t I, class Tdictionary, class Fnc>
        struct TraverseTTMLDictionary
        {
            using entry_t = std::tuple_element_t<I, Tdictionary>;
            static constexpr bool TraverseWithPredicate(const Tdictionary& dictionary, const Fnc& fnc)
            {
                auto reference = std::ref(std::get<I>(dictionary));
                using ref_t = decltype(reference);
                if (fnc(std::get<I>(dictionary))) return fnc(std::get<I>(dictionary));
                return TraverseTTMLDictionary<I - 1, Tdictionary, Fnc>::TraverseWithPredicate(dictionary, fnc);
            }
        };

        template<class Ttup, class S, S... Sseq>
        struct SequencePack
        {
            using sequence_t = std::variant<std::tuple_element_t<Sseq, Ttup>...>;
            constexpr SequencePack(const Ttup& tup, std::integer_sequence<S, Sseq...> sequence)
            {}
        };
    }

    struct TTMLDictionary
    {
        using dictionary_t = decltype(detail::CreateTTMLDictionary());
        // using variant_t = decltype(std::declval<detail::SequencePack>());

        constexpr TTMLDictionary()
        {}

        template<class Fnc>
        static constexpr bool TraverseWithPredicate(const Fnc& fnc)
        {
            return detail::TraverseTTMLDictionary<TTMLDictionary::size - 1, dictionary_t, Fnc>::TraverseWithPredicate(TTMLDictionary::entries, fnc);
        }

        static constexpr dictionary_t entries = detail::CreateTTMLDictionary();
        static constexpr size_t size = std::tuple_size_v<dictionary_t>;
    };
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// TTML Dictionary Helpers ---------------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

namespace vt::dictionary
{
    namespace detail
    {

    }

    template<size_t... Sseq>
    constexpr inline auto FindTTMLDictionaryNode(const std::pair<NS, Tag>& type)
    {
        // Return type for matched entry
        const auto get_entry = [](const auto& entry) {
            // const auto& [ ns, tag ] = entry;
            return (entry.element.ns.id == NS::tt && entry.element.element.id == Tag::div);
        };

        return TTMLDictionary::TraverseWithPredicate(get_entry);
    }
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif // VTTTML1DICTIONARY_HEADER