#include "Platform/OpenGL/OGL_RenderCommands.h"

#include <glad/glad.h>

namespace Yor::OGL
{
  void OGL_RenderCommands::_enableDepthTesting(bool enable)
  {
    if (enable) glEnable(GL_DEPTH_TEST);
    else glDisable(GL_DEPTH_TEST);
  }

  void OGL_RenderCommands::_setClearColor(float r, float g, float b)
  {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void OGL_RenderCommands::_resize(int width, int height)
  {
    if (width <= 0 || height <= 0) return;
    glViewport(0, 0, width, height);
  }
}