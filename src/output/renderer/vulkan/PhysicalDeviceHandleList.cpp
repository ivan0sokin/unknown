#include "PhysicalDeviceHandleList.h"

void PhysicalDeviceHandleList::TryInitialize() {
    unsigned physicalDeviceCount;
    VulkanResult result = vkEnumeratePhysicalDevices(mInstance, &physicalDeviceCount, nullptr);
    if (!result.Success()) {
        throw std::runtime_error("Failed to get VkPhysicalDevice handle count, result: " + result.ToString());
    }

    mPhysicalDevices.resize(static_cast<std::size_t>(physicalDeviceCount));
    result = vkEnumeratePhysicalDevices(mInstance, &physicalDeviceCount, mPhysicalDevices.data());
    if (!result.Success()) {
        throw std::runtime_error("Failed to get VkPhysicalDevice handles, result: " + result.ToString());
    }
}