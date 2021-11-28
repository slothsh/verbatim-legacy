#pragma once

// Stefan "SoulXP" Olivier
// File: radixtrie.cpp
// Description: Implementation for radix trie structure object

// Standared headers
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdint>
#include <vector>
#include <string>
#include <string_view>
#include <sstream>
#include <utility>

// Project headers
#include "../include/radixtrie.hpp"

namespace vt::radixtrie
{
    // Namespace aliases
    using container_t = typename RadixTrie::container_t;

    // Default initialize static storage for structure
    container_t RadixTrie::container_t = {};

    // Helper to populate a radix trie structure
    void PopulateRadixTrie(const std::string_view& path)
    {
        // Load file into memory & error checking
        std::ifstream word_list_file(path.data(), std::ios::binary | std::ios::in | std::ios::ate);
        std::ptrdiff_t file_length = word_list_file.tellg();
        word_list_file.seekg(std::ios::beg);

        if (word_list_file) {
            std::cerr << "ERROR: could not load specified path '" << path << "' in PopulateRadixTrie()\n";
            return;
        }

        // Get words from file
        std::string word_list;
        while (word_list_file.getline(word_list.data(), file_length, '\n')) {
            // TODO
        }
    }
}