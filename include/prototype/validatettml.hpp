// Stefan "SoulXP" Olivier
// File: validatettml.hpp
// Description: header file for static TTML dictionary templates

#ifndef VTNODE_HEADER
#define VTNODE_HEADER

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "../config.hpp"
#endif

// Standard headers
#include <iostream>
#include <type_traits>
#include <string_view>
#include <tuple>
#include <memory>
#include <utility>
#include <concepts>
#include <iterator>
#include <initializer_list>

// Enumerations for TTML nodes --------------------------------------------------------------------------------------- 1 of 1 -|
// ============================================================================================================================|

namespace vt::prototype
{
    // Error codes
    enum class VT_ERROR_CODE : size_t
    {
        IS_ERROR = VT_ENUM_ID,
        error_empty,
        none = VT_ENUM_NONE
    };

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

    // Assert TTML enumerations are configured correctly
    static_assert(magic_enum::enum_integer(NS::none) == MAGIC_ENUM_RANGE_MAX);
    static_assert(magic_enum::enum_integer(Tag::none) == MAGIC_ENUM_RANGE_MAX);
    static_assert(magic_enum::enum_integer(Attribute::none) == MAGIC_ENUM_RANGE_MAX);
    static_assert(magic_enum::enum_integer(ValueExpression::none) == MAGIC_ENUM_RANGE_MAX);
    static_assert(magic_enum::enum_integer(GenericData::none) == MAGIC_ENUM_RANGE_MAX);
    static_assert(magic_enum::enum_integer(NS::IS_NS) == MAGIC_ENUM_RANGE_MIN);
    static_assert(magic_enum::enum_integer(Tag::IS_TAG) == MAGIC_ENUM_RANGE_MIN);
    static_assert(magic_enum::enum_integer(Attribute::IS_ATTRIBUTE) == MAGIC_ENUM_RANGE_MIN);
    static_assert(magic_enum::enum_integer(ValueExpression::IS_VALUE_EXPRESSION) == MAGIC_ENUM_RANGE_MIN);
    static_assert(magic_enum::enum_integer(GenericData::IS_DATA) == MAGIC_ENUM_RANGE_MIN);
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
        using id_t = std::remove_cvref_t<E>;

        constexpr NodeID()
            : id(id_t::none)
            , value(mge::enum_name(id_t::none))
        {}

        constexpr ~NodeID() = default;

        constexpr NodeID(id_t&& _id)
            : id(_id),
            value(magic_enum::enum_name<id_t>(_id))
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
        using ns_t = NodeID<std::remove_cvref_t<Tns>>;
        using element_t = NodeID<std::remove_cvref_t<Telem>>;

        constexpr Node()
            : ns({})
            , element({})
        {}

        constexpr ~Node() = default;

        constexpr Node(Tns&& _ns, Telem&& _element)
            : ns(std::move(_ns)),
            element(std::move(_element))
        {}

        constexpr Node(const Tns&& _ns, const Telem&& _element)
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
    concept string_view_c =
        std::same_as<T, std::string_view> || std::is_constructible_v<std::string_view, T>;
    
    template<class T>
    concept integral_c = std::is_integral_v<T>;

    template<class T>
    concept signed_integral_c = integral_c<T> && std::is_signed_v<T>;

    template<class T>
    concept unsigned_integral_c = integral_c<T> && !signed_integral_c<T>;

    template<class F, class... Args>
    concept invocable_c = requires(F&& f, Args&&... args) {
        std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
    };

    // Base class for ValidatingNodeData
    template<class...>
    struct ValidatingNodeData
    {
    public:
        constexpr ValidatingNodeData() = delete;
        constexpr ~ValidatingNodeData() = default;
    };
    // Base class for ValidatingNode
    template<class...>
    struct ValidatingNode
    {
    public:
        constexpr ValidatingNode() = delete;
        constexpr ~ValidatingNode() = default;
    };

    namespace detail
    {
        template<class T> // TODO: concepts
        struct _validatingnode_data_part
        {
        public:
            // Type aliases
            using type = typename std::decay_t<T>::data_t;
            static type value;
        };

        template<size_t Size, class Tdata>
        struct _validatingnode_input_iter
        {
        public:
            using data_t            = std::decay_t<Tdata>;
            using iterator_t        = _validatingnode_input_iter<Size, data_t>;
            using iterator_category = std::forward_iterator_tag;
            using difference_type   = size_t;

            // Default ctor
            constexpr _validatingnode_input_iter()
                : index(0)
                , size(1)
                , data()
            {
                static_assert(Size == 0, "templated size of default constructed _validatingnode_input_iter must be 0");
            }

            // Default dtor
            constexpr ~_validatingnode_input_iter() = default;

            // Copy ctor
            constexpr _validatingnode_input_iter(const _validatingnode_input_iter& _iterator)
                : index(_iterator.index)
                , size(_iterator.size)
            {
                for (size_t i = 0; i < this->size; ++i) {
                    this->data[i] =  _iterator.data[i]; 
                }
            }

            // Copy assignment
            constexpr _validatingnode_input_iter& operator=(const _validatingnode_input_iter& _iterator)
            {
                this->index = _iterator.index;
                this->size = _iterator.size;

                for (size_t i = 0; i < this->size; ++i) {
                    this->data[i] =  _iterator.data[i]; 
                }

                return *this;
            }

            // Templated base case ctor
            constexpr explicit _validatingnode_input_iter(data_t&& _data)
                : index(0)
                , size(1)
            {
                for (size_t i = this->index; i < this->size; ++i) {
                    if (i == 0) this->data[i] = _data;
                }
            }

            // Templated recursive case ctor
            template<class Tnext> // TODO: Concept to validate type
            constexpr explicit _validatingnode_input_iter(data_t&& _data, Tnext&& _next)
                : index(0)
                , size(Size)
            {
                for (size_t i = this->index; i < this->size; ++i) {
                    if (i == 0) this->data[i] = _data;
                    else this->data[i] = std::move(_next(std::move(i)));
                }
            }

            // Indexed access call operator
            constexpr iterator_t& operator()(int _index)
            {
                if (_index >= static_cast<int>(this->size) || _index < 0) this->index = this->size;
                else this->index = _index;
                return *this;
            }

            constexpr iterator_t operator()(int _index) const
            {
                iterator_t tmp = *this;
                if (_index >= static_cast<int>(this->size) || _index < 0) tmp.index = tmp.size;
                else tmp.index = _index;
                return tmp;
            }

            // Dereference operators
            constexpr data_t& operator*() { return this->data[this->index]; }
            constexpr data_t operator*() const { return this->data[this->index]; }
            constexpr data_t& operator->() { return this->data[this->index]; }
            constexpr data_t operator->() const { return this->data[this->index]; }

            // Increment operators
            constexpr iterator_t& operator++()
            {
                ++this->index;
                return *this;
            }

            constexpr iterator_t operator++(int)
            {
                auto tmp = *this;
                ++(*this);
                return tmp;
            }

            // Equality comparison operators
            template<class Tleft, class Tright>
            constexpr inline bool compareEquals(Tleft&& lhs, Tright&& rhs)
            {
                if (lhs.index == rhs.index && lhs.size == rhs.size) return true;
                return false;
            }

            template<class Tleft, class Tright>
            constexpr inline bool compareEquals(Tleft&& lhs, Tright&& rhs) const
            {
                if (lhs.index == rhs.index && lhs.size == rhs.size) return true;
                return false;
            }

            template<class Tleft, class Tright>
            constexpr inline bool compareNotEquals(Tleft&& lhs, Tright&& rhs)       { return !(lhs == rhs); }

            template<class Tleft, class Tright>
            constexpr inline bool compareNotEquals(Tleft&& lhs, Tright&& rhs) const { return !(lhs == rhs); }

            constexpr bool operator==(auto&& rhs)       { return this->compareEquals(std::forward<decltype(*this)>(*this),    std::forward<decltype(rhs)>(rhs)); }
            constexpr bool operator!=(auto&& rhs)       { return this->compareNotEquals(std::forward<decltype(*this)>(*this), std::forward<decltype(rhs)>(rhs)); }
            constexpr bool operator==(auto&& rhs) const { return this->compareEquals(std::forward<decltype(*this)>(*this),    std::forward<decltype(rhs)>(rhs)); }
            constexpr bool operator!=(auto&& rhs) const { return this->compareNotEquals(std::forward<decltype(*this)>(*this), std::forward<decltype(rhs)>(rhs)); }

            // Standard template library swap implementation
            friend void swap(iterator_t& lhs, iterator_t& rhs)
            {
                std::swap(lhs.index, rhs.index);
                std::swap(lhs.size, rhs.size);
                std::swap(lhs.data, rhs.data);
            }

            // Data members
            size_t  index;
            size_t  size;
            data_t  data[Size + 1];
        };
    }
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// ValidatingNode Specializations for TTML Value Expressions --------------------------------------------------------- 1 of 1 -|
// ============================================================================================================================|

namespace vt::prototype
{
    template<enumerable_ns_c Tns, enumerable_vexpr_c Tvexpr, string_view_c Tvalue, integral_c Tcnd, integral_c Tdoc>
    class ValidatingNodeData<Tns, Tvexpr, Tvalue, Tcnd, Tdoc>
    {
    public:
        // Type aliases
        using value_t = std::conditional_t<std::is_same_v<Tvalue, std::string_view>, std::decay_t<Tvalue>, std::string_view>;
        using data_t = ValidatingNodeData<std::decay_t<Tns>, std::decay_t<Tvexpr>, value_t, std::decay_t<Tcnd>, std::decay_t<Tdoc>>;
        using node_t = Node<std::decay_t<Tns>, std::decay_t<Tvexpr>>;

        // Default ctor & dtor
        constexpr ValidatingNodeData()
            : node({})
            , value(mge::enum_name(VT_ERROR_CODE::error_empty))
            , conditions(mge::enum_integer(constants::NodeCondition::none))
            , documents(mge::enum_integer(constants::TTMLDocument::none))
        {}

        constexpr ~ValidatingNodeData() = default;

        // Templated ctor
        constexpr ValidatingNodeData(Tns&& _ns, Tvexpr&& _vexpr, Tvalue&& _value, Tcnd&& _conditions, Tdoc&& _documents)
            : node(std::move(_ns), std::move(_vexpr))
            , value(std::move(_value))
            , conditions(std::move(_conditions))
            , documents(std::move(_documents))
        {}

        // Standard template library swap implementation
        friend void swap(auto& lhs, auto& rhs)
        {
            std::swap(lhs.node, rhs.node);
            std::swap(lhs.value, rhs.value);
            std::swap(lhs.conditions, rhs.conditions);
            std::swap(lhs.documents, rhs.documents);
        }

        node_t       node;
        value_t      value;
        size_t       conditions;
        size_t       documents;
    };

    template<enumerable_ns_c Tns, enumerable_vexpr_c Tvexpr, string_view_c Tvalue, integral_c Tcnd, integral_c Tdoc>
    class ValidatingNode<Tns, Tvexpr, Tvalue, Tcnd, Tdoc>
    {
    public:
        // Type aliases
        using value_t = std::conditional_t<std::is_same_v<std::decay_t<Tvalue>, std::string_view>, std::decay_t<Tvalue>, std::string_view>;
        using data_t = ValidatingNodeData<std::decay_t<Tns>, std::decay_t<Tvexpr>, value_t, std::decay_t<Tcnd>, std::decay_t<Tdoc>>;
        using iterator_t = detail::_validatingnode_input_iter<1, data_t>;

        // Default ctor & dtor
        constexpr ValidatingNode() = delete;
        constexpr ~ValidatingNode() = default;

        // Template root ctor
        constexpr ValidatingNode(std::decay_t<Tns>&& _ns, std::decay_t<Tvexpr>&& _vexpr, std::decay_t<Tvalue>&& _value, std::decay_t<Tcnd>&& _conditions, std::decay_t<Tdoc>&& _documents)
            : data(std::move(_ns), std::move(_vexpr), std::move(_value), std::move(_conditions), std::move(_documents))
            , index(0)
            , iterator(std::move(this->data))
            , tail_data({})
        {}

        // Template recursive ctor
        constexpr ValidatingNode(size_t&& _index, std::decay_t<Tns>&& _ns, std::decay_t<Tvexpr>&& _vexpr, std::decay_t<Tvalue>&& _value, std::decay_t<Tcnd>&& _conditions, std::decay_t<Tdoc>&& _documents)
            : data(std::move(_ns), std::move(_vexpr), std::move(_value), std::move(_conditions), std::move(_documents))
            , index(_index)
            , iterator(std::move(this->data))
            , tail_data({})
        {}

        // Data access for current node
        constexpr data_t& operator()(size_t&& _index)
        {
            if (this->index == _index) return this->data;
            else return this->tail_data;
        }

        constexpr data_t operator()(size_t&& _index) const noexcept
        {
            if (this->index == _index) return this->data;
            else return data_t{};
        }

        // Iterator access
        constexpr iterator_t& begin()
        {
            return this->iterator(0);
        }

        constexpr iterator_t begin() const noexcept
        {
            return this->iterator(0);
        }

        constexpr iterator_t& end()
        {
            return this->iterator(-1);
        }

        constexpr iterator_t end() const noexcept
        {
            return this->iterator(-1);
        }

        // Member variables
        data_t              data;
        size_t              index;
        iterator_t          iterator;

    private:
        data_t              tail_data;
    };

    template<enumerable_ns_c Tns, enumerable_vexpr_c Tvexpr, string_view_c Tvalue, integral_c Tcnd, integral_c Tdoc, class... Rest>
    class ValidatingNode<Tns, Tvexpr, Tvalue, Tcnd, Tdoc, Rest...>
    {
    public:
        // Type aliases
        using value_t = std::conditional_t<std::is_same_v<std::decay_t<Tvalue>, std::string_view>, std::decay_t<Tvalue>, std::string_view>;
        using data_t = ValidatingNodeData<std::decay_t<Tns>, std::decay_t<Tvexpr>, value_t, std::decay_t<Tcnd>, std::decay_t<Tdoc>>;
        using next_t = ValidatingNode<std::decay_t<Rest>...>;
        using iterator_t = detail::_validatingnode_input_iter<sizeof...(Rest) / 5 + 1, data_t>;

        // Default ctor & dtor
        constexpr ValidatingNode() = delete;
        constexpr ~ValidatingNode() = default;

        // Template root ctor
        constexpr ValidatingNode(std::decay_t<Tns>&& _ns, std::decay_t<Tvexpr>&& _vexpr, std::decay_t<Tvalue>&& _value, std::decay_t<Tcnd>&& _conditions, std::decay_t<Tdoc>&& _documents, std::decay_t<Rest>&&... _rest)
            : data(std::move(_ns), std::move(_vexpr), std::move(_value), std::move(_conditions), std::move(_documents))
            , index(0)
            , next(this->index + 1, std::move(_rest)...)
            , iterator(std::move(this->data), std::move(this->next))
        {}

        // Template recursive ctor
        constexpr ValidatingNode(size_t&& _index, std::decay_t<Tns>&& _ns, std::decay_t<Tvexpr>&& _vexpr, std::decay_t<Tvalue>&& _value, std::decay_t<Tcnd>&& _conditions, std::decay_t<Tdoc>&& _documents, std::decay_t<Rest>&&... _rest)
            : data(std::move(_ns), std::move(_vexpr), std::move(_value), std::move(_conditions), std::move(_documents))
            , index(_index)
            , next(this->index + 1, std::move(_rest)...)
            , iterator(std::move(this->data), std::move(this->next))
        {}

        // Data access for current node
        constexpr data_t& operator()(size_t&& _index)
        {
            if (this->index == _index) return this->data;
            return this->next(std::move(_index));
        }

        constexpr data_t operator()(size_t&& _index) const noexcept
        {
            if (this->index == _index) return this->data;
            return this->next(std::move(_index));
        }

        // Iterator access
        constexpr iterator_t& begin()
        {
            return this->iterator(0);
        }

        constexpr iterator_t begin() const noexcept
        {
            return this->iterator(0);
        }

        constexpr iterator_t& end()
        {
            return this->iterator(-1);
        }

        constexpr iterator_t end() const noexcept
        {
            return this->iterator(-1);
        }

        data_t              data;
        size_t              index;
        next_t              next;
        iterator_t          iterator;
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
        using node_t = Node<std::remove_cvref_t<Tns>, std::remove_cvref_t<Tattr>>;
        using value_t = std::conditional_t<std::is_same_v<Tvalue, std::string_view>, std::remove_cvref_t<Tvalue>, std::string_view>;
        using tuple_t = std::add_const_t<std::tuple<Tns, Tattr, Tvalue, Tcnd, Tqty, Tdoc>>;

        ValidatingNode() = default;
        ~ValidatingNode() = default;

        constexpr ValidatingNode(Tns&& _ns, Tattr&& _attr, Tvalue&& _value, Tcnd&& _conditions, Tqty&& _quantifiers, Tdoc&& _documents)
            : node(std::move(_ns), std::move(_attr)),
            value(std::move(_value)),
            conditions(std::move(_conditions)),
            quantifiers(std::move(_quantifiers)),
            documents(std::move(_documents))
        {}

        constexpr ValidatingNode(std::add_const_t<Tns>&& _ns, std::add_const_t<Tattr>&& _attr, std::add_const_t<Tvalue>&& _value, std::add_const_t<Tcnd>&& _conditions, std::add_const_t<Tqty>&& _quantifiers, std::add_const_t<Tdoc>&& _documents)
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

    template<enumerable_ns_c Tns, enumerable_attr_c Tattr, string_view_c Tvalue, integral_c Tcnd, integral_c Tqty, integral_c Tdoc>
    struct ValidatingNode<std::tuple<Tns, Tattr, Tvalue, Tcnd, Tqty, Tdoc>>
    {
    public:
        using data_t = std::add_const_t<ValidatingNode<Tns, Tattr, Tvalue, Tcnd, Tqty, Tdoc>>;
        using tuple_t = std::add_const_t<std::tuple<Tns, Tattr, Tvalue, Tcnd, Tqty, Tdoc>>;

        ValidatingNode() = default;
        ~ValidatingNode() = default;

        constexpr ValidatingNode(tuple_t&& _data) 
            : data(std::move(std::get<0>(_data)),
                    std::move(std::get<1>(_data)),
                    std::move(std::get<2>(_data)),
                    std::move(std::get<3>(_data)), 
                    std::move(std::get<4>(_data)),
                    std::move(std::get<5>(_data)))
        {}

        constexpr data_t& operator()(const auto&) const noexcept
        {
            return *this;
        }

        constexpr data_t& operator()() const noexcept
        {
            return *this;
        }

        data_t       data;
    };

    template<enumerable_ns_c Tns, enumerable_attr_c Tattr, string_view_c Tvalue, integral_c Tcnd, integral_c Tqty, integral_c Tdoc, class... Rest>
    struct ValidatingNode<Tns, Tattr, Tvalue, Tcnd, Tqty, Tdoc, Rest...>
    {
    public:
        using data_t = std::add_const_t<ValidatingNode<Tns, Tattr, Tvalue, Tcnd, Tqty, Tdoc>>;
        using next_t = std::conditional_t<sizeof...(Rest) == 0, ValidatingNode<>, ValidatingNode<std::remove_cvref_t<Rest>...>>;
        using tuple_t = std::add_const_t<std::tuple<Tns, Tattr, Tvalue, Tcnd, Tqty, Tdoc>>;

        ValidatingNode() = default;
        ~ValidatingNode() = default;

        constexpr ValidatingNode(Tns&& _ns, Tattr&& _attr, Tvalue&& _value, Tcnd&& _conditions, Tqty&& _quantifiers, Tdoc&& _documents)
            : data(std::move(_ns), std::move(_attr), std::move(_value), std::move(_conditions), std::move(_quantifiers), std::move(_documents)),
            next({})
        {}

        constexpr ValidatingNode(std::add_const_t<Tns>&& _ns, std::add_const_t<Tattr>&& _attr, std::add_const_t<Tvalue>&& _value, std::add_const_t<Tcnd>&& _conditions, std::add_const_t<Tqty>&& _quantifiers, std::add_const_t<Tdoc>&& _documents, std::add_const_t<Rest>&&... _rest)
            : data(std::move(_ns), std::move(_attr), std::move(_value), std::move(_conditions), std::move(_quantifiers), std::move(_documents)),
            next(std::move(_rest)...)
        {}

        constexpr data_t& operator()(const auto& f) const noexcept
        {
            if (f(this->data())) return this->data();
            else return this->next(f);
        }

        data_t              data;
        next_t              next;    
    };

    template<enumerable_ns_c Tns, enumerable_attr_c Tattr, string_view_c Tvalue, integral_c Tcnd, integral_c Tqty, integral_c Tdoc, class... Rest>
    struct ValidatingNode<std::tuple<Tns, Tattr, Tvalue, Tcnd, Tqty, Tdoc>, Rest...>
    {
    public:
        using data_t = std::add_const_t<ValidatingNode<Tns, Tattr, Tvalue, Tcnd, Tqty, Tdoc>>;
        using next_t = std::conditional_t<sizeof...(Rest) == 0, ValidatingNode<>, ValidatingNode<std::remove_cvref_t<Rest>...>>;
        using tuple_t = std::add_const_t<std::tuple<Tns, Tattr, Tvalue, Tcnd, Tqty, Tdoc>>;

        ValidatingNode() = default;
        ~ValidatingNode() = default;

        constexpr ValidatingNode(tuple_t&& _data)
            : data(std::move(std::get<0>(_data)),
                    std::move(std::get<1>(_data)),
                    std::move(std::get<2>(_data)),
                    std::move(std::get<3>(_data)), 
                    std::move(std::get<4>(_data)),
                    std::move(std::get<5>(_data))),
            next({})
        {}

        constexpr ValidatingNode(tuple_t&& _data, std::add_const_t<Rest>&&... _rest)
            : data(std::move(std::get<0>(_data)),
                    std::move(std::get<1>(_data)),
                    std::move(std::get<2>(_data)),
                    std::move(std::get<3>(_data)), 
                    std::move(std::get<4>(_data)),
                    std::move(std::get<5>(_data))),
            next(std::move(_rest)...)
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

    template<enumerable_ns_c Tns, enumerable_attr_c Tattr, string_view_c Tvalue, integral_c Tcnd, integral_c Tqty, integral_c Tdoc>
    ValidatingNode(const std::tuple<Tns, Tattr, Tvalue, Tcnd, Tqty, Tdoc>&&) -> ValidatingNode<std::tuple<Tns, Tattr, Tvalue, Tcnd, Tqty, Tdoc>>;

    template<enumerable_ns_c Tns, enumerable_attr_c Tattr, string_view_c Tvalue, integral_c Tcnd, integral_c Tqty, integral_c Tdoc, class... Rest>
    ValidatingNode(const std::tuple<Tns, Tattr, Tvalue, Tcnd, Tqty, Tdoc>&&, Rest&&...) -> ValidatingNode<std::tuple<Tns, Tattr, Tvalue, Tcnd, Tqty, Tdoc>, Rest...>;
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
        using node_t = Node<std::remove_cvref_t<Tns>, std::remove_cvref_t<Tcontent>>;
        using tuple_t = std::add_const_t<std::tuple<Tns, Tcontent, Tqty, Tdoc>>;

        ValidatingNode() = default;
        ~ValidatingNode() = default;

        constexpr ValidatingNode(std::add_const_t<Tns>&& _ns, std::add_const_t<Tcontent>&& _content, std::add_const_t<Tqty>&& _quantifiers, std::add_const_t<Tdoc>&& _documents)
            : node(std::move(_ns), std::move(_content)),
            quantifiers(std::move(_quantifiers)),
            documents(std::move(_documents))
        {}

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

    template<enumerable_ns_c Tns, enumerable_content_c Tcontent, integral_c Tqty, integral_c Tdoc>
    struct ValidatingNode<std::tuple<Tns, Tcontent, Tqty, Tdoc>>
    {
    public:
        using data_t = std::add_const_t<ValidatingNode<Tns, Tcontent, Tqty, Tdoc>>;
        using tuple_t = std::add_const_t<std::tuple<Tns, Tcontent, Tqty, Tdoc>>;

        ValidatingNode() = default;
        ~ValidatingNode() = default;

        constexpr ValidatingNode(tuple_t&& _data)
            : data(std::move(std::get<0>(_data)),
                    std::move(std::get<1>(_data)),
                    std::move(std::get<2>(_data)),
                    std::move(std::get<3>(_data)))
        {}

        constexpr data_t& operator()(const auto&) const noexcept
        {
            return *this;
        }

        constexpr data_t& operator()() const noexcept
        {
            return *this;
        }

        data_t       data;
    };

    template<enumerable_ns_c Tns, enumerable_content_c Tcontent, integral_c Tqty, integral_c Tdoc, class... Rest>
    struct ValidatingNode<Tns, Tcontent, Tqty, Tdoc, Rest...>
    {
    public:
        using data_t = std::add_const_t<ValidatingNode<Tns, Tcontent, Tqty, Tdoc>>;
        using next_t = std::conditional_t<sizeof...(Rest) == 0, ValidatingNode<>, ValidatingNode<std::remove_cvref_t<Rest>...>>;
        using tuple_t = std::add_const_t<std::tuple<Tns, Tcontent, Tqty, Tdoc>>;

        ValidatingNode() = default;
        ~ValidatingNode() = default;

        constexpr ValidatingNode(Tns&& _ns, Tcontent&& _content, Tqty&& _quantifiers, Tdoc&& _documents)
            : data(std::move(_ns), std::move(_content), std::move(_quantifiers), std::move(_documents)),
            next({})
        {}

        constexpr ValidatingNode(std::add_const_t<Tns>&& _ns, std::add_const_t<Tcontent>&& _content, std::add_const_t<Tqty>&& _quantifiers, std::add_const_t<Tdoc>&& _documents, std::add_const_t<Rest>&&... _rest)
            : data(std::move(_ns), std::move(_content), std::move(_quantifiers), std::move(_documents)),
            next(std::move(_rest)...)
        {}

        constexpr data_t& operator()(const auto& f) const noexcept
        {
            if (f(this->data())) return this->data();
            else return this->next(f);
        }

        data_t              data;
        next_t              next;    
    };

    template<enumerable_ns_c Tns, enumerable_content_c Tcontent, integral_c Tqty, integral_c Tdoc, class... Rest>
    struct ValidatingNode<std::tuple<Tns, Tcontent, Tqty, Tdoc>, Rest...>
    {
    public:
        using data_t = std::add_const_t<ValidatingNode<Tns, Tcontent, Tqty, Tdoc>>;
        using next_t = std::conditional_t<sizeof...(Rest) == 0, ValidatingNode<>, ValidatingNode<std::remove_cvref_t<Rest>...>>;
        using tuple_t = std::add_const_t<std::tuple<Tns, Tcontent, Tqty, Tdoc>>;

        ValidatingNode() = default;
        ~ValidatingNode() = default;

        constexpr ValidatingNode(tuple_t&& _data)
            : data(std::move(std::get<0>(_data)),
                    std::move(std::get<1>(_data)),
                    std::move(std::get<2>(_data)),
                    std::move(std::get<3>(_data))),
            next({})
        {}

        constexpr ValidatingNode(tuple_t&& _data, std::add_const_t<Rest>&&... _rest)
            : data(std::move(std::get<0>(_data)),
                    std::move(std::get<1>(_data)),
                    std::move(std::get<2>(_data)),
                    std::move(std::get<3>(_data))),
            next(std::move(_rest)...)
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

    template<enumerable_ns_c Tns, enumerable_content_c Tcontent, integral_c Tqty, integral_c Tdoc>
    ValidatingNode(const std::tuple<Tns, Tcontent, Tqty, Tdoc>&&) -> ValidatingNode<std::tuple<Tns, Tcontent, Tqty, Tdoc>>;

    template<enumerable_ns_c Tns, enumerable_content_c Tcontent, integral_c Tqty, integral_c Tdoc, class... Rest>
    ValidatingNode(const std::tuple<Tns, Tcontent, Tqty, Tdoc>&&, Rest&&...) -> ValidatingNode<std::tuple<Tns, Tcontent, Tqty, Tdoc>, Rest...>;
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// ElementNode for various TTML elements  ---------------------------------------------------------------------------- 1 of 1 -|
// ============================================================================================================================|

namespace vt::prototype
{
    template<class T, class... Rest>
    concept attr_node_c = std::is_same_v<T, ValidatingNode<NS, Attribute, std::string_view, size_t, size_t, size_t, Rest...>>;

    template<class>
    struct is_element_tuple : std::false_type
    {};

    template<enumerable_ns_c Tns, enumerable_tag_c Ttag, class Tattr, class Tcontent, integral_c Tdoc>
    struct is_element_tuple<std::tuple<Tns, Ttag, Tattr, Tcontent, Tdoc>> : std::true_type
    {};

    template<class T>
    concept element_tuple_c = is_element_tuple<std::remove_cvref_t<T>>::value;

    template<enumerable_ns_c Tns, enumerable_tag_c Ttag, class Tattr, class Tcontent, integral_c Tdoc>
    struct ValidatingNode<Tns, Ttag, Tattr, Tcontent, Tdoc>
    {
    public:
        using data_t = std::add_const_t<ValidatingNode<Tns, Ttag, Tattr, Tcontent, Tdoc>>;
        using node_t = Node<std::remove_cvref_t<Tns>, std::remove_cvref_t<Ttag>>;
        using attribute_t = std::remove_cvref_t<Tattr>;
        using content_t = std::remove_cvref_t<Tcontent>;

        ValidatingNode() = default;
        ~ValidatingNode() = default;

        constexpr ValidatingNode(Tns&& _ns, Ttag&& _tag, Tattr&& _attributes, Tcontent&& _content, Tdoc&& _documents)
            : node(std::move(_ns), std::move(_tag)),
            attributes(std::move(_attributes)),
            content(std::move(_content)),
            documents(std::move(_documents))
        {}

        constexpr ValidatingNode(std::add_const_t<Tns>&& _ns, std::add_const_t<Ttag>&& _tag, std::add_const_t<Tattr>&& _attributes, std::add_const_t<Tcontent>&& _content, std::add_const_t<Tdoc>&& _documents)
            : node(std::move(_ns), std::move(_tag)),
            attributes(std::move(_attributes)),
            content(std::move(_content)),
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

        node_t          node;
        attribute_t     attributes;
        content_t       content;
        size_t          documents;
    };

    template<enumerable_ns_c Tns, enumerable_tag_c Ttag, class Tattr, class Tcontent, integral_c Tdoc>
    struct ValidatingNode<std::tuple<Tns, Ttag, Tattr, Tcontent, Tdoc>>
    {
    public:
        using data_t = std::add_const_t<ValidatingNode<Tns, Ttag, Tattr, Tcontent, Tdoc>>;
        using tuple_t = std::add_const_t<std::tuple<Tns, Ttag, Tattr, Tcontent, Tdoc>>;

        ValidatingNode() = default;
        ~ValidatingNode() = default;

        constexpr ValidatingNode(tuple_t&& _data)
            : data(std::move(std::get<0>(_data)),
                    std::move(std::get<1>(_data)),
                    std::move(std::get<2>(_data)),
                    std::move(std::get<3>(_data)),
                    std::move(std::get<4>(_data)))
        {}

        constexpr data_t& operator()(const auto&) const noexcept
        {
            return *this;
        }

        constexpr data_t& operator()() const noexcept
        {
            return *this;
        }

        data_t          data;
    };

    template<enumerable_ns_c Tns, enumerable_tag_c Ttag, class Tattr, class Tcontent, integral_c Tdoc, class... Rest>
    struct ValidatingNode<Tns, Ttag, Tattr, Tcontent, Tdoc, Rest...>
    {
    public:
        using data_t = std::add_const_t<ValidatingNode<Tns, Ttag, Tattr, Tcontent, Tdoc>>;
        using next_t = std::conditional_t<sizeof...(Rest) == 0, ValidatingNode<>, ValidatingNode<std::remove_cvref_t<Rest>...>>;
        using tuple_t = std::add_const_t<std::tuple<Tns, Ttag, Tattr, Tcontent, Tdoc>>;

        ValidatingNode() = default;
        ~ValidatingNode() = default;

        constexpr ValidatingNode(std::add_const_t<Tns>&& _ns, std::add_const_t<Ttag>&& _tag, std::add_const_t<Tattr>&& _attributes, std::add_const_t<Tcontent>&& _content, std::add_const_t<Tdoc>&& _documents, std::add_const_t<Rest>&&... _rest)
            : data(std::move(_ns), std::move(_tag), std::move(_attributes), std::move(_content), std::move(_documents)),
            next(std::move(_rest)...)
        {}

        constexpr ValidatingNode(std::add_const_t<Tns>&& _ns, std::add_const_t<Ttag>&& _tag, std::add_const_t<Tattr>&& _attributes, std::add_const_t<Tcontent>&& _content, std::add_const_t<Tdoc>&& _documents)
            : data(std::move(_ns), std::move(_tag), std::move(_attributes), std::move(_content), std::move(_documents)),
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

    template<enumerable_ns_c Tns, enumerable_tag_c Ttag, class Tattr, class Tcontent, integral_c Tdoc, class... Rest>
    struct ValidatingNode<std::tuple<Tns, Ttag, Tattr, Tcontent, Tdoc>, Rest...>
    {
    public:
        // Data aliases
        using data_t = std::add_const_t<ValidatingNode<Tns, Ttag, Tattr, Tcontent, Tdoc>>;
        using next_t = std::conditional_t<sizeof...(Rest) == 0, ValidatingNode<>, ValidatingNode<std::remove_cvref_t<Rest>...>>;
        using tuple_t = std::add_const_t<std::tuple<Tns, Ttag, Tattr, Tcontent, Tdoc>>;

        ValidatingNode() = default;
        ~ValidatingNode() = default;

        constexpr ValidatingNode(tuple_t&& _data)
            : data(std::move(std::get<0>(_data)),
                    std::move(std::get<1>(_data)),
                    std::move(std::get<2>(_data)),
                    std::move(std::get<3>(_data)),
                    std::move(std::get<4>(_data))),
            next({})
        {}

        constexpr ValidatingNode(tuple_t&& _data, std::add_const_t<Rest>&&... _rest)
            : data(std::move(std::get<0>(_data)),
                    std::move(std::get<1>(_data)),
                    std::move(std::get<2>(_data)),
                    std::move(std::get<3>(_data)),
                    std::move(std::get<4>(_data))),
            next(std::move(_rest)...)
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
    template<enumerable_ns_c Tns, enumerable_tag_c Ttag, class Tattr, class Tcontent, integral_c Tdoc>
    ValidatingNode(Tns&&, Ttag&&, Tattr&&, Tcontent&&, Tdoc&&) -> ValidatingNode<Tns, Ttag, Tattr, Tcontent, Tdoc>;

    template<enumerable_ns_c Tns, enumerable_tag_c Ttag, class Tattr, class Tcontent, integral_c Tdoc, class... Rest>
    ValidatingNode(Tns&&, Ttag&&, Tattr&&, Tcontent&&, Tdoc&&, Rest&&...) -> ValidatingNode<Tns, Ttag, Tattr, Tcontent, Tdoc, Rest...>;

    template<enumerable_ns_c Tns, enumerable_tag_c Ttag, class Tattr, class Tcontent, integral_c Tdoc>
    ValidatingNode(const std::tuple<Tns, Ttag, Tattr, Tcontent, Tdoc>&&) -> ValidatingNode<std::tuple<Tns, Ttag, Tattr, Tcontent, Tdoc>>;

    template<enumerable_ns_c Tns, enumerable_tag_c Ttag, class Tattr, class Tcontent, integral_c Tdoc, class... Rest>
    ValidatingNode(const std::tuple<Tns, Ttag, Tattr, Tcontent, Tdoc>&&, Rest&&...) -> ValidatingNode<std::tuple<Tns, Ttag, Tattr, Tcontent, Tdoc>, Rest...>;
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// vt namespace global type aliases ------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

namespace vt
{
    using ValueExpressionNode = vt::prototype::ValidatingNode<vt::prototype::NS, vt::prototype::ValueExpression, std::string_view, size_t, size_t>;
    using AttributeNode = vt::prototype::ValidatingNode<vt::prototype::NS, vt::prototype::Attribute, std::string_view, size_t, size_t, size_t>;
    using ContentNode = vt::prototype::ValidatingNode<vt::prototype::NS, vt::prototype::GenericData, size_t, size_t>;
    // using ElementNode = vt::prototype::ValidatingNode<vt::prototype::NS, vt::prototype::Tag, AttributeNode, size_t>;
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|


#endif // VTNODE_HEADER