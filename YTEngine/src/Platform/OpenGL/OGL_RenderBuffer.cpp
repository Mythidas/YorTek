#include "Platform/OpenGL/OGL_RenderBuffer.h"
#include "YTEngine/Debug/Log.h"

#include <glad/glad.h>

namespace Yor::OGL
{
	namespace Utils
	{
		static GLenum GetBufferUsage(BufferUsage usage)
		{
			switch (usage)
			{
			case BufferUsage::Vertex: return GL_ARRAY_BUFFER;
			case BufferUsage::Index: return GL_ELEMENT_ARRAY_BUFFER;
			case BufferUsage::Uniform: return GL_UNIFORM_BUFFER;
			case BufferUsage::ShaderStorage: return GL_SHADER_STORAGE_BUFFER;
			default: return 0;
			}
		}

		static GLenum GetDrawRate(BufferRate rate)
		{
			switch (rate)
			{
			case BufferRate::Static: return GL_STATIC_DRAW;
			case BufferRate::Dynamic: return GL_DYNAMIC_DRAW;
			default: return 0;
			}
		}

		static GLenum GetBufferAccess(BufferAccess access)
		{
			switch (access)
			{
			case BufferAccess::ReadOnly: return GL_READ_ONLY;
			case BufferAccess::WriteOnly: return GL_WRITE_ONLY;
			case BufferAccess::ReadWrite: return GL_READ_WRITE;
			default: return GL_READ_WRITE;
			}
		}
	}

	OGL_RenderBuffer::OGL_RenderBuffer(const Builder& builder)
		: m_builder(builder), m_renderID(0)
	{
		glGenBuffers(1, &m_renderID);
		glBindBuffer(Utils::GetBufferUsage(builder.usage), m_renderID);
		glBufferData(Utils::GetBufferUsage(builder.usage), builder.size, nullptr, Utils::GetDrawRate(builder.rate));

		if (builder.usage == BufferUsage::Uniform)
		{
			glBindBufferRange(GL_UNIFORM_BUFFER, builder.binding, m_renderID, 0, builder.size);
		}
	}

	void OGL_RenderBuffer::bind() const
	{
		glBindBuffer(Utils::GetBufferUsage(m_builder.usage), m_renderID);
	}

	void OGL_RenderBuffer::setData(void* data, size_t size, uint32_t offset)
	{
		if (size + offset > m_builder.size)
		{
			Log::error("Size exceeds allocated RenderBuffer!");
			return;
		}

		bind();
		glNamedBufferSubData(m_renderID, offset, size, data);
	}

	void* OGL_RenderBuffer::mapBufferPtr(BufferAccess access)
	{
		return glMapNamedBuffer(m_renderID, Utils::GetBufferAccess(access));
	}

	void OGL_RenderBuffer::unmapBufferPtr()
	{
		glUnmapNamedBuffer(m_renderID);
	}
}