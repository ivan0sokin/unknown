#include "VulkanContext.h"

void VulkanContext::Initialize() {
    auto applicationInfo = ApplicationInfo(
        Core::Application::NAME,
        Core::Application::VERSION,
        Core::Engine::NAME,
        Core::Engine::VERSION,
        Instance::GetMinimumRequiredAPIVersion()
    );
    applicationInfo.Initialize();

    auto requiredLayerNames = GetRequiredInstanceLayerNames();
    auto requiredExtensionNames = GetRequiredInstanceExtensionNames();

    mInstance = std::make_unique<Instance>(requiredLayerNames, requiredExtensionNames);
    mInstance->TryCreate(applicationInfo.GetDescriptor());

    if (Core::Build::CONFIGURATION == Core::Build::Configuration::Debug) {
        mDebugger = std::make_unique<Debugger>(mInstance->GetHandle(), preferredCallbackMessageSeverity, preferredCallbackMessageType, [&](MessageSeverity const &messageSeverity, MessageType const &messageType, std::string_view message) {
            auto &outputStream = (messageSeverity >= MessageSeverity::Major ? std::cerr : std::cout);
            outputStream << message << std::endl;
        });
        mDebugger->TryCreate();
    }

    mSurface = std::make_unique<Surface>(mInstance->GetHandle(), mWindowProperties.windowHandle);
    mSurface->TryCreate();

    mPhysicalDevices = PhysicalDevice::GetPhysicalDeviceList(mInstance->GetHandle());
    PickPrimaryPhysicalDevice();
}

std::vector<char const *> VulkanContext::GetRequiredInstanceLayerNames() noexcept {
    std::vector<char const *> requiredLayers;

    if (Core::Build::CONFIGURATION == Core::Build::Configuration::Debug) {
        requiredLayers.insert(requiredLayers.cend(), debugLayers.cbegin(), debugLayers.cend());
    }

    requiredLayers.push_back("VK_LAYER_VALVE_steam_overlay");

    return requiredLayers;
}

std::vector<char const *> VulkanContext::GetRequiredInstanceExtensionNames() noexcept {
    std::vector<char const *> requiredExtensions;
    requiredExtensions.insert(requiredExtensions.cend(), { Surface::GetExtensionName(), Surface::GetPlatformSpecificExtensionName() });

    if (Core::Build::CONFIGURATION == Core::Build::Configuration::Debug) {
        requiredExtensions.insert(requiredExtensions.cend(), debugExtensions.cbegin(), debugExtensions.cend());
    }

    return requiredExtensions;
}

void VulkanContext::PickPrimaryPhysicalDevice() {
    auto suitablePhysicalDevice = std::ranges::find_if(mPhysicalDevices, [&](auto &physicalDevice) {
        auto queueFamilyIndices = QueueFamilyIndices(physicalDevice.GetHandle(), mSurface->GetHandle());
        queueFamilyIndices.Initialize();
        return queueFamilyIndices.TryGetGraphicsQueueFamilyIndex() && queueFamilyIndices.TryGetPresentQueueFamilyIndex();
    });

    if (suitablePhysicalDevice == mPhysicalDevices.end()) {
        throw std::runtime_error("Could not find any compatible GPU");
    }

    mPrimaryPhysicalDevice.reset(&*suitablePhysicalDevice);
}

VulkanContext::~VulkanContext() noexcept {
    mPrimaryPhysicalDevice.release();

    mSurface->Destroy();

    if (Core::Build::CONFIGURATION == Core::Build::Configuration::Debug) {
        mDebugger->Destroy();
    }

    mInstance->Destroy();
}