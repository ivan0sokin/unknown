#ifndef UNKNOWN_DEBUGGER_H
#define UNKNOWN_DEBUGGER_H

#include "VulkanHandle.h"

enum class MessageSeverity {
    None = 0,
    Critical = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
    Major = Critical | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT,
    Moderate = Major | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT,
    Low = Moderate | VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
};

enum class MessageType {
    None = 0,
    General = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT,
    Validation = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT,
    Perfomance = VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
    Shared = General | Validation | Perfomance
};

using DebuggerCallback = std::function<void(MessageSeverity const &messageSeverity, MessageType const &messageType,
                                            std::string_view const &message)>;

class Debugger : public VulkanHandle<VkDebugUtilsMessengerEXT> {
public:
    Debugger() = default;
    Debugger(VkInstance instance, MessageSeverity callbackMessageSeverity, MessageType callbackMessageType, DebuggerCallback callback) noexcept;
    ~Debugger() noexcept override;

    void TryCreate();
    void Destroy() noexcept;
private:
    static VKAPI_ATTR VkBool32 VKAPI_CALL CallbackHandler(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                          VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                          VkDebugUtilsMessengerCallbackDataEXT const *pCallbackData,
                                                          void *pUserData);
private:
    VkInstance mInstance;
    DebuggerCallback mCallback;
    MessageSeverity mCallbackMessageSeverity = MessageSeverity::Low;
    MessageType mCallbackMessageType = MessageType::Shared;
};

#endif