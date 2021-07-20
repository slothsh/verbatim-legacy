// Stefan "SoulXP" Olivier
// File: xmlfile.cpp
// Description: Source code for wrapper objects for libxmlpp to be used with edltools

// Standard headers
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cassert>
#include <cstdint>
#include <unordered_map>
#include <optional>
#include <memory>
#include <utility>
#include <array>
#include <algorithm>
#include <numeric>

// Library headers
#include <libxml++/libxml++.h>

// Project headers
#include "../include/xmlfile.hpp"
#include "../include/helpers.hpp"
#include "../include/edlfile.hpp"

// Aliases
using namespace Helpers;
using XMLProfile = Helpers::XML::XMLProfile;

// XmlFile declaration -------------------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

XMLFile::XMLFile()
  : xmlfile_dom(),
  xmlfile_root(nullptr),
  xmlfile_profile(XMLProfile::none),
  xmlfile_isvalid(false)
{
}

XMLFile::XMLFile(const std::string& path)
  : FileSink(path)
{
  if (this->filesink_raw) this->ValidateFile();
}

XMLFile::~XMLFile()
{
}

void XMLFile::Parse()
{
  this->xmlfile_dom.parse_memory_raw(this->filesink_raw, this->filesink_length);
  if (this->xmlfile_dom.get_document()->get_root_node()) {
    xmlfile_isvalid = true;
    this->xmlfile_root = this->xmlfile_dom.get_document()->get_root_node();
    // TODO: Use xmlpp XsdValidator to validate
  } else {
    this->xmlfile_root = nullptr;
    throw std::invalid_argument("Could not create DOM\n");
  }
}

void XMLFile::TraverseDocument(xmlpp::Node* node)
{
  // TODO: Make this more generic
  if (node->get_name() == "text" && static_cast<xmlpp::TextNode*>(node)->get_content()[0] != '\n') {
    std::cout << node->get_parent()->get_name() << ": " << static_cast<xmlpp::TextNode*>(node)->get_content() << '\n';
  }
  if (node->get_first_child()) {
    this->TraverseDocument(node->get_first_child());
  }
  if (node->get_next_sibling()) {
    this->TraverseDocument(node->get_next_sibling());
  }
}

void XMLFile::PrintNodes()
{
    this->TraverseDocument(this->xmlfile_dom.get_document()->get_root_node());
}

void XMLFile::WriteFile(const std::string& path)
{
    // Validate output path
    this->xmlfile_dom.get_document()->write_to_file_formatted(path); // TODO: Set encoding according to system or pass in as argument
}

bool XMLFile::IsUniqueId(const std::string& id) noexcept
{
  // TODO
  if (this->xmlfile_ids.size() > 0) {
    std::vector<std::string> xml_ids;
    xml_ids.reserve(this->xmlfile_ids.size());

    const auto& operation = [](const auto& a) {
      return a.first;
    };

    std::transform(this->xmlfile_ids.begin(), this->xmlfile_ids.end(), std::back_inserter(xml_ids), operation);
    std::sort(xml_ids.begin(), xml_ids.end());

    return !std::binary_search(xml_ids.begin(), xml_ids.end(), id);
  }
  return true;
}

std::string XMLFile::IndexNewId(const std::string& prefix, size_t start) noexcept
{
  while (!this->IsUniqueId(prefix + std::to_string(++start)));
  return prefix + std::to_string(start);
}

void XMLFile::AddNewId(const std::string& id, const std::shared_ptr<xmlpp::Element*>& element) noexcept
{
  if (this->IsUniqueId(id)) this->xmlfile_ids[id] = element;
  else {
    std::cerr << "XML id of " << id << " is not unique\n";
  }
}

std::shared_ptr<xmlpp::Element*> XMLFile::GetIdNode(const std::string& id) noexcept
{
  return this->xmlfile_ids[id];
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// TTML1 Netflix object declarations -----------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

TTML1p0_Netflix::TTML1p0_Netflix()
  : ttml_head(nullptr),
  ttml_body(nullptr),
  ttml_framerate(25), // TODO: Globals for media format
  ttml_subtitles({}),
  ttml_verified_nodes({false, false, false, false, false, false, false}),
  ttml_head_data({})
{
  this->xmlfile_profile = XMLProfile::ttml_1p0_netflix;
  this->ConfigureDocument();
}

TTML1p0_Netflix::TTML1p0_Netflix(const std::string& path)
  : XMLFile(path)
{
  if (this->isValidFile()) {
    xmlpp::XsdValidator xsd;
    xsd.parse_file("./resources/xml/schema/ttml1.xsd"); // TODO: Pass in as argument or default to no validation
    xsd.validate(this->xmlfile_dom.get_document());
  }
}

TTML1p0_Netflix::~TTML1p0_Netflix()
{
}

void TTML1p0_Netflix::AddMetadata(const XMLNode& node) noexcept
{
  // Create valid metadata tags according TTML1 spec
  using namespace Helpers::XML;
  const auto tag_agent = GetXMLTagText(XMLTag::agent);
  const auto tag_copyright = GetXMLTagText(XMLTag::copyright);
  const auto tag_desc = GetXMLTagText(XMLTag::desc);
  const auto tag_metadata = GetXMLTagText(XMLTag::metadata);
  const auto tag_title = GetXMLTagText(XMLTag::title);
  const auto tag_ttm = GetXMLTagText(XMLTag::ttm);

  try {
    // Check if metadata tag exists
    xmlpp::Element* metadata_node = this->GetHeadNode(XMLTag::metadata);

    // Add metadata node or set it
    const auto& VerifyInternalNode = [&](
      const XMLNode& node
    )
    -> bool
    {
      // Tag specific tasks
      switch (Helpers::XML::GetXMLTag(node.tag.second)) {
        case XMLTag::agent:
          // TODO
          return true;

        case XMLTag::copyright:
          // TODO
          return true;

        case XMLTag::desc:
          // TODO
          return true;

        case XMLTag::title:
          // TODO
          return true;

        default:
          return false;
      }
    };

    const auto& CreateInternalNode = [&]()
    -> std::optional<xmlpp::Element*>
    {
      if (!VerifyInternalNode(node)) return nullptr;
      xmlpp::Element* current_node = nullptr;
        if (metadata_node->get_first_child(node.tag.second)) {
          current_node = static_cast<xmlpp::Element*>(metadata_node->get_first_child(node.tag.second));
          this->SetNode(current_node, node);
        } else {
          this->ttml_head_data.metadata[node.tag.second] = std::make_shared<xmlpp::Element*>(this->AddNode(metadata_node, node));
        }
        return current_node;
    };

    // Create and validate node
    if (!CreateInternalNode()) throw std::logic_error("Could not add metadata to document head\n");
    using XMLHeadFlags = Helpers::XML::TTML1p0_Head_Flags;
    this->VerifyNodes(XMLHeadFlags::metadata);
  }
  catch(const std::exception& e) {
    std::cerr << e.what();
    // TODO: Clean up
  }
}

void TTML1p0_Netflix::AddStyling(const XMLNode& node) noexcept
{
  // Create valid styling tags according TTML1 spec
  using namespace Helpers::XML;
  const auto tag_id = GetXMLTagText(XMLTag::id);
  const auto tag_xml = GetXMLTagText(XMLTag::xml);
  const auto tag_style = GetXMLTagText(XMLTag::style);
  const auto tag_styling = GetXMLTagText(XMLTag::styling);

  try {
    // Check if styling tag exists
    xmlpp::Element* styling_node = this->GetHeadNode(XMLTag::styling);

    // Add styling node or set it
    const auto& VerifyInternalNode = [&](
      const XMLNode& node
    )
    -> bool
    {
      // Tag specific tasks
      switch (Helpers::XML::GetXMLTag(node.tag.second)) {
        case XMLTag::styling: {
          // TODO
          return true;
        }

        case XMLTag::style: {
          // Check node for style id
          auto& n = const_cast<XMLNode&>(node);
          std::string new_style_id = "style";
          if (!node.GetNodeId()) {
            uint32_t new_id_num = 0;
            while (!this->IsUniqueId(new_style_id + std::to_string(++new_id_num)));
            new_style_id += std::to_string(new_id_num);
            n.attributes.emplace_back(std::make_tuple(tag_xml, tag_id, new_style_id));
          }

          return true;
        }

        default: {
          return false;
        }
      }
    };

    const auto& CreateInternalNode = [&]()
    -> std::optional<std::shared_ptr<xmlpp::Element*>>
    {
      if (!VerifyInternalNode(node)) return {};
        std::shared_ptr<xmlpp::Element*> current_node = {};
        const auto& [ ns, element, attribute ] = node.GetNodeId()->get();
        if (!this->IsUniqueId(attribute)) {
          current_node = this->GetIdNode(attribute);
          this->SetNode(*current_node, node);
        } else {
          this->ttml_head_data.styling[node.tag.second] = std::make_shared<xmlpp::Element*>(this->AddNode(styling_node, node));
          this->AddNewId(attribute, this->ttml_head_data.styling[node.tag.second]);
        }
        return current_node;
    };

    // Create and validate node
    if (!CreateInternalNode()) throw std::logic_error("Could not add styling to document head\n");
    using XMLHeadFlags = Helpers::XML::TTML1p0_Head_Flags;
    this->VerifyNodes(XMLHeadFlags::styling);
  }
  catch (const std::exception& e) {
    std::cerr << e.what();
    // TODO: Clean up
  }
}

void TTML1p0_Netflix::AddLayout(const XMLNode& node) noexcept
{
  // Create valid styling tags according TTML1 spec
  using namespace Helpers::XML;
  const auto tag_id = GetXMLTagText(XMLTag::id);
  const auto tag_xml = GetXMLTagText(XMLTag::xml);
  const auto tag_layout = GetXMLTagText(XMLTag::layout);
  const auto tag_region = GetXMLTagText(XMLTag::region);

  try {
    // Check if styling tag exists
    xmlpp::Element* layout_node = this->GetHeadNode(XMLTag::layout);

    // Add styling node or set it
    const auto& VerifyInternalNode = [&](
      const XMLNode& node
    )
    -> bool
    {
      // Tag specific tasks
      switch (Helpers::XML::GetXMLTag(node.tag.second)) {
        case XMLTag::layout: {
          // TODO
          return true;
        }

        case XMLTag::region: {
          auto& n = const_cast<XMLNode&>(node);
          std::string new_region_id = "region";
          if (!node.GetNodeId()) {
            uint32_t new_id_num = 0;
            while (!this->IsUniqueId(new_region_id + std::to_string(++new_id_num)));
            new_region_id += std::to_string(new_id_num);
            n.attributes.emplace_back(std::make_tuple(tag_xml, tag_id, new_region_id));
          }
          return true;
        }

        default: {
          return false;
        }
      }
    };

    const auto& CreateInternalNode = [&]()
    -> std::optional<std::shared_ptr<xmlpp::Element*>>
    {
      if (!VerifyInternalNode(node)) return {};
        std::shared_ptr<xmlpp::Element*> current_node = {};
        const auto& [ ns, element, attribute ] = node.GetNodeId()->get();
        if (!this->IsUniqueId(attribute)) {
          current_node = this->GetIdNode(attribute);
          this->SetNode(*current_node, node);
        } else {
          this->ttml_head_data.layout[node.tag.second] = std::make_shared<xmlpp::Element*>(this->AddNode(layout_node, node));
          this->AddNewId(attribute, this->ttml_head_data.layout[node.tag.second]);
        }
        return current_node;
    };

    // Create and validate node
    if (!CreateInternalNode()) throw std::logic_error("Could not add layout to document head\n");
    using XMLHeadFlags = Helpers::XML::TTML1p0_Head_Flags;
    this->VerifyNodes(XMLHeadFlags::layout);
  }
  catch (const std::exception& e) {
    std::cerr << e.what();
    // TODO: Clean up
  }
}

xmlpp::Element* TTML1p0_Netflix::GetHeadData(const XMLHeadFlags& flag, const std::string& id)
{
  switch (flag) {
    case 0x0008:
      return *this->ttml_head_data.layout[id];
    case 0x0010:
      return *this->ttml_head_data.metadata[id];
    case 0x0020:
      return *this->ttml_head_data.parameter[id];
    case 0x0040:
      return *this->ttml_head_data.styling[id];
    default:
      throw std::logic_error("Invalid TTML1 Netlflix flag\n");
  }
}

void TTML1p0_Netflix::VerifyNodes(const uint16_t flags) noexcept
{
  // TODO: Better verification of nodes
  using namespace Helpers::XML;
  for (uint16_t bit = 0x0001; bit != 0x0000; bit <<= 0x0001) {
    switch (flags & bit) {
      case 0x0001: {
        this->ttml_verified_nodes.has_root = 
          (this->xmlfile_root)
            ? true
            : false;
        break;
      }

      case 0x0002: {
        this->ttml_verified_nodes.has_head = 
          (this->ttml_head)
            ? true
            : false;
        break;
      }

      case 0x0004: {
        this->ttml_verified_nodes.has_body = 
          (this->ttml_body)
            ? true
            : false;
        break;
      }

      case 0x0008: {
        this->ttml_verified_nodes.has_layout = 
          (this->ttml_head->get_first_child(GetXMLTagText(XMLTag::layout)))
            ? true
            : false;
        break;
      }

      case 0x0010: {
        this->ttml_verified_nodes.has_metadata = 
          (this->ttml_head->get_first_child(GetXMLTagText(XMLTag::metadata)))
            ? true
            : false;
        break;
      }

      case 0x0020: {
        this->ttml_verified_nodes.has_parameter = 
          (this->ttml_head->get_first_child(GetXMLTagText(XMLTag::parameter)))
            ? true
            : false;
        break;
      }

      case 0x0040: {
        this->ttml_verified_nodes.has_styling = 
          (this->ttml_head->get_first_child(GetXMLTagText(XMLTag::styling)))
            ? true
            : false;
        break;
      }
    }
  }
}

bool TTML1p0_Netflix::IsValidNodes(const uint16_t flags) noexcept
{
  // TODO: Better verification of nodes
  bool nodes_are_valid = true;
  using namespace Helpers::XML;
  for (uint16_t bit = 0x0001; bit != 0x0000; bit <<= 0x0001) {
    switch (flags & bit) {
      case 0x0001: {
          nodes_are_valid = nodes_are_valid && this->ttml_verified_nodes.has_root;
        break;
      }

      case 0x0002: {
        nodes_are_valid = nodes_are_valid && this->ttml_verified_nodes.has_head;
        break;
      }

      case 0x0004: {
        nodes_are_valid = nodes_are_valid && this->ttml_verified_nodes.has_body;
        break;
      }

      case 0x0008: {
        nodes_are_valid = nodes_are_valid
          && (this->ttml_head->get_first_child(GetXMLTagText(XMLTag::layout))) ? true : false;
        break;
      }

      case 0x0010: {
        nodes_are_valid = nodes_are_valid
          && (this->ttml_head->get_first_child(GetXMLTagText(XMLTag::metadata))) ? true : false;
        break;
      }

      case 0x0020: {
        nodes_are_valid = nodes_are_valid
          && (this->ttml_head->get_first_child(GetXMLTagText(XMLTag::parameter))) ? true : false;
        break;
      }

      case 0x0040: {
        nodes_are_valid = nodes_are_valid
          && (this->ttml_head->get_first_child(GetXMLTagText(XMLTag::styling))) ? true : false;
        break;
      }

      default: {
        return false;
      }
    }
  }

  return nodes_are_valid;
}

void TTML1p0_Netflix::AddSubtitle(std::vector<std::map<std::string, std::string>>& subtitle_data) noexcept
{
  using namespace Helpers::XML;
  const auto tag_id = GetXMLTagText(XMLTag::id);
  const auto tag_div = GetXMLTagText(XMLTag::div);
  const auto tag_begin = GetXMLTagText(XMLTag::begin);
  const auto tag_end = GetXMLTagText(XMLTag::end);
  const auto tag_p = GetXMLTagText(XMLTag::paragraph);
  const auto tag_style = GetXMLTagText(XMLTag::style);
  const auto tag_region = GetXMLTagText(XMLTag::region);
  const auto tag_xml = GetXMLTagText(XMLTag::xml);

  // Check if TTML file is configured
  if (!this->xmlfile_isvalid) this->ConfigureDocument();

  xmlpp::Element* div;
  if (this->ttml_body->get_first_child()) {
    div = static_cast<xmlpp::Element*>(this->ttml_body->get_first_child());
  } else {
    div = this->ttml_body->add_child_element(tag_div);
  }

  // Sort data
  std::sort(subtitle_data.begin(), subtitle_data.end()); // TODO: Provide sorting options

  // Add subtitle nodes to DOM
  for (auto data : subtitle_data) {
    const auto& subtitle = div->add_child_element(tag_p);
    const auto subitle_id = this->IndexNewId("subtitle");
    subtitle->set_attribute(tag_id, subitle_id, tag_xml);  // TODO: Check if namespace is declared

    if (!this->IsUniqueId("style1")) subtitle->set_attribute(tag_style, "style1"); // TODO: Check if exists in head & determine which style to use
    else {
      try {
        XMLNode subtitle_style = this->CreatePresetNode(StyleNodePresets::subtitle_default);
        this->AddStyling(subtitle_style);
        const auto& [ ns, attribute, value ] = subtitle_style.GetNodeId()->get();
        subtitle->set_attribute(tag_style, value);
      } catch (const std::exception& e) {
        std::cerr << e.what();
      }
    }

    if (!this->IsUniqueId("region1")) subtitle->set_attribute(tag_region, "region1");  // TODO: Check if exists in head & determine which region to use
    else {
      try {
        XMLNode subtitle_region = this->CreatePresetNode(StyleNodePresets::region_default);
        this->AddLayout(subtitle_region);
        const auto& [ ns, attribute, value ] = subtitle_region.GetNodeId()->get();
        subtitle->set_attribute(tag_region, value);
      } catch (const std::exception& e) {
        std::cerr << e.what();
      }
    }

    if (data.contains("start")) subtitle->set_attribute(tag_begin, data["start"]);
    if (data.contains("end")) subtitle->set_attribute(tag_end, data["end"]);
    if (data.contains("text")) subtitle->add_child_text(data["text"]);

    // Register subtitle with ID container
    this->AddNewId(subitle_id, std::make_shared<xmlpp::Element*>(subtitle));
  }
}

Format::XMLNode TTML1p0_Netflix::CreatePresetNode(const TTML1p0_Netflix::StyleNodePresets& preset)
{
  using namespace Helpers::XML;
  using namespace Helpers::Format;
  using XMLNode = Helpers::Format::XMLNode;
  using preset_t = TTML1p0_Netflix::StyleNodePresets;

  const auto tag_id = GetXMLTagText(XMLTag::id);
  const auto tag_xml = GetXMLTagText(XMLTag::xml);
  const auto tag_tts = GetXMLTagText(XMLTag::tts);
  const auto tag_style = GetXMLTagText(XMLTag::style);
  const auto tag_region = GetXMLTagText(XMLTag::region);
  const auto tag_fontfamily = GetXMLTagText(XMLTag::font_family);
  const auto tag_fontsize = GetXMLTagText(XMLTag::font_size);
  const auto tag_textalign = GetXMLTagText(XMLTag::text_align);
  const auto tag_extent = GetXMLTagText(XMLTag::extent);
  const auto tag_origin = GetXMLTagText(XMLTag::origin);
  const auto tag_displayalign = GetXMLTagText(XMLTag::display_align);
  const auto tag_color = GetXMLTagText(XMLTag::color);

  switch (preset) {
    case preset_t::subtitle_default: {
      std::vector attributes = { 
        CreateAttributeType(tag_id, this->IndexNewId("style"), tag_xml),
        CreateAttributeType(tag_fontfamily, "Arial", tag_tts),
        CreateAttributeType(tag_fontsize, "12px", tag_tts),
        CreateAttributeType(tag_textalign, "left", tag_tts),
      };

      return Format::XMLNodeFactory(tag_style, attributes);
    }

    case preset_t::region_default: {
      std::vector attributes = { 
        CreateAttributeType(tag_id, this->IndexNewId("region"), tag_xml),
        CreateAttributeType(tag_displayalign, "after", tag_tts),
        CreateAttributeType(tag_extent, "80% 40%", tag_tts),
        CreateAttributeType(tag_origin, "10% 50%", tag_tts)
      };

      return Format::XMLNodeFactory(tag_region, attributes);
    }

    default: {
      throw std::invalid_argument("Invalid preset for new TTML1.0 Netflix style\n");
    }
  }
}

xmlpp::Element* TTML1p0_Netflix::AddNode(xmlpp::Element* parent, const XMLNode& node)
{
  // TODO: Make this an inline/member function
  if (!this->ttml_head && parent) {
    throw std::logic_error("Could not add node\n");
  }

  const auto& new_node = parent->add_child_element(node.tag.second);
  if (node.text != "") new_node->add_child_text(node.text); // TODO: Conditional set
  if (node.tag.first != "") new_node->set_namespace(node.tag.first);
  for (const auto& attribute : node.attributes) {
    const auto& [ ns, tag, value ] = attribute;
    if (tag != "") new_node->set_attribute(tag, value, ns); // TODO: Function to validate attribute
  }

  return new_node;
}

void TTML1p0_Netflix::SetNode(xmlpp::Element* parent, const XMLNode& node)
{
  // TODO: Make this an inline/member function
  if (!this->ttml_head && parent) {
    throw std::logic_error("Could not modify node\n");
  }

  parent->set_first_child_text(node.text);
  if (node.tag.first != "") parent->set_namespace(node.tag.first);
  for (const auto& attribute : node.attributes) {
    const auto& [ ns, tag, value ] = attribute;
    if (tag != "") parent->set_attribute(tag, value, ns); // TODO: Function to validate attribute
  }
}

void TTML1p0_Netflix::ConfigureDocument()
{
  // Clean up first
  if (this->filesink_raw) this->Purge();

  using namespace Helpers::XML;
  this->xmlfile_profile = XMLProfile::ttml_1p0_netflix;

  // Declare root namespaces for TTML 1.1 Netflix profile
  const auto url_nsttml = GetXMLUrlText(XMLUrl::w3_ns_ttml);
  const auto url_nsparameter = GetXMLUrlText(XMLUrl::w3_ns_ttml_parameter);
  const auto url_nstyling = GetXMLUrlText(XMLUrl::w3_ns_ttml_styling);
  const auto url_nsmetadata = GetXMLUrlText(XMLUrl::w3_ns_ttml_metadata);
  const auto url_nsxml = GetXMLUrlText(XMLUrl::w3_ns_xml);

  const auto tag_tt = GetXMLTagText(XMLTag::tt);
  const auto tag_ttp = GetXMLTagText(XMLTag::ttp);
  const auto tag_tts = GetXMLTagText(XMLTag::tts);
  const auto tag_ttm = GetXMLTagText(XMLTag::ttm);
  const auto tag_xml = GetXMLTagText(XMLTag::xml);
  const auto tag_media = GetXMLTagText(XMLTag::media);
  const auto tag_metadata = GetXMLTagText(XMLTag::metadata);
  const auto tag_en = GetXMLTagText(XMLTag::en);
  const auto tag_lang = GetXMLTagText(XMLTag::lang);
  const auto tag_head = GetXMLTagText(XMLTag::head);
  const auto tag_body = GetXMLTagText(XMLTag::body);
  const auto tag_time_base = GetXMLTagText(XMLTag::time_base);
  const auto tag_title = GetXMLTagText(XMLTag::title);
  const auto tag_frame_rate = GetXMLTagText(XMLTag::frame_rate);

  const auto& root = this->xmlfile_dom.get_document()->create_root_node(tag_tt);
  root->set_namespace_declaration(url_nsttml);
  root->set_namespace_declaration(url_nsparameter, tag_ttp);
  root->set_namespace_declaration(url_nstyling, tag_tts);
  root->set_namespace_declaration(url_nsmetadata, tag_ttm);
  root->set_namespace_declaration(url_nsxml, tag_xml);

  // Set attributes for root node
  root->set_attribute(tag_time_base, tag_media, tag_ttp);
  root->set_attribute(tag_frame_rate, std::to_string(this->ttml_framerate), tag_ttp);
  root->set_attribute(tag_lang, tag_en, tag_xml);

  // Header
  const auto& head = root->add_child_element(tag_head);
  
  // Body
  const auto& body = root->add_child_element(tag_body);

  // Store pointers to key nodes
  this->xmlfile_root = root;
  this->ttml_head = head;
  this->ttml_body = body;

  // Set flags
  this->xmlfile_isvalid = true;
  this->ttml_verified_nodes.has_root = true;
  this->ttml_verified_nodes.has_head = true;
  this->ttml_verified_nodes.has_body = true;
}

void TTML1p0_Netflix::operator<<(EDLFilePTX& edl_file) noexcept
{
  // XML tags
  using namespace Helpers::XML;
  const auto tag_ttp = GetXMLTagText(XMLTag::ttp);
  const auto tag_framerate = GetXMLTagText(XMLTag::frame_rate);

  std::vector<std::map<std::string, std::string>> subtitles;
  subtitles.reserve(edl_file.TotalAudioTracks());

  // Set global TTML document settings
  this->ttml_framerate = std::stoi(edl_file.FrameRate());
  static_cast<xmlpp::Element*>(this->xmlfile_root)->set_attribute(tag_framerate, edl_file.FrameRate(), tag_ttp);

  // Move this function into a namespace for general purpose use
  const auto MakeTimecode = [this](
		std::string timecode)
	-> std::string
	{
		std::string ms = std::to_string(
			(std::stod(timecode.substr(9,10)) * this->ttml_framerate) / 1000.0 // TODO: Figure out frame-rate
		);
		ms.erase(0,2);
		ms.erase(3);

		return timecode.replace(8, 3, ('.' + ms));
	};

  edl_file.ForEach([&](PTXTrack track, size_t track_index) {
    track.ForEach(0, [&](PTXTrackData data, size_t data_index) {
      std::map<std::string, std::string> subtitle;
      subtitle["start"] = MakeTimecode(data.timecode["start"]);
      subtitle["end"] = MakeTimecode(data.timecode["end"]);
      subtitle["text"] = data.clip_name;
      subtitles.push_back(subtitle);
    });
  });

  this->AddSubtitle(subtitles);
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|