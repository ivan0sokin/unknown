#include "LogicalDevice.h"

LogicalDevice::LogicalDevice(VkPhysicalDevice physicalDevice, std::span<VkDeviceQueueCreateInfo> queueCreateInfoList) noexcept : mPhysicalDevice(physicalDevice) {
    mQueueCreateInfoList.assign(queueCreateInfoList.begin(), queueCreateInfoList.end());
}

void LogicalDevice::TryCreate() {
    VkDeviceCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = static_cast<unsigned>(mQueueCreateInfoList.size()),
        .pQueueCreateInfos = mQueueCreateInfoList.data()
    };

    VulkanResult result = vkCreateDevice(mPhysicalDevice, &createInfo, nullAllocator, &mHandle);
    if (!result.Success()) {
        throw std::runtime_error("Failed to create device, result: " + result.ToString());
    }
}

void LogicalDevice::Destroy() noexcept {
    if (mHandle != VK_NULL_HANDLE) {
        vkDestroyDevice(mHandle, nullAllocator);
        mHandle = VK_NULL_HANDLE;
    }
}

LogicalDevice::~LogicalDevice() noexcept {
    Destroy();
}