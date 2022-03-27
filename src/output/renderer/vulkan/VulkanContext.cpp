#include "VulkanContext.h"

VulkanContext::VulkanContext() noexcept {
    auto requiredLayerNames = GetRequiredInstanceLayerNames();
    auto requiredExtensionNames = GetRequiredInstanceExtensionNames();
    mInstance = std::make_unique<Instance>(requiredLayerNames, requiredExtensionNames);
}

void VulkanContext::Initialize() {
    mAppInfo.Initialize();
    mInstance->TryCreate(mAppInfo.GetDescriptor());
}

std::vector<char const *> VulkanContext::GetRequiredInstanceLayerNames() noexcept {
    std::vector<char const *> requiredLayers;

    if (Core::Build::configuration == Core::Build::Configuration::Debug) {
        requiredLayers.insert(requiredLayers.cend(), debugLayers.cbegin(), debugLayers.cend());
    }

    return requiredLayers;
}

std::vector<char const *> VulkanContext::GetRequiredInstanceExtensionNames() noexcept {
    std::vector<char const *> requiredExtensions;
    requiredExtensions.insert(requiredExtensions.cend(), { Surface::GetExtensionName(), Surface::GetPlatformSpecificExtensionName() });

    if (Core::Build::configuration == Core::Build::Configuration::Debug) {
        requiredExtensions.insert(requiredExtensions.cend(), debugExtensions.cbegin(), debugExtensions.cend());
    }

    return requiredExtensions;
}