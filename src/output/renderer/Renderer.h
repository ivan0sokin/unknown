#ifndef UNKNOWN_RENDERER_H
#define UNKNOWN_RENDERER_H

#include "../window/WindowProperties.h"
#include "vulkan/VulkanContext.h"

#include <memory>

enum class GraphicsAPI {
    Vulkan = 0
};

class Renderer {
public:
    Renderer() = default;
    Renderer(GraphicsAPI const &API) noexcept;
    void Initialize(WindowProperties const &windowProperties);
private:
    GraphicsAPI mGraphicsAPI;
    std::unique_ptr<VulkanContext> mContext;
};

#endif