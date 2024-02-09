#pragma once

#include "YTEngine/Tools/Stringf.h"

#include <type_traits>
#include <string>

namespace Yor
{
	using TypeID = uint64_t;

	// Used as a tag to know which types are objects at compile time
	// Objects still need to have a registered ObjectMeta with the Domain to be dereferenced
	class Object {};

	// Used as a tag to know which types are objects at compile time
	// Objects still need to have a registered ComponentMeta with the ComponentRegistry to be dereferenced
	class Component {};

	enum class TypeRef : int
	{
		Unknown = 0,
		Object,
		Component,
		Bool,
		String,
		Int32,
		Int64,
		UInt32,
		UInt64,
		Float,
		Double
	};

	template<typename T>
	class type
	{
	public:
		std::string name() const
		{
			std::string debug = debugName();
			size_t offset = debug.find_last_of(':') + 1;
			if (offset == 0)
				offset = debug.find_last_of(' ') + 1;
			return debug.substr(offset);
		}

		std::string debugName() const
		{
			return typeid(T).name();
		}

		TypeID id() const
		{
			return Stringf::hash(typeid(T).name());
		}

		TypeRef ref() const
		{
			if constexpr (std::is_convertible_v<T, Object>)
				return TypeRef::Object;
			else if constexpr (std::is_convertible_v<T, Component>)
				return TypeRef::Component;
			else if constexpr (std::is_same_v<T, std::string>)
				return TypeRef::String;
			else if constexpr (std::is_same_v<T, bool>)
				return TypeRef::Bool;
			else if constexpr (std::is_same_v<T, int>)
				return TypeRef::Int32;
			else if constexpr (std::is_same_v<T, long long>)
				return TypeRef::Int64;
			else if constexpr (std::is_same_v<T, unsigned int>)
				return TypeRef::UInt32;
			else if constexpr (std::is_same_v<T, unsigned long long>)
				return TypeRef::UInt64;
			else if constexpr (std::is_same_v<T, float>)
				return TypeRef::Float;
			else if constexpr (std::is_same_v<T, double>)
				return TypeRef::Double;

			return TypeRef::Unknown;
		}
	};
}