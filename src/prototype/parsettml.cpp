// Stefan "SoulXP" Olivier
// File: edltool.cpp
// Description: Small tool to parse various edit decision list files

// Global flags
#define EDL_DEBUG_MEMORY

// Standard headers
#include <iostream>
#include <stdexcept>

// Project headers
#include "../../include/xmlfile.hpp"
#include "../../include/edlfile.hpp"
#include "../../include/ttml1dictionary.hpp"

#ifdef EDL_DEBUG_MEMORY
static size_t allocations = 0;
static size_t deallocations = 0;

void diagnostics_exit() {
	if (allocations - deallocations > 0) {
		std::clog << "Warning - a total of " << (allocations - deallocations) << " bytes have not been deallocated.\n";
	}
	std::clog << "Total allocations: " << allocations << " bytes\n";
	std::clog << "Total deallocations: " << deallocations << " bytes\n";
}

void* operator new(size_t size) {
	allocations += size;
	return malloc(size);
}

void operator delete(void* ptr, size_t size) noexcept {
	deallocations += size;
	std::free(ptr);
}
#endif

using namespace vt;
using namespace EDL;

int main(int argc, char** argv)
{
	#ifdef EDL_DEBUG_MEMORY
	std::atexit(diagnostics_exit);
	#endif

    if (argc < 2) {
        std::cerr << "Please pass a valid input argument\n";
        std::exit(1);
    }

	using namespace vt::xml;
	try {
		EDLFilePTX edlfile((std::string(argv[1])));
		edlfile.PrintOutput(vt::format::File::table_all);
		
		// std::string name(argv[2]);

		// edlfile.FilterTracks([&name](PTXTrack track, size_t tIndex) {
		// 	return regex::FirstMatch(track.track_name, std::regex(name)) == name;
		// });

		// edlfile.PrintOutput(format::File::table_all);
		// RemoveBoundaryEvents(edlfile, "(cross fade)");
		// MergeBoundaryEvents(edlfile, "(cross fade)");
		// edlfile.WriteOutput((std::string(argv[2])), vt::format::File::edl_ptx_minimal);
		TTML1p0_Netflix ttml;
		// ttml << edlfile;
		// ttml.PrintNodes();
		// ttml.WriteFile((std::string(argv[2])));
		// MergeBoundaryEvents(edlfile, "(cross fade)");
		// edlfile.EnumerateEvents();
		// edlfile.PrintOutputformat::File::edl_ptx_minimal);
	} catch (const std::exception& e) {
		std::cerr << e.what();
		std::exit(1);
	}

    return 0;
}
