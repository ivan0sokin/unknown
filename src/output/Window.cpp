#include "Window.h"

static unsigned int windowsCount = 0;

Window::Window(int width, int height, std::string_view title) : mWidth(width), mHeight(height), mTitle(title) {
    TryInitializeGLFW();
}

void Window::TryInitializeGLFW() {
    if (windowsCount == 0 && !glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
}

void Window::TryTerminateGLFW() {
    if (windowsCount == 0) {
        glfwTerminate();
    }
}

void Window::TryCreateWindow(GLFWmonitor *fullscreenModeMonitor, GLFWwindow *sharingWindow) {
    if (mIsOpened) {
        throw std::runtime_error("Window is already opened");
    }

    mHandle = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), fullscreenModeMonitor, sharingWindow);

    if (!mHandle) {
        TryTerminateGLFW();
        throw std::runtime_error("Failed to create window");
    }

    ++windowsCount;
    mIsOpened = true;
}

void Window::Open() {
    TryCreateWindow(nullptr, nullptr);
}

void Window::OpenFullscreen() {
    TryCreateWindow(glfwGetPrimaryMonitor(), nullptr);
}

void Window::Close() noexcept {
    glfwDestroyWindow(mHandle);
    mIsOpened = false;
}

void Window::PollEvents() {
    glfwPollEvents();
}

Window::~Window() {
    --windowsCount;
    TryTerminateGLFW();
}

bool Window::ShouldBeClosed() {
    return glfwWindowShouldClose(mHandle);
}