#ifndef UNKNOWN_VULKANCONTEXT_H
#define UNKNOWN_VULKANCONTEXT_H

#include "../../../os/OperatingSystem.h"
#include "../../../core/Core.h"
#include "../GraphicsContext.h"
#include "Instance.h"
#include "ApplicationInfo.h"
#include "Surface.h"

class VulkanContext : public GraphicsContext {
public:
    VulkanContext() noexcept;
    ~VulkanContext() override = default;

    void Initialize() override;
private:
    std::vector<char const *> GetRequiredInstanceLayerNames() noexcept;
    std::vector<char const *> GetRequiredInstanceExtensionNames() noexcept;
private:
    ApplicationInfo mAppInfo;
    std::unique_ptr<Instance> mInstance;

    constexpr static std::array<char const *, 1> debugLayers = { "VK_LAYER_KHRONOS_validation" };
    constexpr static std::array<char const *, 1> debugExtensions = { VK_EXT_DEBUG_UTILS_EXTENSION_NAME };
};

#endif