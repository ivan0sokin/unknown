#ifndef UNKNOWN_QUEUEFAMILYINDICES_H
#define UNKNOWN_QUEUEFAMILYINDICES_H

#include <vector>
#include <optional>

#include "VulkanResult.h"

class QueueFamilyIndices {
public:
    QueueFamilyIndices() = delete;
    constexpr QueueFamilyIndices(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface) noexcept : mPhysicalDevice(physicalDevice), mSurface(surface) {}

    void TryInitialize();

    constexpr std::optional<unsigned> TryGetGraphicsQueueFamilyIndex() const noexcept { return mGraphicsQueueFamilyIndex; }
    constexpr std::optional<unsigned> TryGetPresentQueueFamilyIndex() const noexcept { return mPresentQueueFamilyIndex; }
    bool AreGraphicsAndPresentFamilyIndicesSimilar() const;
private:
    bool QueueFamilyIndexIsSupportedBySurface(unsigned queueFamilyIndex);
    std::vector<VkQueueFamilyProperties> GetQueueFamilyPropertiesList() noexcept;
private:
    VkPhysicalDevice mPhysicalDevice;
    VkSurfaceKHR mSurface;
    std::optional<unsigned> mGraphicsQueueFamilyIndex = {}, mPresentQueueFamilyIndex = {};
};

#endif