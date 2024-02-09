#pragma once

#include "YTEngine/ImGUI/ImGUIDisplay.h"

namespace Yor::OGL
{
  class OGL_ImGUIDisplay : public ImGUIDisplay
  {
  public:
    OGL_ImGUIDisplay();
    ~OGL_ImGUIDisplay();

    virtual void beginUI() override;
    virtual void endUI() override;
  };
}