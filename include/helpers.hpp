// Stefan "SoulXP" Olivier
// File: helpers.hpp
// Description: Auxiliary functions to help with parsing EDL files

#ifndef VT_HEADER
#define VT_HEADER

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "config.hpp"
#endif

// Standard headers
#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <regex>
#include <concepts>
#include <type_traits>

// Project headers

namespace vt
{
	namespace regex
	{
		bool HasMatch(const std::string& text, const std::regex& expr, size_t start_offset = 0);
		std::string FirstMatch(const std::string& text, const std::regex& expr, size_t start_offset = 0);
		void AllMatches(std::vector<std::string>& text_list, const std::string& text, const std::regex& expr, size_t start_offset = 0);

		template<class Tstart, class Tend>
		void AllMatches(std::vector<std::string>& text_list, const Tstart& start, const Tend& end, const std::regex& expr)
		{
			std::sregex_iterator current(start, end, expr);
			std::sregex_iterator last;
			while (current != last) {
				std::smatch match = *current++;
				text_list.push_back(match.str());
			}
		}
	}

	namespace format
	{
		typedef
		enum class SampleRate
		{	
			_44kHz,
			_48kHz,
			_88kHz,
			_96kHz,
			_192kHz,
			_384kHz,
			none
		} SAMPLERATE;

		typedef
		enum class BitDepth
		{	
			int8,
			int16,
			int24,
			int32,
			float32,
			float64,
			none
		} BITDEPTH;

		typedef
		enum class TimeFormat
		{
			timecode,
			timecode_subframes,
			feet_frames,
			bars_beats,
			minute_seconds,
			samples,
			frames,
			sub_frames,
			hours,
			minutes,
			seconds,
			digits,
			none
		} TIMEFORMAT;

		typedef
		enum class FrameRate
		{
			_23_976Fps,
			_24Fps,
			_25Fps,
			_30Fps,
			_60Fps,
			none
		} FRAMERATE;

		typedef
		enum class File
		{
			srt,
			edl_ptx_all,
			edl_ptx_minimal,
			table_all,
			db_dump,
			none
		} FILE;
		
		typedef
		struct Time
		{
		public:
			Time();
			Time(const double& n);
			~Time();

			void Modify(const double& n);

			double nanoseconds;

		} TIME;

		typedef
		struct XMLNode // TODO: Move int ::XML namespace
		{
		public:
			using tag_t = std::pair<std::string, std::string>;
			using attribute_t = std::tuple<std::string, std::string, std::string>;
			using flag_t = std::array<bool, 3>;
			XMLNode();
			XMLNode(const XMLNode& xml_node) noexcept;
			XMLNode(XMLNode&& xml_node) noexcept;
			XMLNode(const tag_t& new_tag, const std::vector<attribute_t>& new_attributes, const std::string& new_text = "") noexcept;

			std::optional<std::reference_wrapper<const attribute_t>> GetNodeId() const noexcept;

			tag_t tag;
			std::string text;
			std::vector<attribute_t> attributes;
			flag_t update_flags;
			XMLNode& operator=(const XMLNode& xml_node) noexcept;
			XMLNode& operator=(XMLNode&& xml_node) noexcept;
		} XMLNODE;

		SampleRate GetSampleRate(const std::string text);
		std::string GetSampleRate(const SampleRate& sample_rate);
		size_t ParseSampleRate(const SampleRate& sample_rate);
		BitDepth GetBitDepth(const std::string text);
		std::string GetBitDepth(const BitDepth& bit_depth);
		size_t ParseBitDepth(const BitDepth& bit_depth);
		TimeFormat ParseTimeFormat(const std::string text);
		std::string GetTimeFormat(const TimeFormat& time_format);
		FrameRate GetFrameRate(const std::string text);
		std::string GetFrameRate(const FrameRate& frame_rate);
		double ParseFrameRate(const FrameRate& frame_rate);

		using attribute_t = std::tuple<std::string, std::string, std::string>;
		XMLNode XMLNodeFactory(const std::string& ns,
								const std::string& tag,
								const std::string& text,
								const std::vector<attribute_t>& attributes) noexcept;

		XMLNode XMLNodeFactory(const std::string& tag,
								const std::vector<attribute_t>& attributes) noexcept;

		inline attribute_t CreateAttributeType(const std::string& attribute,
												const std::string& value,
												const std::string& ns = "")
		{
			return std::make_tuple(ns, attribute, value); // TODO: Verify if valid attribute
		}
	}

namespace numbers
	{
		size_t CountDigits(const size_t n);
		double ParseTimecode(const std::string text, const format::FrameRate& format);
		std::string ParseTimecode(double n, const format::FrameRate& format);
		size_t ParseTime(const std::string text, const format::TimeFormat& format);
	}

	namespace string
	{
		typedef
		enum WhiteSpace : size_t
		{
			space		= 0xffffffe1,
			tab			= 0xffffffe2,
			linefeed	= 0xffffffe4,
			carriage	= 0xffffffe8,
			vertical	= 0xfffffff0,
			all_spaces 	= 0xffffffff,
			no_space	= 0x00000001,
			no_tab		= 0x00000002,
			no_linefeed	= 0x00000004,
			no_carriage	= 0x00000008,
			no_vertical	= 0x00000030
		} WHITESPACE;

		std::string WhiteSpaceMask(const size_t& type);
		std::string Trim(std::string text, const size_t& type);
	}

	namespace PTX
	{
		typedef
		enum class PTXString
		{
			edl_session_name,
			edl_sample_rate,
			edl_bit_depth,
			edl_start_timcode,
			edl_timecode_format,
			edl_audio_tracks,
			edl_audio_clips,
			edl_audio_files,
			edl_track_listing,
			edl_track_name,
			edl_comments,
			edl_user_delay,
			edl_track_state,
			edl_clip_channel,
			edl_clip_event,
			edl_clip_name,
			edl_clip_start,
			edl_clip_end,
			edl_clip_duration,
			edl_clip_state,
			edl_unmuted,
			edl_muted,
			edl_inactive,
			edl_hidden,
			none
		} PTXSTRING;

		std::string GetPTXString(const PTXString& string);
	}

	namespace xml
	{
		typedef
		enum class XMLProfile
		{
			ttml_1p0_netflix,
			imsc_1p1_netflix,
			unknown,
			none
		} XMLPROFILE;

		typedef
		enum class XMLTag
		{
			// General xml tags
			after, agent, before, begin, body, br, copyright, color, desc, div, en, end, encoding, extent, head, id, lang, layout, metadata, media, paragraph,
			parameter, region, span, style, styling, title, version, xml, xmlns,

			// TTML tags
			tt, ttp, tts, ttm,
			
			// Text tags
			font_family, font_size, text_align,

			// Media tags
			display_align, frame_rate, origin, time_base,

			// Default
			none
		} XMLTAG;

		typedef
		enum class XMLUrl
		{
			// Namespaces
			w3_ns_xml, w3_ns_ttml, w3_ns_ttml_styling, w3_ns_ttml_parameter, w3_ns_ttml_metadata
		} XMLURL;

		typedef
		enum TTML1p0_Head_Flags : size_t
		{
			root			= 0x0001,
			head			= 0x0002,
			body			= 0x0004,
			layout			= 0x0008,
			metadata		= 0x0010,
			parameter		= 0x0020,
			styling			= 0x0040,
			none			= 0x0000
		} TTML1P0_HEAD_FLAGS;

		std::string GetXMLProfileText(const XMLProfile& profile);
		XMLTag GetXMLTag(const std::string& profile);
		std::string GetXMLTagText(const XMLTag& tag);
		std::string GetXMLUrlText(const XMLUrl& url);
	}
}

#endif