#include "YTEngine/Scene/SceneManager.h"

namespace Yor
{
  SceneManager::SceneManager()
  {
    m_activeScene = CreateShared<Scene>();
  }
}