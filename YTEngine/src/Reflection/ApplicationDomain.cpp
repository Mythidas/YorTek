#include "YTEngine/Reflection/ApplicationDomain.h"
#include "YTEngine/Reflection/ComponentFactory.h"
#include "YTEngine/Reflection/ObjectFactory.h"
#include "YTEngine/Core/Application.h"

#include "YTEngine/Math/Vector3.h"
#include "YTEngine/Math/Transform.h"
#include "YTEngine/Graphics/Color.h"

namespace Yor
{
  ApplicationDomain::ApplicationDomain()
  {
  }

  void ApplicationDomain::registerObject(const ObjectMeta& meta)
  {
    m_registeredObjects[meta.info.id] = meta;
  }

  const ObjectMeta& ApplicationDomain::findObject(const TypeID& id)
  {
    return m_registeredObjects[id];
  }

  const std::unordered_map<TypeID, ObjectMeta>& ApplicationDomain::getAllObjects()
  {
    return m_registeredObjects;
  }

  void ApplicationDomain::registerComponent(const ObjectMeta& meta, CompAdd func)
  {
    m_registeredComponents[meta.info.id] = meta;
    m_registeredComponentFuncs[meta.info.id] = func;
  }

  const ObjectMeta& ApplicationDomain::findComponent(const TypeID& id)
  {
    return m_registeredComponents[id];
  }

  const std::unordered_map<TypeID, ObjectMeta>& ApplicationDomain::getAllComponents()
  {
    return m_registeredComponents;
  }

  void ApplicationDomain::callComponentAdd(const TypeID& id, SceneRegistry* registry, unsigned long long uuid)
  {
    m_registeredComponentFuncs[id](registry, uuid);
  }
}