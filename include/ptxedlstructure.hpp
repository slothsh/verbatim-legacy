// Stefan "SoulXP" Olivier
// File: ptxedlstructure.hpp
// Description: Headers for Pro Tools edit decision list data structures

#ifndef EDLPTX_HEADER
#define EDLPTX_HEADER

// Standard headers
#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <functional>

// Project headers
#include "helpers.hpp"

// Pro Tools EDL Structures ---------------------------------------------------------------------------------------------------|
// ============================================================================================================================|

typedef
enum TrackState : uint32_t
{
	muted		= 0x00000001,
	solo		= 0x00000002,
	inactive	= 0x00000004,
	hidden		= 0x00000008,
	all_states	= 0x0000000f
} TRACKSTATE;

typedef
struct PTXTrackData
{
public:
	PTXTrackData();
	~PTXTrackData();

	uint32_t channel;
	uint32_t event;
	std::string clip_name;
	std::map<std::string, std::string> timecode; // TODO: Refactor with better name
	std::map<std::string, Helpers::Format::Time> time;
	bool clip_state;

} PTXTRACKDATA;

typedef
struct PTXTrack
{
public:
	PTXTrack();
	~PTXTrack();

	bool HasState(const uint32_t& type);
	void ForEach(size_t index = 0, const std::function<void(PTXTrackData& data, size_t index)>& function = {});

	uint32_t total_clips;
	std::string track_name;
	std::string comments;
	std::string user_delay;
	std::map<std::string, bool> track_state;
	std::vector<PTXTrackData> track_data;

} PTXTRACK;

typedef
struct PTXHeader
{
public:
	PTXHeader();
	~PTXHeader();

	uint32_t audio_tracks_edl;
	uint32_t audio_tracks;
	uint32_t audio_clips;
	uint32_t audio_files;
	std::string session_name;
	std::string session_start;
	Helpers::Format::SampleRate sample_rate;
	Helpers::Format::BitDepth bit_depth;
	Helpers::Format::TimeFormat timecode_format;
	Helpers::Format::TimeFormat counter_format;
	Helpers::Format::FrameRate frame_rate;
} PTXHEADER;

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif