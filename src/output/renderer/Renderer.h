#ifndef UNKNOWN_RENDERER_H
#define UNKNOWN_RENDERER_H

#include <memory>

#include "GraphicsContext.h"

enum class GraphicsAPI {
    Vulkan = 0
};

class Renderer {
public:
    Renderer(GraphicsAPI const &API) noexcept;
    void Initialize();
private:
    std::unique_ptr<GraphicsContext> mContext;
};

#endif