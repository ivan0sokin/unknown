#ifndef UNKNOWN_SURFACEPROPERTIES_H
#define UNKNOWN_SURFACEPROPERTIES_H

#include <vector>

#include <vulkan/vulkan.hpp>

#include "VulkanResult.h"
#include "../../window/WindowProperties.h"

class SurfaceProperties {
public:
    SurfaceProperties() = delete;
    constexpr SurfaceProperties(VkSurfaceKHR surface, VkPhysicalDevice physicalDevice, WindowProperties const &windowProperties) noexcept :
        mSurface(surface), mPhysicalDevice(physicalDevice), mWindowProperties(windowProperties) {}

    unsigned TryGetMinImageCount();
    VkSurfaceFormatKHR TryGetPreferredSurfaceFormatOrFirst(VkFormat preferredFormat, VkColorSpaceKHR preferredColorSpace);
    VkPresentModeKHR TryGetPreferredPresentModeOrFIFO(VkPresentModeKHR preferredPresentMode);
    VkExtent2D TryGetCorrectExtent();
    VkSurfaceTransformFlagBitsKHR TryGetCurrentTransform();
private:
    VkSurfaceCapabilitiesKHR TryGetCapabilities();
    std::vector<VkSurfaceFormatKHR> TryGetSurfaceFormats();
    std::vector<VkPresentModeKHR> TryGetPresentModes();
private:
    VkSurfaceKHR mSurface;
    VkPhysicalDevice mPhysicalDevice;
    WindowProperties mWindowProperties;
};

#endif