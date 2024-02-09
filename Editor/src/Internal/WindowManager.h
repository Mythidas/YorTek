#pragma once

#include "GUI/EditorWindow.h"

#include <YTEngine/Tools/AutoSingleton.h>
#include <unordered_map>
#include <functional>
#include <string>

namespace Yor::Editor::Internal
{
  struct WindowMeta
  {
    std::string Name;
    std::string MenuPath;
    std::function<EditorWindow*()> CreateWindow;
  };

  class WindowManager : public AutoSingleton<WindowManager>
  {
  public:
    WindowManager();

    void RegisterWindow(WindowMeta meta);
    void OpenWindow(const std::string& name);
    void CloseWindow(const std::string& name);

    const std::unordered_map<uint64_t, EditorWindow*>& GetWindows() const { return m_Windows; }

  private:
    std::unordered_map<uint64_t, EditorWindow*> m_Windows;
    std::unordered_map<uint64_t, WindowMeta> m_RegisteredWindows;
  };
}