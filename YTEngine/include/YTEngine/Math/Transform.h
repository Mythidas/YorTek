#pragma once

#include "YTEngine/Math/Vector3.h"
#include "YTEngine/Reflection/Object.h"

#include <glm/glm.hpp>

namespace Yor
{
  struct Transform : public Object
  {
    Vector3 position{ 0.0f };
    Vector3 rotation{ 0.0f };
    Vector3 scale{ 1.0f };

    glm::mat4 getMatrix() const;
    glm::mat4 getInverseMatrix() const;

    Vector3 forward() const;
    Vector3 back() const;
    Vector3 right() const;
    Vector3 left() const;
    Vector3 up() const;
    Vector3 down() const;

    virtual void _registerData() override
    {
      _registerProperty<Vector3>("Position", offsetof(Transform, position));
      _registerProperty<Vector3>("Rotation", offsetof(Transform, rotation));
      _registerProperty<Vector3>("Scale", offsetof(Transform, scale));
    }
  };
  OBJ_CLASS(Transform)
}