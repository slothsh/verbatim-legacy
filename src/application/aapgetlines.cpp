// -----------------------------------------------------------------+
// Version: 0.1.0
// Data: 22/11/2021
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

// Project headers
#include "../../include/edlfile.hpp"

using namespace vt;
using namespace EDL;

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "Please pass a valid input argument\n";
        std::exit(1);
    }

	try {
		std::clog << "Parsing file: " << argv[1] << '\n';

        // Construct EDL object from input and parse
		EDLFilePTX edlfile((std::string(argv[1])));
		
        // Get command line arguments as comma-seperated files
        std::vector<std::string> name_list;
		std::string name;
        std::stringstream name_stream {argv[2]};
        while (std::getline(name_stream, name, ',')) {
            name_list.push_back(name);
        }
		bool found = false;

        // Filter EDL according to list
		edlfile.FilterTracks([&name_list, &found](PTXTrack track, size_t) {
            for (const auto& n : name_list) {
                if (regex::FirstMatch(track.track_name, std::regex(n)) == n) {
                    found = true;
                    return true;
                }
            }
			return false;
		});

        // Exit if no characters were found
		if (!found) {
			std::clog << "Could not find character\n";
			std::exit(1);
		}

        // Print results of filtered EDL
		edlfile.PrintOutput(vt::format::File::table_all);

	} catch (const std::exception& e) {
		std::cerr << e.what();
		std::exit(1);
	}

    return 0;
}
