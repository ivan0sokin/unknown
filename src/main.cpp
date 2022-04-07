#include <iostream>

#include "output/window/Window.h"
#include "output/renderer/Renderer.h"

int main() {
    auto window = Window(640, 480, "Hello, w1!");
    try {
        window.Open();
    } catch (std::exception const &e) {
        std::cerr << e.what() << '\n';
        exit(-1);
    }

    auto vulkanRenderer = Renderer(GraphicsAPI::Vulkan);
    try {
        vulkanRenderer.Initialize(window.GetProperties());
    } catch (std::exception const &e) {
        std::cerr << e.what() << '\n';
        exit(-1);
    }

    while (!window.ShouldBeClosed()) {
        window.PollEvents();
    }

    window.Close();

    return 0;
}