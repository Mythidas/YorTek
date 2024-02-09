#pragma once

#include "Internal/WindowManager.h"

namespace Yor::Editor::Internal
{
  template <typename T>
  class WindowFactory
  {
  public:
    WindowFactory& SetWindowName(const std::string& name)
    {
      m_Meta.Name = name;
      return *this;
    }

    WindowFactory& SetWindowPath(const std::string& path)
    {
      m_Meta.MenuPath = path;
      return *this;
    }

    WindowMeta Register()
    {
      m_Meta.CreateWindow = _CreateWindow;
      WindowManager::get().RegisterWindow(m_Meta);
      return m_Meta;
    }

    static inline T* _CreateWindow()
    {
      return new T();
    }

  private:
    WindowMeta m_Meta;
  };
}