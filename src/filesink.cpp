// Stefan "SoulXP" Olivier
// File: edlfile.cpp
// Description: Source code for edit decision list file parsing

// Standard headers
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <memory>
#include <cstdint>
#include <string>

// Project headers
#include "../include/filesink.hpp"

FileSink::FileSink() noexcept
    : filesink_path(""),
	filesink_file({}),
	filesink_length(0),
	filesink_isvalid(false)
{
}

FileSink::FileSink(const path_t& path)
    : filesink_path(path),
	filesink_file(path.data(), std::ios::binary | std::ios::in | std::ios::ate),
	filesink_length(this->filesink_file.tellg()),
	filesink_isvalid(false)
{
	if (!this->filesink_file) throw std::invalid_argument("Could not open file with specified path\n");
	this->LoadFile(path);
}

FileSink::~FileSink()
{
}

void FileSink::LoadFile(const std::string_view& path)
{
	if (this->filesink_file.tellg() <= 0) throw std::invalid_argument("File is empty\n");
	this->filesink_path = path;
	this->filesink_file.seekg(std::ios::beg);
}

bool FileSink::isValidFile() noexcept
{
	return this->filesink_isvalid;
}

void FileSink::Purge()
{
	this->filesink_path = "";
	this->filesink_length = 0;
	this->filesink_isvalid = false;

	if constexpr (VTDEBUG) {
		std::clog << "File successfully purged\n\n";
	}
}

void FileSink::ValidateFile() noexcept
{
	try {
		this->Parse();
		this->filesink_isvalid = true;

		if constexpr (VTDEBUG) {
			std::clog
				<< "File successfully loaded"
				<< "\nFile path: " << this->filesink_path
				<< "\nFile length: " << this->filesink_length
				<< "\n\n";
		} else {
			std::clog << "File successfully loaded\n\n";
		}
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		this->Purge();
	}
}