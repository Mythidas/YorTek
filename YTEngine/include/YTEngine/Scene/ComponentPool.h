#pragma once

#include "YTEngine/Scene/EntityConstants.h"
#include "YTEngine/Reflection/Type.h"

#include <string>

namespace Yor
{
  class ComponentPool
  {
  public:
    ComponentPool(const TypeID& type, size_t size)
      : m_type(type), m_size(size)
    {
      m_data = new char[size * MAX_ENTITIES];
    }

    ~ComponentPool()
    {
      delete[] m_data;
    }

    bool isType(const TypeID& type)
    {
      return m_type == type;
    }

    void* getData(size_t index)
    {
      return m_data + index * m_size;
    }

    TypeID getType() const
    {
      return m_type;
    }

  private:
    TypeID m_type;
    size_t m_size;
    char* m_data;
  };
}