// Stefan "SoulXP" Olivier
// File: versions.hpp
// Description: Macros and structures for various document versioning

#ifndef VERSIONS_HEADER
#define VERSIONS_HEADER

// Document version macros ---------------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

// No version
#define VER_NONE            0ull

// W3C spec TTML documents
#define VER_TTML1           1ull
#define VER_TTML2           2ull
#define VER_TTML3           4ull

// Proprietary TTML
#define VER_TTML1_SMPTETT   8ull
#define VER_TTML1_EBUDD     16ull

// W3C spec IMSC documents
#define VER_IMSC1           32ull
#define VER_IMSC11          64ull

// ------------------------------------------------------------|END|-----------------------------------------------------------|


// Macros for enums and structures -------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

// Pre-processor items
#define MAKE_ENUM(ITEM) ITEM,

#define CREATE_NSTAG_ITEMS(FN)          \
    FN(undefined)                       \
    FN(xml)                             \
    FN(xmlns)                           \
    FN(tt)                              \
    FN(ttp)                             \
    FN(tts)                             \
    FN(ttm)                             \
    FN(smpte)                           \
    FN(ebu)                             \

#define CREATE_NODETAG_ITEMS(FN)        \
    FN(undefined)                       \
    FN(tt)                              \
    FN(set)                             \
    FN(body)                            \
    FN(div)                             \
    FN(p)                               \
    FN(span)                            \
    FN(br)                              \
    FN(head)                            \
    FN(layout)                          \
    FN(metadata)                        \
    FN(styling)                         \
    FN(style)                           \
    FN(region)                          \
    FN(begin)                           \
    FN(dur)                             \
    FN(end)                             \
    FN(actor)                           \
    FN(agent)                           \
    FN(copyright)                       \
    FN(desc)                            \
    FN(name)                            \
    FN(title)                           \
    FN(role)                            \
    FN(profile)                         \
    FN(features)                        \
    FN(feature)                         \
    FN(extensions)                      \
    FN(extension)                       \

#define CREATE_ATTRTAG_ITEMS(FN)        \
    FN(undefined)                       \
    FN(id)                              \
    FN(lang)                            \
    FN(space)                           \
    FN(base)                            \
    FN(tt)                              \
    FN(ttm)                             \
    FN(ttp)                             \
    FN(tts)                             \
    FN(value)                           \
    FN(type)                            \
    FN(style)                           \
    FN(region)                          \
    FN(begin)                           \
    FN(dur)                             \
    FN(end)                             \
    FN(timeContainer)                   \
    FN(actor)                           \
    FN(agent)                           \
    FN(name)                            \
    FN(title)                           \
    FN(role)                            \
    FN(profile)                         \
    FN(features)                        \
    FN(feature)                         \
    FN(extensions)                      \
    FN(extension)                       \
    FN(backgroundColor)                 \
    FN(color)                           \
    FN(direction)                       \
    FN(display)                         \
    FN(displayAlign)                    \
    FN(extent)                          \
    FN(fontFamily)                      \
    FN(fontSize)                        \
    FN(fontStyle)                       \
    FN(fontWeight)                      \
    FN(lineHeight)                      \
    FN(opacity)                         \
    FN(origin)                          \
    FN(overflow)                        \
    FN(padding)                         \
    FN(showBackground)                  \
    FN(textAlign)                       \
    FN(textDecoration)                  \
    FN(textOutline)                     \
    FN(unicodeBidi)                     \
    FN(visibility)                      \
    FN(wrapOption)                      \
    FN(writingMode)                     \
    FN(zIndex)                          \
    FN(cellResolution)                  \
    FN(clockMode)                       \
    FN(dropMode)                        \
    FN(frameRate)                       \
    FN(frameRateMultiplier)             \
    FN(markerMode)                      \
    FN(pixelAspectRatio)                \
    FN(subFrameRate)                    \
    FN(tickRate)                        \
    FN(timeBase)                        \
    FN(use)                             \
    
// ------------------------------------------------------------|END|-----------------------------------------------------------|

// XML versioning structures -------------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

namespace Helpers
{
    namespace XML
    {
        enum class NSTag
        {
            CREATE_NSTAG_ITEMS(MAKE_ENUM)
            none
        };

        enum class NodeTag
        {
            CREATE_NODETAG_ITEMS(MAKE_ENUM)
            none
        };

        enum class AttrTag
        {
            CREATE_ATTRTAG_ITEMS(MAKE_ENUM)
            none
        };

        typedef
        struct _NSTagID
        {
            NSTag               ns;
            std::string_view    ns_name;
        } NSTagID;

        typedef
        struct _NodeTagID
        {
            NSTag               ns;
            NodeTag             tag;
            std::string_view    name;
        } NodeTagID;

        typedef
        struct _AttrTagID
        {
            NSTag               ns;
            AttrTag             attribute;
            std::string_view    name;
        } AttrTagID;

        typedef
        struct _NSTagVersion
        {
            NSTagID            ns;
            size_t             versions;
        } NSTagVersion;

        typedef
        struct _NodeTagVersion
        {
            NodeTagID          tag;
            size_t             versions;
        } NodeTagVersion;

        typedef
        struct _AttrTagVersion
        {
            NSTagID           ns_tag;
            AttrTagID         attribute;
            size_t            versions;
        } AttrTagVersion;
    }
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif // VERSIONS_HEADER