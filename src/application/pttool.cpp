/*
* MIT License
*
* Copyright (c) 2021 Stefan Olivier
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

// Author: Stefan Olivier : https://github.com/SoulXP
// File: pttool.cpp
// Description: Application code for parsing Avid Pro Tools .pt[x] files

// Standard headers
#include <cstdlib>

// Third-party headers
#include <fmt/core.h>

// Project headers
#include "../../include/ptparser.hpp"

int main(int argc, char** argv)
{
    if (argc < 2) {
        fmt::print("Please specify an input path\n");
        std::exit(1);
    }

    // Load ptf file
    // const auto& [ signal, pt_file ] = vt::ptparser::parse_ptf(argv[1], 48000);

    const auto& pt_file = vt::ptparser::parse_ptf(argv[1], 48000);
    // if (signal) {
    //     fmt::print(stderr, "ERROR: pro tools file @ path {} file could not be loaded\n", argv[1]);
    // }

    for (const auto& r : pt_file.miditracks()) {
        fmt::print("index: {0}    name: {1}\n",
            r.index,
            r.name
        );
    }

    return 0;
}