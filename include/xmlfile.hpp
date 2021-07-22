// Stefan "SoulXP" Olivier
// File: xmlfile.hpp
// Description: Wrapper objects for libxmlpp to be used with edltools

#ifndef XMLFILE_HEADER
#define XMLFILE_HEADER

// Standard headers
#include <iostream>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <memory>

// Library headers
#include <libxml++/libxml++.h>
#include <magic_enum.hpp>

// Project headers
#include "filesink.hpp"
#include "helpers.hpp"
#include "edlfile.hpp"
#include "node.hpp"

// Aliases
using namespace vt::xml;
using XMLProfile = vt::xml::XMLProfile;

// XmlFile declaration -------------------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

struct XMLFile : public FileSink
{
public:
    XMLFile();
    explicit XMLFile(const std::string& path);
    ~XMLFile();

    virtual void PrintNodes();
    virtual void WriteFile(const std::string& path);

protected:
    virtual void Parse();
    virtual void TraverseDocument(xmlpp::Node* node);
    virtual void ConfigureDocument() = 0;

    bool IsUniqueId(const std::string& id) noexcept;
    std::string IndexNewId(const std::string& prefix, size_t start = 0) noexcept;
    void AddNewId(const std::string& id, const std::shared_ptr<xmlpp::Element*>& element) noexcept;
    std::shared_ptr<xmlpp::Element*> GetIdNode(const std::string& id) noexcept;

    bool xmlfile_isvalid;
    xmlpp::DomParser xmlfile_dom;
    xmlpp::Node* xmlfile_root;
    XMLProfile xmlfile_profile;
    std::map<std::string, std::shared_ptr<xmlpp::Element*>> xmlfile_ids;
};

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// TTML1 Netflix object declarations -----------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

typedef
struct TTML1p0_Netflix : public XMLFile
{
public:
    using XMLNode = vt::format::XMLNode;
    using XMLHeadFlags = vt::xml::TTML1p0_Head_Flags;
    TTML1p0_Netflix();
    explicit TTML1p0_Netflix(const std::string& path);
    ~TTML1p0_Netflix();

    void AddMetadata(const XMLNode& node) noexcept;
    void AddStyling(const XMLNode& node) noexcept;
    void AddLayout(const XMLNode& node) noexcept;
    void AddSubtitle(std::vector<std::map<std::string, std::string>>& subtitle_data) noexcept;
    void operator<<(EDLFilePTX& edl_file) noexcept; // TODO: Make this more generic

private:
    enum class StyleNodePresets
    {
        subtitle_default, region_default 
    };

public:
    XMLNode CreatePresetNode(const StyleNodePresets& preset);

private:
    xmlpp::Element* GetHeadData(const XMLHeadFlags& flag, const std::string& id);
    xmlpp::Element* AddNode(xmlpp::Element* parent, const XMLNode& node);
    void SetNode(xmlpp::Element* parent, const XMLNode& node);
    void VerifyNodes(const uint16_t flags) noexcept;
    bool IsValidNodes(const uint16_t flags) noexcept;
    void ConfigureDocument();

    // TODO: size_t ttml_flags;
    uint32_t ttml_framerate;
    xmlpp::Element* ttml_head;
    xmlpp::Element* ttml_body;
    std::vector<std::shared_ptr<xmlpp::ContentNode>> ttml_subtitles;

    struct {
        bool has_root;
        bool has_head;
        bool has_body;
        bool has_layout;
        bool has_metadata;
        bool has_parameter;
        bool has_styling;
    } ttml_verified_nodes;

    struct {
        using ttmlhead_t = std::map< std::string, std::shared_ptr<xmlpp::Element*> >;
        ttmlhead_t layout;
        ttmlhead_t metadata;
        ttmlhead_t parameter;
        ttmlhead_t styling;
    } ttml_head_data;

    inline xmlpp::Element* GetHeadNode(const XMLTag& tag, const XMLTag ns = XMLTag::none) noexcept
    {
        using namespace vt::xml;
        uint16_t flags = 0x0000;
        switch (tag) {
            case XMLTag::tt:        flags = 0x0001;      break;
            case XMLTag::head:      flags = 0x0002;      break;
            case XMLTag::body:      flags = 0x0004;      break;
            case XMLTag::layout:    flags = 0x0008;      break;
            case XMLTag::metadata:  flags = 0x0010;      break;
            case XMLTag::parameter: flags = 0x0020;      break;
            case XMLTag::styling:   flags = 0x0040;      break;
            default:                                     break;
        }

        const auto tag_string = GetXMLTagText(tag);
        const auto ns_string = GetXMLTagText(ns);

        if (!this->IsValidNodes(flags)) {
            XMLNode styling(std::make_pair(ns_string, tag_string), {}, "");
            return this->AddNode(this->ttml_head, styling);
        } else {
            return static_cast<xmlpp::Element*>(this->ttml_head->get_first_child(tag_string));
        }
    }

} TTML1P0_NETFLIX;

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif
