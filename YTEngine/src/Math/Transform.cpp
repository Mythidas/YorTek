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
    return glm::translate(glm::mat4(1.0f), position)
      * glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f))
      * glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f))
      * glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f))
      * glm::scale(glm::mat4(1.0f), scale);
  }

  glm::mat4 Transform::getInverseMatrix() const
  {
    return glm::inverse(getMatrix());
  }

  glm::vec3 Transform::forward() const
  {
    return glm::rotate(Utils::GetOrientation(rotation), Vector3::forward);
  }

  glm::vec3 Transform::back() const
  {
    return glm::rotate(Utils::GetOrientation(rotation), Vector3::back);
  }

  glm::vec3 Transform::right() const
  {
    return glm::rotate(Utils::GetOrientation(rotation), Vector3::right);
  }

  glm::vec3 Transform::left() const
  {
    return glm::rotate(Utils::GetOrientation(rotation), Vector3::left);
  }

  glm::vec3 Transform::up() const
  {
    return glm::rotate(Utils::GetOrientation(rotation), Vector3::up);
  }

  glm::vec3 Transform::down() const
  {
    return glm::rotate(Utils::GetOrientation(rotation), Vector3::down);
  }
}