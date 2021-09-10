// Stefan "SoulXP" Olivier
// File: ttml.hpp
// Description: TTML object declarations and templates

#ifndef VTTTML_HEADER
#define VTTTML_HEADER

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "../config.hpp"
#endif

// Standard headers
#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include <string_view>
#include <memory>

// Library headers
#include <libxml++/libxml++.h>

// Generic Document Parser ---------------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

namespace vt::prototype::utility
{
    class DocumentParser
    {
    public:
        using engine_t = xmlpp::DomParser;
        using parser_t = DocumentParser<engine_t>;
        using nodeptr_t = std::unique_ptr<xmlpp::Node>;
        using elementptr_t = std::unique_ptr<xmlpp::Element>;

        // Constructors and operators
        DocumentParser() = delete;
        DocumentParser(const parser_t& _parser);
        DocumentParser(parser_t&& _parser) noexcept;
        parser_t& operator=(const parser_t& _parser);
        parser_t& operator=(parser_t&& _parser) noexcept;

        // User interfaces
        virtual void Parse() = 0;
        virtual void Parse(const std::string_view& path) = 0;

    private:
        engine_t parser_engine;
    };
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// XML Abstract Class ---------------------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

namespace vt::prototype::xml
{
    template<class Tparser>
    class XMLObject
    {
    public:
        XMLFile();
        explicit XMLFile(const std::string_view& path);
        ~XMLFile();

        virtual void PrintNodes();
        virtual void WriteFile(const std::string_view& path);

    protected:
        virtual void Parse();
        virtual void TraverseDocument(xmlpp::Node* node);
        virtual void ConfigureDocument() = 0;

        bool IsUniqueId(const std::string_view& id) noexcept;
        std::string_view IndexNewId(const std::string_view& prefix, size_t start = 0) noexcept;
        void AddNewId(const std::string& id, const std::shared_ptr<xmlpp::Element*>& element) noexcept;
        std::shared_ptr<xmlpp::Element*> GetIdNode(const std::string_view& id) noexcept;

        bool xmlfile_isvalid;
        xmlpp::DomParser xmlfile_dom;
        std::unique_ptr<xmlpp::Node> xmlfile_root;
        XMLProfile xmlfile_profile;
        std::map<std::string_view, std::shared_ptr<xmlpp::Element*>> xmlfile_ids;
    };
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

// TTML Template Objects -----------------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

namespace vt::prototype::ttml
{
    class TimedTextContainer
    {
    public:
        // Constructors and operators
        constexpr TimedTextContainer() = delete;
        constexpr TimedTextContainer(const TimedTextContainer& _container);
        constexpr TimedTextContainer(TimedTextContainer&& _container) noexcept;
        constexpr TimedTextContainer operator=(const TimedTextContainer& _container);
        constexpr TimedTextContainer operator=(TimedTextContainer&& _container) noexcept;

        // Path constructor
        TimedTextContainer(const std::string_view& path);

    private:
        
    };
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif // VTTTML_HEADER