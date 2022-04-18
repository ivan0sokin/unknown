#ifndef UNKNOWN_PHYSICALDEVICE_H
#define UNKNOWN_PHYSICALDEVICE_H

#include <vector>
#include <unordered_set>

#include "VulkanHandle.h"
#include "PhysicalDeviceDescriptor.h"

class PhysicalDevice : public VulkanHandle<VkPhysicalDevice> {
    friend class Instance;
public:
    PhysicalDevice() = delete;

    PhysicalDeviceDescriptor GetDescriptor() noexcept;

    bool SupportsExtensions(std::initializer_list<std::string_view> extensionNames);
private:
    constexpr PhysicalDevice(VkPhysicalDevice physicalDevice) noexcept { mHandle = physicalDevice; }
};


#endif