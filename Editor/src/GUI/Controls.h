#pragma once

#include <glm/glm.hpp>
#include <string>

namespace Yor::Editor
{
  class Controls
  {
  public:
    static void Vector3(const std::string& label, glm::vec3& vec3);
  };
}