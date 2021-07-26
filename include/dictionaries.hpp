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
        template<enumerable_node Tnstag, enumerable_tag Ttag,
                    enumerable_ns Tnsattr, enumerable_attr Tattr,
                    enumerable_ns Tnsvexpr, enumerable_vexpr Tvexpr,
                    enumerable_ns Tnsattropt, enumerable_attropt Tattropt,
                    enumerable_ns Tnsdata, enumerable_content Tdata>
        struct XMLNodeTypes
        {
            using nstag_t                     	= Tnstag;
            using tag_t                       	= Ttag;
            using nsattribute_t               	= Tnsattr;
            using attribute_t                 	= Tattr;
            using nsvalueexpr_t               	= Tnsvexpr;
            using valueexpr_t                 	= Tvexpr;
            using nsattroption_t              	= Tnsattropt;
            using attroption_t                	= Tattropt;
            using nscontent_t                 	= Tnsdata;
            using content_t                   	= Tdata;

            nstag_t                     		nstag_v 				= nstag_t::none;
            tag_t                       		tag_v 					= tag_t::none;
            nsattribute_t               		nsattribute_v 			= nsattribute_t::none;
            attribute_t                 		attribute_v 			= attribute_t::none;
            nsvalueexpr_t               		nsvalueexpr_v 			= nsvalueexpr_t::none;
            valueexpr_t                 		valueexpr_v 			= valueexpr_t::none;
            nsattroption_t              		nsattroption_v 			= nsattroption_t::none;
            attroption_t                		attroption_v 			= attroption_t::none;
            nscontent_t                 		nscontent_v 			= nscontent_t::none;
            content_t                   		content_v 				= content_t::none;
        };

        // Dictionary type definitions
        using ns_component_t = XMLNodeTypes<NS, Tag, NS, Attribute, NS, ValueExpression, NS, AttributeOption, NS, Content>;

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