#include "YTEngine/Core/Application.h"
#include "YTEngine/Core/Time.h"
#include "YTEngine/Graphics/Renderer.h"
#include "YTEngine/Debug/Log.h"

namespace Yor
{
  Application* Application::s_instance{ nullptr };

  Application::Application(const ApplicationSpecs& specs)
    : m_specs(specs)
  {
    if (s_instance) return;
    s_instance = this;

    m_window = Window::Builder().build();
    m_window->OnWindowClose += YT_BIND_FNC(_onClose);

    m_imGUI = ImGUIDisplay::Builder().build();

    Renderer::_construct();

    Log::info("Application Started!");
  }

  void Application::run()
  {
    onStart();

    while (m_running)
    {
      Time::_tick();

      onUpdate();

      if (Time::getFixedDeltaTime() > 0.0f)
      {
        onFixedUpdate();
      }

      m_imGUI->beginUI();
      onGUI();
      m_imGUI->endUI();

      m_window->onUpdate();
    }
  }

  bool Application::_onClose()
  {
    OnClose();
    Renderer::_destruct();
    m_running = false;
    return true;
  }
}