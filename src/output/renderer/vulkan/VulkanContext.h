#ifndef UNKNOWN_VULKANCONTEXT_H
#define UNKNOWN_VULKANCONTEXT_H

#include <iostream>

#include "../../../os/OperatingSystem.h"
#include "../../../core/Core.h"
#include "../../window/WindowProperties.h"
#include "../GraphicsContext.h"
#include "ApplicationInfo.h"
#include "Instance.h"
#include "Debugger.h"
#include "PhysicalDevice.h"
#include "Surface.h"
#include "QueueFamilyIndices.h"

class VulkanContext : public GraphicsContext {
public:
    VulkanContext() = default;
    inline VulkanContext(WindowProperties const &windowProperties) noexcept : mWindowProperties(windowProperties) {}
    ~VulkanContext() noexcept override;

    void Initialize() override;
private:
    std::vector<char const *> GetRequiredInstanceLayerNames() noexcept;
    std::vector<char const *> GetRequiredInstanceExtensionNames() noexcept;

    void PickPrimaryPhysicalDevice();
private:
    WindowProperties mWindowProperties;

    std::unique_ptr<Instance> mInstance;
    std::unique_ptr<Debugger> mDebugger;
    std::unique_ptr<Surface> mSurface;
    std::vector<PhysicalDevice> mPhysicalDevices;
    std::unique_ptr<PhysicalDevice> mPrimaryPhysicalDevice;

    constexpr static std::array<char const *, 1> debugLayers = { "VK_LAYER_KHRONOS_validation" };
    constexpr static std::array<char const *, 1> debugExtensions = { VK_EXT_DEBUG_UTILS_EXTENSION_NAME };
    constexpr static MessageSeverity preferredCallbackMessageSeverity = MessageSeverity::Moderate;
    constexpr static MessageType preferredCallbackMessageType = MessageType::Shared;
};

#endif