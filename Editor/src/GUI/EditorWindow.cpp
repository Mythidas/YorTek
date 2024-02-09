#include "GUI/EditorWindow.h"

#include <imgui.h>

namespace Yor::Editor
{
  void EditorWindow::beginUI()
  {
    ImGui::Begin(getWindowTitle());
  }

  void EditorWindow::endUI()
  {
    ImGui::End();
  }
}