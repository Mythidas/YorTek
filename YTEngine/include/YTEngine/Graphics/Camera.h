#pragma once

#include "YTEngine/Core/Defines.h"
#include "YTEngine/Reflection/Type.h"
#include "YTEngine/Graphics/Framebuffer.h"

#include <glm/glm.hpp>

namespace Yor
{
  template <typename T>
  class Ref;

  enum class CameraMode
  {
    Perspective,
    Orthographic
  };

  struct Camera : public Component
  {
    glm::vec4 clearColor{ 1.0f };
    CameraMode mode{ CameraMode::Perspective };
    float fieldOfView{ 60.0f };
    float nearClip{ 0.01f };
    float farClip{ 100.0f };
    float orthoSize{ 10.0f };
    bool active{ false };

    Camera();

    void resize(int width, int height);

    glm::mat4 getProjection() const { return m_projection; }
    Shared<Framebuffer> getSwapBuffer() const { return m_swapBuffer; }
    
  public:
    static Ref<Camera> getActiveCamera();

  private:
    glm::mat4 m_projection;
    Shared<Framebuffer> m_swapBuffer;
    glm::uvec2 m_currentSize;
  };
}