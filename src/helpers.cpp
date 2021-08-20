// Stefan "SoulXP" Olivier
// File: edlvt.cpp
// Description: Source files for auxiliary functions to help with parsing EDL files

// Standard headers
#include <iostream>
#include <cstdint>
#include <cmath>
#include <string>
#include <vector>
#include <regex>

// Project headers
#include "../include/helpers.hpp"

namespace vt
{
	namespace regex
	{
		bool HasMatch(const std::string& text, const std::string& expr)
		{
			return std::regex_search(text, std::regex(expr));
		}

		std::string FirstMatch(
			const std::string& text,
			const std::regex& expr)
		{
			std::sregex_iterator current(text.begin(), text.end(), expr);
			std::smatch match = *current;
			return match.str();
		}

		void AllMatches(
			std::vector<std::string>& text_list,
			const std::string& text,
			const std::regex& expr)
		{
			std::sregex_iterator current(text.begin(), text.end(), expr);
			std::sregex_iterator last;
			while (current != last) {
				std::smatch match = *current++;
				text_list.push_back(match.str());
			}
		}
	}

	namespace format
	{
		SampleRate GetSampleRate(const std::string text)
		{
			if (text.find("44100") != std::string::npos) return format::SampleRate::_44kHz;
			if (text.find("48000") != std::string::npos) return format::SampleRate::_48kHz;
			if (text.find("88200") != std::string::npos) return format::SampleRate::_88kHz;
			if (text.find("96000") != std::string::npos) return format::SampleRate::_96kHz;
			if (text.find("192000") != std::string::npos) return format::SampleRate::_192kHz;
			if (text.find("384000") != std::string::npos) return format::SampleRate::_384kHz;
			return format::SampleRate::none;
		}
        
        std::string GetSampleRate(const SampleRate& sample_rate)
        {
            if (sample_rate == format::SampleRate::_44kHz) return "44100";
			if (sample_rate == format::SampleRate::_48kHz) return "48000";
			if (sample_rate == format::SampleRate::_88kHz) return "88200";
			if (sample_rate == format::SampleRate::_96kHz) return "96000";
			if (sample_rate == format::SampleRate::_192kHz) return "192000";
			if (sample_rate == format::SampleRate::_384kHz) return "384000";
			return "";
        }

		size_t ParseSampleRate(const SampleRate& sample_rate)
		{
			if (sample_rate == format::SampleRate::_44kHz) return 44100;
			if (sample_rate == format::SampleRate::_48kHz) return 48000;
			if (sample_rate == format::SampleRate::_88kHz) return 88200;
			if (sample_rate == format::SampleRate::_96kHz) return 96000;
			if (sample_rate == format::SampleRate::_192kHz) return 192000;
			if (sample_rate == format::SampleRate::_384kHz) return 384000;
			return 0;
		}

		BitDepth GetBitDepth(const std::string text)
		{
			if (text.find("8-bit") != std::string::npos) return format::BitDepth::int8;
			if (text.find("16-bit") != std::string::npos) return format::BitDepth::int16;
			if (text.find("24-bit") != std::string::npos) return format::BitDepth::int24;
			// if (text.find("32-bit") != std::string::npos) return format::BitDepth::int32;
			if (text.find("32-bit") != std::string::npos) return format::BitDepth::float32;
			if (text.find("64-bit") != std::string::npos) return format::BitDepth::float64;
			return format::BitDepth::none;
		}
        
        std::string GetBitDepth(const BitDepth& bit_depth)
        {
            if (bit_depth == format::BitDepth::int8) return "8";
			if (bit_depth == format::BitDepth::int16) return "16";
			if (bit_depth == format::BitDepth::int24) return "24";
			// if (bit_depth == format::BitDepth::int32) return "32";
			if (bit_depth == format::BitDepth::float32) return "32";
			if (bit_depth == format::BitDepth::float64) return "64";
			return "";
        }

		size_t ParseBitDepth(const BitDepth& bit_depth)
		{
			if (bit_depth == format::BitDepth::int8) return 8;
			if (bit_depth == format::BitDepth::int16) return 16;
			if (bit_depth == format::BitDepth::int24) return 24;
			// if (bit_depth == format::BitDepth::int32) return 32;
			if (bit_depth == format::BitDepth::float32) return 32;
			if (bit_depth == format::BitDepth::float64) return 64;
			return 0;
		}

		TimeFormat ParseTimeFormat(const std::string text)
		{
			if (regex::HasMatch(text, "\\d\\d:\\d\\d:\\d\\d:\\d\\d") && !regex::HasMatch(text, "\\d\\d:\\d\\d:\\d\\d:\\d\\d\\.\\d\\d")) return format::TimeFormat::timecode;
			if (regex::HasMatch(text, "\\d\\d:\\d\\d:\\d\\d:\\d\\d\\.\\d\\d")) return format::TimeFormat::timecode_subframes;
			// if () return format::TimeFormat::feet_frames;
			// if () return format::TimeFormat::minute_seconds;
			// if () return format::TimeFormat::bars_beats;
			// if () return format::TimeFormat::samples;
			return format::TimeFormat::none;
		}
        
        std::string GetTimeFormat(const TimeFormat& time_format)
        {
            if (time_format == format::TimeFormat::timecode) return "timecode";
			if (time_format == format::TimeFormat::timecode_subframes) return "timecode.subframes";
			if (time_format == format::TimeFormat::feet_frames) return "feet+frames";
			if (time_format == format::TimeFormat::minute_seconds) return "minute:seconds";
			if (time_format == format::TimeFormat::bars_beats) return "bars|beats";
			if (time_format == format::TimeFormat::samples) return "samples";
			if (time_format == format::TimeFormat::frames) return "frames";
			if (time_format == format::TimeFormat::sub_frames) return "sub_frames";
			if (time_format == format::TimeFormat::hours) return "hours";
			if (time_format == format::TimeFormat::minutes) return "minutes";
			if (time_format == format::TimeFormat::seconds) return "seconds";
			if (time_format == format::TimeFormat::digits) return "digits";
			return "";
        }

		FrameRate GetFrameRate(const std::string text)
		{
			if (text.find("24") != std::string::npos) return format::FrameRate::_24Fps;
			if (text.find("25") != std::string::npos) return format::FrameRate::_25Fps;
			if (text.find("30") != std::string::npos) return format::FrameRate::_30Fps;
			if (text.find("60") != std::string::npos) return format::FrameRate::_60Fps;
			return format::FrameRate::none;
		}
        
        std::string GetFrameRate(const FrameRate& frame_rate)
        {
            if (frame_rate == format::FrameRate::_24Fps) return "24";
			if (frame_rate == format::FrameRate::_25Fps) return "25";
			if (frame_rate == format::FrameRate::_30Fps) return "30";
			if (frame_rate == format::FrameRate::_60Fps) return "60";
			return "";
        }

		size_t ParseFrameRate(const FrameRate& frame_rate)
		{
			if (frame_rate == format::FrameRate::_24Fps) return 24;
			if (frame_rate == format::FrameRate::_25Fps) return 25;
			if (frame_rate == format::FrameRate::_30Fps) return 30;
			if (frame_rate == format::FrameRate::_60Fps) return 60;
			return 0;
		}

		using attribute_t = std::tuple<std::string, std::string, std::string>;
		XMLNode XMLNodeFactory(const std::string& tag,
								const std::string& ns,
								const std::string& text,
								const std::vector<attribute_t>& attributes) noexcept
		{
			XMLNode node;
			node.tag = std::make_pair(ns, tag);
			node.text = text;
			node.attributes = attributes;
			return node;
		}

		XMLNode XMLNodeFactory(const std::string& tag,
								const std::vector<attribute_t>& attributes) noexcept
		{
			return XMLNodeFactory(
				std::forward<const std::string>(tag),
				std::forward<const std::string>(""),
				std::forward<const std::string>(""),
				std::forward<decltype(attributes)>(attributes)
			);
		}

		Time::Time():
			nanoseconds(0.0)
		{
		}

		Time::Time(const double& n)
		{
			this->nanoseconds = n;
		}

		Time::~Time()
		{
		}

		void Time::Modify(const double& n)
		{
			this->nanoseconds += n;
		}

		XMLNode::XMLNode()
			: tag({}),
			text(""),
			attributes({}),
			update_flags({ true, true, true })
		{
		}

		XMLNode::XMLNode(const XMLNode& xml_node) noexcept
		{
			this->tag = xml_node.tag;
			this->text = xml_node.text;
			this->attributes = xml_node.attributes;
			this->update_flags = xml_node.update_flags;
		}

		XMLNode::XMLNode(XMLNode&& xml_node) noexcept
		{
			*this = std::move(xml_node);
		}

		XMLNode::XMLNode(const tag_t& new_tag, const std::vector<attribute_t>& new_attributes, const std::string& new_text) noexcept
			: tag(new_tag),
			text(new_text),
			attributes(new_attributes),
			update_flags({ true, true, true })
		{
		}

		using attribute_t = std::tuple<std::string, std::string, std::string>;
		std::optional<std::reference_wrapper<const attribute_t>> XMLNode::GetNodeId() const noexcept
		{
			using namespace vt::xml;
			const auto& predicate = [&](const auto& a) {
				const auto tag_id = GetXMLTagText(XMLTag::id);
				const auto tag_xml = GetXMLTagText(XMLTag::xml);
				const auto& [ ns, element, attribute ] = a;
				if (ns == tag_xml && element == tag_id) {
					return true;
				}
				return false;
			};
			const auto& id_itr = std::find_if(this->attributes.begin(), this->attributes.end(), predicate);
			return (id_itr == this->attributes.end())
				? std::nullopt
				: std::optional<std::reference_wrapper<const attribute_t>>{*id_itr};
		}

		XMLNode& XMLNode::operator=(const XMLNode& xml_node) noexcept
		{
			this->tag = xml_node.tag;
			this->text = xml_node.text;
			this->attributes = xml_node.attributes;
			this->update_flags = xml_node.update_flags;
			return *this;
		}

		XMLNode& XMLNode::operator=(XMLNode&& xml_node) noexcept
		{
			this->tag = xml_node.tag;
			this->text = xml_node.text;
			this->attributes = xml_node.attributes;
			this->update_flags = xml_node.update_flags;

			if (this != &xml_node) {
				this->tag = {};
				this->text = "";
				this->attributes = {};
				this->update_flags = {};
			}

			return *this;
		}

	}

	namespace numbers
	{
		size_t CountDigits(size_t n)
		{
			size_t digits = 0;
			while (n > 0) {
				n /= 10;
				digits++;
			}

			return digits;
		}

		double ParseTimecode(const std::string text, const format::FrameRate& format)
		{
			std::vector<std::string> chunks;
			regex::AllMatches(chunks, text, std::regex("\\d+"));
			if (chunks.size() != 4) throw std::invalid_argument("Not enough chunks to parse timecode\n");
			size_t frame_rate = ParseFrameRate(format);
			double h = std::stod(chunks[0]) * 60.0 * 60.0;
			double m = std::stod(chunks[1]) * 60.0;
			double s = std::stod(chunks[2]);
			double f = (std::stod(chunks[3]) / frame_rate);

			return (h + m + s + f) * 10000000; // TODO: Create a precision constant for this
		}

		std::string ParseTimecode(double n, const format::FrameRate& format)
		{
			size_t frame_rate = ParseFrameRate(format);
			std::string h = "00", m = "00", s = "00", f = "00";
			if (n >= 60.0 * 60.0 * 10000000.0) {
				h = std::to_string(n / 60.0 * 60.0 / 10000000.0);
				h = h.substr(0, h.find_first_of('.', 0));
				n = std::fmod(n, (60.0 * 60.0 * 10000000.0));
			}
			if (n >= 60.0 * 10000000.0) {
				m = std::to_string(n / 60.0 / 10000000.0);
				m = m.substr(0, m.find_first_of('.', 0));
				n = std::fmod(n, 60.0 * 10000000.0);
			}
			if (n >= 10000000.0) {
				s = std::to_string(n / 10000000.0);
				s = s.substr(0, s.find_first_of('.', 0));
				n = std::fmod(n, 10000000.0);
			}

			f = std::to_string(std::round(n * frame_rate / 10000000.0));
			f = f.substr(0, f.find_first_of('.', 0));
			// n -= (n / 1000000000 * frame_rate);

			return ((h.length() == 1) ? ("0" + h) : h)+ ":"
					+ ((m.length() == 1) ? ("0" + m) : m) + ":"
					+ ((s.length() == 1) ? ("0" + s) : s) + ":"
					+ ((f.length() == 1) ? ("0" + f) : f);
		}

		size_t ParseTime(const std::string text, const format::TimeFormat& format)
		{
			std::string expr;
			size_t total_chunks;
			std::vector<std::string> chunks;
			switch (format) {
				case format::TimeFormat::timecode: 
					expr = "\\d+";
					total_chunks = 4;
					break;
				case format::TimeFormat::timecode_subframes: 
					expr = "\\d+";
					total_chunks = 5;
					break;
				case format::TimeFormat::minute_seconds: 
					expr = "\\d+";
					total_chunks = 2;
					break;
				case format::TimeFormat::digits: 
					expr = "\\d+";
					total_chunks = 1;
					break;
				default:
					throw std::invalid_argument("Invalid format to parse time with\n");
					break;
			}

			regex::AllMatches(chunks, text, std::regex(expr));
			if (chunks.size() != total_chunks) throw std::invalid_argument("The time format could not parsed\n");

			size_t nanoseconds = 0;
			switch (format) {
				case format::TimeFormat::timecode: break;
				case format::TimeFormat::timecode_subframes: break;
				case format::TimeFormat::minute_seconds: break;
				case format::TimeFormat::digits: break;
				default: break;
			}

			return 0;
		}
	}

	namespace string
	{

		std::string WhiteSpaceMask(const size_t& type)
		{
			std::string white_space;
			switch (type) {
				case 0xffffffe1: white_space = " ";					break;
				case 0xffffffe2: white_space = "\t";				break;
				case 0xffffffe3: white_space = " \t";				break;
				case 0xffffffe4: white_space = "\n";				break;
				case 0xffffffe5: white_space = " \n";				break;
				case 0xffffffe6: white_space = "\t\n";				break;
				case 0xffffffe7: white_space = " \t\n";				break;
				case 0xffffffe8: white_space = "\r";				break;
				case 0xffffffe9: white_space = " \r";				break;
				case 0xffffffea: white_space = "\t\r";				break;
				case 0xffffffeb: white_space = " \t\r";				break;
				case 0xffffffec: white_space = "\n\r";				break;
				case 0xffffffed: white_space = " \n\r";				break;
				case 0xffffffee: white_space = "\t\n\r";			break;
				case 0xffffffef: white_space = " \t\n\r";			break;
				case 0xfffffff0: white_space = "\v";				break;
				case 0xfffffff1: white_space = " \v";				break;
				case 0xfffffff2: white_space = "\t\v";				break;
				case 0xfffffff3: white_space = " \t\v";				break;
				case 0xfffffff4: white_space = "\n\v";				break;
				case 0xfffffff5: white_space = " \n\v";				break;
				case 0xfffffff6: white_space = "\t\n\v";			break;
				case 0xfffffff7: white_space = " \t\n\v";			break;
				case 0xfffffff8: white_space = "\r\v";				break;
				case 0xfffffff9: white_space = " \r\v";				break;
				case 0xfffffffa: white_space = "\t\r\v";			break;
				case 0xfffffffb: white_space = " \t\r\v";			break;
				case 0xfffffffc: white_space = "\n\r\v";			break;
				case 0xfffffffd: white_space = " \n\r\v";			break;
				case 0xfffffffe: white_space = "\t\n\r\v";			break;
				case 0xffffffff: white_space = " \t\n\r\v";			break;
			}

			return white_space;
		}

		std::string Trim(
			std::string text,
			const size_t& type)
		{
			std::string white_space =string::WhiteSpaceMask(type);
			text.erase(text.find_last_not_of(white_space) + 1);
			text.erase(0, text.find_first_not_of(white_space));
			return text;
		}
	}

	namespace PTX
	{
		std::string GetPTXString(const PTXString& string)
		{
			if (string == PTXString::edl_session_name) return "SESSION NAME";
			if (string == PTXString::edl_sample_rate) return "SAMPLE RATE";
			if (string == PTXString::edl_bit_depth) return "BIT DEPTH";
			if (string == PTXString::edl_start_timcode) return "SESSION START TIMECODE";
			if (string == PTXString::edl_timecode_format) return "TIMECODE FORMAT";
			if (string == PTXString::edl_audio_tracks) return "# OF AUDIO TRACKS";
			if (string == PTXString::edl_audio_clips) return "# OF AUDIO CLIPS";
			if (string == PTXString::edl_audio_files) return "# OF AUDIO FILES";
			if (string == PTXString::edl_track_listing) return "T R A C K  L I S T I N G";
			if (string == PTXString::edl_track_name) return "TRACK NAME";
			if (string == PTXString::edl_comments) return "COMMENTS";
			if (string == PTXString::edl_user_delay) return "USER DELAY";
			if (string == PTXString::edl_track_state) return "STATE";
			if (string == PTXString::edl_clip_channel) return "CHANNEL";
			if (string == PTXString::edl_clip_event) return "EVENT";
			if (string == PTXString::edl_clip_name) return "CLIP NAME";
			if (string == PTXString::edl_clip_start) return "START TIME";
			if (string == PTXString::edl_clip_end) return "END TIME";
			if (string == PTXString::edl_clip_duration) return "DURATION";
			if (string == PTXString::edl_clip_state) return "STATE";
			if (string == PTXString::edl_unmuted) return "Unmuted";
			if (string == PTXString::edl_muted) return "Muted";
			if (string == PTXString::edl_inactive) return "Inactive";
			if (string == PTXString::edl_hidden) return "Hidden";
			return "";
		}
	}

	namespace xml
	{
		std::string GetXMLProfileText(const XMLProfile& profile)
		{
			if (profile == XMLProfile::ttml_1p0_netflix) return "TTML 1.0 Netflix";
			if (profile == XMLProfile::imsc_1p1_netflix) return "IMSC 1.1 Netflix";
			if (profile == XMLProfile::unknown) return "TTML Unknown";
			return "";
		}

		XMLTag GetXMLTag(const std::string& tag)
		{
			// General xml tags
			if (tag == "after") return XMLTag::after;
			if (tag == "agent") return XMLTag::agent;
			if (tag == "before") return XMLTag::before;
			if (tag == "begin") return XMLTag::begin;
			if (tag == "body") return XMLTag::body;
			if (tag == "br") return XMLTag::br;
			if (tag == "copyright") return XMLTag::copyright;
			if (tag == "desc") return XMLTag::desc;
			if (tag == "div") return XMLTag::div;
			if (tag == "en") return XMLTag::en;
			if (tag == "end") return XMLTag::end;
			if (tag == "encoding") return XMLTag::encoding;
			if (tag == "extent") return XMLTag::extent;
			if (tag == "head") return XMLTag::head;
			if (tag == "id") return XMLTag::id;
			if (tag == "lang") return XMLTag::lang;
			if (tag == "layout") return XMLTag::layout;
			if (tag == "media") return XMLTag::media;
			if (tag == "metadata") return XMLTag::metadata;
			if (tag == "p") return XMLTag::paragraph;
			if (tag == "parameter") return XMLTag::parameter;
			if (tag == "region") return XMLTag::region;
			if (tag == "span") return XMLTag::span;
			if (tag == "style") return XMLTag::style;
			if (tag == "styling") return XMLTag::styling;
			if (tag == "title") return XMLTag::title;
			if (tag == "version") return XMLTag::version;
			if (tag == "xml") return XMLTag::xml;
			// TTML tags
			if (tag == "tt") return XMLTag::tt;
			if (tag == "ttp") return XMLTag::ttp;
			if (tag == "tts") return XMLTag::tts;
			if (tag == "ttm") return XMLTag::ttm;
			// Text tags
			if (tag == "fontFamily") return XMLTag::font_family;
			if (tag == "fontSize") return XMLTag::font_size;
			if (tag == "textAlign") return XMLTag::text_align;
			// Media tags
			if (tag == "displayAlign") return XMLTag::display_align;
			if (tag == "frameRate") return XMLTag::frame_rate;
			if (tag == "origin") return XMLTag::origin;
			if (tag == "timeBase") return XMLTag::time_base;
			// Default
			return XMLTag::none;
		}

		std::string GetXMLTagText(const XMLTag& tag)
		{
			// General xml tags
			if (tag == XMLTag::after) return "after";
			if (tag == XMLTag::agent) return "agent";
			if (tag == XMLTag::before) return "before";
			if (tag == XMLTag::begin) return "begin";
			if (tag == XMLTag::body) return "body";
			if (tag == XMLTag::br) return "br";
			if (tag == XMLTag::copyright) return "copyright";
			if (tag == XMLTag::color) return "color";
			if (tag == XMLTag::desc) return "desc";
			if (tag == XMLTag::div) return "div";
			if (tag == XMLTag::en) return "en";
			if (tag == XMLTag::end) return "end";
			if (tag == XMLTag::encoding) return "encoding";
			if (tag == XMLTag::extent) return "extent";
			if (tag == XMLTag::head) return "head";
			if (tag == XMLTag::id) return "id";
			if (tag == XMLTag::lang) return "lang";
			if (tag == XMLTag::layout) return "layout";
			if (tag == XMLTag::media) return "media";
			if (tag == XMLTag::metadata) return "metadata";
			if (tag == XMLTag::paragraph) return "p";
			if (tag == XMLTag::parameter) return "parameter";
			if (tag == XMLTag::region) return "region";
			if (tag == XMLTag::span) return "span";
			if (tag == XMLTag::style) return "style";
			if (tag == XMLTag::styling) return "styling";
			if (tag == XMLTag::title) return "title";
			if (tag == XMLTag::version) return "version";
			if (tag == XMLTag::xml) return "xml";
			// TTML tags
			if (tag == XMLTag::tt) return "tt";
			if (tag == XMLTag::ttp) return "ttp";
			if (tag == XMLTag::tts) return "tts";
			if (tag == XMLTag::ttm) return "ttm";
			// Text tags
			if (tag == XMLTag::font_family) return "fontFamily";
			if (tag == XMLTag::font_size) return "fontSize";
			if (tag == XMLTag::text_align) return "textAlign";
			// Media tags
			if (tag == XMLTag::display_align) return "displayAlign";
			if (tag == XMLTag::frame_rate) return "frameRate";
			if (tag == XMLTag::origin) return "origin";
			if (tag == XMLTag::time_base) return "timeBase";
			return "";
		}

		std::string GetXMLUrlText(const XMLUrl& url)
		{
			if (url == XMLUrl::w3_ns_xml) return "http://www.w3.org/XML/1998/namespace";
			if (url == XMLUrl::w3_ns_ttml) return "http://www.w3.org/ns/ttml";
			if (url == XMLUrl::w3_ns_ttml_styling) return "http://www.w3.org/ns/ttml#styling";
			if (url == XMLUrl::w3_ns_ttml_parameter) return "http://www.w3.org/ns/ttml#parameter";
			if (url == XMLUrl::w3_ns_ttml_metadata) return "http://www.w3.org/ns/ttml#metadata";
			return "";
		}
	}
}