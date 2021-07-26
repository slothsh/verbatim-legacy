// Stefan "SoulXP" Olivier
// File: config.hpp
// Description: Configuration and global defines for project

#ifndef VTCONFIG_HEADER
#define VTCONFIG_HEADER

// Magic Enum configuration for project
#define MAGIC_ENUM_RANGE_MIN 0
#define MAGIC_ENUM_RANGE_MAX 256
#include <magic_enum.hpp>

// Enum control values
#define VT_ENUM_NONE MAGIC_ENUM_RANGE_MAX
#define VT_ENUM_ID MAGIC_ENUM_RANGE_MIN

#endif // VTCONFIG_HEADER