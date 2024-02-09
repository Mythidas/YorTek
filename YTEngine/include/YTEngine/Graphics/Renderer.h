#pragma once

#include "YTEngine/Core/Defines.h"
#include "YTEngine/Graphics/Image.h"
#include "YTEngine/Graphics/Framebuffer.h"
#include "YTEngine/Graphics/RenderData.h"
#include "YTEngine/Graphics/RenderData.h"
#include "YTEngine/Graphics/Camera.h"
#include "YTEngine/Math/Transform.h"
#include "YTEngine/Graphics/RenderCommands.h"

#include <glm/glm.hpp>

namespace Yor
{
	class Renderer
	{
	public:
		static void beginFrame(Ref<Camera> camera, const Transform& transform);
		static void endFrame();

		static void drawQuad(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, const glm::vec3& color);
		static void drawQuad(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, const glm::vec3& color, Shared<Image> texture);
		static void drawQuad(const glm::mat4& transform, const glm::vec3& color, float textureID);
		static void drawQuad(const glm::mat4& transform, const glm::vec3& color, glm::vec2 texCoords[4], float textureID);

	private:
		static void _construct();
		static void _destruct();
		static void _checkBatch();
		static void _beginBatch();
		static void _endBatch();
		static float _getTextureIndex(Shared<Image> texture);

		friend class Application;

	private:
		static RenderData s_quadData;
		static Unique<RenderCommands> s_renderCommands;
	};
}