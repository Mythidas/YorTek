#pragma once

#include "YTEngine/Core/Defines.h"
#include "YTEngine/Core/Window.h"
#include "YTEngine/ImGUI/ImGUIDisplay.h"

namespace Yor
{
  enum class ApplicationPlatform
  {
    Windows
  };

  enum class ApplicationBackend
  {
    None,
    OpenGL
  };

  struct ApplicationSpecs
  {
    ApplicationBackend backend{ ApplicationBackend::None };

    ApplicationSpecs& setBackend(ApplicationBackend backend) { backend = backend; return *this; }
  };

  class Application
  {
  public:
    Event<> OnClose;

  public:
    Application(const ApplicationSpecs& specs);

    void run();

    virtual void onStart() {}
    virtual void onUpdate() {}
    virtual void onFixedUpdate() {}
    virtual void onGUI() {}

  public:
    static Application& get() { return *s_instance; }
    static Unique<Window>& getWindow() { return get().m_window; }
    static ApplicationBackend getBackend() { return get().m_specs.backend; }
    static Unique<ImGUIDisplay>& getImGUI() { return get().m_imGUI; }
    static bool isRunning() { return s_running; }

  private:
    bool _onClose();

  private:
    static Application* s_instance;
    static bool s_running;

  private:
    ApplicationSpecs m_specs;
    Unique<Window> m_window;
    Unique<ImGUIDisplay> m_imGUI;
  };

  static Application* CreateApplication();
}