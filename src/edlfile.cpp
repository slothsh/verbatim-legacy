// Stefan "SoulXP" Olivier
// File: edlfile.cpp
// Description: Source code for edit decision list file parsing

// Standard headers
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <memory>
#include <cstdint>
#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <regex>

// Project headers
#include "../include/filesink.hpp"
#include "../include/helpers.hpp"
#include "../include/ptxedlstructure.hpp"
#include "../include/edlfile.hpp"

// Inline member functions ----------------------------------------------------------------------------------------------------|
// ============================================================================================================================|

inline void EDLFilePTX::ConstructorAssignment(const EDLFilePTX& edl_file) noexcept
{
	this->filesink_length = edl_file.filesink_length;
	this->filesink_path = edl_file.filesink_path;
	this->filesink_isvalid = edl_file.filesink_isvalid;

	this->session_info.audio_tracks = edl_file.session_info.audio_tracks;
	this->session_info.audio_clips = edl_file.session_info.audio_clips;
	this->session_info.audio_files = edl_file.session_info.audio_files;
	this->session_info.session_name = edl_file.session_info.session_name;
	this->session_info.session_start = edl_file.session_info.session_start;
	this->session_info.sample_rate = edl_file.session_info.sample_rate;
	this->session_info.bit_depth = edl_file.session_info.bit_depth;
	this->session_info.timecode_format = edl_file.session_info.timecode_format;
	this->session_info.counter_format = edl_file.session_info.counter_format;
	this->session_info.frame_rate = edl_file.session_info.frame_rate;

	this->marked_tracks = edl_file.marked_tracks;
	this->marked_data = edl_file.marked_data;
	this->ptx_tracks = edl_file.ptx_tracks;
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

EDLFilePTX::EDLFilePTX(const EDLFilePTX& edl_file) noexcept
{
	this->filesink_raw = (uint8_t*)std::malloc(edl_file.filesink_length * sizeof(uint8_t));
	this->filesink_raw = (uint8_t*)std::memcpy(this->filesink_raw, edl_file.filesink_raw, edl_file.filesink_length * sizeof(uint8_t));
	this->ConstructorAssignment(edl_file);
}

EDLFilePTX::EDLFilePTX(EDLFilePTX&& edl_file) noexcept
{
	*this = std::move(edl_file);
}

EDLFilePTX::EDLFilePTX(const std::string& path)
	: FileSink(path)
{
	if (this->filesink_raw) this->ValidateFile();
}

EDLFilePTX::~EDLFilePTX()
{
}

void EDLFilePTX::Parse()
{
	using namespace vt;
	// Functions for parsing data
	const auto ParseHeaderData = [](
		PTXHEADER& header,
		const std::vector<std::string>& header_chunks)
	{

	};

	// TODO: Make enumerations to hold common ptx edl titles & regex patterns
	const auto GetEDLHeaderData = [](
		const std::string& chunk)
	-> PTXHEADER
	{
		PTXHEADER new_header;
		uint32_t bit_mask = String::WhiteSpace::tab | String::WhiteSpace::carriage | String::WhiteSpace::linefeed;
		new_header.session_name = String::Trim(Regex::FirstMatch(chunk, std::regex("(SESSION NAME:)(.*?)\n")), bit_mask).substr(14);
		new_header.session_start = String::Trim(Regex::FirstMatch(chunk, std::regex("(SESSION START TIMECODE:)(.*?)\n")), bit_mask).substr(24);
		new_header.sample_rate = Format::GetSampleRate(String::Trim(Regex::FirstMatch(chunk, std::regex("(SAMPLE RATE:)(.*?)\n")), bit_mask).substr(12));
		new_header.bit_depth = Format::GetBitDepth(String::Trim(Regex::FirstMatch(chunk, std::regex("(BIT DEPTH:)(.*?)\n")), bit_mask).substr(11));
		new_header.timecode_format = Format::ParseTimeFormat(String::Trim(Regex::FirstMatch(chunk, std::regex("(SESSION START TIMECODE:)(.*?)\n")), bit_mask).substr(24));
		new_header.frame_rate = Format::GetFrameRate(String::Trim(Regex::FirstMatch(chunk, std::regex("(TIMECODE FORMAT:)(.*?)\n")), bit_mask).substr(16));
		new_header.audio_tracks = std::stoi(String::Trim(Regex::FirstMatch(chunk, std::regex("(# OF AUDIO TRACKS:)(.*?)\n")), bit_mask).substr(18));
		new_header.audio_clips = std::stoi(String::Trim(Regex::FirstMatch(chunk, std::regex("(# OF AUDIO CLIPS:)(.*?)\n")), bit_mask).substr(17));
		new_header.audio_files = std::stoi(String::Trim(Regex::FirstMatch(chunk, std::regex("(# OF AUDIO FILES:)(.*?)\n")), bit_mask).substr(17));

		return new_header;
	};
	

	const auto GetTrackHeaderData = [](
		const std::string& chunk)
	-> PTXTRACK
	{
		PTXTRACK new_track;
		uint32_t bit_mask = String::WhiteSpace::tab | String::WhiteSpace::carriage | String::WhiteSpace::linefeed;
		new_track.track_name = String::Trim(Regex::FirstMatch(chunk, std::regex("(TRACK NAME:)(.*?)\n")), bit_mask).substr(12);
		new_track.comments = String::Trim(Regex::FirstMatch(chunk, std::regex("(COMMENTS:)(.*?)\n")), bit_mask).substr(9);
		new_track.user_delay = String::Trim(Regex::FirstMatch(chunk, std::regex("(USER DELAY:)(.*?)\n")), bit_mask).substr(12);

		std::vector<std::string> track_states;
		std::string track_state_str = String::Trim(Regex::FirstMatch(chunk, std::regex("(STATE:)(.*?)\n")), bit_mask).substr(7);
		Regex::AllMatches(track_states, track_state_str, std::regex("Muted|Inactive|Solo|Hidden"));
		for (const auto& state : track_states) {
			// TODO: Make enumerations for these
			if (state == "Muted") new_track.track_state["Muted"] = true;
			if (state == "Inactive") new_track.track_state["Inactive"] = true;
			if (state == "Solo") new_track.track_state["Solo"] = true;
			if (state == "Hidden") new_track.track_state["Hidden"] = true;
		}

		return new_track;
	};

	const auto GetTrackBodyData = [](
		PTXHEADER& header,
		PTXTRACK& track,
		const std::string& chunk)
	{
		std::vector<std::string> data_entries;
		Regex::AllMatches(
			data_entries,
			chunk,
			std::regex("(?!\\n)\\d.*?\\n")
		);

		// TODO: Fix this issue with regex to avoid popping first two elements
		data_entries.erase(data_entries.begin(), data_entries.begin() + 2);

		std::vector<std::string> entry_data;
		uint32_t total_clips = 0;
		for (auto& rows : data_entries) {
			PTXTRACKDATA track_data;
			Regex::AllMatches(entry_data, rows, std::regex("((.+?)\\t|(.+?)\\n)"));

			uint64_t i = 0;
			uint32_t bit_mask = String::WhiteSpace::tab | String::WhiteSpace::carriage | String::WhiteSpace::linefeed;
			for (auto& column : entry_data) {
				if (i >= 7) i = 0;
				switch (i++) {
					case 0: track_data.channel = std::stoi(String::Trim(String::Trim(column, bit_mask), String::WhiteSpace::space)); break;
					case 1: track_data.event = std::stoi(String::Trim(String::Trim(column, bit_mask), String::WhiteSpace::space)); break;
					case 2: track_data.clip_name = String::Trim(String::Trim(column, bit_mask), String::WhiteSpace::space); break;
					case 3: track_data.timecode["start"] = String::Trim(String::Trim(column, bit_mask), String::WhiteSpace::space); break;
					case 4: track_data.timecode["end"] = String::Trim(String::Trim(column, bit_mask), String::WhiteSpace::space); break;
					case 5: track_data.timecode["duration"] = String::Trim(String::Trim(column, bit_mask), String::WhiteSpace::space); break;
					case 6: track_data.clip_state = (column.find("Unmuted", 0) == std::string::npos) ? true : false; break;
					default: throw std::logic_error("Error parsing EDL track data\n"); break;
				}
			}

			// TODO: Refactor time calculations
			track_data.time["start"] = Numbers::ParseTimecode(track_data.timecode["start"], header.frame_rate);
			track_data.time["end"] = Numbers::ParseTimecode(track_data.timecode["end"], header.frame_rate);
			track_data.time["duration"] = Numbers::ParseTimecode(track_data.timecode["duration"], header.frame_rate);

			track.track_data.push_back(track_data);
		}
		track.total_clips = total_clips++;
	};

	// Extract track chunks from raw file
 	std::string text((char*)this->filesink_raw);
	std::vector<std::string> chunks;
	Regex::AllMatches(
		chunks,
		text,
		std::regex("((^|\\w+?)([\\x00-\\xFF]+?))(\\x0a\\x0a\\x0a)+")
	);

	// Parse EDL header
	this->session_info = GetEDLHeaderData(chunks[0]);

	// Parse the data chunks
	chunks.erase(chunks.begin());
	size_t i = 0;
	for (auto chunk : chunks) {
		PTXTRACK data = GetTrackHeaderData(chunk);
		GetTrackBodyData(this->session_info, data, chunk);
		this->ptx_tracks[i++] = data;
	}
	this->session_info.audio_tracks_edl = i;
}

void EDLFilePTX::PrintOutput(const vt::Format::File& file_format)
{
	std::cout << this->GetOutput(file_format).str();
}

void EDLFilePTX::WriteOutput(const std::string& path, const vt::Format::File& format)
{
	std::ofstream file(path, std::ios::binary | std::ios::out);
	if (!file.is_open()) throw std::invalid_argument("Could not create specified file\n");
	file << this->GetOutput(format).str();
}

void EDLFilePTX::AddTrack() noexcept
{
	// TODO
}

void EDLFilePTX::Flush() noexcept
{
	// Remove data
	size_t size_offset = 0;
	size_t old_track = 0;
	size_t cascade_offset = 0;
	bool cascade = false;
	for (auto& data_index : this->marked_data) {
		if (old_track != data_index.first) {
			old_track = data_index.first;	
			size_offset = 0;
		}

		this->ptx_tracks[data_index.first]
			.track_data.erase(
				this->ptx_tracks[data_index.first].track_data.begin() + ( data_index.second - size_offset++)
			);
	}
	this->marked_data.clear();

	// Remove tracks
	for (auto& track_index : this->marked_tracks) {
		this->ptx_tracks.erase(track_index);
		this->session_info.audio_tracks_edl--;
	}
	this->marked_tracks.clear();
}

void EDLFilePTX::RemoveTrack(const uint32_t& track_index) noexcept
{
	if (this->marked_tracks.find(track_index) == this->marked_tracks.end()
		&& track_index < this->session_info.audio_tracks)
	{
		uint32_t i = 0;
		this->marked_tracks.insert(track_index);
		for (auto& data : this->ptx_tracks[track_index].track_data) {
			this->marked_data.insert(
				std::make_pair(track_index, i++)
			);
		}
	}
}

void EDLFilePTX::RemoveTrackEvent(const uint32_t& track_index, const uint32_t& entry_index) noexcept
{
	// TODO: Remove track entirely if there aren't clips?
	if (this->marked_data.find({track_index, entry_index}) == this->marked_data.end()
		&& track_index < this->session_info.audio_tracks
		&& entry_index < this->ptx_tracks[track_index].track_data.size())
	{
		this->marked_data.insert(
			std::make_pair(track_index, entry_index)
		);
	}
}

void EDLFilePTX::ForEach(const std::function<void(PTXTrack& track, size_t index)>& function) noexcept
{
	for (auto& track : this->ptx_tracks) {
		function(track.second, track.first);
	}
}

void EDLFilePTX::ForEach(const std::function<void(PTXTrack& track, size_t index)>& function) const noexcept
{
	this->ForEach(function);
}

void EDLFilePTX::FilterTracks(const std::function<bool(PTXTrack& track, size_t index)>& function) noexcept
{
	for (auto& track : this->ptx_tracks) {
		if (!function(track.second, track.first)) this->RemoveTrack(track.first);
	}

	this->Flush();
}

void EDLFilePTX::FilterData(const std::function<bool(PTXTrack& current_track, PTXTrackData& current_data, size_t index)>& function) noexcept
{
	// TODO: Optimize
	size_t data_index = 0;
	for (auto& track : this->ptx_tracks) {
		for (auto& data : track.second.track_data) {
			if (!function(track.second, data, data_index)) this->RemoveTrackEvent(track.first, data_index);
			data_index++;
		}
		data_index = 0;
	}

	this->Flush();
}

void EDLFilePTX::EnumerateEvents(size_t start) noexcept
{
	this->ForEach([&start](PTXTrack& track, size_t track_index) {

		track.ForEach(size_t(),[&start, &track_index](PTXTrackData& data, size_t data_index) {
			data.event = start++;
		});

		start = 1;
	});

}

void EDLFilePTX::EnumerateEvents(const size_t& track_index, size_t start) noexcept
{
	
}

uint32_t EDLFilePTX::TotalAudioTracks() noexcept
{
	return this->session_info.audio_tracks_edl;
	// return this->session_info.audio_tracks; // For when the actual track count of the ptx session is needed.
}

uint32_t EDLFilePTX::TotalAudioTracks() const noexcept
{
	return this->session_info.audio_tracks_edl;
}

uint32_t EDLFilePTX::TotalAudioClips() noexcept
{
	return this->session_info.audio_clips;
}

uint32_t EDLFilePTX::TotalAudioFiles() noexcept
{
	return this->session_info.audio_files;
}

uint32_t EDLFilePTX::TrackClips(const uint32_t& index) noexcept
{
	return this->ptx_tracks[index].total_clips;
}

std::string EDLFilePTX::SessionName() noexcept
{
	return this->session_info.session_name;
}

std::string EDLFilePTX::SessionStart() noexcept
{
	return this->session_info.session_start;
}

std::string EDLFilePTX::SampleRate() noexcept
{
	return vt::Format::GetSampleRate(this->session_info.sample_rate);
}

std::string EDLFilePTX::BitDepth() noexcept
{
	return vt::Format::GetBitDepth(this->session_info.bit_depth);
}

std::string EDLFilePTX::TimecodeFormat() noexcept
{
	return vt::Format::GetTimeFormat(this->session_info.timecode_format);
}

std::string EDLFilePTX::FrameRate() noexcept
{
	return vt::Format::GetFrameRate(this->session_info.frame_rate);
}

void EDLFilePTX::SetAudioTracks(const uint32_t audio_tracks) noexcept
{
	this->session_info.audio_tracks = audio_tracks;
}

void EDLFilePTX::SetAudioClips(const uint32_t audio_clips) noexcept
{
	this->session_info.audio_clips = audio_clips;
}

void EDLFilePTX::SetAudioFiles(const uint32_t audio_files) noexcept
{
	this->session_info.audio_files = audio_files;
}

void EDLFilePTX::SetSessionName(const std::string& name) noexcept
{
	this->session_info.session_name = name;
}

void EDLFilePTX::SetSessionStart(const std::string& session_start) noexcept
{
	this->session_info.session_start = session_start;
}

void EDLFilePTX::SetSampleRate(const std::string& sample_rate) noexcept
{
	this->session_info.sample_rate = vt::Format::GetSampleRate(sample_rate);
}

void EDLFilePTX::SetBitDepth(const std::string& bit_depth) noexcept
{
	this->session_info.bit_depth = vt::Format::GetBitDepth(bit_depth);
}

void EDLFilePTX::SetTimecodeFormat(const std::string& timecode_format) noexcept
{
	this->session_info.timecode_format = vt::Format::ParseTimeFormat(timecode_format);
}

void EDLFilePTX::SetFrameRate(const std::string& frame_rate) noexcept
{
	this->session_info.frame_rate = vt::Format::GetFrameRate(frame_rate);
}

std::stringstream EDLFilePTX::GetOutput(const vt::Format::File& file_format)
{
	using namespace vt;
	// TODO: Update srt conversion to include format enumerations
	// Timecode parsing
	const auto ParseTimecode = [](
		const std::string& timecode)	
	-> uint32_t // TODO: Make double
	{
		std::vector<std::string> timecode_chunks;
		Regex::AllMatches(timecode_chunks, timecode, std::regex("\\d\\d"));
		uint32_t ms = 0;
		uint64_t i = 0;
		for (auto& n : timecode_chunks) {
			if (n[0] == '0') n.erase(n.begin());
			switch (i++) {
				case 0: ms += std::stoi(n) * 60 * 60; break;
				case 1: ms += std::stoi(n) * 60; break;
				case 2: ms += std::stoi(n);	break;
				case 3: ms += (std::stoi(n) / 25); break; // TODO: Consider different frame rates
				default: break;
			}
		}

		return ms * 1000;
	};

	// TODO: Make this more accurate
	// Move this function into a namespace for general purpose use
	const auto MakeTimecode = [](
		std::string timecode)
	-> std::string
	{
		std::string ms = std::to_string(
			(std::stod(timecode.substr(9)) * 25.0) / 1000.0
		);
		ms.erase(0,2);
		ms.erase(3);

		return timecode.replace(8, 3, (',' + ms));
	};

	// Move this function into a namespace for general purpose use
	const auto& PadColumn = [](
		const char& pad,
		const int32_t& total,
		const uint32_t& item_length)
	-> std::string
	{
		std::string padding = "";
		for (int32_t i = total - item_length; i > 0; i--) {
			padding += pad;
		}
		return padding;
	};


	// Extract & sort data
	// TODO: Write tracks to outpute if they don't have any clips on them?
    std::stringstream output;
	switch (file_format) {
		case Format::File::srt:
		{
			size_t tracks_written = 0;
			size_t clips_written = 0;
			std::vector<std::tuple<uint32_t, uint32_t, std::unique_ptr<PTXTRACKDATA>>> timecode_map;
			for (auto& track : this->ptx_tracks) {
				if (true/* track.second.HasState(TrackState::muted) */) tracks_written++;
				for (auto& data : track.second.track_data) {
					if (true/* data.clip_state && !track.second.HasState(TrackState::muted) */) {
						clips_written++;
						timecode_map.push_back(
							std::make_tuple(
								ParseTimecode(data.timecode["start"]),
								ParseTimecode(data.timecode["end"]),
								std::make_unique<PTXTRACKDATA>(data)
							)
						);
					}
				}
			}

			std::sort(timecode_map.begin(), timecode_map.end());

			// Output to SRT format
			size_t i = 1;
			for (auto& n : timecode_map) {
				auto& [ start, end, data ] = n;
				output
					<< i++ << '\n'
					<< MakeTimecode(data->timecode["start"]) << " --> " << MakeTimecode(data->timecode["end"]) << '\n'
					<< data->clip_name
					<< "\n\n";
			}

			std::clog 
				<< "Tracks written: " << tracks_written << '\n'
				<< "Clips written: " << clips_written << "\n\n";

			return output;
		}

		case Format::File::edl_ptx_minimal:
		{
			output
				<< PTX::GetPTXString(PTX::PTXSTRING::edl_session_name) << ":\t" << this->SessionName() << '\n'
				<< PTX::GetPTXString(PTX::PTXSTRING::edl_sample_rate) << ":\t" << this->SampleRate() << ".000000\n" // TODO: Convert to float
				<< PTX::GetPTXString(PTX::PTXSTRING::edl_bit_depth) << ":\t" << this->BitDepth() << "-bit\n"
				<< PTX::GetPTXString(PTX::PTXSTRING::edl_start_timcode) << ":\t" << this->SessionStart() << '\n'
				<< PTX::GetPTXString(PTX::PTXSTRING::edl_timecode_format) << ":\t" << this->FrameRate() << " Frame\n" 
				<< PTX::GetPTXString(PTX::PTXSTRING::edl_audio_tracks) << ":\t" << this->TotalAudioTracks() << '\n'
				<< PTX::GetPTXString(PTX::PTXSTRING::edl_audio_clips) << ":\t" << this->TotalAudioClips() << '\n'
				<< PTX::GetPTXString(PTX::PTXSTRING::edl_audio_files) << ":\t" << this->TotalAudioFiles() << "\n\n\n"
				<< PTX::GetPTXString(PTX::PTXSTRING::edl_track_listing) << '\n';

				this->ForEach([&output, &PadColumn](PTXTRACK& track, size_t index) {
					output
						<< PTX::GetPTXString(PTX::PTXSTRING::edl_track_name) << ":\t" << track.track_name << '\n'
						<< PTX::GetPTXString(PTX::PTXSTRING::edl_comments) << ":\t" << String::Trim(track.comments, String::WhiteSpace::tab) << '\n' // TODO: Why is there still a tab in the comment?!
						<< PTX::GetPTXString(PTX::PTXSTRING::edl_user_delay) << ":\t" << track.user_delay << '\n'
						<< PTX::GetPTXString(PTX::PTXSTRING::edl_track_state) << ": ";
						size_t i = 0;
						for (auto& state : track.track_state) {
							if (state.second) output << state.first << ((i < track.track_state.size()) ? " " : "");
							i++;
						}
						output << '\n';

					output
						<< PTX::GetPTXString(PTX::PTXSTRING::edl_clip_channel) << PadColumn(' ', 8, PTX::GetPTXString(PTX::PTXSTRING::edl_clip_channel).length()) << '\t'
						<< PTX::GetPTXString(PTX::PTXSTRING::edl_clip_event) << PadColumn(' ', 8, PTX::GetPTXString(PTX::PTXSTRING::edl_clip_event).length()) << '\t'
						<< PTX::GetPTXString(PTX::PTXSTRING::edl_clip_name) << PadColumn(' ', 30, PTX::GetPTXString(PTX::PTXSTRING::edl_clip_name).length()) << '\t'
						<< PTX::GetPTXString(PTX::PTXSTRING::edl_clip_start) << PadColumn(' ', 14, PTX::GetPTXString(PTX::PTXSTRING::edl_clip_start).length()) << '\t'
						<< PTX::GetPTXString(PTX::PTXSTRING::edl_clip_end) << PadColumn(' ', 14, PTX::GetPTXString(PTX::PTXSTRING::edl_clip_end).length()) << '\t'
						<< PTX::GetPTXString(PTX::PTXSTRING::edl_clip_duration) << PadColumn(' ', 14, PTX::GetPTXString(PTX::PTXSTRING::edl_clip_duration).length()) << '\t'
						<< PTX::GetPTXString(PTX::PTXSTRING::edl_clip_state) << '\n';

						// TODO: Use this->ForEachData
						for (auto& data : track.track_data) {
							output
								<< data.channel << PadColumn(' ', 8, Numbers::CountDigits(data.channel)) << '\t'
								<< data.event << PadColumn(' ', 8, Numbers::CountDigits(data.event)) << '\t'
								<< data.clip_name << PadColumn(' ', 30, data.clip_name.length()) << '\t'
								<< PadColumn(' ', 14, data.timecode["start"].length()) << data.timecode["start"] << '\t'
								<< PadColumn(' ', 14, data.timecode["end"].length()) << data.timecode["end"] << '\t'
								<< PadColumn(' ', 14, data.timecode["duration"].length()) << data.timecode["duration"] << '\t'
								<< ((data.clip_state) ? PTX::GetPTXString(PTX::PTXSTRING::edl_muted) : PTX::GetPTXString(PTX::PTXSTRING::edl_unmuted)) << '\n';
						}

					output << "\n\n";
				});
			
			return output;
		}

		case Format::File::table_all: {
			size_t column_width_ep = 0;
			size_t column_width_name = 0;
			size_t column_width_line = 0;
			size_t column_width_tcin = 0;
			size_t column_width_tcout = 0;

			this->ForEach([&](PTXTrack track, size_t i_track) {
				auto production_code = Regex::FirstMatch(this->SessionName(), std::regex("\\[\\w{6}\\]"));
				auto ep_number = Regex::FirstMatch(this->SessionName(), std::regex("EP\\d{2,3}"));
				track.ForEach(0, [&](PTXTrackData data, size_t i_data) {
					if (production_code.length() + ep_number.length() + 2 > column_width_ep) column_width_ep = production_code.length() + ep_number.length() + 2;
					if (track.track_name.length() > column_width_name) column_width_name = track.track_name.length();
					if (data.clip_name.length() > column_width_line) column_width_line = data.clip_name.length();
					if (data.timecode["start"].length() + 7 > column_width_tcin) column_width_tcin = data.timecode["start"].length() + 7;
					if (data.timecode["end"].length() + 8 > column_width_tcout) column_width_tcout = data.timecode["end"].length() + 8;
				});
			});

			this->ForEach([&](PTXTrack track, size_t i_track) {
				track.ForEach(0, [&](PTXTrackData data, size_t i_data) {
					auto production_code = Regex::FirstMatch(this->SessionName(), std::regex("\\[\\w{6}\\]"));
					auto ep_number = Regex::FirstMatch(this->SessionName(), std::regex("EP\\d{2,3}"));
					output 
						<< production_code << " "
						<< ep_number << ":" << PadColumn(' ', column_width_ep, ep_number.length()) << '\t'
						<< track.track_name << PadColumn(' ', column_width_name, track.track_name.length()) << '\t'
						<< data.clip_name << PadColumn(' ', column_width_line, data.clip_name.length()) << '\t'
						<< "TC IN: " << data.timecode["start"] << PadColumn(' ', column_width_tcin, data.timecode["start"].length()) << '\t'
						<< "TC OUT: " << data.timecode["end"] << PadColumn(' ', column_width_tcout, data.timecode["end"].length()) << '\n';
				});
			});

			return output;
		}
			
		default:
			throw std::invalid_argument("Specified file format is not supported\n");
			return output;
	}
}

EDLFilePTX& EDLFilePTX::operator=(const EDLFilePTX& edl_file) noexcept
{
	if (this->filesink_raw) {
		std::free(this->filesink_raw);
	}

	this->filesink_raw = (uint8_t*)std::malloc(edl_file.filesink_length * sizeof(uint8_t));
	this->filesink_raw = (uint8_t*)std::memcpy(this->filesink_raw, edl_file.filesink_raw, edl_file.filesink_length * sizeof(uint8_t));
	this->ConstructorAssignment(edl_file);

	return *this;
}

EDLFilePTX& EDLFilePTX::operator=(EDLFilePTX&& edl_file) noexcept
{
	this->filesink_raw = edl_file.filesink_raw;
	this->ConstructorAssignment(edl_file);

	if (this != &edl_file) {
		edl_file.filesink_raw = nullptr;
		edl_file.filesink_length = 0;
		edl_file.filesink_path = "";
		edl_file.filesink_isvalid = false;

		edl_file.session_info = {};

		edl_file.marked_tracks = {};
		edl_file.marked_data = {};
		edl_file.ptx_tracks = {};
	}

	return *this;
}

namespace EDL
{
	inline void AddEventTime(EDLFilePTX& edl_file, PTXTrackData& data_1, PTXTrackData& data_2)
	{
		using namespace vt;
		double duration = Numbers::ParseTimecode(data_2.timecode["end"], Format::GetFrameRate(edl_file.FrameRate())) - data_1.time["start"].nanoseconds;
		data_1.time["end"].nanoseconds = data_2.time["end"].nanoseconds;
		data_1.time["duration"].nanoseconds = duration;
		data_1.timecode["end"] = data_2.timecode["end"];
		data_1.timecode["duration"] = Numbers::ParseTimecode(duration, Format::GetFrameRate(edl_file.FrameRate()));
	}

	std::string DuplicateTextFromDuration(const std::pair<double, double>& time_us, const std::string_view& character, const double& divisor, const uint32_t max_delimiter = 3)
	{
		if (time_us.second > time_us.first) {
			double quotient = std::ceil((time_us.second - time_us.first) / divisor);
			std::string delimiter = "";
			for (uint32_t i = 0; i < (uint32_t)quotient && i < max_delimiter; i++) {
				delimiter += " ";
				delimiter += character;
			}
			return delimiter + " ";
		}

		return " ";
	}

	void MergeBoundaryEvents(EDLFilePTX& edl_file, const std::string_view& delimiter)
	{
		// TODO: This should only work for events that are bordering on a delimiter event
		// TODO: Delete dangling delimiter events
		// TODO: Validate delimiter event length before merging
		using namespace vt;
		edl_file.ForEach([&edl_file, &delimiter](PTXTrack& track, size_t track_index) {
			// Temporaries
			size_t start_index = 0;

			track.ForEach(0, [&edl_file, &delimiter, &track, &start_index, &track_index](PTXTRACKDATA& data, size_t data_index) {
				// Conditions for checking boundaries
				bool is_delimiter = data.clip_name == delimiter;
				bool next_size_lt_total = data_index + 1 < track.track_data.size();
				bool start_eq_prev_end = (data_index)
					? data.time["start"].nanoseconds == track.track_data[data_index - 1].time["end"].nanoseconds
					: false;
				bool prev_is_delimiter = (data_index)
					? track.track_data[data_index - 1].clip_name == delimiter
					: false;

				// Check if start of new section
				if (start_eq_prev_end) {
					if (is_delimiter) {
						edl_file.RemoveTrackEvent(track_index, data_index);
					}

					else if (prev_is_delimiter) {
						// Put next event's text into start event's text
						track.track_data[start_index].clip_name +=
						DuplicateTextFromDuration(
							std::make_pair(track.track_data[data_index - 1].time["start"].nanoseconds, track.track_data[data_index - 1].time["end"].nanoseconds),
							"-", // TODO: Standardise this as a global or command line variable
							7500000.0 // TODO: Standardise this as a global or command line variable
						)
						+ track.track_data[data_index].clip_name;
						AddEventTime(edl_file, track.track_data[start_index], data);
						edl_file.RemoveTrackEvent(track_index, data_index);
					}

					else if (!prev_is_delimiter) {
						track.track_data[start_index].clip_name += " " + track.track_data[data_index].clip_name;
						AddEventTime(edl_file, track.track_data[start_index], data);
						edl_file.RemoveTrackEvent(track_index, data_index);
					}
				}
				
				// New section
				else {
					if (is_delimiter) {
						// Must not start on new section. Issue warning.
					}

					start_index = data_index;
				}
			});
		});

		edl_file.Flush();
	}

	void RemoveBoundaryEvents(EDLFilePTX& edl_file, const std::string_view& delimiter)
	{
		// TODO: This should only work for events that are bordering on a delimiter event
		// TODO: Delete dangling delimiter events
		// TODO: Validate delimiter event length before merging
		using namespace vt;
		edl_file.ForEach([&edl_file, &delimiter](PTXTrack& track, size_t track_index) {
			// Temporaries
			size_t start_index = 0;

			track.ForEach(0, [&edl_file, &delimiter, &track, &start_index, &track_index](PTXTRACKDATA& data, size_t data_index) {
				// Conditions for checking boundaries
				bool is_delimiter = data.clip_name == delimiter;
				bool next_size_lt_total = data_index + 1 < track.track_data.size();
				bool start_eq_prev_end = (data_index)
					? data.time["start"].nanoseconds == track.track_data[data_index - 1].time["end"].nanoseconds
					: false;
				bool prev_is_delimiter = (data_index)
					? track.track_data[data_index - 1].clip_name == delimiter
					: false;

				// Check if start of new section
				if (start_eq_prev_end) {
					if (is_delimiter) {
						edl_file.RemoveTrackEvent(track_index, data_index);
					}
				}
				
				// New section
				else {
					start_index = data_index;
				}
			});
		});

		edl_file.Flush();
	}
}

