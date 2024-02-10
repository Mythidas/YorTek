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
    uint64_t hashID;
    std::string name;
    std::string menuPath;
    std::function<EditorWindow*()> createWindow;
  };

  class WindowManager : public AutoSingleton<WindowManager>
  {
  public:
    WindowManager();

    void registerWindow(WindowMeta meta);

    void openWindow(uint64_t id);
    void openWindow(const std::string& name);
    void closeWindow(uint64_t id);
    void closeWindow(const std::string& name);
    void toggleWindow(uint64_t id);
    void toggleWindow(const std::string& name);

    const std::unordered_map<uint64_t, EditorWindow*> getWindows();
    const std::unordered_map<uint64_t, WindowMeta>& getWindowMetas() const { return m_registeredWindows; }

  private:
    std::unordered_map<uint64_t, EditorWindow*> m_windows;
    std::unordered_map<uint64_t, WindowMeta> m_registeredWindows;
  };
}