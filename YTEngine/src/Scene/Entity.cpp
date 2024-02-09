#include "YTEngine/Scene/Entity.h"
#include "YTEngine/Scene/SceneManager.h"
#include "YTEngine/Scene/SceneRegistry.h"

namespace Yor
{
	Entity::Entity()
		: m_id(UUID::INVALID)
	{
	}

	Entity::Entity(const UUID& id)
    : m_id(id), m_registry(&SceneManager::getActive()->getRegistry())
  {
  }

  Entity::Entity(const UUID& id, SceneRegistry* registry)
    : m_id(id), m_registry(registry)
  {
  }

	bool Entity::isValid() const
	{
		return m_registry && m_id != UUID::INVALID;
	}

	std::vector<ComponentMeta> Entity::getComponents() const
	{
		if (!m_registry) return std::vector<ComponentMeta>();
		return m_registry->getComponents(m_id);
	}

	void* Entity::addComponent(const TypeID& component)
	{
		if (!m_registry) return nullptr;
		return m_registry->addComponent(m_id, component);
	}

	void* Entity::getComponent(const TypeID& component) const
	{
		if (!m_registry) return nullptr;
		return m_registry->getComponent(m_id, component);
	}

	bool Entity::hasComponent(const TypeID& component) const
	{
		if (!m_registry) return false;
		return m_registry->hasComponent(m_id, component);
	}

	void Entity::removeComponent(const TypeID& component)
	{
		if (!m_registry) return;
		m_registry->removeComponent(m_id, component);
	}

	void Entity::destroy()
	{
		if (!m_registry) return;
		m_registry->destroyEntity(m_id);
	}

  Entity Entity::create(SceneRegistry* registry)
  {
		if (!registry)
			return SceneManager::getActive()->getRegistry().createEntity();
		
		return registry->createEntity();
  }
  Entity Entity::create(const std::string& name, SceneRegistry* registry)
  {
		if (!registry)
			return SceneManager::getActive()->getRegistry().createEntity(name);

		return registry->createEntity(name);
  }
}