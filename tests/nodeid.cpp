// Stefan "SoulXP" Olivier
// File: validatettml.cpp
// Description: Test code for building a TTML tree for run time structure validation

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "../include/config.hpp"
#endif

// Standard headers
#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <string_view>

// Third-party headers
#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

// Project headers
#include "../include/prototype/validatettml.hpp"

// ValidatingNode Value Expressions
TEST_CASE("Generic NodeID & Node for ValidatingNode initialization & move semantics", "[NodeID & Node : ValidatingNode] [Initialization & Move Semantics]")
{
    using 
}