#include "Renderer.h"

Renderer::Renderer(GraphicsAPI const &API) noexcept {
    mGraphicsAPI = API;
}

void Renderer::Initialize(WindowProperties const &windowProperties) {
    mContext = std::make_unique<VulkanContext>(windowProperties);
    mContext->Initialize();
}