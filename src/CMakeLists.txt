cmake_minimum_required(VERSION 3.3)
project(unknown)

if (WIN32)
    message("Platform: WIN32")
    set(GLFW_EXPOSE -DGLFW_EXPOSE_NATIVE_WIN32)
elseif(APPLE)
    message("Platform: APPLE")
    set(GLFW_EXPOSE -DGLFW_EXPOSE_NATIVE_COCOA)
elseif(UNIX AND NOT APPLE)
    message("Platform: UNIX AND NOT APPLE")
    set(GLFW_EXPOSE -DGLFW_EXPOSE_NATIVE_X11)
endif ()

message("GLFW expose definition: ${GLFW_EXPOSE}")

add_definitions(-DGLFW_INCLUDE_NONE ${GLFW_EXPOSE} -DDEBUG)

set(GLFW_DIR D:/coding/third_party_libraries/glfw)
set(VULKAN_DIR D:/coding/third_party_libraries/vulkan)
set(SOURCES main.cpp
            output/window/Window.cpp
            output/renderer/Renderer.cpp
            output/renderer/vulkan/VulkanContext.cpp
            output/renderer/vulkan/VulkanResult.cpp
            output/renderer/vulkan/Instance.cpp
            output/renderer/vulkan/Debugger.cpp
            output/renderer/vulkan/Surface.cpp
            output/renderer/vulkan/PhysicalDevice.cpp
            output/renderer/vulkan/QueueFamilyIndices.cpp
            output/renderer/vulkan/LogicalDevice.cpp
            output/renderer/vulkan/SurfaceProperties.cpp
            output/renderer/vulkan/SwapChain.cpp)

find_library(GLFW NAMES glfw3 PATHS ${GLFW_DIR}/*)
find_library(VULKAN NAMES vulkan-1 PATHS ${VULKAN_DIR}/*)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${GLFW} ${VULKAN})
target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_DIR}/include ${VULKAN_DIR}/include)

message("GLFW library path: ${GLFW}")
message("Vulkan library path: ${VULKAN}")