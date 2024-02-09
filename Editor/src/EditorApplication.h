#pragma once

#include "Core/EditorCamera.h"
#include "Core/ContextPayload.h"
#include "Core/EditorMainMenu.h"

#include <YTEngine.h>

namespace Yor::Editor
{
  enum class EditorMode
  {
    Editing,
    Playing
  };

  class EditorApplication : public Application
  {
  public:
    EditorApplication();

    virtual void onStart() override;
    virtual void onUpdate() override;
    virtual void onGUI() override;

  public:
    static EditorMode getMode();
    static EditorCamera& getCamera();
    static ContextPayload* getPayload();

    static void setMode(EditorMode mode);
    static void setPayload(uint64_t hashId, const void* data, size_t size);

    static void clearPayload();

  private:
    EditorMode m_mode{ EditorMode::Editing };
    EditorCamera m_camera;
    EditorMainMenu m_mainMenu;
    ContextPayload* m_payload{ nullptr };
  };
}