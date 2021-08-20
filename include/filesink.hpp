// Stefan "SoulXP" Olivier
// File: filesink.hpp
// Description: General file IO objects

#ifndef FILESINK_HEADER
#define FILESINK_HEADER

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "config.hpp"
#endif

// Standard headers
#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>

// FileSink object declaration ------------------------------------------------------------------------------------------------|
// ============================================================================================================================|

struct FileSink
{
public:
	using file_t = std::ifstream;
	using path_t = std::string_view;

    FileSink() noexcept;
	FileSink(const path_t& path);
    ~FileSink();

    void LoadFile(const path_t& path);
	bool isValidFile() noexcept;

protected:
	void Purge();
	void ValidateFile() noexcept;
	virtual void Parse() = 0;

    path_t filesink_path;
	file_t filesink_file;
	size_t filesink_length;
	bool filesink_isvalid;
};

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif