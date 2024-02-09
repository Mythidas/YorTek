#include "YTEngine/Graphics/GraphicsContext.h"
#include "YTEngine/Core/Application.h"
#include "Platform/OpenGL/OGL_GraphicsContext.h"

namespace Yor
{
	Unique<GraphicsContext> GraphicsContext::Builder::build() const
	{
		switch (Application::getBackend())
		{
		case ApplicationBackend::None: return nullptr;
		case ApplicationBackend::OpenGL: return CreateUnique<OGL::OGL_GraphicsContext>(*this);
		}

		return nullptr;
	}
}