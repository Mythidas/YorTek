#pragma once

#include "YTEngine/Core/Defines.h"

namespace Yor
{
	class GraphicsContext
	{
	public:
		struct Builder
		{
			void* windowHandle;

			Builder& setWindowHandle(void* handle) { windowHandle = handle; return *this; }
			Unique<GraphicsContext> build() const;
		};

		virtual void swapBuffers() = 0;
	};
}