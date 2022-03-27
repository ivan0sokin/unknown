#ifndef UNKNOWN_VULKANDESCRIPTOR_H
#define UNKNOWN_VULKANDESCRIPTOR_H

#include <vulkan/vulkan.hpp>

template <typename T>
class VulkanDescriptor {
public:
    VulkanDescriptor() = default;
    virtual ~VulkanDescriptor() = default;
    constexpr virtual T GetDescriptor() const noexcept = 0;
};

#endif