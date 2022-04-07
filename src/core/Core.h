#ifndef UNKNOWN_CORE_H
#define UNKNOWN_CORE_H

#if defined(DEBUG)
#define DEBUG_STATE 0
#else
#define DEBUG_STATE 1
#endif

#include "Version.h"

namespace Core {
    namespace Build {
        enum class Configuration {
            Debug = 0,
            Release
        };

        constexpr Configuration CONFIGURATION = static_cast<Configuration>(DEBUG_STATE);
    }

    namespace Engine {
        constexpr std::string_view NAME = "Raycast";
        constexpr Version VERSION = Version(0, 0, 1);
    }

    namespace Application {
        constexpr std::string_view NAME = "Unknown";
        constexpr Version VERSION = Version(0, 0, 1);
    }
}

#endif