#ifndef UNKNOWN_PHYSICALDEVICEDESCRIPTOR_H
#define UNKNOWN_PHYSICALDEVICEDESCRIPTOR_H

#include <vulkan/vulkan.hpp>

class PhysicalDeviceDescriptor {
    friend class PhysicalDevice;
public:
    PhysicalDeviceDescriptor() = default;

    constexpr std::string_view const Name() const noexcept { return mPhysicalDeviceProperties.deviceName; }
    constexpr unsigned VendorID() const noexcept { return mPhysicalDeviceProperties.vendorID; }
private:
    constexpr PhysicalDeviceDescriptor(VkPhysicalDeviceProperties const &physicalDeviceProperties) noexcept : mPhysicalDeviceProperties(physicalDeviceProperties) {}
private:
    VkPhysicalDeviceProperties mPhysicalDeviceProperties;
};

#endif