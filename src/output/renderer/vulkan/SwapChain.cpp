#include "SwapChain.h"

void SwapChain::TryCreate() {
    auto surfaceFormat = mSurfaceProperties.TryGetPreferredSurfaceFormatOrFirst(preferredFormat, preferredColorSpace);
    auto queueFamilyIndices = std::unordered_set<unsigned>(mQueueFamilyIndices.cbegin(), mQueueFamilyIndices.cend());
    bool uniqueQueueFamily = queueFamilyIndices.size() == 1;
    VkSwapchainCreateInfoKHR createInfo = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .surface = mSurface,
        .minImageCount = mSurfaceProperties.TryGetMinImageCount(),
        .imageFormat = surfaceFormat.format,
        .imageColorSpace = surfaceFormat.colorSpace,
        .imageExtent = mSurfaceProperties.TryGetCorrectExtent(),
        .imageArrayLayers = 1,
        .imageUsage = colorAttachment,
        .imageSharingMode = uniqueQueueFamily ? VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT,
        .queueFamilyIndexCount = uniqueQueueFamily ? 0u : static_cast<unsigned>(mQueueFamilyIndices.size()),
        .pQueueFamilyIndices = uniqueQueueFamily ? nullptr : mQueueFamilyIndices.data(),
        .preTransform = mSurfaceProperties.TryGetCurrentTransform(),
        .compositeAlpha = opaqueWindow,
        .presentMode = mSurfaceProperties.TryGetPreferredPresentModeOrFIFO(preferredPresentMode),
        .clipped = VK_TRUE,
        .oldSwapchain = VK_NULL_HANDLE
    };

    VulkanResult result = vkCreateSwapchainKHR(mLogicalDevice, &createInfo, nullAllocator, &mHandle);
    if (!result.Success()) {
        throw std::runtime_error("Failed to create VkSwapchainKHR, result: " + result.ToString());
    }
}

void SwapChain::Destroy() noexcept {
    if (mHandle != VK_NULL_HANDLE) {
        vkDestroySwapchainKHR(mLogicalDevice, mHandle, nullAllocator);
        mHandle = VK_NULL_HANDLE;
    }
}

SwapChain::~SwapChain() noexcept {
    Destroy();
}