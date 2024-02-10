#include "Platform/Windows/W_Window.h"
#include "YTEngine/Debug/Log.h"

namespace Yor::Windows
{
  W_Window::W_Window(const Builder& builder)
    : m_builder(builder), m_window(nullptr)
  {
    if (int glfw = glfwInit(); !glfw)
    {
			Log::critical("Failed to init GLFW");
      return;
    }

    if (m_window = glfwCreateWindow(builder.width, builder.height, builder.title.c_str(), nullptr, nullptr); !m_window)
    {
			Log::critical("Failed to create GLFW window!");
      return;
    }

    glfwMakeContextCurrent(m_window);
		m_graphicsContext = GraphicsContext::Builder()
			.setWindowHandle(m_window)
			.build();

    glfwSwapInterval((int)builder.vSync);
    glfwSetWindowUserPointer(m_window, this);

    if (builder.fixedAspectRatio)
      glfwSetWindowAspectRatio(m_window, builder.width, builder.height);

		// Setup Callbacks GLFW

		glfwSetErrorCallback([](int error, const char* desc)
			{
				Log::error(desc);
			});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
			{
				W_Window* wWindow = ((W_Window*)glfwGetWindowUserPointer(window));
				wWindow->OnWindowClose();
			});

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
			{
				W_Window* wWindow = ((W_Window*)glfwGetWindowUserPointer(window));
				wWindow->m_builder.width = width;
				wWindow->m_builder.height = height;

				wWindow->OnWindowResize(width, height);
			});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				W_Window* wWindow = ((W_Window*)glfwGetWindowUserPointer(window));
				if (action == GLFW_PRESS)
					wWindow->OnKeyPressed(key);
				else if (action == GLFW_RELEASE)
					wWindow->OnKeyReleased(key);
			});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos)
			{
				W_Window* wWindow = ((W_Window*)glfwGetWindowUserPointer(window));
				wWindow->OnMouseMoved(xpos, ypos);
			});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				W_Window* wWindow = ((W_Window*)glfwGetWindowUserPointer(window));
				wWindow->OnMouseScrolled((float)yoffset);
			});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				W_Window* wWindow = ((W_Window*)glfwGetWindowUserPointer(window));
				if (action == GLFW_PRESS)
				{
					wWindow->OnMouseButtonPressed(button);
				}
				else if (action == GLFW_RELEASE)
					wWindow->OnMouseButtonReleased(button);
			});

		Log::info("Window Created!");
  }

	W_Window::~W_Window()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

  void W_Window::onUpdate()
  {
    glfwPollEvents();
		m_graphicsContext->swapBuffers();
  }

	void W_Window::setTitle(const std::string& title)
	{
		m_builder.setTitle(title);
		glfwSetWindowTitle(m_window, m_builder.title.c_str());
	}

	void W_Window::setCursorMode(bool locked)
	{
		if (locked)
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}