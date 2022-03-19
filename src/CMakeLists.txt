cmake_minimum_required(VERSION 3.3)
project(unknown)


add_definitions(-DGLFW_STATIC)

set(GLFW_DIR D:/coding/third_party_libraries/glfw)
set(VULKAN_DIR D:/coding/third_party_libraries/vulkan)
set(SOURCES main.cpp
            output/Window.cpp)

find_library(GLFW NAMES glfw3 PATHS ${GLFW_DIR}/*)
find_library(VULKAN NAMES vulkan-1 PATHS ${VULKAN_DIR}/*)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${GLFW} ${VULKAN})
target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_DIR}/include ${VULKAN_DIR}/include)

message(${GLFW}\n${VULKAN})
