# Add executable
add_executable(VulkanTutorialTest
    VulkanTutorialTest.cpp
    VulkanTutorialTest.h
)

# Include directories
target_include_directories(VulkanTutorialTest PRIVATE
    ${glm_SOURCE_DIR}
)

# Link libraries
target_link_libraries(VulkanTutorialTest
    Vulkan::Vulkan
    glfw
    tinyobjloader
)

# Define Vulkan-hpp options
target_compile_definitions(VulkanTutorialTest PUBLIC
    VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
    VULKAN_HPP_DISPATCH_LOADER_DYNAMIC
)

# Ensure C++20 for this target as well
set_property(TARGET VulkanTutorialTest PROPERTY CXX_STANDARD 20)
