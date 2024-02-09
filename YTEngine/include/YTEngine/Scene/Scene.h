#pragma once

#include "YTEngine/Scene/SceneRegistry.h"
#include "YTEngine/Graphics/Camera.h"
#include "YTEngine/Tools/Path.h"

namespace Yor
{
  class Scene
  {
  public:
    Scene();
    Scene(const Path& path);

    void onUpdate();
    void onEditorUpdate(Camera* camera, const Transform& transform);

    bool valid() const;

    SceneRegistry& getRegistry() { return m_registry; }

  private:
    SceneRegistry m_registry;
    Path m_localPath;
  };
}