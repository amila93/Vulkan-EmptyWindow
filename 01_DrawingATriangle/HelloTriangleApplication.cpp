#include "HelloTriangleApplication.h"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string.h>
#include <algorithm>
#include <functional>

void HelloTriangleApplication::run()
{
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void HelloTriangleApplication::initWindow()
{
    // Initialize the GLFW library
    glfwInit();

    // Tell GLFW to not create an OpenGL context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    // Disable window resizability
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Creating a WIDTHxHEIGHT window with the title of "Vulkan"
    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void HelloTriangleApplication::initVulkan()
{
    createInstance();
}

void HelloTriangleApplication::createInstance()
{
    VkApplicationInfo appInfo{};
    // Filling this struct is optional, but this may provide some useful information
    // to the driver in order to optimize this application
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // Enumerating available extensions
    uint32_t extensionsCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionsCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, extensions.data());

    // Vulkan needs extensions to interface with the window system
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    // GLFW has a built-in function which returns required extensions
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    // Checking if any of the required extensions are missing
    bool requiredExtensionsAvailable = true;
    for (int i = 0; i < glfwExtensionCount; i++)
    {
        std::function<bool(VkExtensionProperties&)> findExtension =
            [&i, &glfwExtensions](const VkExtensionProperties& extension) { return strcmp(extension.extensionName, glfwExtensions[i]) == 0; };

        auto it = std::find_if(extensions.begin(), extensions.end(), findExtension);

        if (it == extensions.end())
        {
            std::cout << "Required extension not found: " << glfwExtensions[i] << std::endl;

            requiredExtensionsAvailable = false;
        }
    }

    if (!requiredExtensionsAvailable)
    {
        throw std::runtime_error("Required extensions are missing!");
    }

    // Setting those global extensions to the Vulkan driver
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    // Global validation layers to enable
    createInfo.enabledLayerCount = 0;

    // Creating the Vulkan instance
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create instance!");
    }
}

void HelloTriangleApplication::mainLoop()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }
}

void HelloTriangleApplication::cleanup()
{
    vkDestroyInstance(instance, nullptr);

    glfwDestroyWindow(window);

    glfwTerminate();
}
