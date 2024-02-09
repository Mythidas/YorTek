#pragma once

#include "YTEngine/Core/UUID.h"
#include "YTEngine/Reflection/Type.h"
#include "YTEngine/Scene/SceneManager.h"

namespace Yor
{
  // Used to store component refs at runtime
  template <typename T>
  class Ref
  {
  public:
    Ref() = default;
    Ref(const UUID& id) : m_entity(id) {}
    Ref(T* ref) : m_ref(ref) {}

    T* operator->() const
    {
      if (m_ref) return m_ref;
      return SceneManager::getActive()->getRegistry().getComponent<T>(m_entity);
    }

    operator bool() const
    {
      if (m_ref) return true;
      return SceneManager::getActive()->getRegistry().hasComponent<T>(m_entity);
    }

    static_assert(std::is_base_of_v<Component, T>, "Ref<T> is not derived from Component");

  private:
    UUID m_entity{ UUID::INVALID };
    T* m_ref{ nullptr };
  };
}