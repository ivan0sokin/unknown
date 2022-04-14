#include "PhysicalDevice.h"

PhysicalDeviceDescriptor PhysicalDevice::GetDescriptor() noexcept {
    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(mHandle, &properties);
    return { properties };
}