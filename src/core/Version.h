#ifndef UNKNOWN_VERSION_H
#define UNKNOWN_VERSION_H

struct Version {
    unsigned major = 0, minor = 0, patch = 0;

    Version() = default;
    constexpr Version(unsigned major) noexcept : major(major) {}
    constexpr Version(unsigned major, unsigned minor) noexcept : Version(major) { this->minor = minor; }
    constexpr Version(unsigned major, unsigned minor, unsigned patch) noexcept : Version(major, minor) { this->patch = patch; }
};

#endif