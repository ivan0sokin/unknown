#ifndef UNKNOWN_VULKANCONTEXT_H
#define UNKNOWN_VULKANCONTEXT_H

#include <vulkan/vulkan.hpp>

#include "../GraphicsContext.h"

class VulkanContext : public GraphicsContext {
public:
    VulkanContext() = default;
    ~VulkanContext() override = default;
    void Initialize() override;
};

#endif