#include "Platform/OpenGL/OGL_GraphicsContext.h"
#include "YTEngine/Debug/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace Yor::OGL
{
	OGL_GraphicsContext::OGL_GraphicsContext(const Builder& builder)
		: m_builder(builder)
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			Log::critical("Failed to load GLAD!");
		}
	}

	void OGL_GraphicsContext::swapBuffers()
	{
		glfwSwapBuffers(static_cast<GLFWwindow*>(m_builder.windowHandle));
	}
}