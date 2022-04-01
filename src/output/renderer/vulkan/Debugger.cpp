#include "Debugger.h"

Debugger::Debugger(VkInstance instance, MessageSeverity callbackMessageSeverity, MessageType callbackMessageType, DebuggerCallback callback) noexcept :
        mInstance(instance), mCallbackMessageSeverity(callbackMessageSeverity),
        mCallbackMessageType(callbackMessageType), mCallback(std::move(callback)) {}

void Debugger::TryCreate() {
    VkDebugUtilsMessengerCreateInfoEXT createInfo = {
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        .messageSeverity = static_cast<VkDebugUtilsMessageSeverityFlagsEXT>(mCallbackMessageSeverity),
        .messageType = static_cast<VkDebugUtilsMessageTypeFlagsEXT>(mCallbackMessageType),
        .pfnUserCallback = CallbackHandler,
        .pUserData = reinterpret_cast<void *>(this)
    };

    VulkanResult result = CreateDebugUtilsMessengerEXT(mInstance, &createInfo, nullAllocator, &mHandle);
    if (!result.Success()) {
        throw std::runtime_error("Failed to create VkDebugUtilsMessengerEXT, result: " + result.ToString());
    }
}

VkBool32 Debugger::CallbackHandler(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                   VkDebugUtilsMessageTypeFlagsEXT messageType,
                                   const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                   void *pUserData) {

    reinterpret_cast<Debugger *>(pUserData)->mCallback(static_cast<MessageSeverity>(messageSeverity),
                                                       static_cast<MessageType>(messageType),
                                                       pCallbackData->pMessage);

    return VK_FALSE;
}

void Debugger::Destroy() noexcept {
    if (mHandle != nullptr) {
        DestroyDebugUtilsMessengerEXT(mInstance, mHandle, nullAllocator);
        mHandle = nullptr;
    }
}

Debugger::~Debugger() noexcept {
    Destroy();
}