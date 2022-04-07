#include "ApplicationInfo.h"

ApplicationInfo::ApplicationInfo(std::string_view applicationName, VulkanVersion const &applicationVersion,
                                 std::string_view engineName, VulkanVersion const &engineVersion,
                                 VulkanVersion const &APIVersion) noexcept : mApplicationName(applicationName),
                                                                             mApplicationVersion(applicationVersion),
                                                                             mEngineName(engineName),
                                                                             mEngineVersion(engineVersion),
                                                                             mAPIVersion(APIVersion) {}


void ApplicationInfo::Initialize() noexcept {
    mDescriptor = VkApplicationInfo {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = mApplicationName.c_str(),
        .applicationVersion = mApplicationVersion,
        .pEngineName = mEngineName.c_str(),
        .engineVersion = mEngineVersion,
        .apiVersion = mAPIVersion
    };
}