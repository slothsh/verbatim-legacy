#pragma once

// Stefan "SoulXP" Olivier
// File: radixtrie.hpp
// Description: Headers for radix trie structure and associaited helpers

// Standard headers
#include <cstdint>
#include <vector>
#include <string_view>

namespace vt::radixtrie
{
    struct RadixTrie
    {
        using container_t = std::vector<std::string_view>;
        static container_t prefixes;
        bool is_word;
        std::size_t index;
        RadixTrie* next;
    };

    // Helper functions
    void PopulateRadixTrie(const std::string_view& path);
}

namespace vt
{
    // Global aliases for header
    using RadixTrie = vt::radixtrie::RadixTrie;
}