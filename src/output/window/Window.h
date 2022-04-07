#ifndef UNKNOWN_WINDOW_H
#define UNKNOWN_WINDOW_H

#include <string>
#include <string_view>
#include <stdexcept>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "WindowProperties.h"

class Window {
public:
    Window() = default;
    Window(int width, int height, std::string_view title) noexcept;
    ~Window() noexcept;

    void Open();
    void OpenFullscreen();
    void Close() noexcept;
    void PollEvents();

    WindowProperties GetProperties() noexcept;

    bool ShouldBeClosed();
    constexpr bool IsOpened() const { return mIsOpened; }
private:
    void TryInitializeGLFW();
    void TryTerminateGLFW();
    void SetSpecificWindowHints() noexcept;
    void TryCreateWindow(GLFWmonitor *fullscreenModeMonitor, GLFWwindow *sharingWindow);
private:
    int mWidth, mHeight;
    std::string mTitle;
    bool mIsOpened = false;
    GLFWwindow *mHandle;
};

#endif