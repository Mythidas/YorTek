#pragma once

#include "YTEngine/Reflection/MetaInfo.h"

#include <type_traits>

namespace Yor
{
  // Declare after class definition
#define OBJ_CLASS(ClassName) \
    struct ClassName##_reflection { \
      ClassName _reg; \
      Type<ClassName> _type; \
      ClassName##_reflection() { \
        _reg._registerObject(_type.name(), _type.debugName(), _type.id(), sizeof(ClassName)); } \
    }; \
    static ClassName##_reflection ClassName##_reg; \

  class Object : public _BaseObject
  {
  public:
    void _registerObject(const std::string& name, const std::string& debug, const TypeID& id, size_t size);
    template <typename T>
    inline void _registerProperty(const std::string& name, size_t offset)
    {
      Type<T> type;

      if (type.ref() != TypeRef::Unknown)
      {
        MetaInfo meta(name, type.debugName(), type.id());
        m_meta.properties.push_back({ meta, type.ref(), offset });
      }
    }

    virtual void _registerData() = 0;

  private:
    ObjectMeta m_meta;
    bool m_registered{ false };
  };
}