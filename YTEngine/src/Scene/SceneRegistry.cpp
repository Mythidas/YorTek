#include "YTEngine/Scene/SceneRegistry.h"
#include "YTEngine/Scene/Entity.h"
#include "YTEngine/Reflection/ApplicationDomain.h"
#include "YTEngine/Debug/Log.h"

namespace Yor
{
  SceneRegistry::SceneRegistry()
  {
    m_entities = new Entity[MAX_ENTITIES]{};
  }

  SceneRegistry::~SceneRegistry()
  {
    delete[] m_entities;
    for (size_t i = 0; i < m_componentPools.size(); i++)
    {
      delete m_componentPools[i];
    }
  }

  Entity SceneRegistry::createEntity(UUID id)
  {
    return createEntity("Empty Entity", id);
  }

  Entity SceneRegistry::createEntity(const std::string& name, UUID id)
  {
    Log::info("New Entity Created! ID: {0}", id);

    if (!m_freeIndices.empty())
    {
      size_t oldIndex = m_freeIndices.back();
      m_freeIndices.pop_back();
      
      m_entities[oldIndex] = Entity(id, this);
      m_entities[oldIndex].m_name = name;
      m_entityIndices[id] = oldIndex;
      return m_entities[oldIndex];
    }
    else
    {
      m_entities[m_entityCounter] = Entity(id, this);
      m_entities[m_entityCounter].m_name = name;
      m_entityIndices[id] = m_entityCounter;
      m_entityCounter++;
      return m_entities[m_entityCounter - 1];
    }
  }

  void SceneRegistry::destroyEntity(const UUID& id)
  {
    if (!isValidEntity(id)) return;

    m_freeIndices.push_back(m_entityIndices[id]);
    m_entities[m_entityIndices[id]].m_id = UUID::INVALID;
    m_entityIndices.erase(id);
  }

  Entity SceneRegistry::findEntity(const UUID& id) const
  {
    if (!m_entityIndices.contains(id)) return Entity(UUID::INVALID);
    return m_entities[m_entityIndices.at(id)];
  }

  Entity SceneRegistry::entityAtIndex(size_t index) const
  {
    return m_entities[index];
  }

  Entity* SceneRegistry::findEntityData(const UUID& id)
  {
    if (!m_entityIndices.contains(id)) return nullptr;
    return &m_entities[m_entityIndices.at(id)];
  }

  Entity* SceneRegistry::findEntityData(const UUID& id) const
  {
    if (!m_entityIndices.contains(id)) return nullptr;
    return &m_entities[m_entityIndices.at(id)];
  }

  void* SceneRegistry::addComponent(const UUID& id, const TypeID& component)
  {
    if (!isValidEntity(id)) return nullptr;

    size_t compID = findComponentID(component);
    if (compID > MAX_COMPONENTS) return nullptr;

    if (m_entities[m_entityIndices[id]].m_components.test(compID))
      return m_componentPools[compID]->getData(m_entityIndices[id]);

    if (compID >= m_componentPools.size())
    {
      m_componentPools.push_back(new ComponentPool(component, ApplicationDomain::get().findComponent(component).info.size));
    }

    m_entities[m_entityIndices[id]].m_components.set(compID);
    return m_componentPools[compID]->getData(m_entityIndices[id]);
  }

  void* SceneRegistry::getComponent(const UUID& id, const TypeID& component) const
  {
    if (!isValidEntity(id)) return nullptr;

    size_t compID = findComponentID(component);

    if (m_entities[m_entityIndices.at(id)].m_components.test(compID))
      return (void*)(m_componentPools[compID]->getData(m_entityIndices.at(id)));

    return nullptr;
  }

  bool SceneRegistry::hasComponent(const UUID& id, const TypeID& component) const
  {
    if (!isValidEntity(id)) return false;

    size_t compID = findComponentID(component);

    if (m_entities[m_entityIndices.at(id)].m_components.test(compID))
      return true;

    return false;
  }

  void SceneRegistry::removeComponent(const UUID& id, const TypeID& component)
  {
    if (!isValidEntity(id)) return;

    size_t compID = findComponentID(component);
    m_entities[m_entityIndices[id]].m_components.reset(compID);
  }

  std::vector<ComponentMeta> SceneRegistry::getComponents(const UUID& id) const
  {
    if (!isValidEntity(id)) return std::vector<ComponentMeta>();

    std::vector<ComponentMeta> components;
    for (size_t i = 0; i < m_componentPools.size(); i++)
    {
      if (m_entities[m_entityIndices.at(id)].m_components.test(i))
        components.push_back(ApplicationDomain::get().findComponent(m_componentPools[i]->getType()));
    }

    return components;
  }
  
  size_t SceneRegistry::findComponentID(const TypeID& component) const
  {
    for (size_t i = 0; i < m_componentPools.size(); i++)
    {
      if (m_componentPools[i]->isType(component))
        return i;
    }

    return m_componentPools.size();
  }

  bool SceneRegistry::isValidEntity(const UUID& id) const
  {
    if (!id.valid()) return false;
    if (!m_entityIndices.contains(id)) return false;
    return true;
  }
}