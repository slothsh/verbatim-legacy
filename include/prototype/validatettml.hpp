// Stefan "SoulXP" Olivier
// File: validatettml.hpp
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
#include <string_view>
#include <tuple>
#include <memory>
#include <utility>
#include <concepts>

// Enumerations for TTML nodes --------------------------------------------------------------------------------------- 1 of 1 -|
// ============================================================================================================================|

namespace vt::prototype
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

namespace vt::constants
{
    // Constants for dictionary entry and document configurations
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

// Concepts for TTML nodes ------------------------------------------------------------------------------------------- 1 of 1 -|
// ============================================================================================================================|

namespace vt::prototype
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
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// Fundamental node types for TTML elements -------------------------------------------------------------------------- 1 of 1 -|
// ============================================================================================================================|

namespace vt::prototype
{
    // Generic types
    template<enumerable_node_c E>
    struct NodeID
    {
    public:
        using id_t = std::decay_t<E>;

        constexpr NodeID() = default;
        constexpr ~NodeID() = default;

        constexpr NodeID(E&& _id)
            : id(_id),
            value(magic_enum::enum_name<E>(_id))
        {}

        constexpr bool operator==(const NodeID& _nodeid) const noexcept
        {
            return (this->id == _nodeid.id && this->value == _nodeid.value);
        }

        id_t                  id;
        std::string_view      value;
    };

    template<enumerable_node_c Tns, enumerable_node_c Telem>
    struct Node
    {
    public:
        using ns_t = NodeID<std::decay_t<Tns>>;
        using element_t = NodeID<std::decay_t<Telem>>;

        constexpr Node() = default;
        constexpr ~Node() = default;

        constexpr Node(Tns&& _ns, Telem&& _element)
            : ns(std::move(_ns)),
            element(std::move(_element))
        {}

        constexpr bool operator==(const Node& _node) const noexcept
        {
            return (this->ns == _node.ns && this->element == _node.element);
        }

        ns_t                 ns;
        element_t            element;
    };
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// ValidatingNode Generic Node and Concepts -------------------------------------------------------------------------- 1 of 1 -|
// ============================================================================================================================|

namespace vt::prototype
{
    // Concepts for ValidatingNode
    template<class T>
    concept string_view_c = std::same_as<T, std::string_view>;
    
    template <class T>
    concept integral_c = std::is_integral_v<T>;

    template <class T>
    concept signed_integral_c = integral_c<T> && std::is_signed_v<T>;

    template <class T>
    concept unsigned_integral_c = integral_c<T> && !signed_integral_c<T>;

    // Base class for ValidatingNode
    template<class...>
    struct ValidatingNode
    {};

    template<>
    struct ValidatingNode<>
    {
    public:
        auto operator()() const
        {
            return *this;
        }
    };
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// ValidatingNode Specializations for TTML Value Expressions --------------------------------------------------------- 1 of 1 -|
// ============================================================================================================================|

namespace vt::prototype
{
    template<enumerable_ns_c Tns, enumerable_vexpr_c Tvexpr, string_view_c Tvalue, integral_c Tcnd, integral_c Tdoc>
    struct ValidatingNode<Tns, Tvexpr, Tvalue, Tcnd, Tdoc>
    {
    public:
        using data_t = std::add_const_t<ValidatingNode<Tns, Tvexpr, Tvalue, Tcnd, Tdoc>>;
        using node_t = Node<std::decay_t<Tns>, std::decay_t<Tvexpr>>;
        using value_t = std::decay_t<Tvalue>;

        ValidatingNode() = default;
        ~ValidatingNode() = default;

        constexpr ValidatingNode(Tns&& _ns, Tvexpr&& _vexpr, Tvalue&& _value, Tcnd&& _conditions, Tdoc&& _documents)
            : node(std::move(_ns), std::move(_vexpr)),
            value(std::move(_value)),
            conditions(std::move(_conditions)),
            documents(std::move(_documents))
        {}

        constexpr data_t& operator()(const auto&) const noexcept
        {
            return *this;
        }

        constexpr data_t& operator()() const noexcept
        {
            return *this;
        }

        node_t       node;
        value_t      value;
        size_t       conditions;    
        size_t       documents;
    };

    template<enumerable_ns_c Tns, enumerable_vexpr_c Tvexpr, string_view_c Tvalue, integral_c Tcnd, integral_c Tdoc, class... Rest>
    struct ValidatingNode<Tns, Tvexpr, Tvalue, Tcnd, Tdoc, Rest...>
    {
    public:
        using data_t = std::add_const_t<ValidatingNode<Tns, Tvexpr, Tvalue, Tcnd, Tdoc>>;
        using next_t = std::conditional_t<sizeof...(Rest) == 0, ValidatingNode<>, ValidatingNode<Rest...>>;

        ValidatingNode() = default;
        ~ValidatingNode() = default;

        constexpr ValidatingNode(Tns&& _ns, Tvexpr&& _vexpr, Tvalue&& _value, Tcnd&& _conditions, Tdoc&& _documents, Rest&&... _rest)
            : data(std::move(_ns), std::move(_vexpr), std::move(_value), std::move(_conditions), std::move(_documents)),
            next(std::move(_rest)...)
        {}

        constexpr ValidatingNode(Tns&& _ns, Tvexpr&& _vexpr, Tvalue&& _value, Tcnd&& _conditions, Tdoc&& _documents)
            : data(std::move(_ns), std::move(_vexpr), std::move(_value), std::move(_conditions), std::move(_documents)),
            next({})
        {}

        constexpr data_t& operator()(const auto& f) const noexcept
        {
            if (f(this->data())) return this->data();
            else return this->next(f);
        }

        data_t              data;
        next_t              next;    
    };

    // Deduction guides for TTML value expressions
    template<enumerable_ns_c Tns, enumerable_vexpr_c Tvexpr, string_view_c Tvalue, integral_c Tcnd, integral_c Tdoc>
    ValidatingNode(Tns&&, Tvexpr&&, Tvalue&&, Tcnd&&, Tdoc&&) -> ValidatingNode<Tns, Tvexpr, Tvalue, Tcnd, Tdoc>;

    template<enumerable_ns_c Tns, enumerable_vexpr_c Tvexpr, string_view_c Tvalue, integral_c Tcnd, integral_c Tdoc, class... Rest>
    ValidatingNode(Tns&&, Tvexpr&&, Tvalue&&, Tcnd&&, Tdoc&&, Rest&&...) -> ValidatingNode<Tns, Tvexpr, Tvalue, Tcnd, Tdoc, Rest...>;
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// ValidatingNode Specializations for TTML Attributes ---------------------------------------------------------------- 1 of 1 -|
// ============================================================================================================================|

namespace vt::prototype
{
    template<enumerable_ns_c Tns, enumerable_attr_c Tattr, string_view_c Tvalue, integral_c Tcnd, integral_c Tqty, integral_c Tdoc>
    struct ValidatingNode<Tns, Tattr, Tvalue, Tcnd, Tqty, Tdoc>
    {
    public:
        using data_t = std::add_const_t<ValidatingNode<Tns, Tattr, Tvalue, Tcnd, Tqty, Tdoc>>;
        using node_t = Node<std::decay_t<Tns>, std::decay_t<Tattr>>;
        using value_t = std::decay_t<Tvalue>;

        ValidatingNode() = default;
        ~ValidatingNode() = default;

        constexpr ValidatingNode(Tns&& _ns, Tattr&& _attr, Tvalue&& _value, Tcnd&& _conditions, Tqty&& _quantifiers, Tdoc&& _documents)
            : node(std::move(_ns), std::move(_attr)),
            value(std::move(_value)),
            conditions(std::move(_conditions)),
            quantifiers(std::move(_quantifiers)),
            documents(std::move(_documents))
        {}

        constexpr data_t& operator()(const auto&) const noexcept
        {
            return *this;
        }

        constexpr data_t& operator()() const noexcept
        {
            return *this;
        }

        node_t       node;
        value_t      value;
        size_t       conditions;    
        size_t       quantifiers;    
        size_t       documents;
    };

    template<enumerable_ns_c Tns, enumerable_attr_c Tattr, string_view_c Tvalue, integral_c Tcnd, integral_c Tqty, integral_c Tdoc, class... Rest>
    struct ValidatingNode<Tns, Tattr, Tvalue, Tcnd, Tqty, Tdoc, Rest...>
    {
    public:
        using data_t = std::add_const_t<ValidatingNode<Tns, Tattr, Tvalue, Tcnd, Tqty, Tdoc>>;
        using next_t = std::conditional_t<sizeof...(Rest) == 0, ValidatingNode<>, ValidatingNode<Rest...>>;

        ValidatingNode() = default;
        ~ValidatingNode() = default;

        constexpr ValidatingNode(Tns&& _ns, Tattr&& _attr, Tvalue&& _value, Tcnd&& _conditions, Tqty&& _quantifiers, Tdoc&& _documents, Rest&&... _rest)
            : data(std::move(_ns), std::move(_attr), std::move(_value), std::move(_conditions), std::move(_quantifiers), std::move(_documents)),
            next(std::move(_rest)...)
        {}

        constexpr ValidatingNode(Tns&& _ns, Tattr&& _attr, Tvalue&& _value, Tcnd&& _conditions, Tqty&& _quantifiers, Tdoc&& _documents)
            : data(std::move(_ns), std::move(_attr), std::move(_value), std::move(_conditions), std::move(_quantifiers), std::move(_documents)),
            next({})
        {}

        constexpr data_t& operator()(const auto& f) const noexcept
        {
            if (f(this->data())) return this->data();
            else return this->next(f);
        }

        data_t              data;
        next_t              next;    
    };

    // Deduction guides for TTML attributes
    template<enumerable_ns_c Tns, enumerable_attr_c Tattr, string_view_c Tvalue, integral_c Tcnd, integral_c Tqty, integral_c Tdoc>
    ValidatingNode(Tns&&, Tattr&&, Tvalue&&, Tcnd&&, Tqty&&, Tdoc&&) -> ValidatingNode<Tns, Tattr, Tvalue, Tcnd, Tqty, Tdoc>;

    template<enumerable_ns_c Tns, enumerable_attr_c Tattr, string_view_c Tvalue, integral_c Tcnd, integral_c Tqty, integral_c Tdoc, class... Rest>
    ValidatingNode(Tns&&, Tattr&&, Tvalue&&, Tcnd&&, Tqty&&, Tdoc&&, Rest&&...) -> ValidatingNode<Tns, Tattr, Tvalue, Tcnd, Tqty, Tdoc, Rest...>;
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// ContentNode for various TTML content types ------------------------------------------------------------------------ 1 of 1 -|
// ============================================================================================================================|

namespace vt::prototype
{
    template<enumerable_ns_c Tns, enumerable_content_c Tcontent, integral_c Tqty, integral_c Tdoc>
    struct ValidatingNode<Tns, Tcontent, Tqty, Tdoc>
    {
    public:
        using data_t = std::add_const_t<ValidatingNode<Tns, Tcontent, Tqty, Tdoc>>;
        using node_t = Node<std::decay_t<Tns>, std::decay_t<Tcontent>>;

        ValidatingNode() = default;
        ~ValidatingNode() = default;

        constexpr ValidatingNode(Tns&& _ns, Tcontent&& _content, Tqty&& _quantifiers, Tdoc&& _documents)
            : node(std::move(_ns), std::move(_content)),
            quantifiers(std::move(_quantifiers)),
            documents(std::move(_documents))
        {}

        constexpr data_t& operator()(const auto&) const noexcept
        {
            return *this;
        }

        constexpr data_t& operator()() const noexcept
        {
            return *this;
        }

        node_t       node;
        size_t       quantifiers;    
        size_t       documents;
    };

    template<enumerable_ns_c Tns, enumerable_content_c Tcontent, integral_c Tqty, integral_c Tdoc, class... Rest>
    struct ValidatingNode<Tns, Tcontent, Tqty, Tdoc, Rest...>
    {
    public:
        using data_t = std::add_const_t<ValidatingNode<Tns, Tcontent, Tqty, Tdoc>>;
        using next_t = std::conditional_t<sizeof...(Rest) == 0, ValidatingNode<>, ValidatingNode<Rest...>>;

        ValidatingNode() = default;
        ~ValidatingNode() = default;

        constexpr ValidatingNode(Tns&& _ns, Tcontent&& _content, Tqty&& _quantifiers, Tdoc&& _documents, Rest&&... _rest)
            : data(std::move(_ns), std::move(_content), std::move(_quantifiers), std::move(_documents)),
            next(std::move(_rest)...)
        {}

        constexpr ValidatingNode(Tns&& _ns, Tcontent&& _content, Tqty&& _quantifiers, Tdoc&& _documents)
            : data(std::move(_ns), std::move(_content), std::move(_quantifiers), std::move(_documents)),
            next({})
        {}

        constexpr data_t& operator()(const auto& f) const noexcept
        {
            if (f(this->data())) return this->data();
            else return this->next(f);
        }

        data_t              data;
        next_t              next;    
    };

    // Deduction guides for TTML content types
    template<enumerable_ns_c Tns, enumerable_content_c Tcontent, integral_c Tqty, integral_c Tdoc>
    ValidatingNode(Tns&&, Tcontent&&, Tqty&&, Tdoc&&) -> ValidatingNode<Tns, Tcontent, Tqty, Tdoc>;

    template<enumerable_ns_c Tns, enumerable_content_c Tcontent, integral_c Tqty, integral_c Tdoc, class... Rest>
    ValidatingNode(Tns&&, Tcontent&&, Tqty&&, Tdoc&&, Rest&&...) -> ValidatingNode<Tns, Tcontent, Tqty, Tdoc, Rest...>;
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// ElementNode for various TTML elements  ---------------------------------------------------------------------------- 1 of 1 -|
// ============================================================================================================================|

namespace vt::prototype
{
    template<enumerable_ns_c Tns, enumerable_tag_c Ttag, integral_c Tdoc>
    struct ValidatingNode<Tns, Ttag, Tdoc>
    {
    public:
        using data_t = std::add_const_t<ValidatingNode<Tns, Ttag, Tdoc>>;
        using node_t = Node<std::decay_t<Tns>, std::decay_t<Ttag>>;

        ValidatingNode() = default;
        ~ValidatingNode() = default;

        constexpr ValidatingNode(Tns&& _ns, Ttag&& _tag, Tdoc&& _documents)
            : node(std::move(_ns), std::move(_tag)),
            documents(std::move(_documents))
        {}

        constexpr data_t& operator()(const auto&) const noexcept
        {
            return *this;
        }

        constexpr data_t& operator()() const noexcept
        {
            return *this;
        }

        node_t       node;
        size_t       documents;
    };

    template<enumerable_ns_c Tns, enumerable_tag_c Ttag, integral_c Tdoc, class... Rest>
    struct ValidatingNode<Tns, Ttag, Tdoc, Rest...>
    {
    public:
        using data_t = std::add_const_t<ValidatingNode<Tns, Ttag, Tdoc>>;
        using next_t = std::conditional_t<sizeof...(Rest) == 0, ValidatingNode<>, ValidatingNode<Rest...>>;

        ValidatingNode() = default;
        ~ValidatingNode() = default;

        constexpr ValidatingNode(Tns&& _ns, Ttag&& _tag, Tdoc&& _documents, Rest&&... _rest)
            : data(std::move(_ns), std::move(_tag), std::move(_documents)),
            next(std::move(_rest)...)
        {}

        constexpr ValidatingNode(Tns&& _ns, Ttag&& _tag, Tdoc&& _documents)
            : data(std::move(_ns), std::move(_tag), std::move(_documents)),
            next({})
        {}

        constexpr data_t& operator()(const auto& f) const noexcept
        {
            if (f(this->data())) return this->data();
            else return this->next(f);
        }

        data_t              data;
        next_t              next;    
    };

    // Deduction guides for TTML element nodes
    template<enumerable_ns_c Tns, enumerable_tag_c Ttag, integral_c Tdoc>
    ValidatingNode(Tns&&, Ttag&&, Tdoc&&) -> ValidatingNode<Tns, Ttag, Tdoc>;

    template<enumerable_ns_c Tns, enumerable_tag_c Ttag, integral_c Tdoc, class... Rest>
    ValidatingNode(Tns&&, Ttag&&, Tdoc&&, Rest&&...) -> ValidatingNode<Tns, Ttag, Tdoc, Rest...>;
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// vt namespace global type aliases ------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

namespace vt
{
    using ValueExpressionNode = vt::prototype::ValidatingNode<vt::prototype::NS, vt::prototype::ValueExpression, std::string_view, size_t, size_t>;
    using AttributeNode = vt::prototype::ValidatingNode<vt::prototype::NS, vt::prototype::Attribute, std::string_view, size_t, size_t, size_t>;
    using ContentNode = vt::prototype::ValidatingNode<vt::prototype::NS, vt::prototype::GenericData, size_t, size_t>;
    using ElementNode = vt::prototype::ValidatingNode<vt::prototype::NS, vt::prototype::Tag, size_t, size_t>;
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|


#endif // VTNODE_HEADER