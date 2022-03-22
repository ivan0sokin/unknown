#include "Renderer.h"
#include "vulkan/VulkanContext.h"

Renderer::Renderer(GraphicsAPI const &API) {
    mContext = std::make_unique<VulkanContext>();
}

void Renderer::Initialize() {
    mContext->Initialize();
}