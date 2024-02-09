#pragma once

#include "YTEngine/Scene/SceneRegistry.h"
#include "YTEngine/Scene/SceneManager.h"

namespace Yor
{
  template <typename ...Components>
  class SceneView
  {
	public:
		SceneView(SceneRegistry* registry = nullptr)
			: m_registry(registry)
		{
			if (!m_registry)
				m_registry = &SceneManager::getActive()->getRegistry();

			if (sizeof...(Components) == 0)
			{
				m_all = true;
			}
			else
			{
				size_t componentIDs[] = { 0, m_registry->findComponentID<Components>()... };
				for (size_t i = 1; i < (sizeof...(Components) + 1); i++)
				{
					if (componentIDs[i] != UINT64_MAX)
						m_mask.set(componentIDs[i]);
					else
					{
						m_invalid = true;
						break;
					}
				}
			}
		}

		struct Iterator
		{
			Iterator(SceneRegistry* registry, size_t index, ComponentMask components, bool all)
				: registry(registry), index(index), mask(components), all(all)
			{
			}

			Entity operator*() const
			{
				return registry->entityAtIndex(index);
			}

			bool operator ==(const Iterator& other) const
			{
				return index == other.index;
			}

			bool operator !=(const Iterator& other) const
			{
				return index != other.index;
			}

			Iterator& operator++()
			{
				do
				{
					index++;
				} while (index < registry->getEntityCounter() && !IsValidIndex());
				return *this;
			}

			bool IsValidIndex()
			{
				if (!registry->isValidEntity(registry->entityAtIndex(index))) return false;
				return all || mask == (mask & registry->entityAtIndex(index).m_components);
			}

			SceneRegistry* registry;
			size_t index{ 0 };
			ComponentMask mask;
			bool all{ false };
		};

		const Iterator begin() const
		{
			size_t first = m_invalid ? m_registry->getEntityCounter() : 0;
			while (first < m_registry->getEntityCounter() &&
				(m_mask != (m_mask & m_registry->entityAtIndex(first).m_components) ||
					!m_registry->isValidEntity(m_registry->entityAtIndex(first).m_id)))
			{
				first++;
			}

			return Iterator(m_registry, first, m_mask, m_all);
		}

		const Iterator end() const
		{
			return Iterator(m_registry, m_registry->getEntityCounter(), m_mask, m_all);
		}

	private:
		bool m_all{ false };
		bool m_invalid{ false };
		ComponentMask m_mask;
		SceneRegistry* m_registry;
  };
}