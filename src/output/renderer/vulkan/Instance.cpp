#include "Instance.h"

Instance::Instance() {
    InitializeLayerProperties();
    InitializeExtensionProperties();
}

Instance::Instance(std::span<const char *> enabledLayerNames, std::span<const char *> enabledExtensionNames) noexcept : Instance() {
    mEnabledLayerNames.assign(enabledLayerNames.begin(), enabledLayerNames.end());
    mEnabledExtensionNames.assign(enabledExtensionNames.begin(), enabledExtensionNames.end());
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

void Instance::TryCreate(VkApplicationInfo const &applicationInfo) {
    if (!AreEnabledLayersSupported() || !AreEnabledExtensionsSupported()) {
        throw std::runtime_error("Some of enabled layers or extensions are not supported");
    }

    if (!IsRequiredAPIVersionSupported()) {
        throw std::runtime_error("Outdated Vulkan API version");
    }

    VkInstanceCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &applicationInfo,
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
    return std::ranges::all_of(mEnabledLayerNames, [&](auto enabledLayerName) {
        return std::ranges::find_if(std::as_const(mLayerProperties), [&](auto const &layerProperty) {
            return std::string_view(layerProperty.layerName) == std::string_view(enabledLayerName);
        }) != mLayerProperties.cend();
    });
}

bool Instance::AreEnabledExtensionsSupported() const noexcept {
    return std::ranges::all_of(mEnabledExtensionNames, [&](auto enabledExtensionName) {
        return std::ranges::find_if(std::as_const(mExtensionProperties), [&](auto const &extensionProperty) {
            return std::string_view(extensionProperty.extensionName) == std::string_view(enabledExtensionName);
        }) != mExtensionProperties.cend();
    });
}

void Instance::Destroy() noexcept {
    if (mHandle != nullptr) {
        vkDestroyInstance(mHandle, nullAllocator);
        mHandle = nullptr;
    }
}

Instance::~Instance() noexcept {
    Destroy();
}