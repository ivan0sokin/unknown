#ifndef UNKNOWN_VULKANDEFINITIONS_H
#define UNKNOWN_VULKANDEFINITIONS_H

#include <vulkan/vulkan.hpp>

constexpr VkAllocationCallbacks *nullAllocator = nullptr;

inline VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerCreateInfoEXT const *pCreateInfo, VkAllocationCallbacks const *pAllocator, VkDebugUtilsMessengerEXT *pDebugMessenger) {
    auto pFunction = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
    if (pFunction != nullptr) {
        return pFunction(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

inline void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, VkAllocationCallbacks const *pAllocator) {
    auto pFunction = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));
    if (pFunction != nullptr) {
        pFunction(instance, debugMessenger, pAllocator);
    }
}

#endif