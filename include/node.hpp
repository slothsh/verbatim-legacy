// Stefan "SoulXP" Olivier
// File: node.hpp
// Description: header file for static TTML dictionary templates

#ifndef VTNODE_HEADER
#define VTNODE_HEADER

// Standard headers
#include <iostream>
#include <limits>
#include <type_traits>
#include <utility>
#include <memory>

// Project headers
#include <magic_enum.hpp>

// Enumerations for XML nodes ------------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

namespace vt
{
	namespace dictionary
	{
		// Enumerations
		enum class NS : size_t
		{
			one, two, three, four,
			none = std::numeric_limits<size_t>::max()
		};

		enum class Tag : size_t
		{
			one, two, three, four,
			none = std::numeric_limits<size_t>::max()
		};

		enum class Attribute : size_t
		{
			one, two, three, four,
			none = std::numeric_limits<size_t>::max()
		};

		enum class ValueExpression : size_t
		{
			one, two, three, four,
			none = std::numeric_limits<size_t>::max()
		};

		enum class AttributeOption : size_t
		{
			one, two, three, four,
			none = std::numeric_limits<size_t>::max()
		};

		enum class Content : size_t
		{
			one, two, three, four,
			none = std::numeric_limits<size_t>::max()
		};
	}
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// Generic types for XML nodes -----------------------------------------------------------------------------------------1 of 3-|
// ============================================================================================================================|

template<class E>
concept enumerable_node =
    std::is_enum_v<E>
    && (E::none == E::none);

// Generic types
template<enumerable_node E>
struct NodeID
{
    E                     id;
    std::string_view      value;
};

template<enumerable_node Tns, enumerable_node Telem>
struct Node
{
    NodeID<Tns>                 ns;
    NodeID<Telem>               element;
};

// XML node component templates ----------------------------------------------------------------------------------------2 of 3-|
// ============================================================================================================================|

template<class Tns, class Topt>
struct AttributeOptionsNode
{
    Node<Tns, Topt>             option;
    std::string_view            value;
    size_t                      documents;
};

template<class Tns, class Tvexpr>
struct ValueExpressionNode
{
    Node<Tns, Tvexpr>                   expression;
    size_t                              documents;
};

template<class Tns, class Tattr, class Tvexpr, class Topt,
            size_t SizeVexpr, size_t SizeOpt>
struct AttributeNode
{
    Node<Tns, Tattr>                                        attribute;
    ValueExpressionNode<Tns, Tvexpr>                        expressions[SizeVexpr];
    AttributeOptionsNode<Tns, Topt>                         options[SizeOpt];
    size_t                                                  _default;
    size_t                                                  conditions;
    size_t                                                  documents;
};

template<class Tns, class Tdata>
struct ContentNode
{
    Node<Tns, Tdata>            type;
    size_t                      documents;
    size_t                      conditions;
};

template<class Tns, class Ttag, class Tattr, class Tvexpr, class Topt, class Tdata,
            size_t SizeAttr, size_t SizeVexpr, size_t SizeOpt, size_t SizeData>
struct XMLNode
{
    // constexpr XMLNode()                                              = default;
    Node<Tns, Ttag>                                                  element;
    AttributeNode<Tns, Tattr, Tvexpr, Topt, SizeVexpr, SizeOpt>      attributes[SizeAttr];
    ContentNode<Tns, Tdata>                                          content[SizeData];
    size_t                                                           documents;
};

// XML node dictionary template ----------------------------------------------------------------------------------------3 of 3-|
// ============================================================================================================================|

template<size_t E, class... Rest>
struct GetHelper;

template<class... E>
class XMLDictionary {};

template<class E, class... Rest>
class XMLDictionary<E, Rest...>
{
public:
    constexpr XMLDictionary(E entry, Rest... rest)
        : entry(entry),
        next(rest...)
    {}

    template<size_t index>
    constexpr auto get() const
    {
        return GetHelper<index, XMLDictionary<E, Rest...>>::get(*this);
    }

    E                           entry;
    XMLDictionary<Rest...>      next;
};

template<class E, class... Rest>
struct GetHelper<0, XMLDictionary<E, Rest...>>
{
    static constexpr E get(XMLDictionary<E, Rest...> d)
    {
        return d.entry;
    }
};

template<size_t I, class E, class... Rest>
struct GetHelper<I, XMLDictionary<E, Rest...>>
{
    static constexpr auto get(XMLDictionary<E, Rest...> d)
    {
        return GetHelper<I-1, XMLDictionary<Rest...>>::get(d.next);
    }
};

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif // VTNODE_HEADER