#ifndef UNKNOWN_PHYSICALDEVICEHANDLELIST_H
#define UNKNOWN_PHYSICALDEVICEHANDLELIST_H

#include <vector>

#include "VulkanResult.h"

class PhysicalDeviceHandleList {
public:
    PhysicalDeviceHandleList() = default;
    inline PhysicalDeviceHandleList(VkInstance instance) noexcept : mInstance(instance) {}

    void TryInitialize();

    std::size_t Size() const noexcept { return mPhysicalDevices.size(); }
    VkPhysicalDevice AtPosition(int position) const { return mPhysicalDevices.at(position); }
private:
    VkInstance mInstance;
    std::vector<VkPhysicalDevice> mPhysicalDevices;
};

#endif