#pragma once

#include "YTEngine/Reflection/ApplicationDomain.h"
#include "YTEngine/Scene/SceneRegistry.h"

#include <functional>

namespace Yor
{
	template <typename T>
	class ObjectFactory
	{
	public:
		template <auto data>
		inline ObjectFactory<T>& data(const std::string& name, size_t offset)
		{
			if constexpr (std::is_member_object_pointer_v<decltype(data)>)
			{
				using data_type = std::remove_reference_t<std::invoke_result_t<decltype(data), T&>>;
				Type<data_type> type;
				if (type.ref() != TypeRef::Unknown)
				{
					MetaInfo meta(name, type.debugName(), type.id());
					m_properties.push_back({ meta, type.ref(), offset });
				}
			}

			return *this;
		}

		inline ObjectMeta build(ApplicationDomain* domain)
		{
			ObjectMeta meta;
			meta.info.name = Type<T>().name();
			meta.info.debugName = Type<T>().debugName();
			meta.info.id = Type<T>().id();
			meta.info.size = sizeof(T);
			meta.properties = m_properties;
			domain->registerObject(meta);
			return meta;
		}

	private:
		std::vector<PropertyMeta> m_properties;
	};
}