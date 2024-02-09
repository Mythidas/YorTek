#pragma once

#include "YTEngine/Core/Defines.h"

#include <glm/glm.hpp>

namespace Yor
{
	class Framebuffer
	{
	public:
		struct Builder
		{
			glm::uvec2 size;

			Builder& setSize(const glm::uvec2& size) { this->size = size; return *this; }
			Shared<Framebuffer> build() const;
		};


		virtual void bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void resize(const glm::uvec2& size) = 0;
		virtual glm::uvec2 getSize() const = 0;
		virtual void* getRenderID() const = 0;
	};
}