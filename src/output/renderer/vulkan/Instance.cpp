#include "Instance.h"

Instance::Instance(std::span<const char *> enabledLayerNames, std::span<const char *> enabledExtensionNames, VkApplicationInfo const &applicationInfo) noexcept : mApplicationInfo(applicationInfo) {
    mEnabledLayerNames.assign(enabledLayerNames.begin(), enabledLayerNames.end());
    mEnabledExtensionNames.assign(enabledExtensionNames.begin(), enabledExtensionNames.end());
}

void Instance::TryInitialize() {
    InitializeLayerProperties();
    InitializeExtensionProperties();

    if (!AreEnabledLayersSupported() || !AreEnabledExtensionsSupported()) {
        throw std::runtime_error("Some of enabled layers or extensions are not supported");
    }

    if (!IsRequiredAPIVersionSupported()) {
        throw std::runtime_error("Outdated Vulkan API version");
    }
}

void Instance::InitializeLayerProperties() {
    unsigned propertyCount;
    VulkanResult result = vkEnumerateInstanceLayerProperties(&propertyCount, nullptr);
    if (!result.Success()) {
        throw std::runtime_error("Failed to get VkLayerProperties count, result: " + result.ToString());
    }

    mLayerProperties.resize(static_cast<std::size_t>(propertyCount));
    result = vkEnumerateInstanceLayerProperties(&propertyCount, mLayerProperties.data());
    if (!result.Success()) {
        throw std::runtime_error("Failed to get VkLayerProperties, result: " + result.ToString());
    }
}

void Instance::InitializeExtensionProperties() {
    unsigned propertyCount;
    VulkanResult result = vkEnumerateInstanceExtensionProperties(nullptr, &propertyCount, nullptr);
    if (!result.Success()) {
        throw std::runtime_error("Failed to get VkExtensionProperties count, result: " + result.ToString());
    }

    mExtensionProperties.resize(static_cast<std::size_t>(propertyCount));
    result = vkEnumerateInstanceExtensionProperties(nullptr, &propertyCount, mExtensionProperties.data());
    if (!result.Success()) {
        throw std::runtime_error("Failed to get VkExtensionProperties, result: " + result.ToString());
    }
}

void Instance::TryCreate() {
    VkInstanceCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &mApplicationInfo,
        .enabledLayerCount = static_cast<unsigned>(mEnabledLayerNames.size()),
        .ppEnabledLayerNames = mEnabledLayerNames.data(),
        .enabledExtensionCount = static_cast<unsigned>(mEnabledExtensionNames.size()),
        .ppEnabledExtensionNames = mEnabledExtensionNames.data()
    };

    VulkanResult result = vkCreateInstance(&createInfo, nullAllocator, &mHandle);
    if (!result.Success()) {
        throw std::runtime_error("Failed to create VkInstance, result: " + result.ToString());
    }
}

bool Instance::IsRequiredAPIVersionSupported() const {
    unsigned supportedAPIVersion;
    VulkanResult result = vkEnumerateInstanceVersion(&supportedAPIVersion);
    if (!result.Success()) {
        throw std::runtime_error("Failed to enumerate instance version, result: " + result.ToString());
    }

    return supportedAPIVersion >= minimumRequiredAPIVersion.ToNumber();
}

bool Instance::AreEnabledLayersSupported() const noexcept {
    auto enabledLayerNames = std::unordered_set<std::string_view>(mEnabledLayerNames.cbegin(), mEnabledLayerNames.cend());
    std::ranges::for_each(std::as_const(mLayerProperties), [&](auto const &layerProperty) {
        enabledLayerNames.erase(std::string_view(layerProperty.layerName));
    });

    return enabledLayerNames.empty();
}

bool Instance::AreEnabledExtensionsSupported() const noexcept {
    auto enabledExtensionNames = std::unordered_set<std::string_view>(mEnabledExtensionNames.cbegin(), mEnabledExtensionNames.cend());
    std::ranges::for_each(std::as_const(mExtensionProperties), [&](auto const &extensionProperty) {
        enabledExtensionNames.erase(std::string_view(extensionProperty.extensionName));
    });

    return enabledExtensionNames.empty();
}

std::vector<PhysicalDevice> Instance::GetPhysicalDeviceList() {
    unsigned physicalDeviceCount;
    VulkanResult result = vkEnumeratePhysicalDevices(mHandle, &physicalDeviceCount, nullptr);
    if (!result.Success()) {
        throw std::runtime_error("Failed to get VkPhysicalDevice count, result: " + result.ToString());
    }

    auto physicalDeviceHandles = std::vector<VkPhysicalDevice>(static_cast<std::size_t>(physicalDeviceCount));
    result = vkEnumeratePhysicalDevices(mHandle, &physicalDeviceCount, physicalDeviceHandles.data());
    if (!result.Success()) {
        throw std::runtime_error("Failed to get VkPhysicalDevices, result: " + result.ToString());
    }

    std::vector<PhysicalDevice> physicalDevices;
    physicalDevices.reserve(static_cast<std::size_t>(physicalDeviceCount));
    std::ranges::for_each(std::as_const(physicalDeviceHandles), [&](VkPhysicalDevice physicalDeviceHandle) {
        physicalDevices.push_back(physicalDeviceHandle);
    });

    return physicalDevices;
}

void Instance::Destroy() noexcept {
    if (mHandle != VK_NULL_HANDLE) {
        vkDestroyInstance(mHandle, nullAllocator);
        mHandle = VK_NULL_HANDLE;
    }
}

Instance::~Instance() noexcept {
    Destroy();
}