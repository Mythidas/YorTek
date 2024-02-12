#include "YTEngine/Scene/Entity.h"
#include "YTEngine/Scene/SceneManager.h"
#include "YTEngine/Scene/SceneRegistry.h"

namespace Yor
{
	Entity::Entity()
		: Entity(UUID::INVALID, nullptr)
	{
	}

	Entity::Entity(const UUID& id)
    : Entity(id, &SceneManager::getActive()->getRegistry())
  {
  }

  Entity::Entity(const UUID& id, SceneRegistry* registry)
    : m_id(id), m_registry(registry)
  {
  }

	void Entity::destroy()
	{
		if (!m_registry) return;
		m_registry->destroyEntity(m_id);
	}

	bool Entity::isValid() const
	{
		return m_registry && m_registry->isValidEntity(m_id);
	}

	void Entity::addChild(const UUID& id)
	{
		_getData()->m_children.push_back(id);
	}

	void Entity::removeChild(const UUID& id)
	{
		// TODO: Implement Remove
	}

	std::vector<ObjectMeta> Entity::getComponents() const
	{
		if (!m_registry) return std::vector<ObjectMeta>();
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

	Entity Entity::create(SceneRegistry* registry, UUID id)
  {
		if (!registry)
			return SceneManager::getActive()->getRegistry().createEntity();
		
		return registry->createEntity();
  }

  Entity Entity::create(const std::string& name, SceneRegistry* registry, UUID id)
  {
		if (!registry)
			return SceneManager::getActive()->getRegistry().createEntity(name);

		return registry->createEntity(name);
  }

	Entity* Entity::_getData()
	{
		if (isValid())
			return m_registry->findEntityData(m_id);

		return this;
	}

	const Entity* Entity::_getData() const
	{
		if (isValid())
			return m_registry->findEntityData(m_id);

		return this;
	}
}