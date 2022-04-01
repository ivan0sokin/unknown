#ifndef UNKNOWN_VULKANRESULT_H
#define UNKNOWN_VULKANRESULT_H

#include <unordered_map>

#include <vulkan/vulkan.hpp>

class VulkanResult {
public:
    VulkanResult() = default;
    constexpr VulkanResult(VkResult const &result) noexcept : mResult(result) {}

    constexpr bool Success() const noexcept { return mResult == VK_SUCCESS; }
    std::string ToString() const;
private:
    VkResult mResult;
    static std::unordered_map<int, std::string> resultCodeNames;
};

#endif