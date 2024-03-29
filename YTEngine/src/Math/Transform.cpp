#include "YTEngine/Math/Transform.h"
#include "YTEngine/Math/Vector3.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Yor
{
  namespace Utils
  {
    static glm::quat GetOrientation(const glm::vec3& rotation)
    {
      return glm::quat(glm::radians(glm::vec3(-rotation.x, rotation.y, 0.0f)));
    }
  }

  glm::mat4 Transform::getMatrix() const
  {
    return glm::translate(glm::mat4(1.0f), (glm::vec3)position)
      * glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f))
      * glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f))
      * glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f))
      * glm::scale(glm::mat4(1.0f), (glm::vec3)scale);
  }

  glm::mat4 Transform::getInverseMatrix() const
  {
    return glm::inverse(getMatrix());
  }

  Vector3 Transform::forward() const
  {
    return glm::rotate(Utils::GetOrientation(rotation), Vector3::forward);
  }

  Vector3 Transform::back() const
  {
    return glm::rotate(Utils::GetOrientation(rotation), Vector3::back);
  }

  Vector3 Transform::right() const
  {
    return glm::rotate(Utils::GetOrientation(rotation), Vector3::right);
  }

  Vector3 Transform::left() const
  {
    return glm::rotate(Utils::GetOrientation(rotation), Vector3::left);
  }

  Vector3 Transform::up() const
  {
    return glm::rotate(Utils::GetOrientation(rotation), Vector3::up);
  }

  Vector3 Transform::down() const
  {
    return glm::rotate(Utils::GetOrientation(rotation), Vector3::down);
  }
}