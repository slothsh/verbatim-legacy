// Stefan "SoulXP" Olivier
// File: config.hpp
// Description: Configuration and global defines for project

#ifndef VTCONFIG_HEADER
#define VTCONFIG_HEADER

// Magic Enum configuration for project
#define MAGIC_ENUM_RANGE_MIN 0
#define MAGIC_ENUM_RANGE_MAX 256
#include <magic_enum.hpp>

// Assert magic enum is configured
static_assert(MAGIC_ENUM_RANGE_MIN == 0);
static_assert(MAGIC_ENUM_RANGE_MAX == 256);

// Debug configuration
// Global flags
#define EDL_DEBUG_MEMORY

#ifdef NDEBUG
static constexpr bool VTDEBUG        = false;
static constexpr bool VTDEBUG_MEMORY = false;
#else
static constexpr bool VTDEBUG        = true;
static constexpr bool VTDEBUG_MEMORY = true;
#endif

// Enum control values
static constexpr size_t VT_ENUM_NONE = MAGIC_ENUM_RANGE_MAX;
static constexpr size_t VT_ENUM_ID   = MAGIC_ENUM_RANGE_MIN;

#endif // VTCONFIG_HEADER