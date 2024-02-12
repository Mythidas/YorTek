#pragma once

#include "YTEngine/Core/Defines.h"
#include "YTEngine/Tools/AutoSingleton.h"
#include "YTEngine/Reflection/Type.h"
#include "YTEngine/Reflection/MetaInfo.h"

namespace Yor
{
  class ApplicationDomain : public AutoSingleton<ApplicationDomain>
  {
  public:
    ApplicationDomain();

  public:
    void registerObject(const ObjectMeta& meta);
    const ObjectMeta& findObject(const TypeID& id);
    const std::unordered_map<TypeID, ObjectMeta>& getAllObjects();

    void registerComponent(const ObjectMeta& meta);
    const ObjectMeta& findComponent(const TypeID& id);
    const std::unordered_map<TypeID, ObjectMeta>& getAllComponents();

  private:
    std::unordered_map<TypeID, ObjectMeta> m_registeredObjects;
    std::unordered_map<TypeID, ObjectMeta> m_registeredComponents;
  };
}