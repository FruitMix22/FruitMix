#if defined(__INTELLISENSE__) || !defined(USE_CPP20_MODULES)
#include <vulkan/vulkan_raii.hpp>
#else
import vulkan_hpp;
#endif
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;

class HelloTriangleApplication
{
public:
    void run()
    {
        InitWindow();
        InitVulkan();
        MainLoop();
        Cleanup();
    }

private:
    // window context
    GLFWwindow* window;

    // Vulkan context and instance
    vk::raii::Context  context;
    vk::raii::Instance instance = nullptr;

private:

    void InitWindow()
    {
        // ititialise glfw
        if (glfwInit()) { std::cout << "Initalised GLFW succesfully.\n"; }
        else { std::cerr << "Failed to initialise GLFW.\n"; }

        // Disable automatic OpenGL context
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        // No resizing allowed (for now!)
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        // Create window
        std::cout << "Creating GLFW Window...\n";
        if (window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr))
        {
            std::cout << "GLFW window succesfully created.\n";
        }
        else { std::cerr << "Failed to create GLFW window.\n"; }
    }

    void CreateInstance()
    {
        // Initalise VK settings
        constexpr vk::ApplicationInfo appInfo
        {
            .pApplicationName = "Hello Triangle",
            .applicationVersion = VK_MAKE_VERSION(1,0,0),
            .pEngineName = "No engine",
            .engineVersion = VK_MAKE_VERSION(1,0,0),
            .apiVersion = vk::ApiVersion14
        };

        vk::InstanceCreateInfo{ .pApplicationInfo = &appInfo };

        // Get the required instance extensions from GLFW.
        uint32_t glfwExtensionCount = 0;
        auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        // Check if the required GLFW extensions are supported by the Vulkan implementation.
        auto extensionProperties = context.enumerateInstanceExtensionProperties();

        std::cout << "Extensions needed: \n";
        for (uint32_t i = 0; i < glfwExtensionCount; i++)
        {
            std::cout << "\t" << glfwExtensions[i];
            bool found = false;

            for (auto const& ext : extensionProperties)
            {
                if (strcmp(ext.extensionName, glfwExtensions[i]) == 0)
                {
                    std::cout << " found.\n";
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                throw std::runtime_error("Missing extension\n");
            }
        }

        vk::InstanceCreateInfo createInfo
        {
            .pApplicationInfo = &appInfo,
            .enabledExtensionCount = glfwExtensionCount,
            .ppEnabledExtensionNames = glfwExtensions
        };

        instance = vk::raii::Instance(context, createInfo);
    }

    void InitVulkan()
    {
        CreateInstance();
    }

    void MainLoop()
    {
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
        }
    }

    void Cleanup()
    {
        // GLFW
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

int main()
{
    HelloTriangleApplication app;

    try
    {
        app.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}