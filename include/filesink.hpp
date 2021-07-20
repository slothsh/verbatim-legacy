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

typedef
struct FileSink
{
public:
    FileSink() noexcept;
	FileSink(const std::string& path);
    ~FileSink();

    void LoadFile(const std::string& path);
	bool isValidFile() noexcept;

protected:
	void Purge();
	void ValidateFile() noexcept;
	virtual void Parse() = 0;

    uint8_t* filesink_raw;
	uint64_t filesink_length;
    std::string filesink_path;
	bool filesink_isvalid;
} FILESINK;

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif