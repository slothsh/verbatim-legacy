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
#include <utility>
#include <concepts>

// Enumerations for XML nodes ------------------------------------------------------------------------------------------1 of 5-|
// ============================================================================================================================|

namespace vt
{
    namespace dictionary
    {
        // Generic enumerations for prototyping
        enum class NS : size_t
        {
            IS_NS = VT_ENUM_ID,
            one, two, three, four,
            none = VT_ENUM_NONE
        };

        enum class Tag : size_t
        {
            IS_TAG = VT_ENUM_ID,
            one, two, three, four,
            none = VT_ENUM_NONE
        };

        enum class Attribute : size_t
        {
            IS_ATTRIBUTE = VT_ENUM_ID,
            one, two, three, four,
            none = VT_ENUM_NONE
        };

        enum class ValueExpression : size_t
        {
            IS_VALUE_EXPRESSION = VT_ENUM_ID,
            one, two, three, four,
            none = VT_ENUM_NONE
        };

        enum class AttributeOption : size_t
        {
            IS_ATTRIBUTE_OPTION = VT_ENUM_ID,
            one, two, three, four,
            none = VT_ENUM_NONE
        };

        enum class Content : size_t
        {
            IS_CONTENT = VT_ENUM_ID,
            one, two, three, four,
            none = VT_ENUM_NONE
        };
    }
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// Generic types for XML nodes -----------------------------------------------------------------------------------------2 of 5-|
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
            && enum_integer(E::none) == VT_ENUM_NONE;

        // Concept for enumeration types to be used for namespaces
        template<class Tns>
        concept enumerable_ns =
            enumerable_node<Tns>
            && enum_contains<Tns>(Tns::IS_NS)
            && enum_integer(Tns::IS_NS) == VT_ENUM_ID;

        // Concept for enumeration types to be used for xml tags
        template<class Ttag>
        concept enumerable_tag =
            enumerable_node<Ttag>
            && enum_contains<Ttag>(Ttag::IS_TAG)
            && enum_integer(Ttag::IS_TAG) == VT_ENUM_ID;

        // Concept for enumeration types to be used for attributes
        template<class Tattr>
        concept enumerable_attr =
            enumerable_node<Tattr>
            && enum_contains<Tattr>(Tattr::IS_ATTRIBUTE)
            && enum_integer(Tattr::IS_ATTRIBUTE) == VT_ENUM_ID;

        // Concept for enumeration types to be used for value expressions
        template<class Tvexpr>
        concept enumerable_vexpr =
            enumerable_node<Tvexpr>
            && enum_contains<Tvexpr>(Tvexpr::IS_VALUE_EXPRESSION)
            && enum_integer(Tvexpr::IS_VALUE_EXPRESSION) == VT_ENUM_ID;

        // Concept for enumeration types to be used for attribute options
        template<class Topt>
        concept enumerable_attropt =
            enumerable_node<Topt>
            && enum_contains<Topt>(Topt::IS_ATTRIBUTE_OPTION)
            && enum_integer(Topt::IS_ATTRIBUTE_OPTION) == VT_ENUM_ID;

        // Concept for enumeration types to be used for content types
        template<class Tcont>
        concept enumerable_content =
            enumerable_node<Tcont>
            && enum_contains<Tcont>(Tcont::IS_CONTENT)
            && enum_integer(Tcont::IS_CONTENT) == VT_ENUM_ID;

        template<class Telement>
        concept enumerable_element =
            enumerable_node<Telement>
            && (enumerable_tag<Telement>
            || enumerable_attr<Telement>
            || enumerable_vexpr<Telement>
            || enumerable_attropt<Telement>
            || enumerable_content<Telement>);

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

// Entry Collector -----------------------------------------------------------------------------------------------------2 of 5-|
// ============================================================================================================================|

        namespace detail
        {
            template<class... T>
            struct AccumulateType
            {
                constexpr AccumulateType() noexcept
                {
                    AccumulateType::total = 0;
                }

                template<class I> requires(std::is_integral_v<I>)
				static void add(I i) noexcept
                {
                    AccumulateType::total += i; 
                }

                static void reset() noexcept
                {
                    AccumulateType::total = 0;
                }

                static size_t total;
            };
            using accumulate_t = AccumulateType<void>;

            template<class... N> struct EntryCollector;

            template<class... N>
            struct EntryCollector 
            {
                constexpr EntryCollector()
                {
                    // Nothing to do here
                }
            };

            template<class E, class... N>
            struct EntryCollector<E, N...>
            {
                using entry_t = E;
                using next_t = EntryCollector<N...>;

                constexpr EntryCollector()
                {
                    accumulate_t::add(1);
                }

                constexpr EntryCollector(E&& e, N&&... n) noexcept
                    : entry(e),
                    next(std::move(n)...)
                {
                    accumulate_t::add(1);
                }

                constexpr auto Recurse(auto&& fn) const noexcept
                {
                    accumulate_t::add(1);
                    if constexpr(std::is_invocable_v<decltype(this->next.GetSize()), void>) {
                        this->next.Recurse(fn);
                    }
                }

                constexpr size_t GetSize() const noexcept
                {
                    this->Recurse([]() {
                        accumulate_t::add(1);
                    });
                    const auto total = accumulate_t::total - 1;
                    accumulate_t::reset();
                    return total;
                }

                entry_t     entry;
                next_t      next;
            };
        }

// XML node component templates ----------------------------------------------------------------------------------------3 of 5-|
// ============================================================================================================================|

        template<enumerable_ns Tns, enumerable_attropt Topt>
        struct AttributeOptionsNode
        {
            constexpr AttributeOptionsNode(const Tns&& n_ns, const Topt&& n_attropt,
                                            const std::string_view&& n_value, const size_t&& n_documents) noexcept
                : option({ n_ns, n_attropt }),
                value(n_value),
                documents(n_documents)
            {} 

            Node<Tns, Topt>             option;
            std::string_view            value;
            size_t                      documents;
        };

        template<enumerable_ns Tns, enumerable_vexpr Tvexpr>
        struct ValueExpressionNode
        {
            constexpr ValueExpressionNode(const Tns&& n_ns, const Tvexpr&& n_vexpr, const size_t&& n_documents) noexcept
                : expression({ n_ns, n_vexpr }),
                documents(n_documents)
            {}

            Node<Tns, Tvexpr>           expression;
            size_t                      documents;
        };

        template<enumerable_ns Tns, enumerable_attr Tattr,
                    enumerable_ns Tnsvexpr, enumerable_vexpr Tvexpr,
                    enumerable_ns Tnsopt, enumerable_attropt Topt,
                    size_t SizeVexpr, size_t SizeOpt>
        struct AttributeNode
        {
            Node<Tns, Tattr>                       		attribute;
            ValueExpressionNode<Tnsvexpr, Tvexpr>       expressions[SizeVexpr];
            AttributeOptionsNode<Tnsopt, Topt>       	options[SizeOpt];
            size_t                                 		_default;
            size_t                                 		conditions;
            size_t                                 		documents;
        };

        template<enumerable_ns Tns, enumerable_content Tdata>
        struct ContentNode
        {
            constexpr ContentNode(const Tns&& n_ns, const Tdata&& n_data,
									const size_t&& n_conditions, const size_t&& n_documents) noexcept
                : type({ n_ns, n_data }),
                documents(n_documents),
                conditions(n_conditions)
            {}

            Node<Tns, Tdata>            type;
            size_t                      documents;
            size_t                      conditions;
        };

        namespace detail
        {
            template<enumerable_ns Ens, enumerable_tag Etag>
            using node_t = Node<Ens, Etag>;

            template<enumerable_ns Ens, enumerable_attr Eattr,
                        enumerable_ns Ensvexpr, enumerable_vexpr Evexpr,
                        enumerable_ns Ensopt, enumerable_attropt Eopt,
                        size_t SizeVexpr, size_t SizeOpt>
            using attribute_t = AttributeNode<Ens, Eattr, Ensvexpr, Evexpr, Ensopt, Eopt, SizeVexpr, SizeOpt>;

            template<enumerable_ns Ens, enumerable_vexpr Evexpr>
            using vexpression_t = ValueExpressionNode<Ens, Evexpr>;

            template<enumerable_ns Ens, enumerable_attropt Eattrop>
            using attroption_t = AttributeOptionsNode<Ens, Eattrop>;

            template<enumerable_ns Ens, enumerable_content Edata>
            using content_t = ContentNode<Ens, Edata>;
        }

        // General XML node type for XML dictionary entries
        template<enumerable_ns Tns, enumerable_tag Ttag,
                    enumerable_ns Tnsattr, enumerable_attr Tattr, 
                    enumerable_ns Tnsvexpr, enumerable_vexpr Tvexpr,
                    enumerable_ns Tnsattropt, enumerable_attropt Topt,
                    enumerable_ns Tnsdata, enumerable_content Tdata,
                    size_t SizeAttr, size_t SizeVexpr, size_t SizeOpt, size_t SizeData>
        struct XMLNode
        {
            detail::node_t<Tns, Ttag>                                   element;
            detail::attribute_t<Tnsattr, Tattr,
                        Tnsvexpr, Tvexpr,
                        Tnsattropt, Topt,
                        SizeVexpr, SizeOpt>                             attributes[SizeAttr];
            detail::content_t<Tnsdata, Tdata>                           content[SizeData];
            size_t                                                      documents;
        };

// XML node dictionary template ----------------------------------------------------------------------------------------4 of 5-|
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