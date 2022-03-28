#ifndef UNKNOWN_APPLICATIONINFO_H
#define UNKNOWN_APPLICATIONINFO_H

#include "VulkanDescriptor.h"

class ApplicationInfo : public VulkanDescriptor<VkApplicationInfo> {
public:
    ApplicationInfo() = default;
    ApplicationInfo(std::string_view applicationName, unsigned applicationVersion, std::string_view engineName, unsigned engineVersion) noexcept;

    void Initialize() noexcept;
private:
    std::string mApplicationName = "Unknown";
    unsigned mApplicationVersion = VK_MAKE_VERSION(0, 0, 1);
    std::string mEngineName = "Raycast";
    unsigned mEngineVersion = VK_MAKE_VERSION(0, 0, 1);
    constexpr static unsigned apiVersion = VK_MAKE_VERSION(1, 3, 0);
};

#endif