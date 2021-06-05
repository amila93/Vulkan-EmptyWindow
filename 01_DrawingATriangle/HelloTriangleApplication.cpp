#include "HelloTriangleApplication.h"

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
    glfwDestroyWindow(window);

    glfwTerminate();
}
