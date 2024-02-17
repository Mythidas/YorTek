#pragma once

#include "YTEngine/Core/Defines.h"
#include "YTEngine/Tools/AutoSingleton.h"
#include "YTEngine/Reflection/Type.h"
#include "YTEngine/Reflection/MetaInfo.h"

namespace Yor
{
  class SceneRegistry;

  // Contains all info needed for runtime execution
  class ApplicationDomain : public AutoSingleton<ApplicationDomain>
  {
    using CompAdd = std::function<void(SceneRegistry*, unsigned long long)>;
  public:
    ApplicationDomain();

  public:
    void registerObject(const ObjectMeta& meta);
    const ObjectMeta& findObject(const TypeID& id);
    const std::unordered_map<TypeID, ObjectMeta>& getAllObjects();

    void registerComponent(const ObjectMeta& meta, CompAdd func);
    const ObjectMeta& findComponent(const TypeID& id);
    const std::unordered_map<TypeID, ObjectMeta>& getAllComponents();
    void callComponentAdd(const TypeID& id, SceneRegistry* registry, unsigned long long uuid);

  private:
    std::unordered_map<TypeID, ObjectMeta> m_registeredObjects;
    std::unordered_map<TypeID, ObjectMeta> m_registeredComponents;
    std::unordered_map<TypeID, CompAdd> m_registeredComponentFuncs;
  };
}