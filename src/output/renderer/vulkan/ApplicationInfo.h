#ifndef UNKNOWN_APPLICATIONINFO_H
#define UNKNOWN_APPLICATIONINFO_H

#include "VulkanDescriptor.h"
#include "VulkanVersion.h"

class ApplicationInfo : public VulkanDescriptor<VkApplicationInfo> {
public:
    ApplicationInfo() = default;
    ApplicationInfo(std::string_view applicationName, VulkanVersion const &applicationVersion, std::string_view engineName,
                    VulkanVersion const &engineVersion, VulkanVersion const &APIVersion) noexcept;

    void Initialize() noexcept;
private:
    std::string mApplicationName, mEngineName;
    VulkanVersion mApplicationVersion, mEngineVersion, mAPIVersion;
};

#endif