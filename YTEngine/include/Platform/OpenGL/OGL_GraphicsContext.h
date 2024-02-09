#pragma once

#include "YTEngine/Graphics/GraphicsContext.h"

namespace Yor::OGL
{
	class OGL_GraphicsContext : public GraphicsContext
	{
	public:
		OGL_GraphicsContext(const Builder& builder);

		virtual void swapBuffers() override;

	private:
		Builder m_builder;
	};
}