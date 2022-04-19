#include "PhysicalDevice.h"

PhysicalDeviceDescriptor PhysicalDevice::GetDescriptor() const noexcept {
    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(mHandle, &properties);
    return { properties };
}

bool PhysicalDevice::SupportsExtensions(std::initializer_list<std::string_view> extensionNames) {
    constexpr char const *nullLayerName = nullptr;
    unsigned propertyCount;
    VulkanResult result = vkEnumerateDeviceExtensionProperties(mHandle, nullLayerName, &propertyCount, nullptr);
    if (!result.Success()) {
        throw std::runtime_error("Failed to get VkDeviceExtensionProperties count, result: " + result.ToString());
    }

    auto availableExtensionProperties = std::vector<VkExtensionProperties>(static_cast<std::size_t>(propertyCount));
    result = vkEnumerateDeviceExtensionProperties(mHandle, nullLayerName, &propertyCount, availableExtensionProperties.data());
    if (!result.Success()) {
        throw std::runtime_error("Failed to get VkDeviceExtensionProperties, result: " + result.ToString());
    }

    auto unsupportedExtensionNames = std::unordered_set<std::string_view>(extensionNames.begin(), extensionNames.end());
    std::ranges::for_each(std::as_const(availableExtensionProperties), [&](auto const &extensionProperty) {
        unsupportedExtensionNames.erase(std::string_view(extensionProperty.extensionName));
    });

    return unsupportedExtensionNames.empty();
}