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

// Dictionary definitions ----------------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

namespace vt
{
    namespace dictionary
    {
        namespace detail
        {
            // Nothing to do here, yet...
        }

        template<enumerable_ns Tnselement, enumerable_element Telement/* ,
                    enumerable_ns Tnsattr, enumerable_attr Tattr,
                    enumerable_ns Tnsvexpr, enumerable_vexpr Tvexpr,
                    enumerable_ns Tnsattropt, enumerable_attropt Tattropt,
                    enumerable_ns Tnsdata, enumerable_content Tdata */>
        struct XMLNodeTypes
        {
            
            using nselement_t                   = Tnselement;
            using element_t                     = Telement;
            using entry_t                       = std::pair<element_t, std::string_view>;
            using firstentry_t                  = std::disjunction<>;
/*             using nsattribute_t               	= Tnsattr;
            using attribute_t                 	= Tattr;
            using nsvalueexpr_t               	= Tnsvexpr;
            using valueexpr_t                 	= Tvexpr;
            using nsattroption_t              	= Tnsattropt;
            using attroption_t                	= Tattropt;
            using nscontent_t                 	= Tnsdata;
            using content_t                   	= Tdata; */

            constexpr XMLNodeTypes() noexcept
            {
                // Nothing to do here
            }

            constexpr XMLNodeTypes(nselement_t ns, element_t element) noexcept
            {
                namespace mge = magic_enum;
                // this->size = mge::enum_count<element_t>() - 2;
                constexpr auto all_entries = mge::enum_entries<element_t>();

                size_t i = 0, j = 0;
                while (i++ < this->size + 2) // TODO: Make the + 2 into a static constant
                {
                    if (all_entries[i].first != element_t::none
                        || all_entries[i].first != mge::enum_value<element_t>(0) // TODO: Make control indexes for enums a static constant
                        && j < this->size)
                    {
                        this->entries[j++] = all_entries[i];
                    }
                }
            }

            nselement_t                     	nselement_v 			                                    = nselement_t::none;
            element_t                       	element_v 				                                    = element_t::none;
/*             nsattribute_t               		nsattribute_v 			                                    = nsattribute_t::none;
            attribute_t                 		attribute_v 			                                    = attribute_t::none;
            nsvalueexpr_t               		nsvalueexpr_v 			                                    = nsvalueexpr_t::none;
            valueexpr_t                 		valueexpr_v 			                                    = valueexpr_t::none;
            nsattroption_t              		nsattroption_v 			                                    = nsattroption_t::none;
            attroption_t                		attroption_v 			                                    = attroption_t::none;
            nscontent_t                 		nscontent_v 			                                    = nscontent_t::none;
            content_t                   		content_v 				                                    = content_t::none; */

            size_t                        size                                                              = magic_enum::enum_count<element_t>() - 2;
            entry_t                             entries[magic_enum::enum_count<element_t>() - 2]            = {};
        };

        // Dictionary type definitions
        using component_t = XMLNodeTypes<NS, Tag>;
        using attribute_t = XMLNodeTypes<NS, Attribute>;
        using vexpression_t = XMLNodeTypes<NS, ValueExpression>;
        using attroption_t = XMLNodeTypes<NS, AttributeOption>;
        using content_t = XMLNodeTypes<NS, Content>;

        // Function to create XMLNodeType objects
        template<enumerable_node Tenum>
        constexpr inline auto CreateAttributeNode(Tenum e) noexcept
        {
            namespace mge = magic_enum;
            // constexpr auto mge::enum_entries<Tenum>(e);

        }

        // Helper function to create XML nodes for static dictionaries
        template<class Fn> requires(std::is_invocable_v<Fn>)
        constexpr void CreateXMLNode(const Fn&& fn)
        {
            fn();
        }
    }
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif // VTDICTIONARIES_HEADER