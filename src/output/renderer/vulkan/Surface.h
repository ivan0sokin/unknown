#ifndef UNKNOWN_SURFACE_H
#define UNKNOWN_SURFACE_H

#include "VulkanHandle.h"
#include "../../../os/OperatingSystem.h"

#if OPERATING_SYSTEM_ID == WINDOWS_ID
#include <windows.h>
#include <vulkan/vulkan_win32.h>
#elif OPERATING_SYSTEM_ID == LINUX_ID
#include <vulkan/vulkan_xlib.h>
#elif OPERATING_SYSTEM_ID == MACOS_ID
#include <vulkan/vulkan_macos.h>
#endif

class Surface : public VulkanHandle<VkSurfaceKHR> {
public:
    Surface() = default;
    constexpr Surface(VkInstance instance, HWND windowHandle) noexcept : mInstance(instance), mWindowHandle(windowHandle) {}
    ~Surface() noexcept override;

    void TryCreate();
    void Destroy() noexcept;

    static char const * GetExtensionName() noexcept;
    static char const * GetPlatformSpecificExtensionName() noexcept;
private:
    VkInstance mInstance;
    HWND mWindowHandle;

    constexpr static char const *extensionName = "VK_KHR_surface",
    *windowsExtensionName = "VK_KHR_win32_surface",
    *linuxExtensionName = "VK_KHR_xlib_surface",
    *macosExtensionName = "VK_MVK_macos_surface";
};

#endif