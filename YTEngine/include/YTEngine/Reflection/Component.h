#pragma once

#include "YTEngine/Reflection/MetaInfo.h"
#include "YTEngine/Scene/SceneRegistry.h"

#include <functional>

namespace Yor
{
  // Declar after component definition
#define COMPONENT_CLASS(ClassName) \
    struct ClassName##_reflection { \
      ClassName _reg; \
      Type<ClassName> _type; \
      ClassName##_reflection() { \
        _reg._registerObject(_type.name(), _type.debugName(), _type.id(), sizeof(ClassName), YT_BIND_FNC(_addComponentFunc)); } \
      void _addComponentFunc(SceneRegistry* registry, uint64_t id) { registry->addComponent<ClassName>(id); } \
    }; \
    static ClassName##_reflection ClassName##_reg; \

  class SceneRegistry;

  class Component : public _BaseComponent
  {
  public:
    void _registerObject(
      const std::string& name, 
      const std::string& debug, 
      const TypeID& id, 
      size_t size, 
      std::function<void(SceneRegistry*, uint64_t)> add_func);
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