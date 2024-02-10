#include "WindowManager.h"
#include "Internal/WindowFactory.h"
#include "Windows/Viewport.h"
#include "Windows/Hierarchy.h"
#include "Windows/Inspector.h"

#include <YTEngine/Tools/Stringf.h>

namespace Yor::Editor::Internal
{
  WindowManager::WindowManager()
  {
    auto viewport = WindowFactory<Viewport>()
      .setWindowName("Viewport")
      .setWindowPath("Scene/Viewport")
      .build();

    auto hierarchy = WindowFactory<Hierarchy>()
      .setWindowName("Hierarchy")
      .setWindowPath("Scene/Hierarchy")
      .build();

    auto inspector = WindowFactory<Inspector>()
      .setWindowName("Inspector")
      .setWindowPath("Scene/Inspector")
      .build();
  }

  void WindowManager::registerWindow(WindowMeta meta)
  {
    m_registeredWindows[meta.hashID] = meta;
    openWindow(meta.name);
  }

  void WindowManager::openWindow(uint64_t id)
  {
    if (!m_windows.contains(id))
    {
      m_windows[id] = m_registeredWindows[id].createWindow();
    }
    else
    {
      m_windows[id]->setWindowOpen(true);
    }
  }

  void WindowManager::openWindow(const std::string& name)
  {
    uint64_t hashID = Stringf::hash(name);
    openWindow(hashID);
  }

  void WindowManager::closeWindow(uint64_t id)
  {
    if (m_windows.contains(id))
    {
      m_windows[id]->setWindowOpen(false);
    }
  }

  void WindowManager::closeWindow(const std::string& name)
  {
    uint64_t hashID = Stringf::hash(name);
    closeWindow(hashID);
  }

  void WindowManager::toggleWindow(uint64_t id)
  {
    if (m_windows.contains(id))
    {
      m_windows[id]->setWindowOpen(!m_windows[id]->getWindowOpen());
    }
  }

  void WindowManager::toggleWindow(const std::string& name)
  {
    uint64_t hashID = Stringf::hash(name);
    toggleWindow(hashID);
  }

  const std::unordered_map<uint64_t, EditorWindow*> WindowManager::getWindows()
  {
    std::unordered_map<uint64_t, EditorWindow*> filtered;
    for (auto& iter : m_windows)
    {
      if (iter.second->getWindowOpen())
      {
        filtered[iter.first] = iter.second;
      }
    }
    return filtered;
  }
}