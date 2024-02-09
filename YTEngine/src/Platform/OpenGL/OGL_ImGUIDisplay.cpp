#include "Platform/OpenGL/OGL_ImGUIDisplay.h"
#include "YTEngine/Core/Application.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui.h>
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace Yor::OGL
{
  OGL_ImGUIDisplay::OGL_ImGUIDisplay()
  {
    ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(Application::getWindow()->getNativeWindow()), true);
    ImGui_ImplOpenGL3_Init("#version 450");
  }

  OGL_ImGUIDisplay::~OGL_ImGUIDisplay()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  }

  void OGL_ImGUIDisplay::beginUI()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
  }

  void OGL_ImGUIDisplay::endUI()
  {
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)Application::getWindow()->getWidth(), (float)Application::getWindow()->getHeight());

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
      GLFWwindow* backup_current_context = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(backup_current_context);
    }
  }
}