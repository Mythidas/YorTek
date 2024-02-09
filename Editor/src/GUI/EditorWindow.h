#pragma once

namespace Yor::Editor
{
  class EditorWindow
  {
  public:
    void beginUI();
    void endUI();

    virtual void onCreate() {}
    virtual void onUpdate() {}
    virtual void onGUI() {}
    virtual void onDestroy() {}

    virtual const char* getWindowTitle() const = 0;
  };
}