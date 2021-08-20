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
enum TrackState : size_t
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

	size_t channel;
	size_t event;
	std::string clip_name;
	std::map<std::string, std::string> timecode; // TODO: Refactor with better name
	std::map<std::string, vt::format::Time> time;
	bool clip_state;

} PTXTRACKDATA;

typedef
struct PTXTrack
{
public:
	PTXTrack();
	~PTXTrack();

	bool HasState(const size_t& type);
	void ForEach(size_t index = 0, const std::function<void(PTXTrackData& data, size_t index)>& function = {});

	size_t total_clips;
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

	size_t audio_tracks_edl;
	size_t audio_tracks;
	size_t audio_clips;
	size_t audio_files;
	std::string session_name;
	std::string session_start;
	vt::format::SampleRate sample_rate;
	vt::format::BitDepth bit_depth;
	vt::format::TimeFormat timecode_format;
	vt::format::TimeFormat counter_format;
	vt::format::FrameRate frame_rate;
} PTXHEADER;

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif