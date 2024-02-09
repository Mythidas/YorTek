#pragma once

namespace Yor
{
	template <typename T>
	class Singleton
	{
	public:
		Singleton()
		{
			if (s_instance) return;
			s_instance = static_cast<T*>(this);
		}

		static T& get()
		{
			return *s_instance;
		}

		template <typename U>
		static U& cast()
		{
			return *static_cast<U*>(s_instance);
		}

	private:
		inline static T* s_instance{ nullptr };
	};
}