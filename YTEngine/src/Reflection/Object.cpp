#include "YTEngine/Reflection/Object.h"
#include "YTEngine/Reflection/ApplicationDomain.h"

namespace Yor
{
  void Object::_registerObject(const std::string& name, const std::string& debug, const TypeID& id, size_t size)
  {
    if (m_registered) return;
    m_registered = true;
    _registerData();
    m_meta.info.name = name;
    m_meta.info.debugName = debug;
    m_meta.info.id = id;
    m_meta.info.size = size;
    ApplicationDomain::get().registerObject(m_meta);
  }
}