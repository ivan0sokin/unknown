#ifndef UNKNOWN_CORE_H
#define UNKNOWN_CORE_H

#if defined(DEBUG)
#define DEBUG_STATE 0
#else
#define DEBUG_STATE 1
#endif

namespace Core {
    namespace Build {
        enum class Configuration {
            Debug = 0,
            Release
        };

        constexpr Configuration configuration = static_cast<Configuration>(DEBUG_STATE);
    }
}

#endif