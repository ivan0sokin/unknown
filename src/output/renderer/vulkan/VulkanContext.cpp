#include "VulkanContext.h"

void VulkanContext::Initialize() {
    auto applicationInfo = ApplicationInfo(
        Core::Application::NAME,
        Core::Application::VERSION,
        Core::Engine::NAME,
        Core::Engine::VERSION,
        Instance::GetMinimumRequiredAPIVersion()
    );

    auto requiredLayerNames = GetRequiredInstanceLayerNames();
    auto requiredExtensionNames = GetRequiredInstanceExtensionNames();
    mInstance = std::make_unique<Instance>(requiredLayerNames, requiredExtensionNames, applicationInfo.GetDescriptor());
    mInstance->TryInitialize();
    mInstance->TryCreate();

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
    TryPickPrimaryPhysicalDevice();

    auto queueFamilyIndices = QueueFamilyIndices(mPrimaryPhysicalDevice->GetHandle(), mSurface->GetHandle());
    queueFamilyIndices.TryInitialize();

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfoList = { QueueCreateInfo(queueFamilyIndices.TryGetGraphicsQueueFamilyIndex().value(), { HIGH_PRIORITY }).GetDescriptor() };
    if (!queueFamilyIndices.AreGraphicsAndPresentFamilyIndicesSimilar()) {
        queueCreateInfoList.push_back(QueueCreateInfo(queueFamilyIndices.TryGetPresentQueueFamilyIndex().value(), { HIGH_PRIORITY }).GetDescriptor());
    }

    mLogicalDevice = std::make_unique<LogicalDevice>(mPrimaryPhysicalDevice->GetHandle(), queueCreateInfoList);
    mLogicalDevice->TryCreate();
}

std::vector<char const *> VulkanContext::GetRequiredInstanceLayerNames() const noexcept {
    std::vector<char const *> requiredLayers;

    if (Core::Build::CONFIGURATION == Core::Build::Configuration::Debug) {
        requiredLayers.insert(requiredLayers.cend(), debugLayers.cbegin(), debugLayers.cend());
    }

    return requiredLayers;
}

std::vector<char const *> VulkanContext::GetRequiredInstanceExtensionNames() const noexcept {
    std::vector<char const *> requiredExtensions;
    requiredExtensions.insert(requiredExtensions.cend(), { Surface::GetExtensionName(), Surface::GetPlatformSpecificExtensionName() });

    if (Core::Build::CONFIGURATION == Core::Build::Configuration::Debug) {
        requiredExtensions.insert(requiredExtensions.cend(), debugExtensions.cbegin(), debugExtensions.cend());
    }

    return requiredExtensions;
}

void VulkanContext::TryPickPrimaryPhysicalDevice() {
    auto suitablePhysicalDevice = std::ranges::find_if(mPhysicalDevices, [&](auto &physicalDevice) {
        auto queueFamilyIndices = QueueFamilyIndices(physicalDevice.GetHandle(), mSurface->GetHandle());
        queueFamilyIndices.TryInitialize();
        return queueFamilyIndices.TryGetGraphicsQueueFamilyIndex() && queueFamilyIndices.TryGetPresentQueueFamilyIndex();
    });

    if (suitablePhysicalDevice == mPhysicalDevices.end()) {
        throw std::runtime_error("Could not find any compatible GPU");
    }

    mPrimaryPhysicalDevice.reset(&*suitablePhysicalDevice);
}

VulkanContext::~VulkanContext() noexcept {
    mLogicalDevice->Destroy();

    mPrimaryPhysicalDevice.release();

    mSurface->Destroy();

    if (Core::Build::CONFIGURATION == Core::Build::Configuration::Debug) {
        mDebugger->Destroy();
    }

    mInstance->Destroy();
}