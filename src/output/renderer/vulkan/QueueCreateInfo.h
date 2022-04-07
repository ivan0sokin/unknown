#ifndef UNKNOWN_QUEUECREATEINFO_H
#define UNKNOWN_QUEUECREATEINFO_H

#include "VulkanDescriptor.h"

constexpr float HIGH_PRIORITY = 1.0f;

class QueueCreateInfo : public VulkanDescriptor<VkDeviceQueueCreateInfo> {
public:
    QueueCreateInfo() = default;
    constexpr QueueCreateInfo(unsigned familyIndex, std::initializer_list<float> priorities) noexcept {
        mDescriptor = {
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .queueFamilyIndex = familyIndex,
            .queueCount = static_cast<unsigned>(priorities.size()),
            .pQueuePriorities = std::data(priorities)
        };
    }
};


#endif