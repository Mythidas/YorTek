#include "EditorApplication.h"
#include "GUI/EditorWindow.h"
#include "Internal/WindowManager.h"

#include <YTEngine/Core/EntryPoint.h>
#include <imgui.h>

namespace Yor::Editor
{
  EditorApplication::EditorApplication()
    : Application({ ApplicationBackend::OpenGL })
  {

  }

  void EditorApplication::onStart()
  {
    clearPayload();
  }

  void EditorApplication::onUpdate()
  {
    if (m_mode == EditorMode::Editing)
    {
      SceneManager::getActive()->onEditorUpdate(&m_camera, m_camera.getTransform());
    }
    else if (m_mode == EditorMode::Playing)
    {
      SceneManager::getActive()->onUpdate();
    }

    for (auto& iter : Internal::WindowManager::get().getWindows())
    {
      iter.second->onUpdate();
    }
  }

  void EditorApplication::onGUI()
  {
    m_mainMenu.onGUI();

    for (auto& iter : Internal::WindowManager::get().getWindows())
    {
      iter.second->beginUI();
      iter.second->onGUI();
      iter.second->endUI();
    }
  }

  EditorMode EditorApplication::getMode()
  {
    EditorApplication* app = static_cast<EditorApplication*>(&get());
    return app->m_mode;
  }

  EditorCamera& EditorApplication::getCamera()
  {
    EditorApplication* app = static_cast<EditorApplication*>(&get());
    return app->m_camera;
  }

  ContextPayload* EditorApplication::getPayload()
  {
    EditorApplication* app = static_cast<EditorApplication*>(&get());
    return app->m_payload;
  }

  void EditorApplication::setMode(EditorMode mode)
  {
    EditorApplication* app = static_cast<EditorApplication*>(&get());
    app->m_mode = mode;
  }

  void EditorApplication::setPayload(uint64_t hashId, const void* data, size_t size)
  {
    EditorApplication* app = static_cast<EditorApplication*>(&get());
    if (app->m_payload)
    {
      delete app->m_payload;
    }

    app->m_payload = new ContextPayload(hashId, data, size);
  }

  void EditorApplication::clearPayload()
  {
    setPayload("EMPTY_PAYLOAD"_hs, nullptr, 0);
  }
}

Yor::Application* Yor::CreateApplication()
{
  return new Editor::EditorApplication();
}