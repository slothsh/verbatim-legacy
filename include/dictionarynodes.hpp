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
        timeExpression, id, idref, idrefs, literal, language, regex, any_uri, token_char, conditional,
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
        negate                  = (1 << 2),
        not_empty               = (1 << 3),
        not_used                = (1 << 4),
        element_dependent       = (1 << 5),
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
    concept enumerable_node_c =
        std::is_enum_v<E>
        && mge::is_scoped_enum_v<E>
        && mge::enum_contains<E>(E::none)
        && mge::enum_integer(E::none) == VT_ENUM_NONE;

    // Concept for enumeration types to be used for namespaces
    template<class Tns>
    concept enumerable_ns_c =
        enumerable_node_c<Tns>
        && mge::enum_contains<Tns>(Tns::IS_NS)
        && mge::enum_integer(Tns::IS_NS) == VT_ENUM_ID;

    // Concept for enumeration types to be used for xml tags
    template<class Ttag>
    concept enumerable_tag_c =
        enumerable_node_c<Ttag>
        && mge::enum_contains<Ttag>(Ttag::IS_TAG)
        && mge::enum_integer(Ttag::IS_TAG) == VT_ENUM_ID;

    // Concept for enumeration types to be used for attributes
    template<class Tattr>
    concept enumerable_attr_c =
        enumerable_node_c<Tattr>
        && mge::enum_contains<Tattr>(Tattr::IS_ATTRIBUTE)
        && mge::enum_integer(Tattr::IS_ATTRIBUTE) == VT_ENUM_ID;

    // Concept for enumeration types to be used for value expressions
    template<class Tvexpr>
    concept enumerable_vexpr_c =
        enumerable_node_c<Tvexpr>
        && mge::enum_contains<Tvexpr>(Tvexpr::IS_VALUE_EXPRESSION)
        && mge::enum_integer(Tvexpr::IS_VALUE_EXPRESSION) == VT_ENUM_ID;

    // Concept for enumeration types to be used for data tag data types
    template<class Tdata>
    concept enumerable_data_c =
        enumerable_node_c<Tdata>
        && mge::enum_contains<Tdata>(Tdata::IS_DATA)
        && mge::enum_integer(Tdata::IS_DATA) == VT_ENUM_ID;

    // Concept for enumeration types to be used for content types
    template<class Tcont>
    concept enumerable_content_c =
        enumerable_node_c<Tcont>
        && (enumerable_tag_c<Tcont>
        || enumerable_data_c<Tcont>);

    template<class Telement>
    concept enumerable_element_c =
        enumerable_node_c<Telement>
        && (enumerable_tag_c<Telement>
        || enumerable_attr_c<Telement>
        || enumerable_vexpr_c<Telement>
        || enumerable_data_c<Telement>);

    // Generic types
    template<enumerable_node_c E>
    struct NodeID
    {
        constexpr NodeID() = default;
        constexpr ~NodeID() = default;

        constexpr NodeID(const NodeID& node_id)
            : id(node_id.id),
            value(node_id.value)
        {}

        constexpr NodeID(const E& n_id) noexcept
            : id(n_id),
            value(magic_enum::enum_name<E>(n_id))
        {}

        E                     id;
        std::string_view      value;
    };

    template<enumerable_node_c Tns, enumerable_node_c Telem>
    struct Node
    {
        constexpr Node() = default;
        constexpr ~Node() = default;

        constexpr Node(const Node& node)
            : ns(node.ns),
            element(node.element)
        {}

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
    template<enumerable_ns_c Tns, enumerable_vexpr_c Tvexpr>
    struct ValueExpressionNode
    {
        using init_t = ValueExpressionNode<Tns, Tvexpr>;

        constexpr ValueExpressionNode() = default;
        constexpr ~ValueExpressionNode() = default;

        constexpr ValueExpressionNode(const ValueExpressionNode& vexpr)
            : expression(vexpr.expression),
            value(vexpr.value),
            conditions(vexpr.conditions),
            documents(vexpr.documents)
        {}

        constexpr ValueExpressionNode(const Tns& n_ns, const Tvexpr& n_vexpr, const std::string_view& n_value, const size_t& n_conditions, const size_t& n_documents) noexcept
            : expression({ n_ns, n_vexpr }),
            value(n_value),
            conditions(n_conditions),
            documents(n_documents)
        {}

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

    template<enumerable_ns_c Tns, enumerable_attr_c Tattr,
                class Nvexpr>
    struct AttributeNode
    {
        using ns_t = Tns;
        using tag_t = Tattr;
        using vexpr_t = Nvexpr;

        constexpr AttributeNode() = default;
        constexpr ~AttributeNode() = default;

        constexpr AttributeNode(const AttributeNode& attribute)
            : attribute(attribute.attribute),
            expressions(attribute.expressions),
            condition(attribute.condition),
            quantifier(attribute.quantifier),
            documents(attribute.documents),
            size_expressions(attribute.size_expressions)
        {}

        constexpr AttributeNode(const size_t& n_condition, const size_t& n_quantifier, const size_t& n_documents,
                                const Tns& n_ns,  const Tattr& n_attr, const Nvexpr& n_vexpr)
            : attribute({ n_ns, n_attr }),
            expressions(n_vexpr),
            condition(n_condition),
            quantifier(n_quantifier),
            documents(n_documents),
            size_expressions(std::tuple_size_v<Nvexpr>)
        {}

        constexpr AttributeNode(const size_t& n_condition, const size_t& n_quantifier, const size_t& n_documents,
                                const std::tuple<Tns, Tattr>& element, const Nvexpr& n_vexpr)
            : attribute({ std::get<0>(element), std::get<1>(element) }),
            expressions(n_vexpr),
            condition(n_condition),
            quantifier(n_quantifier),
            documents(n_documents),
            size_expressions(std::tuple_size_v<Nvexpr>)
        {}

        constexpr AttributeNode(size_t&& n_condition, size_t&& n_quantifier, size_t&& n_documents,
                                Tns&& n_ns,  Tattr&& n_attr, Nvexpr&& n_vexpr)
            : attribute({ n_ns, n_attr }),
            expressions(n_vexpr),
            condition(n_condition),
            quantifier(n_quantifier),
            documents(n_documents),
            size_expressions(std::tuple_size_v<Nvexpr>)
        {}

        constexpr AttributeNode(const size_t&& n_condition, const size_t&& n_quantifier, const size_t&& n_documents,
                                const Tns&& n_ns,  const Tattr&& n_attr, const Nvexpr&& n_vexpr)
            : attribute({ n_ns, n_attr }),
            expressions(n_vexpr),
            condition(n_condition),
            quantifier(n_quantifier),
            documents(n_documents),
            size_expressions(std::tuple_size_v<Nvexpr>)
        {}

        constexpr AttributeNode(const size_t&& n_condition, const size_t&& n_quantifier, const size_t&& n_documents,
                                const std::tuple<Tns, Tattr>&& element, const Nvexpr&& n_vexpr)
            : attribute({ std::get<0>(element), std::get<1>(element) }),
            expressions(n_vexpr),
            condition(n_condition),
            quantifier(n_quantifier),
            documents(n_documents),
            size_expressions(std::tuple_size_v<Nvexpr>)
        {}

        Node<ns_t, tag_t>           attribute;
        Nvexpr                      expressions;
        size_t                      condition;
        size_t                      quantifier;
        size_t                      documents;
        size_t                      size_expressions;
    };

    template<enumerable_ns_c Tns, enumerable_content_c Tdata>
    struct ContentNode
    {   
        constexpr ContentNode() = default;
        constexpr ~ContentNode() = default;

        constexpr ContentNode(const ContentNode& content)
            : type(content.type),
            quantifier(content.quantifier),
            documents(content.documents)
        {}

        constexpr ContentNode(const size_t& n_quantifier, const size_t& n_documents,
                                const Tns& n_ns, const Tdata& n_data) noexcept
            : type({ n_ns, n_data }),
            documents(n_documents),
            quantifier(n_quantifier)
        {}

        constexpr ContentNode(const size_t& n_quantifier, const size_t& n_documents,
                                const std::tuple<Tns, Tdata>& n_element) noexcept
            : type({ std::get<0>(n_element), std::get<1>(n_element) }),
            documents(n_documents),
            quantifier(n_quantifier)
        {}

        constexpr ContentNode(const size_t&& n_quantifier, const size_t&& n_documents,
                                const Tns&& n_ns, const Tdata&& n_data) noexcept
            : type({ n_ns, n_data }),
            documents(n_documents),
            quantifier(n_quantifier)
        {}

        constexpr ContentNode(const size_t&& n_quantifier, const size_t&& n_documents,
                                const std::tuple<Tns, Tdata>&& n_element) noexcept
            : type({ std::get<0>(n_element), std::get<1>(n_element) }),
            documents(n_documents),
            quantifier(n_quantifier)
        {}

        Node<Tns, Tdata>            type;
        size_t                      quantifier;
        size_t                      documents;
    };

    // General XML node type for XML dictionary entries
    template<enumerable_ns_c Tns, enumerable_tag_c Ttag,
                class Tattr, class Tdata>
    struct DictionaryNode
    {
        using element_t = Node<Tns, Ttag>;
        using attribute_t = Tattr;
        using content_t = Tdata;

        constexpr DictionaryNode() = default;
        constexpr ~DictionaryNode() = default;

        constexpr DictionaryNode(const DictionaryNode& dictionary)
            : element(dictionary.element),
            attributes(dictionary.attributes),
            content(dictionary.content),
            documents(dictionary.documents),
            size_attributes(dictionary.size_attributes),
            size_content(dictionary.size_content)
        {}

        constexpr DictionaryNode(const size_t& n_documents,
                            const Tns& n_ns, const Ttag& n_tag,
                            const Tattr& n_attr, const Tdata& n_data)
            : element({ n_ns , n_tag }),
            attributes(n_attr),
            content(n_data),
            documents(n_documents),
            size_attributes(std::tuple_size_v<Tattr>),
            size_content(std::tuple_size_v<Tdata>)
        {}

        element_t                           element;
        attribute_t                         attributes;
        content_t                           content;
        size_t                              documents;
        size_t                              size_attributes;
        size_t                              size_content;
    };
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif // VTNODE_HEADER