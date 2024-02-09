#include "YTEngine/Core/Input.h"
#include "YTEngine/Core/Application.h"

namespace Yor
{
  Input::Input()
  {
    Application::get().getWindow()->OnKeyPressed += YT_BIND_FNC(_onKeyPressed);
    Application::get().getWindow()->OnKeyReleased += YT_BIND_FNC(_onKeyReleased);
    Application::get().getWindow()->OnMouseButtonPressed += YT_BIND_FNC(_onMouseButtonPressed);
    Application::get().getWindow()->OnMouseButtonReleased += YT_BIND_FNC(_onMouseButtonReleased);
  }

  bool Input::isKeyPressed(Key key)
  {
    return get().m_keys[key];
  }

  bool Input::isKeyReleased(Key key)
  {
    return !get().m_keys[key];
  }

  void Input::setCursorMode(bool locked)
  {
    Application::getWindow()->setCursorMode(locked);
  }

  bool Input::_onKeyPressed(int key)
  {
    get().m_keys[key] = true;
    return false;
  }

  bool Input::_onKeyReleased(int key)
  {
    get().m_keys[key] = false;
    return false;
  }

  bool Input::_onMouseMoved(double x, double y)
  {
    return false;
  }

  bool Input::_onMouseButtonPressed(int button)
  {
    if (button == 0)
      get().m_keys[KeyCode::LeftMouseButton] = true;
    else if (button == 1)
      get().m_keys[KeyCode::RightMouseButton] = true;
    else if (button == 2)
      get().m_keys[KeyCode::MiddleMouseButton] = true;
    return false;
  }

  bool Input::_onMouseButtonReleased(int button)
  {
    if (button == 0)
      get().m_keys[KeyCode::LeftMouseButton] = false;
    else if (button == 1)
      get().m_keys[KeyCode::RightMouseButton] = false;
    else if (button == 2)
      get().m_keys[KeyCode::MiddleMouseButton] = false;
    return false;
  }
}