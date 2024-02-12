#pragma once

#include "YTEngine/Core/UUID.h"
#include "YTEngine/Scene/EntityConstants.h"
#include "YTEngine/Reflection/Type.h"
#include "YTEngine/Reflection/MetaInfo.h"
#include "YTEngine/Math/Transform.h"

namespace Yor
{
	class SceneRegistry;

	class Entity
	{
	public:
		Entity();
		Entity(const UUID& id);
		Entity(const UUID& id, SceneRegistry* registry);

		void destroy();
		bool isValid() const;

		std::string getName() const { return _getData()->m_name; }
		bool getActive() const { return _getData()->m_active; }
		Transform getTransform() const { return _getData()->m_transform; }
		UUID getID() const { return m_id; }
		UUID getParentID() const { return _getData()->m_parent; }
		const std::vector<UUID>& getChildren() const { return _getData()->m_children; }
		std::vector<ComponentMeta> getComponents() const;

		void setName(const std::string& name) { _getData()->m_name = name; }
		void setActive(bool active) { _getData()->m_active = active; }
		void setTransform(const Transform& transform) { _getData()->m_transform = transform; }

		std::string& getNameRef() { return _getData()->m_name; }
		bool& getActiveRef() { return _getData()->m_active; }
		Transform& getTransformRef() { return _getData()->m_transform; }

	public:
		template <typename T>
		T* addComponent()
		{
			return static_cast<T*>(addComponent(type<T>().id()));
		}

		template <typename T>
		T* getComponent() const
		{
			return static_cast<T*>(getComponent(type<T>().id()));
		}
		template <typename T>
		bool hasComponent() const
		{
			return hasComponent(type<T>().id());
		}
		template <typename T>
		void removeComponent()
		{
			removeComponent(type<T>().id());
		}

		void* addComponent(const TypeID& component);
		void* getComponent(const TypeID& component) const;
		bool hasComponent(const TypeID& component) const;
		void removeComponent(const TypeID& component);

	public:
		static Entity create(SceneRegistry* registry = nullptr, UUID id = UUID());
		static Entity create(const std::string& name, SceneRegistry* registry = nullptr, UUID id = UUID());

	public:
		operator UUID() const
		{
			return m_id;
		}

	private:
		Entity* _getData();
		const Entity* _getData() const;

	private:
		friend class SceneRegistry;
		template <typename ...Components>
		friend class SceneView;

	private:
		std::string m_name{""};
		Transform m_transform{};
		bool m_active{ true };
		SceneRegistry* m_registry;
		UUID m_id{ UUID::INVALID };
		UUID m_parent{ UUID::INVALID };
		std::vector<UUID> m_children{};
		ComponentMask m_components{};
	};
}