#ifndef UNKNOWN_SURFACE_H
#define UNKNOWN_SURFACE_H

#include "VulkanHandle.h"
#include "../../../os/OperatingSystem.h"

class Surface : public VulkanHandle<VkSurfaceKHR> {
public:
    Surface() = default;

    static char const * GetExtensionName() noexcept;
    static char const * GetPlatformSpecificExtensionName() noexcept;
private:
    constexpr static char const *extensionName = "VK_KHR_surface",
    *windowsExtensionName = "VK_KHR_win32_surface",
    *linuxExtensionName = "VK_KHR_xlib_surface",
    *macosExtensionName = "VK_MVK_macos_surface";
};

#endif