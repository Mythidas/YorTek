#pragma once

namespace Yor
{
	template <typename T>
	class AutoSingleton
	{
	public:
		AutoSingleton()
		{
			if (s_instance) return;
			s_instance = static_cast<T*>(this);
		}

		~AutoSingleton()
		{
			delete s_instance;
		}

		static T& get()
		{
			if (!s_instance)
			{
				s_instance = new T();
			}

			return *s_instance;
		}

		template <typename U>
		static U& cast()
		{
			if (!s_instance)
			{
				s_instance = new T();
			}

			return *static_cast<U*>(s_instance);
		}

	private:
		inline static T* s_instance{ nullptr };
	};
}