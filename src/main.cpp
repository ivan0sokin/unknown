#include <iostream>
#include <memory>

#include "output/Window.h"
#include "output/renderer/Renderer.h"

int main() {
    std::unique_ptr<Window> window;
    try {
        window = std::make_unique<Window>(640, 480, "Hello, w1!");
        window->Open();
    } catch (std::exception const &e) {
        std::cerr << e.what() << '\n';
        exit(-1);
    }

    auto vulkanRenderer = Renderer(GraphicsAPI::Vulkan);

    while (!window->ShouldBeClosed()) {
        window->PollEvents();
    }

    window->Close();

    return 0;
}