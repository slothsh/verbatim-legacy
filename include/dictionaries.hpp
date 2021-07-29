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

// Master TTML definition function -------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

namespace vt
{
    namespace dictionary
    {
        namespace contstants
        {
            // Constants for dictionary entrt and document configurations
            static constexpr 
        }

        enum class NodeCondition
        {
            IS_CONDITION            = VT_ENUM_ID,
            kleene_asterisk         = (1 << 0),
            kleene_plus             = (1 << 1),
            explicit_value          = (1 << 16),
            none                    = VT_ENUM_NONE
        };

        static constexpr auto CreateTTMLDictionary()
        {
            // Generic alias types
            using attroption_t          = AttributeOptionsNode<NS, AttributeOption>;
            using vexpression_t         = ValueExpressionNode<NS, StyleExpression>;
            using content_data_t        = ContentNode<NS, GenericData>;
            using content_tag_t         = ContentNode<NS, Tag>;

            // Naming format:
            // <ns:tag/> [nsentry:entry]
            // type_nstag_tag_nsentry_entry(_t | _init)

            // SECTION: <tt:tt/> ---------------------------------------------------------------------------------|
            // ===================================================================================================|

            // TODO: document & conditions member variable constants
            // Value expressions for <tt:tt/> [tts:extent]
            std::initializer_list<vexpression_t> vexpr_tt_tt_tts_extent_init 
            { 
                vexpression_t( NS::tt,          StyleExpression::digit,         0),
                vexpression_t( NS::tts,         StyleExpression::color,         0),
                vexpression_t( NS::ttp,         StyleExpression::namedColor,    0),
                vexpression_t( NS::ttm,         StyleExpression::duration,      0)
            };
            using vexpr_tt_tt_tts_extent_t = XMLNodeTree<vexpression_t, vexpression_t, vexpression_t, vexpression_t>;
            vexpr_tt_tt_tts_extent_t vexpr_tt_tt_tts_extent { vexpr_tt_tt_tts_extent_init };

            // Attribute options for <tt:tt/> [tts:extent]
            std::initializer_list<attroption_t> list2 { 
                attroption_t(NS::tt, AttributeOption::one, "Value", 0),
                attroption_t(NS::tt, AttributeOption::one, "Value", 0),
                attroption_t(NS::tt, AttributeOption::one, "Value", 0),
                attroption_t(NS::tt, AttributeOption::one, "Value", 0)
            };
            using attropts_1_t = XMLNodeTree<attroption_t, attroption_t, attroption_t, attroption_t>;
            attropts_1_t attropts1 { list2 };

            // Attribute node for <tt:tt/> [tts:extent]
            using attribute_1_t = AttributeNode<NS, Attribute, vexpr_tt_tt_tts_extent_t, attropts_1_t>;
            attribute_1_t attribute1 {
                0, 0, 0,
                NS::tt, Attribute::display,
                vexpr1, attropts1
            };

            // Attribute tree for <tt:tt/>
            using attributetree_1_t = XMLNodeTree<attribute_1_t>;
            attributetree_1_t attributetree1 {
                attribute1
            };

            // Content tree
            using content_1_t = XMLNodeTree<content_data_t, content_tag_t>;
            content_1_t contenttree1 {
                content_data_t(NS::tt, GenericData::PCDATA, 0, 0),
                content_tag_t(NS::tt, Tag::div, 0, 0)
            };

            // Node
            using node_1_t = XMLNode<NS, Tag, attributetree_1_t, content_1_t>;
            node_1_t node_1 {
                0,
                NS::tt, Tag::div,
                attributetree1, contenttree1
            };

            // ---------------------------------------------------------------------------------------------------|

            return node_1;
        }

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// Dictionary helpers ---------------------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

        template<enumerable_ns Tnselement, enumerable_element Telement>
        struct EnumerationCollector
        {
            
            using nselement_t                   = Tnselement;
            using element_t                     = Telement;
            using entry_t                       = std::pair<element_t, std::string_view>;

            constexpr EnumerationCollector() noexcept
            {
                namespace mge = magic_enum;

                this->size = mge::enum_count<element_t>() - 2;
                constexpr auto all_entries = mge::enum_entries<element_t>();

                size_t i = 0, j = 0;
                while (i++ < this->size)
                {
                    if (all_entries[i].first != element_t::none
                        || all_entries[i].first != mge::enum_value<element_t>(0) // TODO: Make control indexes for enums a static constant
                        && j < this->size)
                    {
                        this->entries[j++] = all_entries[i];
                    }
                }
            }

            size_t                              size                                                        = magic_enum::enum_count<element_t>() - 2;
            entry_t                             entries[magic_enum::enum_count<element_t>() - 2]            = {};
        };
    }
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif // VTDICTIONARIES_HEADER