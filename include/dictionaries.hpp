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
#include "./dictionaries/node_tt_tt.hpp"
#include "./dictionaries/node_tt_head.hpp"

// Master TTML definition function ----------------------------------------------------------------------------------- 1 of 1 -|
// ============================================================================================================================|

namespace vt::dictionary
{
    static constexpr auto CreateTTMLDictionary()
    {
        constexpr auto node_tt_tt = detail::CreateTTMLNode<NS::tt, Tag::tt>();
        constexpr auto node_tt_head = detail::CreateTTMLNode<NS::tt, Tag::head>();

        return node_tt_tt;
    }
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// Dictionary helpers ------------------------------------------------------------------------------------------------ 1 of 1 -|
// ============================================================================================================================|

namespace vt::dictionary
{
    template<enumerable_ns Tnselement, enumerable_element Telement>
    struct EnumerationCollector
    {
        
        using nselement_t                   = Tnselement;
        using element_t                     = Telement;
        using entry_t                       = std::pair<element_t, std::string_view>;

        constexpr EnumerationCollector() noexcept
        {
            namespace mge = magic_enum;

            this->size = mge::enum_count<element_t>() - 2;
            constexpr auto all_entries = mge::enum_entries<element_t>();

            size_t i = 0, j = 0;
            while (i++ < this->size)
            {
                if (all_entries[i].first != element_t::none
                    || all_entries[i].first != mge::enum_value<element_t>(0) // TODO: Make control indexes for enums a static constant
                    && j < this->size)
                {
                    this->entries[j++] = all_entries[i];
                }
            }
        }

        size_t                              size                                                        = magic_enum::enum_count<element_t>() - 2;
        entry_t                             entries[magic_enum::enum_count<element_t>() - 2]            = {};
    };
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif // VTDICTIONARIES_HEADER