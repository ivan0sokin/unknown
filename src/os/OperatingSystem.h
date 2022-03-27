#ifndef UNKNOWN_OPERATINGSYSTEM_H
#define UNKNOWN_OPERATINGSYSTEM_H

#define UNKNOWN_OPERATING_SYSTEM_ID -1
#define WINDOWS_ID 0
#define LINUX_ID 1
#define MACOS_ID 2

#if defined(_WIN32)
    #define OPERATING_SYSTEM_ID WINDOWS_ID
#elif defined(__linux__)
    #define OPERATING_SYSTEM_ID LINUX_ID
#elif defined(__APPLE__)
    #define OPERATING_SYSTEM_ID MACOS_ID
#else
    #define OPERATING_SYSTEM_ID UNKNOWN_OPERATING_SYSTEM_ID
#endif

enum class OperatingSystem {
    Unknown = -1,
    Windows,
    Linux,
    MacOS
};

constexpr OperatingSystem OS = static_cast<OperatingSystem>(OPERATING_SYSTEM_ID);

#endif