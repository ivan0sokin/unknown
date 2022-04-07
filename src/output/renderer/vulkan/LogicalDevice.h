#ifndef UNKNOWN_LOGICALDEVICE_H
#define UNKNOWN_LOGICALDEVICE_H

#include <span>

#include "VulkanHandle.h"

class LogicalDevice : public VulkanHandle<VkDevice> {
public:
    LogicalDevice() = delete;
    LogicalDevice(VkPhysicalDevice physicalDevice, std::span<VkDeviceQueueCreateInfo> queueCreateInfoList) noexcept;
    ~LogicalDevice() noexcept override;

    void TryCreate();
    void Destroy() noexcept;
private:
    VkPhysicalDevice mPhysicalDevice;
    std::vector<VkDeviceQueueCreateInfo> mQueueCreateInfoList;
};


#endif