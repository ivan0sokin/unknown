#ifndef UNKNOWN_VULKANCONTEXT_H
#define UNKNOWN_VULKANCONTEXT_H

#include <iostream>

#include "../../../os/OperatingSystem.h"
#include "../../../core/Core.h"
#include "../GraphicsContext.h"
#include "ApplicationInfo.h"
#include "Instance.h"
#include "Debugger.h"
#include "PhysicalDeviceHandleList.h"
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
    std::unique_ptr<PhysicalDeviceHandleList> mPhysicalDeviceHandleList;

    constexpr static std::array<char const *, 1> debugLayers = { "VK_LAYER_KHRONOS_validation" };
    constexpr static std::array<char const *, 1> debugExtensions = { VK_EXT_DEBUG_UTILS_EXTENSION_NAME };
    constexpr static MessageSeverity preferredCallbackMessageSeverity = MessageSeverity::Moderate;
    constexpr static MessageType preferredCallbackMessageType = MessageType::Shared;
};

#endif