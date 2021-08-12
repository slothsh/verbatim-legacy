// Stefan "SoulXP" Olivier
// File: node.hpp
// Description: header file for static TTML dictionary templates


#ifndef VTNODE_HEADER
#define VTNODE_HEADER

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "config.hpp"
#endif

// Standard headers
#include <iostream>
#include <type_traits>
#include <tuple>
#include <utility>
#include <concepts>

// Enumerations for XML nodes ------------------------------------------------------------------------------------------1 of 5-|
// ============================================================================================================================|

namespace vt::dictionary
{
    // Generic enumerations for prototyping
    enum class NS : size_t
    {
        IS_NS = VT_ENUM_ID,
        undefined, xml, xmlns, tt, ttp, tts, ttm, smpte, ebu,
        none = VT_ENUM_NONE
    };

    enum class Tag : size_t
    {
        IS_TAG = VT_ENUM_ID,
        undefined, tt, set, body, div, p, span, br, head, layout, metadata, styling, style, region, begin, dur, end,
        actor, agent, copyright, desc, name, title, role, profile, features, feature, extensions, extension,
        none = VT_ENUM_NONE
    };

    enum class Attribute : size_t
    {
        IS_ATTRIBUTE = VT_ENUM_ID,
        undefined, id, lang, space, base, tt, ttm, ttp, tts, value, type, style, region, begin, dur, end, timeContainer,
        actor, agent, name, title, role, profile, features, feature, extensions, extension, backgroundColor,color, direction,
        display, displayAlign, extent, fontFamily, fontSize, fontStyle, fontWeight, lineHeight, opacity, origin, overflow, padding,
        showBackground, textAlign, textDecoration, textOutline, unicodeBidi, visibility, wrapOption, writingMode, zIndex, cellResolution,
        clockMode, dropMode, frameRate, frameRateMultiplier, markerMode, pixelAspectRatio, subFrameRate, tickRate, timeBase, use,
        none = VT_ENUM_NONE
    };

    enum class ValueExpression : size_t
    {
        IS_VALUE_EXPRESSION = VT_ENUM_ID,
        undefined, alpha, color, compound, digit, duration, font, familyName, genericFamilyName, hexDigit, integer, length, namedColor, quotedString, string,
        timeExpression, id, idref, idrefs, literal, language, regex, any_uri, token_char,
        none = VT_ENUM_NONE
    };

    enum class GenericData : size_t
    {
        IS_DATA = VT_ENUM_ID,
        undefined, CDATA, PCDATA, IMPLIED,
        none = VT_ENUM_NONE
    };

    enum AttributeGroup : size_t
    {
        IS_GROUP        = VT_ENUM_ID,
        xml_core,
        tt_core, tt_core_styling, tt_core_layout, tt_core_timing,
        tt_parameter, tt_metadata, tt_styling,
        tt_class_animation, tt_class_block, tt_class_inline, tt_class_metadata, tt_class_parameters,
        none            = VT_ENUM_NONE  
    };
}

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
        is_default              = (1 << 1),
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

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// Generic types for XML nodes -----------------------------------------------------------------------------------------2 of 5-|
// ============================================================================================================================|

namespace vt::dictionary
{
    namespace mge = magic_enum;

    // Concept for generic enumeration types
    template<class E>
    concept enumerable_node =
        std::is_enum_v<E>
        && mge::is_scoped_enum_v<E>
        && mge::enum_contains<E>(E::none)
        && mge::enum_integer(E::none) == VT_ENUM_NONE;

    // Concept for enumeration types to be used for namespaces
    template<class Tns>
    concept enumerable_ns =
        enumerable_node<Tns>
        && mge::enum_contains<Tns>(Tns::IS_NS)
        && mge::enum_integer(Tns::IS_NS) == VT_ENUM_ID;

    // Concept for enumeration types to be used for xml tags
    template<class Ttag>
    concept enumerable_tag =
        enumerable_node<Ttag>
        && mge::enum_contains<Ttag>(Ttag::IS_TAG)
        && mge::enum_integer(Ttag::IS_TAG) == VT_ENUM_ID;

    // Concept for enumeration types to be used for attributes
    template<class Tattr>
    concept enumerable_attr =
        enumerable_node<Tattr>
        && mge::enum_contains<Tattr>(Tattr::IS_ATTRIBUTE)
        && mge::enum_integer(Tattr::IS_ATTRIBUTE) == VT_ENUM_ID;

    // Concept for enumeration types to be used for value expressions
    template<class Tvexpr>
    concept enumerable_vexpr =
        enumerable_node<Tvexpr>
        && mge::enum_contains<Tvexpr>(Tvexpr::IS_VALUE_EXPRESSION)
        && mge::enum_integer(Tvexpr::IS_VALUE_EXPRESSION) == VT_ENUM_ID;

    // Concept for enumeration types to be used for data tag data types
    template<class Tdata>
    concept enumerable_data =
        enumerable_node<Tdata>
        && mge::enum_contains<Tdata>(Tdata::IS_DATA)
        && mge::enum_integer(Tdata::IS_DATA) == VT_ENUM_ID;

    // Concept for enumeration types to be used for content types
    template<class Tcont>
    concept enumerable_content =
        enumerable_node<Tcont>
        && (enumerable_tag<Tcont>
        || enumerable_data<Tcont>);

    template<class Telement>
    concept enumerable_element =
        enumerable_node<Telement>
        && (enumerable_tag<Telement>
        || enumerable_attr<Telement>
        || enumerable_vexpr<Telement>
        || enumerable_data<Telement>);

    // Generic types
    template<enumerable_node E>
    struct NodeID
    {
        constexpr NodeID(const E& n_id) noexcept
            : id(n_id),
            value(magic_enum::enum_name<E>(n_id))
        {}

        E                     id;
        std::string_view      value;
    };

    template<enumerable_node Tns, enumerable_node Telem>
    struct Node
    {
        constexpr Node(const Tns& n_ns, const Telem& n_element) noexcept
            : ns(n_ns),
            element(n_element)
        {}

        NodeID<Tns>                 ns;
        NodeID<Telem>               element;
    };
}

// XML node component templates ----------------------------------------------------------------------------------------3 of 5-|
// ============================================================================================================================|

namespace vt::dictionary
{
    template<enumerable_ns Tns, enumerable_vexpr Tvexpr>
    struct ValueExpressionNode
    {
        using init_t = ValueExpressionNode<Tns, Tvexpr>;

        constexpr ValueExpressionNode(Tns&& n_ns, Tvexpr&& n_vexpr, std::string_view&& n_value, size_t&& n_conditions, size_t&& n_documents) noexcept
            : expression({ n_ns, n_vexpr }),
            value(n_value),
            conditions(n_conditions),
            documents(n_documents)
        {}

        constexpr ValueExpressionNode(const Tns&& n_ns, const Tvexpr&& n_vexpr, const std::string_view&& n_value, const size_t&& n_conditions, const size_t&& n_documents) noexcept
            : expression({ n_ns, n_vexpr }),
            value(n_value),
            conditions(n_conditions),
            documents(n_documents)
        {}

        constexpr ValueExpressionNode(const std::initializer_list<init_t>& init_list) noexcept
            : expression({ init_list.begin(), init_list.begin() + 1 }),
            value(init_list.begin() + 2),
            conditions(init_list.begin() + 3),
            documents(init_list.begin() + 4)
        {} 

        Node<Tns, Tvexpr>           expression;
        std::string_view            value;
        size_t                      conditions;
        size_t                      documents;
    };

    template<enumerable_ns Tns, enumerable_attr Tattr,
                class Nvexpr>
    struct AttributeNode
    {
        constexpr AttributeNode(size_t&& n_condition, size_t&& n_quantifier, size_t&& n_documents,
                                Tns&& n_ns,  Tattr&& n_attr, Nvexpr&& n_vexpr)
            : attribute({ n_ns, n_attr }),
            expressions(n_vexpr),
            condition(n_condition),
            quantifier(n_quantifier),
            documents(n_documents)
        {}

        constexpr AttributeNode(const size_t&& n_condition, const size_t&& n_quantifier, const size_t&& n_documents,
                                const Tns&& n_ns,  const Tattr&& n_attr, const Nvexpr&& n_vexpr)
            : attribute({ n_ns, n_attr }),
            expressions(n_vexpr),
            condition(n_condition),
            quantifier(n_quantifier),
            documents(n_documents)
        {}

        Node<Tns, Tattr>            attribute;
        Nvexpr                      expressions;
        size_t                      condition;
        size_t                      quantifier;
        size_t                      documents;
    };

    template<enumerable_ns Tns, enumerable_content Tdata>
    struct ContentNode
    {
        constexpr ContentNode(Tns&& n_ns, Tdata&& n_data,
                                size_t&& n_quantifier, size_t&& n_documents) noexcept
            : type({ n_ns, n_data }),
            documents(n_documents),
            quantifier(n_quantifier)
        {}

        Node<Tns, Tdata>            type;
        size_t                      quantifier;
        size_t                      documents;
    };

    // General XML node type for XML dictionary entries
    template<enumerable_ns Tns, enumerable_tag Ttag,
                class Tattr, class Tdata>
    struct XMLNode
    {
        using element_t = Node<Tns, Ttag>;
        using attribute_t = Tattr;
        using content_t = Tdata;

        constexpr XMLNode(size_t&& n_documents,
                            Tns&& n_ns, Ttag&& n_tag,
                            const Tattr& n_attr, const Tdata& n_data)
            : element({ n_ns , n_tag }),
            attributes(n_attr),
            content(n_data),
            documents(n_documents)
        {}

        constexpr XMLNode(const size_t&& n_documents,
                            const Tns&& n_ns, const Ttag&& n_tag,
                            const Tattr& n_attr, const Tdata& n_data)
            : element({ n_ns , n_tag }),
            attributes(n_attr),
            content(n_data),
            documents(n_documents)
        {}

        element_t                           element;
        attribute_t                         attributes;
        content_t                           content;
        size_t                              documents;
    };
}

// XML node dictionary template ----------------------------------------------------------------------------------------4 of 5-|
// ============================================================================================================================|

namespace vt::dictionary::detail
{
    template<class Tns = NS, class Ttag = Tag,
                class Tattr_elem, class Tattr_vexpr, class Tattr_flags,
                class Tfnattr, class Tfndata> // TODO: invocable concept for Tfn
    constexpr inline auto CreateTTMLNode(const size_t&& docs, const Tns&& ns, const Ttag&& tag,
                                            const Tattr_elem&& init_attr_element, const Tattr_vexpr&& init_attr_vexpr, const Tattr_flags&& init_attr_flags,
                                            const Tfnattr&& fn_attr, const Tfndata&& fn_data)
    {
        // static_assert(Tns != NS::none && Ttag != Tag::none, "Invalid TTMLNode type\n");

        using ns_t = decltype(ns);
        using tag_t = decltype(tag);
        using attr_element_t = decltype(init_attr_element);
        using attr_vexpr_t = decltype(init_attr_vexpr);
        using attr_flags_t = decltype(init_attr_flags);

        const auto attributes = fn_attr (
            std::forward<attr_element_t>(init_attr_element),
            std::forward<attr_vexpr_t>(init_attr_vexpr),
            std::forward<attr_flags_t>(init_attr_flags)
        );

        // const auto content = fn_data(std::move(ns), std::move(tag));
        constexpr ContentNode content{ NS::none, Tag::none, 0, 0 };

        using node_t = XMLNode<NS, Tag, decltype(attributes), decltype(content)>;

        return node_t {
            std::move(docs),
            std::forward<ns_t>(ns), std::forward<tag_t>(tag),
            std::move(attributes), std::move(content)
        };
    }

    template<class Ttup, class S, S... Sseq>
    constexpr inline auto CreateTTMLNodeList(const Ttup&& tup, std::integer_sequence<S, Sseq...> sequence)
    {
        return std::tuple {
            CreateTTMLNode(
                std::move(std::get<0>(std::get<Sseq>(tup))),
                std::move(std::get<1>(std::get<Sseq>(tup))),
                std::move(std::get<2>(std::get<Sseq>(tup))),
                std::move(std::get<3>(std::get<Sseq>(tup))),
                std::move(std::get<4>(std::get<Sseq>(tup))),
                std::move(std::get<5>(std::get<Sseq>(tup))),
                std::move(std::get<6>(std::get<Sseq>(tup))),
                std::move(std::get<7>(std::get<Sseq>(tup)))
            )...
        };
    }
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif // VTNODE_HEADER