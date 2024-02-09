#pragma once

#include "YTEngine/Core/Defines.h"

#include <functional>

namespace Yor
{
	template <typename... Args>
	class Event
	{
	private:
		using Func = std::function<bool(Args...)>;

	public:
		void dispatch(Args... args)
		{
			for (auto& callback : m_callbacks)
			{
				if (callback(args...))
					break;
			}

			for (auto& callback : m_listeners)
			{
				callback->dispatch(args...);
			}
		}

		void operator()(Args... args)
		{
			dispatch(args...);
		}

		void operator +=(const Func& callback)
		{
			m_callbacks.push_back(callback);
		}

		void operator +=(Event<Args...>& e)
		{
			m_listeners.push_back(&e);
		}

	private:
		std::vector<Func> m_callbacks;
		std::vector<Event<Args...>*> m_listeners;
	};
}