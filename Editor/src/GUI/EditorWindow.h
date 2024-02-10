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

    bool getWindowOpen() const { return m_open; }
    void setWindowOpen(bool open) { m_open = open; }

  private:
    bool m_open{ true };
  };
}