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

FileSink::FileSink() noexcept:
    filesink_raw(nullptr),
	filesink_length(0),
    filesink_path(""),
	filesink_isvalid(false)
{
}

FileSink::FileSink(const std::string& path)
{
	if (path == "") throw std::invalid_argument("Invalid file path\n");
	this->LoadFile(path);
}

FileSink::~FileSink()
{
	if (this->filesink_raw) {
		#ifndef NDEBUG
		std::clog << "Destroying FileSink!" << "\n\n";
		#endif
		std::free(this->filesink_raw);
	}
}

void FileSink::LoadFile(const std::string& path)
{
	// Clean up first
	if (this->filesink_raw) this->Purge();

	// Load new file
	std::ifstream file(path, std::ios::binary | std::ios::in | std::ios::ate);
	if (!file.is_open()) throw std::invalid_argument("Could not open specified path\n");
	if (file.tellg() <= 0) throw std::invalid_argument("File is empty\n");
	this->filesink_path = path;
	this->filesink_length = file.tellg();
    this->filesink_raw = (uint8_t*)std::malloc(
        file.tellg() * sizeof(uint8_t) + 1 // Null byte
	);
	file.seekg(std::ios::beg);
	file.read((char*)this->filesink_raw, this->filesink_length);
}

bool FileSink::isValidFile() noexcept
{
	return this->filesink_isvalid;
}

void FileSink::Purge()
{
	this->filesink_raw = nullptr;
	std::free(this->filesink_raw);
	this->filesink_path = "";
	this->filesink_length = 0;
	this->filesink_isvalid = false;

	#ifndef NDEBUG
	std::clog << "File successfully purged\n\n";
	#endif
}

void FileSink::ValidateFile() noexcept
{
	try {
		this->Parse();
		this->filesink_isvalid = true;

		#ifndef NDEBUG
		std::clog
			<< "File successfully loaded"
			<< "\nFile path: " << this->filesink_path
			<< "\nFile length: " << this->filesink_length
			<< "\n\n";
		#else
		std::clog << "File successfully loaded\n\n";
		#endif
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
		this->Purge();
	}
}