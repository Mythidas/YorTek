#include "EditorMainMenu.h"

#include <YTEngine.h>
#include <imgui.h>

namespace Yor::Editor
{
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
        if (ImGui::MenuItem("Save Scene", "CTRL+S"))
        {
          // Save Scene
        }

        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("Editor"))
      {
        ImGui::EndMenu();
      }

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
}