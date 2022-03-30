#ifndef UNKNOWN_VULKANDESCRIPTOR_H
#define UNKNOWN_VULKANDESCRIPTOR_H

#include "VulkanDefinitions.h"

template <typename T>
class VulkanDescriptor {
public:
    VulkanDescriptor() = default;
    virtual ~VulkanDescriptor() = default;
    constexpr virtual T GetDescriptor() const noexcept { return mDescriptor; }
protected:
    T mDescriptor;
};

#endif