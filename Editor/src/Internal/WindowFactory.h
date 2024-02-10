#pragma once

#include "Internal/WindowManager.h"

#include <YTEngine/Tools/Stringf.h>

namespace Yor::Editor::Internal
{
  template <typename T>
  class WindowFactory
  {
  public:
    WindowFactory& setWindowName(const std::string& name)
    {
      m_meta.hashID = Stringf::hash(name);
      m_meta.name = name;
      return *this;
    }

    WindowFactory& setWindowPath(const std::string& path)
    {
      m_meta.menuPath = path;
      return *this;
    }

    WindowMeta build()
    {
      m_meta.createWindow = _createWindow;
      WindowManager::get().registerWindow(m_meta);
      return m_meta;
    }

  private:
    static inline T* _createWindow()
    {
      return new T();
    }

  private:
    WindowMeta m_meta;
  };
}