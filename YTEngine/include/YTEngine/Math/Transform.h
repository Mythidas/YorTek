#pragma once

#include <glm/glm.hpp>

namespace Yor
{
  struct Transform
  {
    glm::vec3 position{ 0.0f };
    glm::vec3 rotation{ 0.0f };
    glm::vec3 scale{ 1.0f };

    glm::mat4 getMatrix() const;
    glm::mat4 getInverseMatrix() const;

    glm::vec3 forward() const;
    glm::vec3 back() const;
    glm::vec3 right() const;
    glm::vec3 left() const;
    glm::vec3 up() const;
    glm::vec3 down() const;
  };
}