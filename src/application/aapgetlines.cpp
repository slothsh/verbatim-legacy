// -----------------------------------------------------------------+
// Version: 0.1.1
// Data: 25/11/2021
// TODO: Copyright

// Stefan "SoulXP" Olivier
// File: edltool.cpp
// Description: Small tool to parse various edit decision list files
// -----------------------------------------------------------------+

// Standard headers
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>
#include <cassert>

// Project headers
#include "../../include/edlfile.hpp"

using namespace vt;
using namespace EDL;

enum class output_formats
{
    db,
    table_all,
    none
};

inline std::vector<std::string> split_characters(const char* c)
{
    std::string name {};
    std::stringstream name_stream { c };
    std::vector<std::string> name_list;
    while (std::getline(name_stream, name, ',')) {
        name_list.push_back(name);
    }

    return name_list;
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "Please pass a valid input argument\n";
        std::exit(1);
    }

    // Parse input arguments and determine what procedure to follow
    output_formats format = output_formats::none;
    std::string_view arg { argv[3] };

    if (arg == "--output-table") {
        format = output_formats::table_all;
    } else if (arg == "--output-db") {
        format = output_formats::db;
    }

    if (format == output_formats::none) {
        std::cerr << "aapgetlines: please specify an output format\n";
        std::exit(1);
    }

	try {
        // Construct EDL object from input and parse
		EDLFilePTX edlfile { argv[1] };

        // Get command line arguments as comma-seperated files
        const auto name_list = split_characters(argv[2]);

        // Filter EDL according to list
        if (name_list[0] != "*") {
            edlfile.FilterTracks([&name_list](PTXTrack track, size_t) {
                for (const auto& n : name_list) {
                    // TODO: Add escapes for special regex characters
                    if (regex::FirstMatch(track.track_name, std::regex(n)) == n) {
                        return true;
                    }
                }
                return false;
            });
        }

        // Call output procedure according to output format
        using f = output_formats;
        switch(format) {
            case f::table_all: {
                // Print results of filtered EDL
                edlfile.PrintOutput(vt::format::File::table_all);
                break;
            }

            case f::db: {
                // Print results of filtered EDL
                edlfile.PrintOutput(vt::format::File::db_dump);
                break;
            }

            default: {
                std::cerr << "invalid arguments\n";
                std::exit(1);
                break;
            }
        }
	}
    
    catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		std::exit(1);
	}

    return 0;
}
