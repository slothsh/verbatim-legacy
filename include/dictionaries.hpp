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
        constexpr size_t vexpr_isDefault            = enum_integer(cnd::is_default)
        constexpr size_t default_vexpr_condition    = enum_integer(cnd::none);
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

        /// Value Expression Entries
        // ---------------------------------------------------------------------------------------------------|

        // [xml:id]
        constexpr std::tuple vexpr_xml_id {
            std::tuple { NS::none,       ValueExpression::id,               "<id>"                                          }
        };

        // [xml:lang]
        constexpr std::tuple vexpr_xml_lang {
            std::tuple { NS::none,       ValueExpression::language,         "<language>"                                    }
        };

        // [xml:space]
        constexpr std::tuple vexpr_xml_space {
            std::tuple { NS::none,       ValueExpression::literal,          "default",                      vexpr_isDefault },
            std::tuple { NS::none,       ValueExpression::literal,          "preserve"                                      }
        };

        // [ttp:cellResolution]
        constexpr std::tuple vexpr_ttp_cellResolution {
            std::tuple { NS::none,       ValueExpression::literal,          "32 15",                        vexpr_isDefault },
            std::tuple { NS::none,       ValueExpression::regex,            "<digit>+ <digit>+"                             }
        };

        // [ttp:clockMode]
        constexpr std::tuple vexpr_ttp_clockMode {
            std::tuple { NS::none,       ValueExpression::literal,          "local",                        vexpr_isDefault },
            std::tuple { NS::none,       ValueExpression::literal,          "gps"                                           },
            std::tuple { NS::none,       ValueExpression::literal,          "utc"                                           }
        };

        // [ttp:dropMode]
        constexpr std::tuple vexpr_ttp_dropMode {
            std::tuple { NS::none,       ValueExpression::literal,          "dropNTSC",                     vexpr_isDefault },
            std::tuple { NS::none,       ValueExpression::literal,          "dropPAL"                                       },
            std::tuple { NS::none,       ValueExpression::literal,          "nonDrop"                                       }
        };

        // [ttp:frameRate]
        constexpr std::tuple vexpr_ttp_frameRate {
            std::tuple { NS::none,       ValueExpression::digit,            "<digit>+",                     vexpr_isDefault }
        };

        // [ttp:frameRateMultiplier]
        constexpr std::tuple vexpr_ttp_frameRateMultiplier {
            std::tuple { NS::none,       ValueExpression::regex,            "<digit>+ <digit>+",            vexpr_isDefault }
        };

        // [ttp:markerMode]
        constexpr std::tuple vexpr_ttp_markerMode {
            std::tuple { NS::none,       ValueExpression::literal,          "continuous",                   vexpr_isDefault },
            std::tuple { NS::none,       ValueExpression::literal,          "discontinuous"                                 }
        };

        // [ttp:pixelAspectRatio]
        constexpr std::tuple vexpr_ttp_pixelAspectRatio {
            std::tuple { NS::none,       ValueExpression::regex,            "<digit>+ <digit>+",            vexpr_isDefault }
        };

        // [ttp:profile]
        constexpr std::tuple vexpr_ttp_profile {
            std::tuple { NS::none,       ValueExpression::any_uri,          "<anyURI>",                     vexpr_isDefault }
        };

        // [ttp:subFrameRate]
        constexpr std::tuple vexpr_ttp_subFrameRate {
            std::tuple { NS::none,       ValueExpression::digit,            "<digit>+",                     vexpr_isDefault }
        };

        // [ttp:tickRate]
        constexpr std::tuple vexpr_ttp_tickRate {
            std::tuple { NS::none,       ValueExpression::digit,            "<digit>+",                     vexpr_isDefault }
        };

        // [ttp:timeBase]
        constexpr std::tuple vexpr_ttp_timeBase {
            std::tuple { NS::none,       ValueExpression::literal,          "media",                        vexpr_isDefault },
            std::tuple { NS::none,       ValueExpression::literal,          "smpte"                                         },
            std::tuple { NS::none,       ValueExpression::literal,          "clock"                                         }
        };

        // [tts:extent]
        constexpr std::tuple vexpr_tts_extent {
            std::tuple { NS::none,       ValueExpression::automatic,        "<auto>",                       vexpr_isDefault },
            std::tuple { NS::none,       ValueExpression::regex,            "<length> <length>"                             }
        };
        
        // Old Value Expressions
        constexpr std::tuple flags{ default_vexpr_condition, default_vexpr_quantifier, default_vexpr_document };
        constexpr std::tuple value_expressions { 
            std::tuple { NS::tt, ValueExpression::string, "<string1>", 0, 0 },
            std::tuple { NS::tt, ValueExpression::string, "<string2>", 0, 0 },
            std::tuple { NS::tt, ValueExpression::string, "<string3>", 0, 0 }
        };

        constexpr auto fnc_create_attribute = []
        <class Telem, class Ttup, class Tflags, size_t Stup = std::tuple_size_v<Ttup>>
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