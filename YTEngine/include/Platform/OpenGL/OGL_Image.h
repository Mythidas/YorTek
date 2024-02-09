#pragma once

#include "YTEngine/Graphics/Image.h"

namespace Yor::OGL
{
	class OGL_Image : public Image
	{
	public:
		OGL_Image(const Builder& builder);

		virtual void bind(uint32_t slot) const;
		virtual void setData(void* data, size_t size);
		virtual void loadData(const Path& path);

		virtual glm::uvec3 getSize() const { return m_builder.size; }
		virtual void* getRenderID() const;

	private:
		uint32_t m_renderID;
		Builder m_builder;
	};
}