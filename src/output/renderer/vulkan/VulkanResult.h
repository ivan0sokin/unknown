#ifndef UNKNOWN_VULKANRESULT_H
#define UNKNOWN_VULKANRESULT_H

#include <vulkan/vulkan.hpp>

class VulkanResult {
public:
    VulkanResult() = default;
    constexpr VulkanResult(VkResult const &result) noexcept : mResult(result) {}

    constexpr bool Success() noexcept { return mResult == VK_SUCCESS; }
    std::string ToString();
private:
    VkResult mResult;
    static std::unordered_map<int, std::string> resultCodeNames;
};

#endif