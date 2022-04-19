#include "LogicalDevice.h"

LogicalDevice::LogicalDevice(VkPhysicalDevice physicalDevice, std::span<VkDeviceQueueCreateInfo> queueCreateInfoList, std::span<char const *> extensionNames) noexcept :
    mPhysicalDevice(physicalDevice),
    mQueueCreateInfoList(queueCreateInfoList.begin(), queueCreateInfoList.end()),
    mExtensionNames(extensionNames.begin(), extensionNames.end()) {}

void LogicalDevice::TryCreate() {
    VkDeviceCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = static_cast<unsigned>(mQueueCreateInfoList.size()),
        .pQueueCreateInfos = mQueueCreateInfoList.data(),
        .enabledExtensionCount = static_cast<unsigned>(mExtensionNames.size()),
        .ppEnabledExtensionNames = mExtensionNames.data()
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