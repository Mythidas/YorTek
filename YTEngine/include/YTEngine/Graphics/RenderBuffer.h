#pragma once

#include "YTEngine/Core/Defines.h"

namespace Yor
{
	enum class BufferUsage
	{
		Vertex,
		Index,
		Uniform,
		ShaderStorage
	};

	enum class BufferRate
	{
		Static,
		Dynamic
	};

	enum class BufferAccess
	{
		ReadOnly,
		WriteOnly,
		ReadWrite
	};

	class RenderBuffer
	{
	public:
		struct Builder
		{
			size_t size;
			uint32_t binding;
			BufferUsage usage;
			BufferRate rate;

			Builder& setSize(size_t size) { this->size = size; return *this; }
			Builder& setBinding(uint32_t binding) { this->binding = binding; return *this; }
			Builder& setUsage(BufferUsage usage) { this->usage = usage; return *this; }
			Builder& setRate(BufferRate rate) { this->rate = rate; return *this; }
			Shared<RenderBuffer> build() const;
		};

		virtual void bind() const = 0;
		virtual void setData(void* data, size_t size, uint32_t offset) = 0;
		virtual void* mapBufferPtr(BufferAccess access) = 0;
		virtual void unmapBufferPtr() = 0;
	};
}