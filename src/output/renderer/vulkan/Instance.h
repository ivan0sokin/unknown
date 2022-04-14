#ifndef UNKNOWN_INSTANCE_H
#define UNKNOWN_INSTANCE_H

#include <span>
#include <unordered_set>

#include "VulkanHandle.h"
#include "VulkanVersion.h"
#include "PhysicalDevice.h"

class Instance : public VulkanHandle<VkInstance> {
public:
    Instance() = delete;
    Instance(std::span<char const *> enabledLayerNames, std::span<char const *> enabledExtensionNames, VkApplicationInfo const &applicationInfo) noexcept;
    ~Instance() noexcept override;

    void TryInitialize();
    void TryCreate();
    void Destroy() noexcept;

    std::vector<PhysicalDevice> GetPhysicalDeviceList();

    inline std::vector<VkLayerProperties> GetLayerProperties() const noexcept { return mLayerProperties; }
    inline std::vector<VkExtensionProperties> GetExtensionProperties() const noexcept { return mExtensionProperties; }

    constexpr static VulkanVersion GetMinimumRequiredAPIVersion() noexcept { return minimumRequiredAPIVersion; }
private:
    bool IsRequiredAPIVersionSupported() const;
    void InitializeLayerProperties();
    void InitializeExtensionProperties();
    bool AreEnabledLayersSupported() const noexcept;
    bool AreEnabledExtensionsSupported() const noexcept;
private:
    VkApplicationInfo mApplicationInfo;
    std::vector<char const *> mEnabledLayerNames, mEnabledExtensionNames;
    std::vector<VkLayerProperties> mLayerProperties;
    std::vector<VkExtensionProperties> mExtensionProperties;

    constexpr static VulkanVersion minimumRequiredAPIVersion = VK_API_VERSION_1_2;
};

#endif