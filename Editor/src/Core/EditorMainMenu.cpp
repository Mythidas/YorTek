#include "EditorMainMenu.h"
#include "Internal/WindowManager.h"

#include <YTEngine.h>
#include <imgui.h>

namespace Yor::Editor
{
  namespace Utils
  {
    MenuPath getMenuPath()
    {
      MenuPath menu_path;
      const auto& registered_windows = Internal::WindowManager::get().getWindowMetas();

      for (auto& iter : registered_windows)
      {
        std::vector<std::string> points = Stringf::splitBy(iter.second.menuPath, '/');

        std::string current_path = "";
        for (int i = 0; i < points.size(); i++)
        {
          if (i < points.size() - 1)
          {
            if (menu_path.contains(current_path))
              menu_path[current_path].push_back(current_path + "/" + points[i]);
          }

          if (i == points.size() - 1)
          {
            if (menu_path.contains(current_path))
              menu_path[current_path].push_back(current_path + "/" + points[i]);

            continue;
          }

          current_path += "/" + points[i];

          if (!menu_path.contains(current_path))
            menu_path[current_path] = std::vector<std::string>();
        }
      }

      return menu_path;
    }
  }

  void EditorMainMenu::onGUI()
  {
    static bool showImGuiDemo = false;
    if (showImGuiDemo)
      ImGui::ShowDemoWindow();

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 10.0f, 10.0f });
    if (ImGui::BeginMainMenuBar())
    {
      if (ImGui::BeginMenu("Project"))
      {
        if (ImGui::MenuItem("Load Scene"))
        {

        }

        if (ImGui::MenuItem("Save Scene"))
        {
          
        }

        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("Editor"))
      {
        ImGui::EndMenu();
      }

      _drawWindowMenu();

      if (ImGui::BeginMenu("Debug"))
      {
        if (ImGui::MenuItem("Show ImGui Demo"))
          showImGuiDemo = !showImGuiDemo;

        ImGui::EndMenu();
      }

      ImGui::EndMainMenuBar();
    }
    ImGui::PopStyleVar();
  }

  void EditorMainMenu::_drawWindowMenu()
  {
    auto entries = Utils::getMenuPath();
  
    if (ImGui::BeginMenu("Windows"))
    {
      for (const auto& iter : entries)
      {
        _drawWindowMenuItem(entries, iter.first, iter.second);
      }

      ImGui::EndMenu();
    }
  }

  void EditorMainMenu::_drawWindowMenuItem(const MenuPath& menuPath, const std::string& str, const std::vector<std::string>& items)
  {
    if (!items.empty())
    {
      std::string trimmed = str.substr(str.find_last_of('/') + 1);
      if (ImGui::BeginMenu(trimmed.c_str()))
      {
        for (const auto& str : items)
        {
          if (menuPath.contains(str))
            _drawWindowMenuItem(menuPath, str, menuPath.at(str));
          else
            _drawWindowMenuItem(menuPath, str, std::vector<std::string>());
        }

        ImGui::EndMenu();
      }
    }
    else
    {
      std::string trimmed = str.substr(str.find_last_of('/') + 1);
      if (ImGui::MenuItem(trimmed.c_str()))
      {
        Internal::WindowManager::get().openWindow(trimmed);
      }
    }
  }
}