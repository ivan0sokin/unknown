#ifndef UNKNOWN_APPLICATIONINFO_H
#define UNKNOWN_APPLICATIONINFO_H

#include "VulkanDescriptor.h"
#include "VulkanVersion.h"

class ApplicationInfo : public VulkanDescriptor<VkApplicationInfo> {
public:
    ApplicationInfo() = default;
    constexpr ApplicationInfo(std::string_view applicationName, VulkanVersion const &applicationVersion, std::string_view engineName,
                              VulkanVersion const &engineVersion, VulkanVersion const &APIVersion) noexcept {
        mDescriptor = {
            .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pApplicationName = applicationName.data(),
            .applicationVersion = applicationVersion,
            .pEngineName = engineName.data(),
            .engineVersion = engineVersion,
            .apiVersion = APIVersion
        };
    }
};

#endif