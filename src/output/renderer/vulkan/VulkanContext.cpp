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
    mInstance->TryCreate();
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

    mPhysicalDevices = mInstance->GetPhysicalDeviceList();
    TryPickPrimaryPhysicalDevice();
    DescribePrimaryPhysicalDevice();

    auto queueFamilyIndices = QueueFamilyIndices(mPrimaryPhysicalDevice->GetHandle(), mSurface->GetHandle());
    queueFamilyIndices.TryInitialize();
    unsigned graphicsQueueFamilyIndex = queueFamilyIndices.TryGetGraphicsQueueFamilyIndex().value();
    unsigned presentQueueFamilyIndex = queueFamilyIndices.TryGetPresentQueueFamilyIndex().value();

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfoList = { QueueCreateInfo(graphicsQueueFamilyIndex, { HIGH_PRIORITY }).GetDescriptor() };
    if (!queueFamilyIndices.AreGraphicsAndPresentFamilyIndicesSimilar()) {
        queueCreateInfoList.push_back(QueueCreateInfo(presentQueueFamilyIndex, { HIGH_PRIORITY }).GetDescriptor());
    }

    auto requiredLogicalDeviceExtensionNames = GetRequiredLogicalDeviceExtensionNames();
    mLogicalDevice = std::make_unique<LogicalDevice>(mPrimaryPhysicalDevice->GetHandle(), queueCreateInfoList, requiredLogicalDeviceExtensionNames);
    mLogicalDevice->TryCreate();

    auto queueFamilyIndexList = std::array<unsigned, 2>{ graphicsQueueFamilyIndex, presentQueueFamilyIndex };
    auto surfaceProperties = SurfaceProperties(mSurface->GetHandle(), mPrimaryPhysicalDevice->GetHandle(), mWindowProperties);
    mSwapChain = std::make_unique<SwapChain>(
        mLogicalDevice->GetHandle(),
        mSurface->GetHandle(),
        surfaceProperties,
        queueFamilyIndexList
    );
    mSwapChain->TryCreate();
}

std::vector<char const *> VulkanContext::GetRequiredInstanceLayerNames() const noexcept {
    std::vector<char const *> requiredLayers;

    if (Core::Build::CONFIGURATION == Core::Build::Configuration::Debug) {
        requiredLayers.insert(requiredLayers.cend(), debugLayers.cbegin(), debugLayers.cend());
    }


    return requiredLayers;
}

std::vector<char const *> VulkanContext::GetRequiredInstanceExtensionNames() const noexcept {
    auto requiredExtensions = std::vector<char const *>{ Surface::GetExtensionName().data(), Surface::GetPlatformSpecificExtensionName().data() };

    if (Core::Build::CONFIGURATION == Core::Build::Configuration::Debug) {
        requiredExtensions.insert(requiredExtensions.cend(), debugExtensions.cbegin(), debugExtensions.cend());
    }

    return requiredExtensions;
}

std::vector<char const *> VulkanContext::GetRequiredLogicalDeviceExtensionNames() const noexcept {
    auto requiredExtensions = std::vector<char const*>{ SwapChain::GetRequiredDeviceExtensionName().data() };
    return requiredExtensions;
}

void VulkanContext::TryPickPrimaryPhysicalDevice() {
    auto compatiblePhysicalDevice = std::ranges::find_if(mPhysicalDevices, [&](auto &physicalDevice) {
        return IsDeviceCompatible(physicalDevice);
    });

    if (compatiblePhysicalDevice == mPhysicalDevices.end()) {
        throw std::runtime_error("Could not find any compatible GPU");
    }

    mPrimaryPhysicalDevice.reset(&*compatiblePhysicalDevice);
}

void VulkanContext::DescribePrimaryPhysicalDevice() const noexcept {
    auto descriptor = mPrimaryPhysicalDevice->GetDescriptor();
    std::cout << "Compatible GPU: " << descriptor.Name() << ", vendor id: " << std::hex << "0x" << descriptor.VendorID() << std::endl;
}

bool VulkanContext::IsDeviceCompatible(PhysicalDevice &physicalDevice) {
    auto queueFamilyIndices = QueueFamilyIndices(physicalDevice.GetHandle(), mSurface->GetHandle());
    queueFamilyIndices.TryInitialize();

    return queueFamilyIndices.TryGetGraphicsQueueFamilyIndex() &&
           queueFamilyIndices.TryGetPresentQueueFamilyIndex() &&
           physicalDevice.SupportsExtensions({ SwapChain::GetRequiredDeviceExtensionName() });
}

VulkanContext::~VulkanContext() noexcept {
    mSwapChain->Destroy();
    mLogicalDevice->Destroy();
    mSurface->Destroy();

    if (Core::Build::CONFIGURATION == Core::Build::Configuration::Debug) {
        mDebugger->Destroy();
    }

    mInstance->Destroy();

    mPrimaryPhysicalDevice.release();
}