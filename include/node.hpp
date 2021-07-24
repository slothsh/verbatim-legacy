// Stefan "SoulXP" Olivier
// File: node.hpp
// Description: header file for static TTML dictionary templates

#ifndef VTNODE_HEADER
#define VTNODE_HEADER

// Redefinitions for magic enum size constants
#define MAGIC_ENUM_RANGE_MIN 0
#define MAGIC_ENUM_RANGE_MAX 256

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
        // Dictionary constants
        static constexpr size_t ENUM_ID = MAGIC_ENUM_RANGE_MIN;
        static constexpr size_t ENUM_NONE = MAGIC_ENUM_RANGE_MAX;

		// Enumerations
		enum class NS : size_t
		{
            IS_NS = ENUM_ID,
			one, two, three, four,
			none = ENUM_NONE
		};

		enum class Tag : size_t
		{
            IS_TAG = ENUM_ID,
			one, two, three, four,
			none = ENUM_NONE
		};

		enum class Attribute : size_t
		{
            IS_ATTRIBUTE = ENUM_ID,
			one, two, three, four,
			none = ENUM_NONE
		};

		enum class ValueExpression : size_t
		{
            IS_VALUE_EXPRESSION = ENUM_ID,
			one, two, three, four,
			none = ENUM_NONE
		};

		enum class AttributeOption : size_t
		{
            IS_ATTRIBUTE_OPTION = ENUM_ID,
			one, two, three, four,
			none = ENUM_NONE
		};

		enum class Content : size_t
		{
            IS_CONTENT = ENUM_ID,
			one, two, three, four,
			none = ENUM_NONE
		};
	}
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// Generic types for XML nodes -----------------------------------------------------------------------------------------1 of 3-|
// ============================================================================================================================|

namespace vt
{
	namespace dictionary
	{
        using namespace magic_enum;

        // Concept for generic enumeration types
		template<class E>
		concept enumerable_node =
			std::is_enum_v<E>
            && is_scoped_enum_v<E>
            && enum_contains<E>(E::none)
			&& enum_integer(E::none) == ENUM_NONE;

        // Concept for enumeration types to be used for namespaces
        template<class Tns>
        concept enumerable_ns =
            enumerable_node<Tns>
            && enum_contains<Tns>(Tns::IS_NS)
            && enum_integer(Tns::IS_NS) == ENUM_ID;

        // Concept for enumeration types to be used for xml tags
        template<class Ttag>
        concept enumerable_tag =
            enumerable_node<Ttag>
            && enum_contains<Ttag>(Ttag::IS_TAG)
            && enum_integer(Ttag::IS_TAG) == ENUM_ID;

        // Concept for enumeration types to be used for attributes
        template<class Tattr>
        concept enumerable_attr =
            enumerable_node<Tattr>
            && enum_contains<Tattr>(Tattr::IS_ATTRIBUTE)
            && enum_integer(Tattr::IS_ATTRIBUTE) == ENUM_ID;

        // Concept for enumeration types to be used for attributes
        template<class Tvexpr>
        concept enumerable_vexpr =
            enumerable_node<Tvexpr>
            && enum_contains<Tvexpr>(Tvexpr::IS_VALUE_EXPRESSION)
            && enum_integer(Tvexpr::IS_VALUE_EXPRESSION) == ENUM_ID;

        // Concept for enumeration types to be used for attributes
        template<class Topt>
        concept enumerable_attropt =
            enumerable_node<Topt>
            && enum_contains<Topt>(Topt::IS_ATTRIBUTE_OPTION)
            && enum_integer(Topt::IS_ATTRIBUTE_OPTION) == ENUM_ID;

        // Concept for enumeration types to be used for attributes
        template<class Tcont>
        concept enumerable_content =
            enumerable_node<Tcont>
            && enum_contains<Tcont>(Tcont::IS_CONTENT)
            && enum_integer(Tcont::IS_CONTENT) == ENUM_ID;

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
			Node<Tns, Tvexpr>           expression;
			size_t                      documents;
		};

		template<class Tns, class Tattr, class Tvexpr, class Topt,
					size_t SizeVexpr, size_t SizeOpt>
		struct AttributeNode
		{
			Node<Tns, Tattr>                       attribute;
			ValueExpressionNode<Tns, Tvexpr>       expressions[SizeVexpr];
			AttributeOptionsNode<Tns, Topt>        options[SizeOpt];
			size_t                                 _default;
			size_t                                 conditions;
			size_t                                 documents;
		};

		template<class Tns, class Tdata>
		struct ContentNode
		{
			Node<Tns, Tdata>            type;
			size_t                      documents;
			size_t                      conditions;
		};

        // General XML node type for XML dictionary entries
		template<enumerable_ns Tns, enumerable_tag Ttag,
                    enumerable_attr Tattr, enumerable_vexpr Tvexpr, enumerable_attropt Topt,
                    enumerable_content Tdata,
					size_t SizeAttr, size_t SizeVexpr, size_t SizeOpt, size_t SizeData>
		struct XMLNode
		{
			using node_t = Node<Tns, Ttag>;
			using attribute_t = AttributeNode<Tns, Tattr, Tvexpr, Topt, SizeVexpr, SizeOpt>;
			using content_t = ContentNode<Tns, Tdata>;

            // template<enumerable_node Ens>
            // using enum_t = Ens;

            // // Constructor
            // constexpr XMLNode(Tns&& ns) noexcept
            // {
                
            // }

			node_t				element;	
			attribute_t			attributes[SizeAttr];
			content_t			content[SizeData];
			size_t				documents;
		};

// XML node dictionary template ----------------------------------------------------------------------------------------3 of 3-|
// ============================================================================================================================|

		namespace detail
		{
			template<size_t E, class... Rest>
			struct GetHelper;
		}

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
				return detail::GetHelper<index, XMLDictionary<E, Rest...>>::get(*this);
			}

			E                           entry;
			XMLDictionary<Rest...>      next;
		};

		template<class E, class... Rest>
		struct detail::GetHelper<0, XMLDictionary<E, Rest...>>
		{
			static constexpr E get(XMLDictionary<E, Rest...> d)
			{
				return d.entry;
			}
		};

		template<size_t I, class E, class... Rest>
		struct detail::GetHelper<I, XMLDictionary<E, Rest...>>
		{
			static constexpr auto get(XMLDictionary<E, Rest...> d)
			{
				return detail::GetHelper<I-1, XMLDictionary<Rest...>>::get(d.next);
			}
		};
	}
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif // VTNODE_HEADER