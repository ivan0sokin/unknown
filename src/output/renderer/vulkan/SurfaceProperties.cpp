#include "SurfaceProperties.h"

unsigned SurfaceProperties::TryGetMinImageCount() {
    auto capabilities = TryGetCapabilities();
    unsigned requiredImageCount = capabilities.minImageCount + 1, maximumImageCount = capabilities.maxImageCount;
    if (requiredImageCount > maximumImageCount && maximumImageCount != 0) {
        requiredImageCount = maximumImageCount;
    }

    return requiredImageCount;
}

VkSurfaceCapabilitiesKHR SurfaceProperties::TryGetCapabilities() {
    VkSurfaceCapabilitiesKHR capabilities;
    VulkanResult result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(mPhysicalDevice, mSurface, &capabilities);
    if (!result.Success()) {
        throw std::runtime_error("Failed to get VkSurfaceCapabilitiesKHR, result: " + result.ToString());
    }

    return capabilities;
}

VkSurfaceFormatKHR SurfaceProperties::TryGetPreferredSurfaceFormatOrFirst(VkFormat preferredFormat, VkColorSpaceKHR preferredColorSpace) {
    auto formats = TryGetSurfaceFormats();
    if (formats.empty()) {
        throw std::runtime_error("Surface has no formats available");
    }

    auto preferredSurfaceFormat = std::ranges::find_if(std::as_const(formats), [&](auto const &surfaceFormat) {
        return surfaceFormat.format == preferredFormat && surfaceFormat.colorSpace == preferredColorSpace;
    });

    if (preferredSurfaceFormat != formats.cend()) {
        return *preferredSurfaceFormat;
    }

    return formats[0];
}

std::vector<VkSurfaceFormatKHR> SurfaceProperties::TryGetSurfaceFormats() {
    unsigned formatCount;
    VulkanResult result = vkGetPhysicalDeviceSurfaceFormatsKHR(mPhysicalDevice, mSurface, &formatCount, nullptr);
    if (!result.Success()) {
        throw std::runtime_error("Failed to get VkSurfaceFormatKHR count, result: " + result.ToString());
    }

    auto formats = std::vector<VkSurfaceFormatKHR>(static_cast<std::size_t>(formatCount));
    result = vkGetPhysicalDeviceSurfaceFormatsKHR(mPhysicalDevice, mSurface, &formatCount, formats.data());
    if (!result.Success()) {
        throw std::runtime_error("Failed to get VkSurfaceFormatsKHR, result: " + result.ToString());
    }

    return formats;
}

VkPresentModeKHR SurfaceProperties::TryGetPreferredPresentModeOrFIFO(VkPresentModeKHR preferredPresentMode) {
    auto presentModes = TryGetPresentModes();
    if (presentModes.empty()) {
        throw std::runtime_error("Surface has no present modes available");
    }

    if (std::ranges::any_of(std::as_const(presentModes), [&](auto const &presentMode) { return presentMode == preferredPresentMode; })) {
        return preferredPresentMode;
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

std::vector<VkPresentModeKHR> SurfaceProperties::TryGetPresentModes() {
    unsigned presentModeCount;
    VulkanResult result = vkGetPhysicalDeviceSurfacePresentModesKHR(mPhysicalDevice, mSurface, &presentModeCount, nullptr);
    if (!result.Success()) {
        throw std::runtime_error("Failed to get VkPresentModeKHR count, result: " + result.ToString());
    }

    auto presentModes = std::vector<VkPresentModeKHR>(static_cast<std::size_t>(presentModeCount));
    result = vkGetPhysicalDeviceSurfacePresentModesKHR(mPhysicalDevice, mSurface, &presentModeCount, presentModes.data());
    if (!result.Success()) {
        throw std::runtime_error("Failed to get VkPresentModesKHR, result: " + result.ToString());
    }

    return presentModes;
}

VkExtent2D SurfaceProperties::TryGetCorrectExtent() {
    auto capabilities = TryGetCapabilities();
    if (capabilities.currentExtent.width != std::numeric_limits<unsigned>::max()) {
        return capabilities.currentExtent;
    };

    return VkExtent2D {
        std::clamp(static_cast<unsigned>(mWindowProperties.width), capabilities.minImageExtent.width, capabilities.maxImageExtent.width),
        std::clamp(static_cast<unsigned>(mWindowProperties.height), capabilities.minImageExtent.height, capabilities.maxImageExtent.height),
    };
}

VkSurfaceTransformFlagBitsKHR SurfaceProperties::TryGetCurrentTransform() {
    auto capabilities = TryGetCapabilities();
    return capabilities.currentTransform;
}