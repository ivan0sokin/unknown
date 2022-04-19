#ifndef UNKNOWN_LOGICALDEVICE_H
#define UNKNOWN_LOGICALDEVICE_H

#include <span>
#include <vector>

#include "VulkanHandle.h"

class LogicalDevice : public VulkanHandle<VkDevice> {
public:
    LogicalDevice() = delete;
    LogicalDevice(VkPhysicalDevice physicalDevice, std::span<VkDeviceQueueCreateInfo> queueCreateInfoList, std::span<char const *> extensionNames) noexcept;
    ~LogicalDevice() noexcept override;

    void TryCreate();
    void Destroy() noexcept;
private:
    VkPhysicalDevice mPhysicalDevice;
    std::vector<VkDeviceQueueCreateInfo> mQueueCreateInfoList;
    std::vector<char const *> mExtensionNames;
};


#endif