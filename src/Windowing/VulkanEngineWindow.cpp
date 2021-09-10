#include "Windowing/VulkanEngineWindow.h"
#include <stdexcept>

namespace VulkanEngine
{
	VulkanEngineWindow::VulkanEngineWindow(int w, int h, std::string name) : width{ w }, height{ h }, windowName{ name }
	{
		initWindow();
	}

	VulkanEngineWindow::~VulkanEngineWindow()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void VulkanEngineWindow::initWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);


		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);

	}

	void VulkanEngineWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
	{
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) 
		{
			throw std::runtime_error("VulkanEngineWindow::createWindowSurface: Failed to create window surface.\n");
		}
	}
}