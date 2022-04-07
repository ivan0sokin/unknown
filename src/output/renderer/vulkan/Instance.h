#ifndef UNKNOWN_INSTANCE_H
#define UNKNOWN_INSTANCE_H

#include <span>

#include "VulkanHandle.h"
#include "VulkanVersion.h"

class Instance : public VulkanHandle<VkInstance> {
public:
    Instance();
    Instance(std::span<char const *> enabledLayerNames, std::span<char const *> enabledExtensionNames) noexcept;
    ~Instance() noexcept override;

    void TryCreate(VkApplicationInfo const &applicationInfo);
    void Destroy() noexcept;

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
    std::vector<VkLayerProperties> mLayerProperties;
    std::vector<VkExtensionProperties> mExtensionProperties;
    std::vector<char const *> mEnabledLayerNames, mEnabledExtensionNames;

    constexpr static VulkanVersion minimumRequiredAPIVersion = VK_API_VERSION_1_3;
};

#endif