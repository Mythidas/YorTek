#pragma once

#include "GUI/EditorWindow.h"

namespace Yor::Editor
{
  class Viewport : public Editor::EditorWindow
  {
  public:
    virtual void onGUI() override;

    virtual const char* getWindowTitle() const override { return "Viewport"; }
  };
}