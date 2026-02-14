cmake_minimum_required(VERSION 3.21)

project(VulkanTutorialTutorial)

# Enable C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell CMake to fetch dependencies automatically
include(FetchContent)

# ---- Fetch GLFW ----
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG latest
)
FetchContent_MakeAvailable(glfw)

# ---- Fetch GLM ----
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG master
)
FetchContent_MakeAvailable(glm)

# ---- Fetch tinyobjloader ----
FetchContent_Declare(
    tinyobjloader
    GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
    GIT_TAG release
)
FetchContent_MakeAvailable(tinyobjloader)

# ---- Find Vulkan SDK ----
find_package(Vulkan REQUIRED)

# ---- Add your project folder ----
add_subdirectory(VulkanTutorialTest)
