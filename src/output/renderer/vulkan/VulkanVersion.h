#ifndef UNKNOWN_VULKANVERSION_H
#define UNKNOWN_VULKANVERSION_H

#include <vulkan/vulkan.hpp>

#include "../../../core/Version.h"

class VulkanVersion {
public:
    VulkanVersion() = default;
    constexpr VulkanVersion(unsigned version) noexcept : mVersion(version) {}
    constexpr VulkanVersion(Version const &version) noexcept : mVersion(VK_MAKE_VERSION(version.major, version.minor, version.patch)) {}

    constexpr unsigned ToNumber() const noexcept { return mVersion; }
    constexpr operator unsigned() const noexcept { return ToNumber(); }
private:
    unsigned mVersion;
};

#endif