// Stefan "SoulXP" Olivier
// File: edlptx.cpp
// Description: Source code for Pro Tools edit decision list data structures

// Standard headers
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdint>
#include <string>
#include <map>
#include <functional>

// Project headers
#include "../include/ptxedlstructure.hpp"
#include "../include/helpers.hpp"

PTXTrackData::PTXTrackData():
	channel(0),
	event(0),
	clip_name(""),
    timecode({}),
    time({}),
	clip_state("")
{
}

PTXTrackData::~PTXTrackData()
{
}

PTXTrack::PTXTrack():
	total_clips(0),
	track_name(""),
	comments(""),
	user_delay(""),
	track_state({{"Muted", false}, {"Solo", false}, {"Inactive", false}})
{
}

PTXTrack::~PTXTrack()
{
}

bool PTXTrack::HasState(const uint32_t& type)
{
	// TODO: Create enumerations for these string names
	std::vector<std::string> check_states;
	switch (type) {
		case 0x00000001: check_states = {"Muted"};										break;
		case 0x00000002: check_states = {"Solo"};										break;
		case 0x00000003: check_states = {"Muted", "Solo"};							break;
		case 0x00000004: check_states = {"Inactive"};									break;
		case 0x00000005: check_states = {"Muted", "Inactive"};							break;
		case 0x00000006: check_states = {"Solo", "Inactive"};							break;
		case 0x00000007: check_states = {"Muted", "Solo", "Inactive"};				break;
		case 0x00000008: check_states = {"Hidden"};										break;
		case 0x00000009: check_states = {"Muted", "Hidden"};							break;
		case 0x0000000a: check_states = {"Solo", "Hidden"};							break;
		case 0x0000000b: check_states = {"Muted", "Solo", "Hidden"};					break;
		case 0x0000000c: check_states = {"Inactive", "Hidden"};							break;
		case 0x0000000d: check_states = {"Muted", "Inactive", "Hidden"};				break;
		case 0x0000000e: check_states = {"Solo", "Inactive", "Hidden"};				break;
		case 0x0000000f: check_states = {"Muted", "Solo", "Inactive", "Hidden"};		break;
		default:
			throw std::invalid_argument("Bit mask out of range\n\n");
			break;
	}

	for (const auto& state : check_states) {
		if (!this->track_state[state]) return false;
	} 

	return true;
}

void PTXTrack::ForEach(size_t index, const std::function<void(PTXTrackData& data, size_t index)>& function)
{
	if (index < this->track_data.size()) {
		function(this->track_data[index], index);
		this->ForEach(++index, function);
	}
}

PTXHeader::PTXHeader():
	audio_tracks_edl(0),
	audio_tracks(0),
	audio_clips(0),
	audio_files(0),
	session_name(""),
	session_start(""),
	sample_rate(vt::Format::SampleRate::none),
	bit_depth(vt::Format::BitDepth::none),
	timecode_format(vt::Format::TimeFormat::none),
	counter_format(vt::Format::TimeFormat::none),
	frame_rate(vt::Format::FrameRate::none)
{
}

PTXHeader::~PTXHeader()
{
}
