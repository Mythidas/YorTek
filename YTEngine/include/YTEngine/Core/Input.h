#pragma once

#include "YTEngine/Tools/AutoSingleton.h"
#include "YTEngine/Core/Defines.h"
#include "YTEngine/Core/KeyCodes.h"
#include "YTEngine/Core/Event.h"

namespace Yor
{
  class Input : public AutoSingleton<Input>
  {
  public:
    Input();

  public:
    static bool isKeyPressed(Key key);
    static bool isKeyReleased(Key key);

    static void setCursorMode(bool locked);

  private:
    bool _onKeyPressed(int key);
    bool _onKeyReleased(int key);
    bool _onMouseMoved(double x, double y);
    bool _onMouseButtonPressed(int button);
    bool _onMouseButtonReleased(int button);

  private:
    bool m_keys[512]{};
  };
}