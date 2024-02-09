#include "YTEngine/Reflection/ApplicationDomain.h"
#include "YTEngine/Reflection/ComponentFactory.h"
#include "YTEngine/Core/Application.h"

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
    auto testComp1 = ComponentFactory<TestComp1>()
      .data<&TestComp1::ImplFloat>("ImplFloat", offsetof(TestComp1, ImplFloat))
      .data<&TestComp1::ImplInt>("ImplInt", offsetof(TestComp1, ImplInt))
      .build(this);

    auto testComp2 = ComponentFactory<TestComp2>()
      .data<&TestComp2::ImplShort>("ImplShort", offsetof(TestComp2, ImplShort))
      .data<&TestComp2::ImplUInt64>("ImplUInt64", offsetof(TestComp2, ImplUInt64))
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

  void ApplicationDomain::registerComponent(const ComponentMeta& meta)
  {
    m_registeredComponents[meta.info.id] = meta;
  }

  const ComponentMeta& ApplicationDomain::findComponent(const TypeID& id)
  {
    return m_registeredComponents[id];
  }

  const std::unordered_map<TypeID, ComponentMeta>& ApplicationDomain::getAllComponents()
  {
    return m_registeredComponents;
  }
}