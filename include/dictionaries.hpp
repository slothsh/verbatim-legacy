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
        namespace constants
        {
            // Constants for dictionary entrt and document configurations
            enum class TTMLDocument : size_t
            {
                IS_DOCUMENT_TYPE        = VT_ENUM_ID,
                w3c_ttml1               = (1 << 0),
                w3c_ttml2               = (1 << 1),
                w3c_ttml3               = (1 << 2),
                ebu_ttml1               = (1 << 3),
                smpte_ttml1             = (1 << 4),
                w3c_imsc1               = (1 << 5),
                w3c_imsc2               = (1 << 6),
                none                    = VT_ENUM_NONE
            };

            enum class NodeCondition  : size_t
            {
                IS_CONDITION            = VT_ENUM_ID,
                required                = (1 << 0),
                none                    = VT_ENUM_NONE
            };

            enum class NodeQuantifier : size_t
            {
                IS_QUANTIFIER           = VT_ENUM_ID,
                kleene_asterisk         = (1 << 0),
                kleene_plus             = (1 << 1),
                kleene_question         = (1 << 2),
                kleene_one              = (1 << 3),
                kleene_ranged           = (1 << 16),
                none                    = VT_ENUM_NONE
            };

            enum ByteGroup : size_t
            {
                one             = 0,
                two             = 8,
                three           = 16,
                four            = 32  
            };
        }

        namespace detail
        {
            struct NodeTypes
            {
                using attroption_t          = AttributeOptionsNode<NS, AttributeOption>;
                using vexpression_t         = ValueExpressionNode<NS, ValueExpression>;
                using content_data_t        = ContentNode<NS, GenericData>;
                using content_tag_t         = ContentNode<NS, Tag>;
            };
        }

        template<class Texpr, class... Trest> // TODO: Concept for XMLNodeTree
        constexpr inline auto CreateValueExpressionNode(std::initializer_list<std::initializer_list<Texpr>>&& expressions)
        {
            return XMLNodeTree<Texpr, Trest...>{expressions};
        }

        static constexpr auto CreateTTMLDictionary()
        {
            // Generic alias types
            using attroption_t          = AttributeOptionsNode<NS, AttributeOption>;
            using vexpression_t         = ValueExpressionNode<NS, ValueExpression>;
            using content_data_t        = ContentNode<NS, GenericData>;
            using content_tag_t         = ContentNode<NS, Tag>;

            using namespace magic_enum::bitwise_operators;
            using magic_enum::enum_integer;
            using grp = constants::ByteGroup;
            using doc = constants::TTMLDocument;
            using cnd = constants::NodeCondition;
            using qty = constants::NodeQuantifier;

            // ---------------------------------------------------------------------------------------------------|
            // Legend                                                                                             |
            //                                                                                                    |
            // Tags:        <ns:tag/>                [nsentry:entry]                                              |
            // Naming:      type_nstag_tag_nsentry_entry(_t | _init)                                              |
            //                                                                                                    |
            // ---------------------------------------------------------------------------------------------------|

            // SECTION: <tt:tt/> ---------------------------------------------------------------------------------|
            // ===================================================================================================|

            // TODO: document & conditions member variable constants
            // TODO: value expression regex helper functions

            // <tt:tt/> [tts:extent] ----------------------------------------------- Value expressions -|

            // constexpr auto vexpr_tt_tt_tts_extent
            // = CreateValueExpressionNode <vexpression_t, vexpression_t>
            // ({
            //     {{ NS::none,          ValueExpression::string,        ":<auto>|<length> <length>",        0,         enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }},
            //     {{ NS::none,          ValueExpression::string,        ":<auto>|<length> <length>",        0,         enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) }}
            // });

            std::initializer_list<vexpression_t> vexpr_tt_tt_tts_extent_init 
            { 
                vexpression_t( NS::none,          ValueExpression::string,        ":<auto>|<length> <length>",        0,         enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) ),
            };
            using vexpr_tt_tt_tts_extent_t                                  = XMLNodeTree<vexpression_t>;
            vexpr_tt_tt_tts_extent_t vexpr_tt_tt_tts_extent              { vexpr_tt_tt_tts_extent_init };

            // -----------------------------------------------------------------------------------------|



            // <tt:tt/> [tts:extent] ----------------------------------------------- Attribute Options -|
            
            // TODO: Is AttributeNode needed?
            std::initializer_list<attroption_t> attropt_tt_tt_tts_extent_init
            { 
                attroption_t( NS::tt,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) )
            };
            using attropt_tt_tt_tts_extent_t                                 = XMLNodeTree<attroption_t>;
            attropt_tt_tt_tts_extent_t attropt_tt_tt_tts_extent        { attropt_tt_tt_tts_extent_init };

            // -----------------------------------------------------------------------------------------|



            // <tt:tt/> [tts:extent] -------------------------------------------------- Attribute Node -|

            using attr_tt_tt_tts_extent_t = AttributeNode<NS, Attribute, vexpr_tt_tt_tts_extent_t, attropt_tt_tt_tts_extent_t>;
            attr_tt_tt_tts_extent_t attr_tt_tt_tts_extent {
                enum_integer(cnd::none),
                enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::one),
                enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1),
                NS::tts, Attribute::extent,
                vexpr_tt_tt_tts_extent, attropt_tt_tt_tts_extent
            };

            // -----------------------------------------------------------------------------------------|



            // <tt:tt/> [xml:id] --------------------------------------------------- Value expressions -|

            std::initializer_list<vexpression_t> vexpr_tt_tt_xml_id_init 
            { 
                vexpression_t( NS::none,          ValueExpression::string,        "<id>",        0,                             enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) ),
            };
            using vexpr_tt_tt_xml_id_t                                      = XMLNodeTree<vexpression_t>;
            vexpr_tt_tt_xml_id_t vexpr_tt_tt_xml_id                          { vexpr_tt_tt_xml_id_init };

            // -----------------------------------------------------------------------------------------|



            // <tt:tt/> [xml:id] --------------------------------------------------- Attribute Options -|
            
            // TODO: Is AttributeNode needed?
            std::initializer_list<attroption_t> attropt_tt_tt_xml_id_init
            { 
                attroption_t( NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) )
            };
            using attropt_tt_tt_xml_id_t                                     = XMLNodeTree<attroption_t>;
            attropt_tt_tt_xml_id_t attropt_tt_tt_xml_id                    { attropt_tt_tt_xml_id_init };

            // -----------------------------------------------------------------------------------------|



            // <tt:tt/> [xml:id] ------------------------------------------------------ Attribute Node -|

            using attr_tt_tt_xml_id_t = AttributeNode<NS, Attribute, vexpr_tt_tt_xml_id_t, attropt_tt_tt_xml_id_t>;
            attr_tt_tt_xml_id_t attr_tt_tt_xml_id {
                enum_integer(cnd::none),
                enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::one),
                enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1),
                NS::xml, Attribute::id,
                vexpr_tt_tt_xml_id, attropt_tt_tt_xml_id
            };

            // -----------------------------------------------------------------------------------------|


            // <tt:tt/> [xml:lang] ------------------------------------------------- Value expressions -|

            std::initializer_list<vexpression_t> vexpr_tt_tt_xml_lang_init 
            { 
                vexpression_t( NS::none,          ValueExpression::string,        "<language>",        0,           enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) ),
            };
            using vexpr_tt_tt_xml_lang_t                                    = XMLNodeTree<vexpression_t>;
            vexpr_tt_tt_xml_lang_t vexpr_tt_tt_xml_lang                    { vexpr_tt_tt_xml_lang_init };

            // -----------------------------------------------------------------------------------------|



            // <tt:tt/> [xml:lang] ------------------------------------------------- Attribute Options -|
            
            // TODO: Is AttributeNode needed?
            std::initializer_list<attroption_t> attropt_tt_tt_xml_lang_init
            { 
                attroption_t( NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) )
            };
            using attropt_tt_tt_xml_lang_t                                   = XMLNodeTree<attroption_t>;
            attropt_tt_tt_xml_lang_t attropt_tt_tt_xml_lang              { attropt_tt_tt_xml_lang_init };

            // -----------------------------------------------------------------------------------------|



            // <tt:tt/> [xml:lang] ---------------------------------------------------- Attribute Node -|

            using attr_tt_tt_xml_lang_t = AttributeNode<NS, Attribute, vexpr_tt_tt_xml_lang_t, attropt_tt_tt_xml_lang_t>;
            attr_tt_tt_xml_lang_t attr_tt_tt_xml_lang {
                enum_integer(cnd::required),
                enum_integer(qty::kleene_one) | (0 << grp::one) | (0 << grp::one),
                enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1),
                NS::xml, Attribute::lang,
                vexpr_tt_tt_xml_lang, attropt_tt_tt_xml_lang
            };

            // -----------------------------------------------------------------------------------------|


            // <tt:tt/> [xml:space] ------------------------------------------------ Value expressions -|

            std::initializer_list<vexpression_t> vexpr_tt_tt_xml_space_init 
            { 
                vexpression_t( NS::none,          ValueExpression::string_option,        ":default|preserve",        0,           enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) ),
            };
            using vexpr_tt_tt_xml_space_t                                   = XMLNodeTree<vexpression_t>;
            vexpr_tt_tt_xml_space_t vexpr_tt_tt_xml_space                 { vexpr_tt_tt_xml_space_init };

            // -----------------------------------------------------------------------------------------|



            // <tt:tt/> [xml:space] ------------------------------------------------ Attribute Options -|
            
            // TODO: Is AttributeNode needed?
            std::initializer_list<attroption_t> attropt_tt_tt_xml_space_init
            { 
                attroption_t( NS::none,           AttributeOption::none,          "<null>",            enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1) )
            };
            using attropt_tt_tt_xml_space_t                                  = XMLNodeTree<attroption_t>;
            attropt_tt_tt_xml_space_t attropt_tt_tt_xml_space           { attropt_tt_tt_xml_space_init };

            // -----------------------------------------------------------------------------------------|



            // <tt:tt/> [xml:space] --------------------------------------------------- Attribute Node -|

            using attr_tt_tt_xml_space_t = AttributeNode<NS, Attribute, vexpr_tt_tt_xml_space_t, attropt_tt_tt_xml_space_t>;
            attr_tt_tt_xml_space_t attr_tt_tt_xml_space {
                enum_integer(cnd::none),
                enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::one),
                enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1),
                NS::xml, Attribute::id,
                vexpr_tt_tt_xml_space, attropt_tt_tt_xml_space
            };

            // -----------------------------------------------------------------------------------------|


            
            // <tt:tt/> --------------------------------------------------------------- Attribute Tree -|

            using attr_tt_tt_t                 = XMLNodeTree<attr_tt_tt_tts_extent_t, attr_tt_tt_xml_id_t,
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
                content_data_t( NS::none,         GenericData::PCDATA,    enum_integer(qty::kleene_asterisk) | (0 << grp::one) | (0 << grp::one),          enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1)),
                content_tag_t ( NS::tt,           Tag::head,              enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::one),          enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1)),
                content_tag_t ( NS::tt,           Tag::body,              enum_integer(qty::kleene_question) | (0 << grp::one) | (0 << grp::one),          enum_integer(doc::w3c_ttml1|doc::w3c_ttml2|doc::w3c_ttml3|doc::ebu_ttml1|doc::smpte_ttml1))
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