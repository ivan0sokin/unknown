#include "Surface.h"

void Surface::TryCreate() {
    HINSTANCE currentInstance = GetModuleHandle(nullptr);
    VkWin32SurfaceCreateInfoKHR createInfo = {
        .sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
        .hinstance = currentInstance,
        .hwnd = mWindowHandle
    };

    VulkanResult result = vkCreateWin32SurfaceKHR(mInstance, &createInfo, nullAllocator, &mHandle);
    if (!result.Success()) {
        throw std::runtime_error("Failed to create Win32 SurfaceKHR, result: " + result.ToString());
    }
}

std::string_view const Surface::GetPlatformSpecificExtensionName() noexcept {
    switch (OS) {
        case OperatingSystem::Windows:
            return windowsExtensionName;
        case OperatingSystem::Linux:
            return linuxExtensionName;
        case OperatingSystem::MacOS:
            return macosExtensionName;
        default:
            return "";
    }
}

std::string_view const Surface::GetExtensionName() noexcept {
    return extensionName;
}

void Surface::Destroy() noexcept {
    if (mHandle != VK_NULL_HANDLE) {
        vkDestroySurfaceKHR(mInstance, mHandle, nullAllocator);
        mHandle = VK_NULL_HANDLE;
    }
}

Surface::~Surface() noexcept {
    Destroy();
}