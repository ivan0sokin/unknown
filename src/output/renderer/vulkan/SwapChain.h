#ifndef UNKNOWN_SWAPCHAIN_H
#define UNKNOWN_SWAPCHAIN_H

#include <span>
#include <memory>
#include <utility>
#include <unordered_set>

#include "VulkanHandle.h"
#include "SurfaceProperties.h"

class SwapChain : public VulkanHandle<VkSwapchainKHR> {
public:
    SwapChain() = delete;
    inline SwapChain(VkDevice logicalDevice, VkSurfaceKHR surface, SurfaceProperties const &surfaceInfo, std::span<unsigned> queueFamilyIndices) noexcept :
        mLogicalDevice(logicalDevice), mSurface(surface), mSurfaceProperties(surfaceInfo), mQueueFamilyIndices(queueFamilyIndices.begin(), queueFamilyIndices.end()) {}
    ~SwapChain() noexcept override;

    void TryCreate();
    void Destroy() noexcept;

    constexpr static std::string_view GetRequiredDeviceExtensionName() noexcept { return requiredDeviceExtensionName; }
private:
    VkDevice mLogicalDevice;
    VkSurfaceKHR mSurface;
    SurfaceProperties mSurfaceProperties;
    std::vector<unsigned> mQueueFamilyIndices;

    constexpr static std::string_view requiredDeviceExtensionName = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
    constexpr static VkFormat preferredFormat = VK_FORMAT_B8G8R8A8_SRGB;
    constexpr static VkColorSpaceKHR preferredColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
    constexpr static VkPresentModeKHR preferredPresentMode = VK_PRESENT_MODE_MAILBOX_KHR;
    constexpr static VkImageUsageFlagBits colorAttachment = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    constexpr static VkCompositeAlphaFlagBitsKHR opaqueWindow = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
};


#endif