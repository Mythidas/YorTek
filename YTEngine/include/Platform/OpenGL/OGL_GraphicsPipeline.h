#pragma once

#include "YTEngine/Graphics/GraphicsPipline.h"

namespace Yor::OGL
{
	class OGL_GraphicsPipeline : public GraphicsPipeline
	{
	public:
		OGL_GraphicsPipeline(const Builder& builder);

		virtual void draw(uint32_t count) const override;

	private:
		Builder m_builder;
		uint32_t m_renderID;
		uint32_t m_vertexID;
	};
}