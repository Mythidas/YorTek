#pragma once

#include "YTEngine/Core/Defines.h"
#include "YTEngine/Tools/AutoSingleton.h"
#include "YTEngine/Scene/Scene.h"

namespace Yor
{
  class SceneManager : public AutoSingleton<SceneManager>
  {
  public:
    SceneManager();

    static Shared<Scene> getActive() { return get().m_activeScene; }
    static void setActive(Shared<Scene> scene) { get().m_activeScene = scene; }

  private:
    Shared<Scene> m_activeScene;
  };
}