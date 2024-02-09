#pragma once

#include "YTEngine/Graphics/RenderBuffer.h"

namespace Yor::OGL
{
	class OGL_RenderBuffer : public RenderBuffer
	{
	public:
		OGL_RenderBuffer(const Builder& builder);

		virtual void bind() const override;
		virtual void setData(void* data, size_t size, uint32_t offset) override;
		virtual void* mapBufferPtr(BufferAccess access) override;
		virtual void unmapBufferPtr() override;

	private:
		Builder m_builder;
		uint32_t m_renderID;
	};
}