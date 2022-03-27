#ifndef UNKNOWN_INSTANCE_H
#define UNKNOWN_INSTANCE_H

#include <span>

#include "VulkanHandle.h"

class Instance : public VulkanHandle<VkInstance> {
public:
    Instance() noexcept;
    Instance(std::span<char const *> enabledLayerNames, std::span<char const *> enabledExtensionNames) noexcept;
    ~Instance() noexcept override;

    void TryCreate(VkApplicationInfo const &applicationInfo);

    inline std::vector<VkLayerProperties> GetLayerProperties() noexcept { return mLayerProperties; }
    inline std::vector<VkExtensionProperties> GetExtensionProperties() noexcept { return mExtensionProperties; }

    constexpr VkInstance GetHandle() const noexcept override { return mInstance; }
private:
    void InitializeLayerProperties() noexcept;
    void InitializeExtensionProperties() noexcept;
    bool CheckEnabledLayersSupported() noexcept;
    bool CheckEnabledExtensionsSupported() noexcept;
private:
    std::vector<VkLayerProperties> mLayerProperties;
    std::vector<VkExtensionProperties> mExtensionProperties;
    std::vector<char const *> mEnabledLayerNames, mEnabledExtensionNames;
    VkInstance mInstance;
};

#endif