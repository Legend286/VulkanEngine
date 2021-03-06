#pragma once

#include "Windowing/VulkanEngineWindow.h"
#include "Pipeline/VulkanEnginePipeline.h"
#include "Device/VulkanDevice.h"
#include "SwapChain/VulkanEngineSwapChain.h"
#include "Mesh/Mesh.h"

#include <memory>
#include <vector>

using namespace VulkanEngine;

namespace VulkanEngineApplication
{
	class Application
	{
	public:
		static constexpr int WIDTH = 1280;
		static constexpr int HEIGHT = 720;

		Application();
		~Application();

		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

		void runApplication();

	private:

		void loadModels();
		void createPipelineLayout();
		void createPipeline();
		void createCommandBuffers();
		void drawFrame();

		VulkanEngineWindow window{ WIDTH, HEIGHT, "Vulkan Window" };
		VulkanDevice device{ window };
		VulkanEngineSwapChain swapchain{ device, window.getExtent() };
		std::unique_ptr<VulkanEnginePipeline> pipeline;
		VkPipelineLayout pipelineLayout;
		std::vector<VkCommandBuffer> commandBuffers;
		std::unique_ptr<Mesh> mesh;

	};
}