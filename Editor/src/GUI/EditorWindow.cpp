#include "GUI/EditorWindow.h"
#include "Internal/WindowManager.h"

#include <YTEngine/Debug/Log.h>
#include <imgui.h>

namespace Yor::Editor
{
  void EditorWindow::beginUI()
  {
    ImGui::Begin(getWindowTitle(), &m_open);
  }

  void EditorWindow::endUI()
  {
    ImGui::End();
  }
}