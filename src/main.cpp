#include <iostream>
#include <memory>

#include "output/Window.h"

int main() {
    std::unique_ptr<Window> window;
    try {
        window = std::make_unique<Window>(300, 300, "Hello, w1!");
        window->Open();
    } catch (std::exception const &e) {
        std::cerr << e.what() << '\n';
        exit(-1);
    }

    while (!window->ShouldBeClosed()) {
        window->PollEvents();
    }

    window->Close();

    return 0;
}