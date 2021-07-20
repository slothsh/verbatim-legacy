// Stefan "SoulXP" Olivier
// File: versions.cpp
// Description: Dictionary and macro definitions for different document types

// Library headers
#include <magic_enum.hpp>

// Project headers
#include "../include/versions.hpp"

// Aliases
using namespace Helpers::XML;
using namespace magic_enum;

// TTML table defines --------------------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

// XML Core namespaces according to the W3C
#define INCLUDE_NSTAG_XMLCORE                                                                                                                       \
    { { NSTag::xml,     enum_name(NSTag::xml) },          VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },   \
    { { NSTag::xmlns,   enum_name(NSTag::xml) },          VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },   \

// TTML TT core namespaces according to the W3C
#define INCLUDE_NSTAG_TTCORE                                                                                                                        \
    { { NSTag::tt,      enum_name(NSTag::tt)  },          VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },   \
    { { NSTag::ttm,     enum_name(NSTag::ttm) },          VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },   \
    { { NSTag::ttp,     enum_name(NSTag::ttp) },          VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },   \
    { { NSTag::tts,     enum_name(NSTag::tts) },          VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },   \

// TTML core element nodes
#define INCLUDE_NODETAG_TTCORE                                                                                                                                              \
    { {  NSTag::tt,         NodeTag::set,        enum_name(NodeTag::set)      },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { {  NSTag::tt,         NodeTag::body,       enum_name(NodeTag::body)     },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { {  NSTag::tt,         NodeTag::div,        enum_name(NodeTag::div)      },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { {  NSTag::tt,         NodeTag::p,          enum_name(NodeTag::p)        },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { {  NSTag::tt,         NodeTag::span,       enum_name(NodeTag::span)     },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { {  NSTag::tt,         NodeTag::br,         enum_name(NodeTag::br)       },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { {  NSTag::tt,         NodeTag::tt,         enum_name(NodeTag::tt)       },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { {  NSTag::tt,         NodeTag::head,       enum_name(NodeTag::head)     },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { {  NSTag::tt,         NodeTag::layout,     enum_name(NodeTag::layout)   },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { {  NSTag::tt,         NodeTag::region,     enum_name(NodeTag::region)   },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { {  NSTag::tt,         NodeTag::metadata,   enum_name(NodeTag::metadata) },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { {  NSTag::tt,         NodeTag::styling,    enum_name(NodeTag::styling)  },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { {  NSTag::tt,         NodeTag::style,      enum_name(NodeTag::style)    },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \

// TTML metadata element nodes
#define INCLUDE_NODETAG_TTMCORE                                                                                                                                                    \
    { {  NSTag::ttm,         NodeTag::actor,        enum_name(NodeTag::actor)     },      VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { {  NSTag::ttm,         NodeTag::agent,        enum_name(NodeTag::agent)     },      VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { {  NSTag::ttm,         NodeTag::copyright,    enum_name(NodeTag::copyright) },      VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { {  NSTag::ttm,         NodeTag::desc,         enum_name(NodeTag::desc)      },      VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { {  NSTag::ttm,         NodeTag::name,         enum_name(NodeTag::name)      },      VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { {  NSTag::ttm,         NodeTag::title,        enum_name(NodeTag::title)     },      VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \

// TTML parameter element nodes
#define INCLUDE_NODETAG_TTPCORE                                                                                                                                                      \
    { {  NSTag::ttp,         NodeTag::profile,        enum_name(NodeTag::profile)    },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { {  NSTag::ttp,         NodeTag::features,       enum_name(NodeTag::features)   },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { {  NSTag::ttp,         NodeTag::feature,        enum_name(NodeTag::feature)    },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { {  NSTag::ttp,         NodeTag::extensions,     enum_name(NodeTag::extensions) },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { {  NSTag::ttp,         NodeTag::extension,      enum_name(NodeTag::extension)  },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \

// TTML styling element nodes
#define INCLUDE_NODETAG_TTSCORE                                                                                                                                                  \
    { {  NSTag::tts,         NodeTag::styling,        enum_name(NodeTag::styling) },    VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { {  NSTag::tts,         NodeTag::style,          enum_name(NodeTag::style)   },    VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \

// XML core attributes
#define INCLUDE_ATTRTAG_XMLCORE(NS)                                                                                                                                                                                    \
    { { NS, enum_name(NS) }, {  NSTag::xml,         AttrTag::id,             enum_name(AttrTag::id)    },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::xml,         AttrTag::lang,           enum_name(AttrTag::lang)  },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::xml,         AttrTag::space,          enum_name(AttrTag::space) },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    
// TTML core attributes
#define INCLUDE_ATTRTAG_TTCORE(NS)                                                                                                                                                                                             \
    { { NS, enum_name(NS) }, {  NSTag::tt,         AttrTag::region,          enum_name(AttrTag::region)        },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tt,         AttrTag::style,           enum_name(AttrTag::style)         },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tt,         AttrTag::begin,           enum_name(AttrTag::begin)         },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tt,         AttrTag::end,             enum_name(AttrTag::end)           },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tt,         AttrTag::dur,             enum_name(AttrTag::dur)           },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tt,         AttrTag::timeContainer,   enum_name(AttrTag::timeContainer) },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \

// TTML metadata attributes
#define INCLUDE_ATTRTAG_TTMCORE(NS)                                                                                                                                                                                      \
    { { NS, enum_name(NS) }, {  NSTag::ttm,         AttrTag::agent,            enum_name(AttrTag::agent) },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::ttm,         AttrTag::role,             enum_name(AttrTag::role)  },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \

// TTML parameter attributes
#define INCLUDE_ATTRTAG_TTPCORE(NS)                                                                                                                                                                                                         \
    { { NS, enum_name(NS) }, {  NSTag::ttp,         AttrTag::cellResolution,        enum_name(AttrTag::cellResolution)      },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::ttp,         AttrTag::clockMode,             enum_name(AttrTag::clockMode)           },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::ttp,         AttrTag::dropMode,              enum_name(AttrTag::dropMode)            },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::ttp,         AttrTag::frameRate,             enum_name(AttrTag::frameRate)           },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::ttp,         AttrTag::frameRateMultiplier,   enum_name(AttrTag::frameRateMultiplier) },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::ttp,         AttrTag::markerMode,            enum_name(AttrTag::markerMode)          },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::ttp,         AttrTag::pixelAspectRatio,      enum_name(AttrTag::pixelAspectRatio)    },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::ttp,         AttrTag::profile,               enum_name(AttrTag::profile)             },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::ttp,         AttrTag::subFrameRate,          enum_name(AttrTag::subFrameRate)        },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::ttp,         AttrTag::tickRate,              enum_name(AttrTag::tickRate)            },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::ttp,         AttrTag::timeBase,              enum_name(AttrTag::timeBase)            },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \

// TTML style attributes
#define INCLUDE_ATTRTAG_TTSCORE(NS)                                                                                                                                                                                                      \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::backgroundColor,        enum_name(AttrTag::backgroundColor) },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::color,                  enum_name(AttrTag::color)           },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::direction,              enum_name(AttrTag::direction)       },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::display,                enum_name(AttrTag::display)         },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::displayAlign,           enum_name(AttrTag::displayAlign)    },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::extent,                 enum_name(AttrTag::extent)          },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::fontFamily,             enum_name(AttrTag::fontFamily)      },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::fontSize,               enum_name(AttrTag::fontSize)        },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::fontStyle,              enum_name(AttrTag::fontStyle)       },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::fontWeight,             enum_name(AttrTag::fontWeight)      },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::lineHeight,             enum_name(AttrTag::lineHeight)      },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::opacity,                enum_name(AttrTag::opacity)         },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::origin,                 enum_name(AttrTag::origin)          },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::overflow,               enum_name(AttrTag::overflow)        },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::padding,                enum_name(AttrTag::padding)         },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::showBackground,         enum_name(AttrTag::showBackground)  },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::textAlign,              enum_name(AttrTag::textAlign)       },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::textDecoration,         enum_name(AttrTag::textDecoration)  },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::textOutline,            enum_name(AttrTag::textOutline)     },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::unicodeBidi,            enum_name(AttrTag::unicodeBidi)     },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::visibility,             enum_name(AttrTag::visibility)      },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::wrapOption,             enum_name(AttrTag::wrapOption)      },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::writingMode,            enum_name(AttrTag::writingMode)     },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    { { NS, enum_name(NS) }, {  NSTag::tts,         AttrTag::zIndex,                 enum_name(AttrTag::zIndex)          },   VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },  \
    
// ------------------------------------------------------------|END|-----------------------------------------------------------|

// TTML dictionaries ---------------------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

extern constexpr NSTagVersion NS_DICTIONARY[] =
{
    INCLUDE_NSTAG_XMLCORE
    INCLUDE_NSTAG_TTCORE
    { { NSTag::none,    enum_name(NSTag::none) },   0 }
};

// TODO NSDictionaries for other specs

extern constexpr NodeTagVersion TAG_DICTIONARY[] = 
{
    INCLUDE_NODETAG_TTCORE
    INCLUDE_NODETAG_TTMCORE
    INCLUDE_NODETAG_TTPCORE
    INCLUDE_NODETAG_TTMCORE
    { { NSTag::none,    NodeTag::none,  enum_name(NodeTag::none) },     0 }
};

// TODO node dictionaries for other specs

// Attribute dictionaries for nodes

extern constexpr AttrTagVersion ATTR_DICTIONARY_SET[] =
{
    INCLUDE_ATTRTAG_XMLCORE(NSTag::tt)
    INCLUDE_ATTRTAG_TTSCORE(NSTag::tt)
    { { NSTag::tt,   enum_name(NSTag::tt)   }, { NSTag::tt,      AttrTag::begin,  enum_name(AttrTag::begin) },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::tt,   enum_name(NSTag::tt)   }, { NSTag::tt,      AttrTag::end,    enum_name(AttrTag::end)   },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::tt,   enum_name(NSTag::tt)   }, { NSTag::tt,      AttrTag::dur,    enum_name(AttrTag::dur)   },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,    AttrTag::none,   enum_name(AttrTag::none)  },     0 }
};

extern constexpr AttrTagVersion ATTR_DICTIONARY_BODY[] =
{
    INCLUDE_ATTRTAG_XMLCORE(NSTag::tt)
    INCLUDE_ATTRTAG_TTCORE(NSTag::tt)
    INCLUDE_ATTRTAG_TTMCORE(NSTag::tt)
    INCLUDE_ATTRTAG_TTSCORE(NSTag::tt)
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,    AttrTag::none,  enum_name(AttrTag::none) },     0 }
};

extern constexpr AttrTagVersion ATTR_DICTIONARY_DIV[] =
{
    INCLUDE_ATTRTAG_XMLCORE(NSTag::tt)
    INCLUDE_ATTRTAG_TTCORE(NSTag::tt)
    INCLUDE_ATTRTAG_TTMCORE(NSTag::tt)
    INCLUDE_ATTRTAG_TTSCORE(NSTag::tt)
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,    AttrTag::none,  enum_name(AttrTag::none) },     0 }
};

extern constexpr AttrTagVersion ATTR_DICTIONARY_P[] =
{
    INCLUDE_ATTRTAG_XMLCORE(NSTag::tt)
    INCLUDE_ATTRTAG_TTCORE(NSTag::tt)
    INCLUDE_ATTRTAG_TTMCORE(NSTag::tt)
    INCLUDE_ATTRTAG_TTSCORE(NSTag::tt)
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,    AttrTag::none,  enum_name(AttrTag::none) },     0 }
};

extern constexpr AttrTagVersion ATTR_DICTIONARY_SPAN[] =
{
    INCLUDE_ATTRTAG_XMLCORE(NSTag::tt)
    INCLUDE_ATTRTAG_TTCORE(NSTag::tt)
    INCLUDE_ATTRTAG_TTMCORE(NSTag::tt)
    INCLUDE_ATTRTAG_TTSCORE(NSTag::tt)
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,    AttrTag::none,  enum_name(AttrTag::none) },     0 }
};

extern constexpr AttrTagVersion ATTR_DICTIONARY_BR[] =
{
    INCLUDE_ATTRTAG_XMLCORE(NSTag::tt)
    INCLUDE_ATTRTAG_TTSCORE(NSTag::tt)
    INCLUDE_ATTRTAG_TTMCORE(NSTag::tt)
    { { NSTag::tt,   enum_name(NSTag::tt)   }, { NSTag::tt,      AttrTag::style,  enum_name(AttrTag::style) },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,    AttrTag::none,   enum_name(AttrTag::none)  },     0 }
};

extern constexpr AttrTagVersion ATTR_DICTIONARY_TT[] =
{
    INCLUDE_ATTRTAG_XMLCORE(NSTag::tt)
    INCLUDE_ATTRTAG_TTPCORE(NSTag::tt)
    { { NSTag::tt,   enum_name(NSTag::tt)   }, { NSTag::tts,     AttrTag::extent,  enum_name(AttrTag::extent) },      VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,    AttrTag::none,    enum_name(AttrTag::none)   },      0 }
};

extern constexpr AttrTagVersion ATTR_DICTIONARY_HEAD[] =
{
    INCLUDE_ATTRTAG_XMLCORE(NSTag::tt)
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,    AttrTag::none,  enum_name(AttrTag::none) },     0 }
};

extern constexpr AttrTagVersion ATTR_DICTIONARY_LAYOUT[] =
{
    INCLUDE_ATTRTAG_XMLCORE(NSTag::tt)
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,    AttrTag::none,  enum_name(AttrTag::none) },     0 }
};

extern constexpr AttrTagVersion ATTR_DICTIONARY_REGION[] =
{
    INCLUDE_ATTRTAG_XMLCORE(NSTag::tt)
    { { NSTag::tt, enum_name(NSTag::tt)     }, { NSTag::tt,          AttrTag::begin,          enum_name(AttrTag::begin)         },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::tt, enum_name(NSTag::tt)     }, { NSTag::tt,          AttrTag::end,            enum_name(AttrTag::end)           },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::tt, enum_name(NSTag::tt)     }, { NSTag::tt,          AttrTag::dur,            enum_name(AttrTag::dur)           },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::tt, enum_name(NSTag::tt)     }, { NSTag::tt,          AttrTag::style,          enum_name(AttrTag::style)         },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::tt, enum_name(NSTag::tt)     }, { NSTag::tt,          AttrTag::timeContainer,  enum_name(AttrTag::timeContainer) },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::tt, enum_name(NSTag::tt)     }, { NSTag::ttm,         AttrTag::role,           enum_name(AttrTag::role)          },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,        AttrTag::none,           enum_name(AttrTag::none)          },     0 }
};

extern constexpr AttrTagVersion ATTR_DICTIONARY_METADATA[] =
{
    INCLUDE_ATTRTAG_XMLCORE(NSTag::tt)
    INCLUDE_ATTRTAG_TTMCORE(NSTag::tt)
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,    AttrTag::none,  enum_name(AttrTag::none) },     0 }
};

extern constexpr AttrTagVersion ATTR_DICTIONARY_ACTOR[] =
{
    INCLUDE_ATTRTAG_XMLCORE(NSTag::ttm)
    { { NSTag::ttm,  enum_name(NSTag::ttm)  }, { NSTag::ttm,     AttrTag::agent,  enum_name(AttrTag::agent) },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,    AttrTag::none,  enum_name(AttrTag::none)   },     0 }
};

extern constexpr AttrTagVersion ATTR_DICTIONARY_AGENT[] =
{
    INCLUDE_ATTRTAG_XMLCORE(NSTag::ttm)
    { { NSTag::ttm,  enum_name(NSTag::ttm)  }, { NSTag::tt,      AttrTag::type,  enum_name(AttrTag::type) },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,    AttrTag::none,  enum_name(AttrTag::none) },     0 }
};

extern constexpr AttrTagVersion ATTR_DICTIONARY_COPYRIGHT[] =
{
    INCLUDE_ATTRTAG_XMLCORE(NSTag::ttm)
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,    AttrTag::none,  enum_name(AttrTag::none) },     0 }
};

extern constexpr AttrTagVersion ATTR_DICTIONARY_DESC[] =
{
    INCLUDE_ATTRTAG_XMLCORE(NSTag::ttm)
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,    AttrTag::none,  enum_name(AttrTag::none) },     0 }
};

extern constexpr AttrTagVersion ATTR_DICTIONARY_NAME[] =
{
    INCLUDE_ATTRTAG_XMLCORE(NSTag::ttm)
    { { NSTag::ttm,  enum_name(NSTag::ttm)  }, { NSTag::tt,      AttrTag::type,  enum_name(AttrTag::type) },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,    AttrTag::none,  enum_name(AttrTag::none) },     0 }
};

extern constexpr AttrTagVersion ATTR_DICTIONARY_TITLE[] =
{
    INCLUDE_ATTRTAG_XMLCORE(NSTag::ttm)
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,    AttrTag::none,  enum_name(AttrTag::none) },     0 }
};

extern constexpr AttrTagVersion ATTR_DICTIONARY_PROFILE[] =
{
    { { NSTag::ttp,  enum_name(NSTag::ttp)  }, { NSTag::xml,     AttrTag::id,    enum_name(AttrTag::none) },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::ttp,  enum_name(NSTag::ttp)  }, { NSTag::tt,      AttrTag::use,   enum_name(AttrTag::none) },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,    AttrTag::none,  enum_name(AttrTag::none) },     0 }
};

extern constexpr AttrTagVersion ATTR_DICTIONARY_FEATURES[] =
{
    { { NSTag::ttp,  enum_name(NSTag::ttp)  }, { NSTag::xml,     AttrTag::base,  enum_name(AttrTag::base) },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::ttp,  enum_name(NSTag::ttp)  }, { NSTag::xml,     AttrTag::id,    enum_name(AttrTag::id)   },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,    AttrTag::none,  enum_name(AttrTag::none) },     0 }
};

extern constexpr AttrTagVersion ATTR_DICTIONARY_FEATURE[] =
{
    { { NSTag::ttp,  enum_name(NSTag::ttp)  }, { NSTag::tt,      AttrTag::value,  enum_name(AttrTag::none) },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::ttp,  enum_name(NSTag::ttp)  }, { NSTag::xml,     AttrTag::id,     enum_name(AttrTag::id)   },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,    AttrTag::none,   enum_name(AttrTag::none) },     0 }
};

extern constexpr AttrTagVersion ATTR_DICTIONARY_EXTENSIONS[] =
{
    { { NSTag::ttp,  enum_name(NSTag::ttp)  }, { NSTag::xml,     AttrTag::base,  enum_name(AttrTag::base) },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::ttp,  enum_name(NSTag::ttp)  }, { NSTag::xml,     AttrTag::id,    enum_name(AttrTag::id)   },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,    AttrTag::none,  enum_name(AttrTag::none) },     0 }
};

extern constexpr AttrTagVersion ATTR_DICTIONARY_EXTENSION[] =
{
    { { NSTag::ttp,  enum_name(NSTag::ttp)  }, { NSTag::tt,      AttrTag::value, enum_name(AttrTag::value) },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::ttp,  enum_name(NSTag::ttp)  }, { NSTag::xml,     AttrTag::id,    enum_name(AttrTag::id)    },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,    AttrTag::none,  enum_name(AttrTag::none)  },     0 }
};

extern constexpr AttrTagVersion ATTR_DICTIONARY_STYLING[] =
{
    INCLUDE_ATTRTAG_XMLCORE(NSTag::tt)
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,    AttrTag::none,  enum_name(AttrTag::none) },     0 }
};

extern constexpr AttrTagVersion ATTR_DICTIONARY_STYLE[] =
{
    INCLUDE_ATTRTAG_XMLCORE(NSTag::tt)
    INCLUDE_ATTRTAG_TTSCORE(NSTag::tt)
    { { NSTag::tt,   enum_name(NSTag::tt)   }, { NSTag::tt,      AttrTag::style,  enum_name(AttrTag::style) },     VER_TTML1|VER_TTML2|VER_TTML3|VER_TTML1_SMPTETT|VER_TTML1_EBUDD|VER_IMSC1|VER_IMSC11 },
    { { NSTag::none, enum_name(NSTag::none) }, { NSTag::none,    AttrTag::none,   enum_name(AttrTag::none)  },     0 }
};

// ------------------------------------------------------------|END|-----------------------------------------------------------|