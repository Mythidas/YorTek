#pragma once

#include "YTEngine/Graphics/GraphicsPipline.h"
#include "YTEngine/Graphics/RenderBuffer.h"
#include "YTEngine/Graphics/Framebuffer.h"
#include "YTEngine/Graphics/Image.h"
#include "YTEngine/Graphics/Camera.h"
#include "YTEngine/Scene/Ref.h"

#include <glm/glm.hpp>

namespace Yor
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec2 texCoord;
		float texIndex;
	};

	struct RenderData
	{
		static const int MAX_QUADS = 100;
		static const int MAX_VERTICES = MAX_QUADS * 4;
		static const int MAX_INDICES = MAX_QUADS * 6;
		static const int MAX_TEXTURE_SLOTS = 32;

		Shared<GraphicsPipeline> pipeline;
		Shared<RenderBuffer> buffer;
		Vertex* stagingBuffer{ nullptr };
		Vertex* stagingBufferPtr{ nullptr };
		uint32_t indexCount{ 0 };
		uint32_t textureSlotIndex{ 1 };
		Shared<Image> textureSlots[MAX_TEXTURE_SLOTS];

		glm::vec4 vertexPositions[4]{};
		glm::vec2 texturePositions[4]{};

		Ref<Camera> camera;
		struct CameraBuffer
		{
			glm::mat4 view{ 1.0f };
			glm::mat4 projection{ 1.0f };
		} cameraBuffer;

		Shared<RenderBuffer> cameraUniform;
	};
}