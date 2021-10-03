#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include "Device/VulkanDevice.h"

namespace VulkanEngine
{
	class Mesh
	{


	public:
		struct Vertex 
		{
			glm::vec2 position;

			static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
			static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
		};

		Mesh(VulkanDevice& vkdevice, const std::vector<Vertex>& vertices);
		~Mesh();


		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;

		void bind(VkCommandBuffer commandBuffer);	
		void draw(VkCommandBuffer commandBuffer);

		glm::vec3 boundsMin;
		glm::vec3 boundsMax;
		glm::vec3 boundsCentre;

	private:
		VulkanDevice& vulkanDevice;
		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;
		uint32_t vertexCount;

		void createVertexBuffers(const std::vector<Vertex>& vertices);


	};
}