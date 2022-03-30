#include "VulkanContext.h"

void VulkanContext::Initialize() {
    mAppInfo.Initialize();

    auto requiredLayerNames = GetRequiredInstanceLayerNames();
    auto requiredExtensionNames = GetRequiredInstanceExtensionNames();
    mInstance = std::make_unique<Instance>(requiredLayerNames, requiredExtensionNames);
    mInstance->TryCreate(mAppInfo.GetDescriptor());

    if (Core::Build::configuration == Core::Build::Configuration::Debug) {
        mDebugger = std::make_unique<Debugger>(mInstance->GetHandle(), [&](MessageSeverity const &messageSeverity, MessageType const &messageType, std::string_view message) {
            auto &outputStream = (messageSeverity >= MessageSeverity::Warning ? std::cerr : std::cout);
            outputStream << message << std::endl;
        });
        mDebugger->TryCreate();
    }
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

VulkanContext::~VulkanContext() noexcept {
    if (Core::Build::configuration == Core::Build::Configuration::Debug) {
        mDebugger->Destroy();
    }

    mInstance->Destroy();
}