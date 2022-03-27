#include "Instance.h"

Instance::Instance() noexcept {
    InitializeLayerProperties();
    InitializeExtensionProperties();
}

Instance::Instance(std::span<const char *> enabledLayerNames, std::span<const char *> enabledExtensionNames) noexcept : Instance() {
    mEnabledLayerNames.assign(enabledLayerNames.begin(), enabledLayerNames.end());
    mEnabledExtensionNames.assign(enabledExtensionNames.begin(), enabledExtensionNames.end());
}

void Instance::InitializeLayerProperties() noexcept {
    unsigned propertyCount;
    vkEnumerateInstanceLayerProperties(&propertyCount, nullptr);

    mLayerProperties.resize(static_cast<std::size_t>(propertyCount));
    vkEnumerateInstanceLayerProperties(&propertyCount, mLayerProperties.data());
}

void Instance::InitializeExtensionProperties() noexcept {
    unsigned propertyCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &propertyCount, nullptr);

    mExtensionProperties.resize(static_cast<std::size_t>(propertyCount));
    vkEnumerateInstanceExtensionProperties(nullptr, &propertyCount, mExtensionProperties.data());
}

void Instance::TryCreate(VkApplicationInfo const &applicationInfo) {
    if (!CheckEnabledLayersSupported() || !CheckEnabledExtensionsSupported()) {
        throw std::runtime_error("Some of enabled layers or extensions are not supported");
    }

    VkInstanceCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &applicationInfo,
        .enabledLayerCount = static_cast<unsigned>(mEnabledLayerNames.size()),
        .ppEnabledLayerNames = mEnabledLayerNames.data(),
        .enabledExtensionCount = static_cast<unsigned>(mEnabledExtensionNames.size()),
        .ppEnabledExtensionNames = mEnabledExtensionNames.data()
    };

    VkResult res = vkCreateInstance(&createInfo, nullptr, &mInstance);
    if (res != VK_SUCCESS) {
        throw std::runtime_error("Failed to create VkInstance, error code: " + std::to_string(res));
    }
}

bool Instance::CheckEnabledLayersSupported() noexcept {
    return std::ranges::all_of(mEnabledLayerNames, [&](auto enabledLayerName) {
        return std::ranges::find_if(std::as_const(mLayerProperties), [&](auto const &layerProperty) {
            return std::string_view(layerProperty.layerName) == std::string_view(enabledLayerName);
        }) != mLayerProperties.cend();
    });
}

bool Instance::CheckEnabledExtensionsSupported() noexcept {
    return std::ranges::all_of(mEnabledExtensionNames, [&](auto enabledExtensionName) {
        return std::ranges::find_if(std::as_const(mExtensionProperties), [&](auto const &extensionProperty) {
            return std::string_view(extensionProperty.extensionName) == std::string_view(enabledExtensionName);
        }) != mExtensionProperties.cend();
    });
}

Instance::~Instance() noexcept {
    vkDestroyInstance(mInstance, nullptr);
}