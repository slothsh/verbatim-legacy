// Stefan "SoulXP" Olivier
// File: edlfile.hpp
// Description: Headers for edit decision list file parsing

#ifndef EDLFILE_HEADER
#define EDLFILE_HEADER

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "config.hpp"
#endif

// Standard headers
#include <iostream>
#include <cstdint>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <functional>

// Project headers
#include "filesink.hpp"
#include "ptxedlstructure.hpp"

// EDLFilePTX object declaration ----------------------------------------------------------------------------------------------|
// ============================================================================================================================|

struct EDLFilePTX : public FileSink
{
public:
	EDLFilePTX(const EDLFilePTX& edl_file) noexcept;
	EDLFilePTX(EDLFilePTX&& edl_file) noexcept;
	explicit EDLFilePTX(const std::string& path);
    ~EDLFilePTX();

	void PrintOutput(const vt::format::File& format);
	void WriteOutput(const std::string& path, const vt::format::File& format);
	void AddTrack() noexcept;
	void Flush() noexcept;
	void RemoveTrack(const size_t& track_index) noexcept;
	void RemoveTrackEvent(const size_t& track_index, const size_t& entry_index) noexcept;
	void ForEach(const std::function<void(PTXTrack& track, size_t index)>& function) noexcept;
	void ForEach(const std::function<void(PTXTrack& track, size_t index)>& function) const noexcept;
	void FilterTracks(const std::function<bool(PTXTrack& track, size_t index)>& function) noexcept;
	void FilterData(const std::function<bool(PTXTrack& current_track, PTXTrackData& current_data, size_t index)>& function) noexcept;
	void EnumerateEvents(size_t start = 1) noexcept;
	void EnumerateEvents(const size_t& track_index, size_t start = 1) noexcept;

	// Getters & Setters
	size_t TotalAudioTracks() noexcept;
	size_t TotalAudioTracks() const noexcept;
	size_t TotalAudioClips() noexcept;
	size_t TotalAudioFiles() noexcept;
	size_t TrackClips(const size_t& index) noexcept;
	std::string SessionName() noexcept;
	std::string SessionStart() noexcept;
	std::string SampleRate() noexcept;
	std::string BitDepth() noexcept;
	std::string TimecodeFormat() noexcept;
	std::string FrameRate() noexcept;
	void SetAudioTracks(const size_t audio_tracks) noexcept;
	void SetAudioClips(const size_t audio_clips) noexcept;
	void SetAudioFiles(const size_t audio_files) noexcept;
	void SetSessionName(const std::string& name) noexcept;
	void SetSessionStart(const std::string& session_start) noexcept;
	void SetSampleRate(const std::string& sample_rate) noexcept;
	void SetBitDepth(const std::string& bit_depth) noexcept;
	void SetTimecodeFormat(const std::string& timecode_format) noexcept;
	void SetFrameRate(const std::string& rate) noexcept;

	EDLFilePTX& operator=(const EDLFilePTX& edl_file) noexcept;
	EDLFilePTX& operator=(EDLFilePTX&& edl_file) noexcept;

protected:
	virtual void Parse();

	PTXHeader session_info;
	std::set<size_t> marked_tracks;
	std::set<std::pair<size_t, size_t>> marked_data;
	std::map<size_t, PTXTrack> ptx_tracks;

private:
	std::stringstream GetOutput(const vt::format::File& format);
	inline void ConstructorAssignment(const EDLFilePTX& edl_file) noexcept;
};

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// EDL object functions -------------------------------------------------------------------------------------------------------|
// ============================================================================================================================|

namespace EDL
{
	inline void AddEventTime(EDLFilePTX& edl_file, PTXTrackData& data_1, PTXTrackData& data_2);

	std::string DuplicateTextFromDuration(
		const std::pair<double, double>& time_us,
		const std::string_view& character,
		const double& divisor,
		const size_t max_delimiter
	);

	void MergeBoundaryEvents(EDLFilePTX& edl_file, const std::string_view& delimiter);
	void RemoveBoundaryEvents(EDLFilePTX& edl_file, const std::string_view& delimiter);
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif