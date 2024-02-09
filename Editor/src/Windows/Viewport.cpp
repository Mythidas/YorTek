#include "Viewport.h"
#include "EditorApplication.h"

#include <YTEngine/Reflection/ApplicationDomain.h>
#include <imgui.h>

namespace Yor::Editor
{
  void Viewport::onGUI()
  {
    if (ImGui::IsWindowHovered())
    {
      EditorApplication::getCamera().onUpdate();
    }

    glm::uvec2 size = { ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y };
    EditorApplication::getCamera().resize(size.x, size.y);

    ImGui::Image((ImTextureID)EditorApplication::getCamera().getSwapBuffer()->getRenderID(), ImVec2(size.x, size.y), ImVec2(1, 1), ImVec2(0, 0));
  }
}