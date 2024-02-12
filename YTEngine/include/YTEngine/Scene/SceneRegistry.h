#pragma once

#include "YTEngine/Scene/Entity.h"
#include "YTEngine/Scene/ComponentPool.h"
#include "YTEngine/Reflection/MetaInfo.h"

namespace Yor
{
  class SceneRegistry
  {
  public:
    SceneRegistry();
    ~SceneRegistry();

    Entity createEntity(UUID id = UUID());
    Entity createEntity(const std::string& name, UUID id = UUID());

    void destroyEntity(const UUID& id);

    Entity findEntity(const UUID& id) const;
    Entity entityAtIndex(size_t index) const;
    Entity* findEntityData(const UUID& id);
    Entity* findEntityData(const UUID& id) const;
    size_t getEntityCounter() const { return m_entityCounter; }

  public:
    template <typename T>
    T* addComponent(const UUID& id);
    template <typename T>
    T* getComponent(const UUID& id) const;
    template <typename T>
    bool hasComponent(const UUID& id) const;
    template <typename T>
    void removeComponent(const UUID& id);

    void* addComponent(const UUID& id, const TypeID& component);
    void* getComponent(const UUID& id, const TypeID& component) const;
    bool hasComponent(const UUID& id, const TypeID& component) const;
    void removeComponent(const UUID& id, const TypeID& component);

    std::vector<ObjectMeta> getComponents(const UUID& id) const;

  public:
    template <typename T>
    size_t findComponentID() const;
    size_t findComponentID(const TypeID& component) const;

    bool isValidEntity(const UUID& id) const;

  private:
    friend class SceneSerializer;

  private:
    Entity* m_entities;
    size_t m_entityCounter{ 0 };
    std::vector<size_t> m_freeIndices{};
    std::vector<ComponentPool*> m_componentPools{};
    std::unordered_map<UUID, size_t> m_entityIndices{};
  };

  template<typename T>
  inline T* SceneRegistry::addComponent(const UUID& id)
  {
    if (!isValidEntity(id)) return nullptr;

    size_t compID = findComponentID<T>();
    if (compID > MAX_COMPONENTS) return nullptr;

    if (m_entities[m_entityIndices[id]].m_components.test(compID))
      return static_cast<T*>(m_componentPools[compID]->getData(m_entityIndices[id]));

    if (compID >= m_componentPools.size())
    {
      m_componentPools.push_back(new ComponentPool(type<T>().id(), sizeof(T)));
    }

    T* component = new (m_componentPools[compID]->getData(m_entityIndices[id])) T();
    m_entities[m_entityIndices[id]].m_components.set(compID);
    return component;
  }

  template<typename T>
  inline T* SceneRegistry::getComponent(const UUID& id) const
  {
    if (!isValidEntity(id)) return nullptr;

    size_t compID = findComponentID<T>();

    if (m_entities[m_entityIndices.at(id)].m_components.test(compID))
      return static_cast<T*>(m_componentPools[compID]->getData(m_entityIndices.at(id)));

    return nullptr;
  }

  template<typename T>
  inline bool SceneRegistry::hasComponent(const UUID& id) const
  {
    if (!isValidEntity(id)) return false;

    size_t compID = findComponentID<T>();

    if (m_entities[m_entityIndices.at(id)].m_components.test(compID))
      return false;

    return false;
  }

  template<typename T>
  inline void SceneRegistry::removeComponent(const UUID& id)
  {
    if (!isValidEntity(id)) return;

    size_t compID = findComponentID<T>();
    m_entities[m_entityIndices[id]].m_components.reset(compID);
  }

  template<typename T>
  inline size_t SceneRegistry::findComponentID() const
  {
    return findComponentID(Type<T>().id());
  }
}