#ifndef UNKNOWN_VULKANHANDLE_H
#define UNKNOWN_VULKANHANDLE_H

#include <vulkan/vulkan.hpp>

template <typename T>
class VulkanHandle {
public:
    VulkanHandle() = default;
    virtual ~VulkanHandle() = default;
    constexpr virtual T GetHandle() const noexcept { return mHandle; }
protected:
    T mHandle;
};

#endif