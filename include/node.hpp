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
            alpha, color, digit, duration, familyName, genericFamilyName, hexDigit, integer, length, namedColor, quotedString, string, timeExpression,
            automatic, id, string_option,
            none = VT_ENUM_NONE
        };

        enum class AttributeOption : size_t
        {
            IS_ATTRIBUTE_OPTION = VT_ENUM_ID,
            string,
            none = VT_ENUM_NONE
        };

        enum class GenericData : size_t
        {
            IS_DATA = VT_ENUM_ID,
            CDATA, PCDATA, IMPLIED,
            none = VT_ENUM_NONE
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
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// Generic types for XML nodes -----------------------------------------------------------------------------------------2 of 5-|
// ============================================================================================================================|

namespace vt
{
    namespace dictionary
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

        // Concept for enumeration types to be used for attribute options
        template<class Topt>
        concept enumerable_attropt =
            enumerable_node<Topt>
            && mge::enum_contains<Topt>(Topt::IS_ATTRIBUTE_OPTION)
            && mge::enum_integer(Topt::IS_ATTRIBUTE_OPTION) == VT_ENUM_ID;

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
            || enumerable_attropt<Telement>
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
        }

// XML node component templates ----------------------------------------------------------------------------------------3 of 5-|
// ============================================================================================================================|

        template<class... N>
        struct XMLNodeTree
        {
            constexpr XMLNodeTree()
            {
                // Nothing to do here
            }

            constexpr XMLNodeTree(auto& init_list, size_t&& offset = 0)
            {
                // Nothing to do here
            }
        };

        template<class Tnode, class... Tnext>
        struct XMLNodeTree<Tnode, Tnext...>
        {
            using value_t = Tnode;
            using next_t = XMLNodeTree<Tnext...>;

            constexpr XMLNodeTree() = delete;

            constexpr XMLNodeTree(const Tnode& v, const Tnext&... n)
                : value(v),
                next(std::move(n)...)
            {}

            constexpr XMLNodeTree(const std::initializer_list<value_t>& init_list, size_t&& offset = 0)
                : value(*(init_list.begin() + offset)),
                next(std::move(init_list), offset + 1)
            {}

            constexpr XMLNodeTree(const std::initializer_list<std::initializer_list<value_t>>& init_list, size_t&& offset = 0)
                : value(*(*(init_list.begin() + offset)).begin()),
                next(std::move(init_list), offset + 1)
            {}

            constexpr auto Recurse(auto&& fn) const
            {
                detail::accumulate_t::add(1);
                if constexpr(std::is_invocable_v<decltype(this->next.GetSize()), void>) {
                    this->next.Recurse(fn);
                }
            }

            constexpr size_t GetSize() const noexcept
            {
                this->Recurse([]() {
                    detail::accumulate_t::add(1);
                });
                const auto total = detail::accumulate_t::total - 1;
                detail::accumulate_t::reset();
                return total;
            }

            value_t             value;
            next_t              next;
        };

        template<enumerable_ns Tns, enumerable_attropt Topt>
        struct AttributeOptionsNode
        {
            constexpr AttributeOptionsNode(Tns&& n_ns, Topt&& n_attropt,
                                            std::string_view&& n_value, size_t&& n_documents) noexcept
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
            using init_t = ValueExpressionNode<Tns, Tvexpr>;

            constexpr ValueExpressionNode(Tns&& n_ns, Tvexpr&& n_vexpr, std::string_view&& n_value, size_t&& n_quantifier, size_t&& n_documents) noexcept
                : expression({ n_ns, n_vexpr }),
                value(n_value),
                quantifier(n_quantifier),
                documents(n_documents)
            {}

            constexpr ValueExpressionNode(const std::initializer_list<init_t>& init_list) noexcept
                : expression({ init_list.begin(), init_list.begin() + 1 }),
                value(init_list.begin() + 2),
                quantifier(init_list.begin() + 3),
                documents(init_list.begin() + 4)
            {} 

            Node<Tns, Tvexpr>           expression;
            std::string_view            value;
            size_t                      quantifier;
            size_t                      documents;
        };

        template<enumerable_ns Tns, enumerable_attr Tattr,
                    class Nvexpr, class Nopt>
        struct AttributeNode
        {
            constexpr AttributeNode(size_t&& n_condition, size_t&& n_quantifier, size_t&& n_documents,
                                    Tns&& n_ns,  Tattr&& n_attr, const Nvexpr& n_vexpr, const Nopt& n_opt)
                : attribute({ n_ns, n_attr }),
                expressions(n_vexpr),
                options(n_opt),
                condition(n_condition),
                quantifier(n_quantifier),
                documents(n_documents)
            {}

            Node<Tns, Tattr>            attribute;
            Nvexpr                      expressions;
            Nopt       	                options;
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

            element_t                           element;
            attribute_t                         attributes;
            content_t                           content;
            size_t                              documents;
        };

// XML node dictionary template ----------------------------------------------------------------------------------------4 of 5-|
// ============================================================================================================================|

        namespace detail
        {
            template<size_t E, class... Rest>
            struct GetHelper;

            template<NS Tns = NS::none, Tag Ttag = Tag::none>
            constexpr inline auto CreateTTMLNode() { return; }

            template<class Texpr, class... Trest> // TODO: Concept for XMLNodeTree
            constexpr inline auto CreateValueExpressionNode(std::initializer_list<std::initializer_list<Texpr>>&& expressions)
            {
                return XMLNodeTree<Texpr, Trest...>{expressions};
            }
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