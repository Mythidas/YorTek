#pragma once

#include "YTEngine/Graphics/Framebuffer.h"

namespace Yor::OGL
{
	class OGL_Framebuffer : public Framebuffer
	{
	public:
		OGL_Framebuffer(const Builder& builder);
		~OGL_Framebuffer();

		virtual void bind() const override;
		virtual void Unbind() const override;
		virtual void resize(const glm::uvec2& size) override;

		virtual glm::uvec2 getSize() const override { return m_size; }
		virtual void* getRenderID() const { return reinterpret_cast<void*>((uint32_t)m_texture); }

	private:
		uint32_t m_renderID{ 0 };
		uint32_t m_texture{ 0 };
		uint32_t m_renderObject{ 0 };
		glm::uvec2 m_size;
	};
}