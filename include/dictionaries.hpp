// Stefan "SoulXP" Olivier
// File: dictionaries.hpp
// Description: Definitions for various tables and dictionaries

#ifndef VTDICTIONARIES_HEADER
#define VTDICTIONARIES_HEADER

// Standard headers
#include <iostream>
#include <type_traits>
#include <utility>
#include <concepts>

// Library headers
#include <magic_enum.hpp>

// Project headers
#include "node.hpp"

// Dictionary definitions ----------------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

namespace vt
{
    namespace dictionary
    {
        template<enumerable_ns Tnstag, enumerable_tag Ttag,
                    enumerable_ns Tnsattr, enumerable_attr Tattr,
                    enumerable_ns Tnsvexpr, enumerable_vexpr Tvexpr,
                    enumerable_ns Tnsattropt, enumerable_attropt Tattropt,
                    enumerable_ns Tnsdata, enumerable_content Tdata>
        struct XMLNodeTypes
        {
            using nstag_t                     = Tnstag;
            using tag_t                       = Ttag;

            using nsattribute_t               = Tnsattr;
            using attribute_t                 = Tattr;

            using nsvalueexpr_t               = Tnsvexpr;
            using valueexpr_t                 = Tvexpr;
            
            using nsattroption_t              = Tnsattropt;
            using attroption_t                = Tattropt;

            using nscontent_t                 = Tnsdata;
            using content_t                   = Tdata;
        };

        // Dictionary type definitions
        // using ns_component_t = XMLNodeTypes<NS, Tag, NS, Attribute, NS, ValueExpression, NS, AttributeOption, NS, Content>;

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