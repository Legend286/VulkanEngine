#include "AppFramework/VulkanEngineApplication.h"

#include <stdexcept>
#include <array>
#include <cstdlib>
#include <iostream>

namespace VulkanEngineApplication
{
	Application::Application()
	{
		loadModels();
		createPipelineLayout();
		createPipeline();
		createCommandBuffers();
	}

	Application::~Application()
	{
		vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
	}

	void Application::runApplication()
	{
		while (!window.shouldClose())
		{
			glfwPollEvents();
			drawFrame();
		}

		vkDeviceWaitIdle(device.device());
	}

	void Application::createPipelineLayout()
	{
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};

		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;

		if (vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
		{
			throw std::runtime_error("Application::createPipelineLayout(): Failed to create Pipeline Layout!\n");
		}
	}

	void Application::createPipeline()
	{
		auto pipelineConfig = VulkanEnginePipeline::defaultPipelineConfigInfo(swapchain.width(), swapchain.height());
		pipelineConfig.renderPass = swapchain.getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		pipeline = std::make_unique<VulkanEnginePipeline>(device, "shaders/basic.vert.spv", "shaders/basic.frag.spv", pipelineConfig);
	}

	void Application::createCommandBuffers()
	{
		commandBuffers.resize(swapchain.imageCount());

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = device.getCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

		if (vkAllocateCommandBuffers(device.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS)
		{
			throw std::runtime_error("Application::createCommandBuffers(): Failed to allocate Command Buffers! \n");
		}

		for (int i = 0; i < commandBuffers.size(); i++)
		{
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

			if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS)
			{
				throw std::runtime_error("Application::createCommandBuffers(): Failed to begin recording Command Buffer! \n");
			}

			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = swapchain.getRenderPass();
			renderPassInfo.framebuffer = swapchain.getFrameBuffer(i);
			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent = swapchain.getSwapChainExtent();

			std::array<VkClearValue, 2> clearValues{};
			clearValues[0].color = { 0.3f, 0.1f, 0.1f, 1.0f };
			clearValues[1].depthStencil = { 1.0f, 0 };
			renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();

			vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			pipeline->bind(commandBuffers[i]);

			mesh->bind(commandBuffers[i]);
			mesh->draw(commandBuffers[i]);

			vkCmdEndRenderPass(commandBuffers[i]);
			if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("Application::createCommandBuffers(): Failed to record Command Buffer! \n");
			}
		}
	}

	void Application::drawFrame()
	{
		uint32_t imageIndex;
		auto result = swapchain.acquireNextImage(&imageIndex);

		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		{
			throw std::runtime_error("Application::drawFrame(): Failed to acquire SwapChain image! \n");
		}

		result = swapchain.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);

		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Application::drawFrame(): Failed to present SwapChain image! \n");
		}
	}

	void Application::loadModels()
	{
		std::vector<Mesh::Vertex> vertices {
			{ {  0.5f, -0.5f } },
			{ {  0.5f,  0.5f } },
			{ { -0.5f,  0.5f } }
		};
		mesh = std::make_unique<Mesh>(device, vertices);

	}
}

int main() // actual main function that runs our application.
{
	VulkanEngineApplication::Application application{};

	try
	{
		application.runApplication();
		//run application
		std::cout << "int main(): Running Application VulkanEngine." << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}