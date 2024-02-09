#include "YTEngine/Scene/Scene.h"
#include "YTEngine/Graphics/Renderer.h"
#include "YTEngine/Scene/Ref.h"

#include <glad/glad.h>
#include <iostream>

namespace Yor
{
  Scene::Scene()
    : Scene("")
  {
  }

  Scene::Scene(const Path& path)
    : m_localPath(path)
  {
  }

  void Scene::onUpdate()
  {
    Ref<Camera> camera = Camera::getActiveCamera();
    if (camera)
    {

    }
  }

  void Scene::onEditorUpdate(Camera* camera, const Transform& transform)
  {
    Renderer::beginFrame(camera, transform);
    Renderer::drawQuad({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f });
    Renderer::endFrame();
  }

  bool Scene::valid() const
  {
    return m_localPath.exists() && m_localPath.isFile();
  }
}