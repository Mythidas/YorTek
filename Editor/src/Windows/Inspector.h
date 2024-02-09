#pragma once

#include "GUI/EditorWindow.h"

#include <YTEngine/Reflection/MetaInfo.h>

namespace Yor::Editor
{
  class Inspector : public Editor::EditorWindow
  {
  public:
    virtual void onGUI() override;

    virtual const char* getWindowTitle() const override { return "Inspector"; }

  private:
    void _drawEntityInfo();
    void _drawVariableInfo(char* data, PropertyMeta meta);
  };
}