#pragma once

#include <glm/glm.hpp>

namespace Yor
{
  class Vector3
  {
  public:
		inline static const glm::vec3 one{ 1.0f, 1.0f, 1.0f };
		inline static const glm::vec3 zero{ 0.0f, 0.0f, 0.0f };
		inline static const glm::vec3 up{ 0.0f, 1.0f, 0.0f };
		inline static const glm::vec3 right{ 1.0f, 0.0f, 0.0f };
		inline static const glm::vec3 left{ -1.0f, 0.0f, 0.0f };
		inline static const glm::vec3 down{ 0.0f, -1.0f, 0.0 };
		inline static const glm::vec3 back{ 0.0f, 0.0f, -1.0f };
		inline static const glm::vec3 forward{ 0.0f, 0.0f, 1.0f };
  };
}