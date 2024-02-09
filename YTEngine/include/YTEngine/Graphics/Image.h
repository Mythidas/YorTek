#pragma once

#include "YTEngine/Core/Defines.h"
#include "YTEngine/Tools/Path.h"

#include <glm/glm.hpp>

namespace Yor
{
	enum class ImageType
	{
		e1D,
		e2D,
		e3D
	};

	enum class ImageFormat
	{
		R8,
		RGBA8,
		RGBA32F
	};

	enum class ImageWrap
	{
		Repeat,
		ClampToEdge,
		MirroredRepeat
	};

	enum class ImageTiling
	{
		Linear,
		Nearest
	};

	class Image
	{
	public:
		struct Builder
		{
			uint32_t binding{ 0 };
			ImageType type{ ImageType::e2D };
			ImageFormat format{ ImageFormat::RGBA8 };
			ImageWrap wrap{ ImageWrap::Repeat };
			ImageTiling tiling{ ImageTiling::Nearest };
			glm::uvec3 size{ 1, 1, 1 };
			bool flipped{ false };

			Builder& setBinding(uint32_t binding) { this->binding = binding; return *this; }
			Builder& setType(ImageType type) { this->type = type; return *this; }
			Builder& setFormat(ImageFormat format) { this->format = format; return *this; }
			Builder& setWrap(ImageWrap wrap) { this->wrap = wrap; return *this; }
			Builder& setTiling(ImageTiling tiling) { this->tiling = tiling; return *this; }
			Builder& setSize(glm::uvec3 size) { this->size = size; return *this; }
			Builder& setFlipped(bool flipped) { this->flipped = flipped; return *this; }
			Shared<Image> build() const;
		};

		virtual void bind(uint32_t slot) const = 0;
		virtual void setData(void* data, size_t size) = 0;
		virtual void loadData(const Path& path) = 0;

		virtual glm::uvec3 getSize() const = 0;
		virtual void* getRenderID() const = 0;
	};
}