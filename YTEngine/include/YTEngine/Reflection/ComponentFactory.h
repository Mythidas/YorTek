#pragma once

#include "YTEngine/Reflection/ApplicationDomain.h"
#include "YTEngine/Scene/SceneRegistry.h"

#include <functional>

namespace Yor
{
	template <typename T>
	class ComponentFactory
	{
	public:
		template <auto data>
		inline ComponentFactory<T>& data(const std::string& name, size_t offset)
		{
			if constexpr (std::is_member_object_pointer_v<decltype(data)>)
			{
				using data_type = std::remove_reference_t<std::invoke_result_t<decltype(data), T&>>;
				type<data_type> type;
				if (type.ref() != TypeRef::Unknown)
				{
					MetaInfo meta(name, name, type.id());
					m_properties.push_back({ meta, type.ref(), offset});
				}
			}

			return *this;
		}

		inline ComponentMeta build(ApplicationDomain* domain)
		{
			ComponentMeta meta;
			meta.info.name = type<T>().name();
			meta.info.debugName = type<T>().debugName();
			meta.info.id = type<T>().id();
			meta.info.size = sizeof(T);
			meta.properties = m_properties;
			domain->registerComponent(meta);
			return meta;
		}

	private:
		std::vector<PropertyMeta> m_properties;
	};
}