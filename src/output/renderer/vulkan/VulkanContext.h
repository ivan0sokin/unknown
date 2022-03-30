#ifndef UNKNOWN_VULKANCONTEXT_H
#define UNKNOWN_VULKANCONTEXT_H

#include <iostream>

#include "../../../os/OperatingSystem.h"
#include "../../../core/Core.h"
#include "../GraphicsContext.h"
#include "Instance.h"
#include "Debugger.h"
#include "ApplicationInfo.h"
#include "Surface.h"

class VulkanContext : public GraphicsContext {
public:
    VulkanContext() = default;
    ~VulkanContext() noexcept override;

    void Initialize() override;
private:
    std::vector<char const *> GetRequiredInstanceLayerNames() noexcept;
    std::vector<char const *> GetRequiredInstanceExtensionNames() noexcept;
private:
    ApplicationInfo mAppInfo;
    std::unique_ptr<Instance> mInstance;
    std::unique_ptr<Debugger> mDebugger;

    constexpr static std::array<char const *, 1> debugLayers = { "VK_LAYER_KHRONOS_validation" };
    constexpr static std::array<char const *, 1> debugExtensions = { VK_EXT_DEBUG_UTILS_EXTENSION_NAME };
};

#endif