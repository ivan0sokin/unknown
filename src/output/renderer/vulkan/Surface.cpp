#include "Surface.h"

char const * Surface::GetPlatformSpecificExtensionName() noexcept {
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

char const * Surface::GetExtensionName() noexcept {
    return extensionName;
}
