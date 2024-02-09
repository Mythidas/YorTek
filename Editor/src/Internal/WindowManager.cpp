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
      .SetWindowName("Viewport")
      .SetWindowPath("Scene/Viewport")
      .Register();

    auto hierarchy = WindowFactory<Hierarchy>()
      .SetWindowName("Hierarchy")
      .SetWindowPath("Scene/Hierarchy")
      .Register();

    auto inspector = WindowFactory<Inspector>()
      .SetWindowName("Inspector")
      .SetWindowPath("Scene/Inspector")
      .Register();
  }

  void WindowManager::RegisterWindow(WindowMeta meta)
  {
    uint64_t hashID = Stringf::hash(meta.Name);
    m_RegisteredWindows[hashID] = meta;
    OpenWindow(meta.Name);
  }

  void WindowManager::OpenWindow(const std::string& name)
  {
    uint64_t hashID = Stringf::hash(name);

    if (!m_Windows.contains(hashID))
    {
      m_Windows[hashID] = m_RegisteredWindows[hashID].CreateWindow();
    }
  }

  void WindowManager::CloseWindow(const std::string& name)
  {
    uint64_t hashID = Stringf::hash(name);

    if (m_Windows.contains(hashID))
    {
      delete m_Windows[hashID];
    }
  }
}