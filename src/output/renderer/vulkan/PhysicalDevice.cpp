#include "PhysicalDevice.h"

std::vector<PhysicalDevice> PhysicalDevice::GetPhysicalDeviceList(VkInstance instance) {
    unsigned physicalDeviceCount;
    VulkanResult result = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);
    if (!result.Success()) {
        throw std::runtime_error("Failed to get VkPhysicalDevice handle count, result: " + result.ToString());
    }

    auto physicalDeviceHandles = std::vector<VkPhysicalDevice>(static_cast<std::size_t>(physicalDeviceCount));
    result = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDeviceHandles.data());
    if (!result.Success()) {
        throw std::runtime_error("Failed to get VkPhysicalDevice handles, result: " + result.ToString());
    }

    std::vector<PhysicalDevice> physicalDevices;
    physicalDevices.reserve(static_cast<std::size_t>(physicalDeviceCount));

    std::ranges::for_each(std::as_const(physicalDeviceHandles), [&](auto physicalDeviceHandle) {
       physicalDevices.push_back(physicalDeviceHandle);
    });

    return physicalDevices;
}
