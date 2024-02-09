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

		bool getActive() const { return m_active; }
		std::string getName() const { return m_name; }
		UUID getID() const { return m_id; }
		UUID getParentID() const { return m_parent; }

		bool isValid() const;

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

		void destroy();
		std::vector<ComponentMeta> getComponents() const;

	public:
		static Entity create(SceneRegistry* registry = nullptr);
		static Entity create(const std::string& name, SceneRegistry* registry = nullptr);

	public:
		operator UUID() const
		{
			return m_id;
		}

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