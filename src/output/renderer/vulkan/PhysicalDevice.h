#ifndef UNKNOWN_PHYSICALDEVICE_H
#define UNKNOWN_PHYSICALDEVICE_H

#include <vector>

#include "VulkanHandle.h"
#include "PhysicalDeviceDescriptor.h"

class PhysicalDevice : public VulkanHandle<VkPhysicalDevice> {
    friend class Instance;
public:
    PhysicalDevice() = delete;
    PhysicalDeviceDescriptor GetDescriptor() noexcept;
private:
    constexpr PhysicalDevice(VkPhysicalDevice physicalDevice) noexcept { mHandle = physicalDevice; }
};


#endif