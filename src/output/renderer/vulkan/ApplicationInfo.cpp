#include "ApplicationInfo.h"

ApplicationInfo::ApplicationInfo(std::string_view applicationName, unsigned applicationVersion,
                                 std::string_view engineName, unsigned engineVersion) noexcept : mApplicationName(
        applicationName), mApplicationVersion(applicationVersion), mEngineName(engineName), mEngineVersion(
        engineVersion) {}

void ApplicationInfo::Initialize() noexcept {
    mApplicationInfo = VkApplicationInfo {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = mApplicationName.c_str(),
        .applicationVersion = mApplicationVersion,
        .pEngineName = mEngineName.c_str(),
        .engineVersion = mEngineVersion,
        .apiVersion = apiVersion
    };
}
