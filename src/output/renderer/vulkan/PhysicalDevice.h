#ifndef UNKNOWN_PHYSICALDEVICE_H
#define UNKNOWN_PHYSICALDEVICE_H

#include <vector>

#include "VulkanHandle.h"

class PhysicalDevice : public VulkanHandle<VkPhysicalDevice> {
public:
    PhysicalDevice() = default;
    static std::vector<PhysicalDevice> GetPhysicalDeviceList(VkInstance instance);
private:
    constexpr PhysicalDevice(VkPhysicalDevice physicalDevice) noexcept { mHandle = physicalDevice; }
};


#endif