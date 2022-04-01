#include "VulkanResult.h"

std::unordered_map<int, std::string> VulkanResult::resultCodeNames = {
    { VK_SUCCESS,                                            "Success" },
    { VK_NOT_READY,                                          "Not ready" },
    { VK_TIMEOUT,                                            "Timeout" },
    { VK_EVENT_SET,                                          "Event { set }" },
    { VK_EVENT_RESET,                                        "Event { reset }" },
    { VK_INCOMPLETE,                                         "Incomplete" },
    { VK_ERROR_OUT_OF_HOST_MEMORY,                           "Error { out of host memory }" },
    { VK_ERROR_OUT_OF_DEVICE_MEMORY,                         "Error { out of device memory }" },
    { VK_ERROR_INITIALIZATION_FAILED,                        "Error { initialization failed }" },
    { VK_ERROR_DEVICE_LOST,                                  "Error { device lost }" },
    { VK_ERROR_MEMORY_MAP_FAILED,                            "Error { memory map failed }" },
    { VK_ERROR_LAYER_NOT_PRESENT,                            "Error { layer not present }" },
    { VK_ERROR_EXTENSION_NOT_PRESENT,                        "Error { extension not present }" },
    { VK_ERROR_FEATURE_NOT_PRESENT,                          "Error { feature not present }" },
    { VK_ERROR_INCOMPATIBLE_DRIVER,                          "Error { incompatible driver }" },
    { VK_ERROR_TOO_MANY_OBJECTS,                             "Error { too many objects }" },
    { VK_ERROR_FORMAT_NOT_SUPPORTED,                         "Error { format not supported }" },
    { VK_ERROR_FRAGMENTED_POOL,                              "Error { fragmented pool }" },
    { VK_ERROR_UNKNOWN,                                      "Error { unknown }" },
    { VK_ERROR_OUT_OF_POOL_MEMORY,                           "Error { out of pool memory }" },
    { VK_ERROR_INVALID_EXTERNAL_HANDLE,                      "Error { invalid external handle }" },
    { VK_ERROR_FRAGMENTATION,                                "Error { fragmentation }" },
    { VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS,               "Error { invalid opaque capture address }" },
    { VK_PIPELINE_COMPILE_REQUIRED,                          "Pipeline compile required" },
    { VK_ERROR_SURFACE_LOST_KHR,                             "Error { surface lost }" },
    { VK_ERROR_NATIVE_WINDOW_IN_USE_KHR,                     "Error { native window in use }" },
    { VK_SUBOPTIMAL_KHR,                                     "Suboptimal" },
    { VK_ERROR_OUT_OF_DATE_KHR,                              "Error { out of date }" },
    { VK_ERROR_INCOMPATIBLE_DISPLAY_KHR,                     "Error { incompatible display }" },
    { VK_ERROR_VALIDATION_FAILED_EXT,                        "Error { validation failed }" },
    { VK_ERROR_INVALID_SHADER_NV,                            "Error { invalid shader }" },
    { VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT, "Error { invalid DRM format modifier plane layout }" },
    { VK_ERROR_NOT_PERMITTED_KHR,                            "Error { not permitted }" },
    { VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT,          "Error { full screen exclusive mode lost }" },
    { VK_THREAD_IDLE_KHR,                                    "Thread idle" },
    { VK_THREAD_DONE_KHR,                                    "Thread done" },
    { VK_OPERATION_DEFERRED_KHR,                             "Operation { deferred }" },
    { VK_OPERATION_NOT_DEFERRED_KHR,                         "Operation { not deferred }" }
};

std::string VulkanResult::ToString() const {
    int resultCode = static_cast<int>(mResult);
    if (!resultCodeNames.contains(resultCode)) {
        throw std::runtime_error("Invalid result code: " + std::to_string(resultCode));
    }

    return resultCodeNames[static_cast<int>(mResult)];
}