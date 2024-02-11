#pragma once

#include "YTEngine/Scene/Scene.h"
#include "YTEngine/Tools/Path.h"

namespace Yor
{
  class SceneSerializer
  {
  public:
    static bool save(Shared<Scene> scene, const Path& dst);
    static bool load(Shared<Scene> scene, const Path& src);
    static Shared<Scene> copy(Shared<Scene> scene);
  };
}