#include "YTEngine/Reflection/ApplicationDomain.h"
#include "YTEngine/Reflection/ComponentFactory.h"
#include "YTEngine/Reflection/ObjectFactory.h"
#include "YTEngine/Core/Application.h"

#include "YTEngine/Math/Vector3.h"
#include "YTEngine/Math/Transform.h"

struct TestComp1 : public Yor::Component
{
  float ImplFloat;
  int ImplInt;
};

struct TestComp2 : public Yor::Component
{
  short ImplShort;
  unsigned long long ImplUInt64;
};

namespace Yor
{
  ApplicationDomain::ApplicationDomain()
  {
    auto vec3 = ObjectFactory<Vector3>()
      .data<&Vector3::x>("X", offsetof(Vector3, x))
      .data<&Vector3::y>("Y", offsetof(Vector3, y))
      .data<&Vector3::z>("Z", offsetof(Vector3, z))
      .build(this);
    auto ivec3 = ObjectFactory<IVector3>()
      .data<&IVector3::x>("X", offsetof(IVector3, x))
      .data<&IVector3::y>("Y", offsetof(IVector3, y))
      .data<&IVector3::z>("Z", offsetof(IVector3, z))
      .build(this);
    auto uvec3 = ObjectFactory<UVector3>()
      .data<&UVector3::x>("X", offsetof(UVector3, x))
      .data<&UVector3::y>("Y", offsetof(UVector3, y))
      .data<&UVector3::z>("Z", offsetof(UVector3, z))
      .build(this);
    auto transform = ObjectFactory<Transform>()
      .data<&Transform::position>("Position", offsetof(Transform, position))
      .data<&Transform::rotation>("Rotation", offsetof(Transform, rotation))
      .data<&Transform::scale>("Scale", offsetof(Transform, scale))
      .build(this);
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

  void ApplicationDomain::registerComponent(const ObjectMeta& meta)
  {
    m_registeredComponents[meta.info.id] = meta;
  }

  const ObjectMeta& ApplicationDomain::findComponent(const TypeID& id)
  {
    return m_registeredComponents[id];
  }

  const std::unordered_map<TypeID, ObjectMeta>& ApplicationDomain::getAllComponents()
  {
    return m_registeredComponents;
  }
}