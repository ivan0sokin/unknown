#include "QueueFamilyIndices.h"

void QueueFamilyIndices::TryInitialize() {
    auto queueFamilyPropertiesList = GetQueueFamilyPropertiesList();
    unsigned queueFamilyIndex = 0;
    std::ranges::find_if(queueFamilyPropertiesList | std::views::transform([](auto const &properties) { return properties.queueFlags; }), [&](auto queueFlags) {
        if (queueFlags | VK_QUEUE_GRAPHICS_BIT) {
            mGraphicsQueueFamilyIndex = queueFamilyIndex;
        }

        if (QueueFamilyIndexIsSupportedBySurface(queueFamilyIndex)) {
            mPresentQueueFamilyIndex = queueFamilyIndex;
        }

        ++queueFamilyIndex;
        return mGraphicsQueueFamilyIndex && mPresentQueueFamilyIndex;
    });
}

std::vector<VkQueueFamilyProperties> QueueFamilyIndices::GetQueueFamilyPropertiesList() noexcept {
    unsigned propertyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(mPhysicalDevice, &propertyCount, nullptr);

    auto queueFamilyPropertiesList = std::vector<VkQueueFamilyProperties>(static_cast<std::size_t>(propertyCount));
    vkGetPhysicalDeviceQueueFamilyProperties(mPhysicalDevice, &propertyCount, queueFamilyPropertiesList.data());

    return queueFamilyPropertiesList;
}

bool QueueFamilyIndices::QueueFamilyIndexIsSupportedBySurface(unsigned queueFamilyIndex) {
    VkBool32 isQueueFamilySupportedBySurface;
    VulkanResult result = vkGetPhysicalDeviceSurfaceSupportKHR(mPhysicalDevice, queueFamilyIndex, mSurface, &isQueueFamilySupportedBySurface);
    if (!result.Success()) {
        throw std::runtime_error("Failed to get physical device surface support for queue " + std::to_string(queueFamilyIndex) + ", result: "  + result.ToString());
    }

    return isQueueFamilySupportedBySurface == VK_TRUE;
}

bool QueueFamilyIndices::AreGraphicsAndPresentFamilyIndicesSimilar() const {
    if (!mGraphicsQueueFamilyIndex || !mPresentQueueFamilyIndex) {
        throw std::runtime_error("Graphics or Present queue family was not found");
    }

    return mGraphicsQueueFamilyIndex == mPresentQueueFamilyIndex;
}