// Stefan "SoulXP" Olivier
// File: filesink.hpp
// Description: General file IO objects

#ifndef FILESINK_HEADER
#define FILESINK_HEADER

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
	using ptr_t = std::unique_ptr<char>;
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

    ptr_t filesink_raw;
	size_t filesink_length;
    path_t filesink_path;
	bool filesink_isvalid;
};

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif