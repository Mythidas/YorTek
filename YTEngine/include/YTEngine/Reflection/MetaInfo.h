#pragma once

#include "YTEngine/Reflection/Type.h"
#include "YTEngine/Core/UUID.h"

#include <vector>

namespace Yor
{
  struct MetaInfo
  {
    std::string name;
    std::string debugName;
    TypeID id;
    size_t size;
  };

  struct PropertyMeta
  {
    MetaInfo info;
    TypeRef ref;
    size_t offset;
  };

  struct ObjectMeta
  {
    MetaInfo info;
    std::vector<PropertyMeta> properties;
  };

  struct ComponentMeta
  {
    MetaInfo info;
    std::vector<PropertyMeta> properties;
  };
}