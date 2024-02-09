#pragma once

#include "YTEngine/Core/Defines.h"
#include "YTEngine/Graphics/RenderBuffer.h"

#include <string>

namespace Yor
{
	enum class VertexAttribute
	{
		Float,
		Float2,
		Float3,
		Float4
	};

	class GraphicsPipeline
	{
	public:
		struct Builder
		{
			std::string vertPath;
			std::string fragPath;
			Shared<RenderBuffer> pVertexBuffer;
			Shared<RenderBuffer> pIndexBuffer;
			std::vector<Shared<RenderBuffer>> pRenderBuffers;
			std::vector<VertexAttribute> attributes;

			Builder& setVertPath(const std::string& path) { vertPath = path; return *this; }
			Builder& setFragPath(const std::string& path) { fragPath = path; return *this; }
			Builder& setVertexBuffer(const Shared<RenderBuffer>& buffer) { pVertexBuffer = buffer; return *this; }
			Builder& setIndexBuffer(const Shared<RenderBuffer>& buffer) { pIndexBuffer = buffer; return *this; }
			Builder& setRenderBuffers(const std::vector<Shared<RenderBuffer>>& buffers) { pRenderBuffers = buffers; return *this; }
			Builder& setAttributes(const std::vector<VertexAttribute>& attributes) { this->attributes = attributes; return *this; }
			Shared<GraphicsPipeline> build() const;
		};

		virtual void draw(uint32_t count) const = 0;
	};
}