#ifndef UNKNOWN_WINDOW_H
#define UNKNOWN_WINDOW_H

#include <string>
#include <string_view>
#include <stdexcept>

#include <GLFW/glfw3.h>

class Window {
public:
    Window() = default;
    Window(int width, int height, std::string_view title);
    ~Window() noexcept;

    void Open();
    void Close() noexcept;

    void PollEvents();
    bool ShouldBeClosed();
private:
    void TryInitializeGLFW();
    void TryTerminateGLFW();
private:
    int mWidth, mHeight;
    std::string mTitle;
    GLFWwindow *mHandle;
};

#endif