#pragma once

#include "YTEngine/Tools/AutoSingleton.h"

#include <spdlog/spdlog.h>
#include <memory>

namespace spdlog
{
	class spdlog::logger;
}

namespace Yor
{
	class Log : public AutoSingleton<Log>
	{
	public:
		Log();

		template <typename... Args>
		inline static void trace(spdlog::format_string_t<Args...> message, Args &&...args)
		{
			get().m_logger->trace(message, std::forward<Args>(args)...);
		}
		template <typename... Args>
		inline static void info(spdlog::format_string_t<Args...> message, Args &&...args)
		{
			get().m_logger->info(message, std::forward<Args>(args)...);
		}
		template <typename... Args>
		inline static void warn(spdlog::format_string_t<Args...> message, Args &&...args)
		{
			get().m_logger->warn(message, std::forward<Args>(args)...);
		}
		template <typename... Args>
		inline static void error(spdlog::format_string_t<Args...> message, Args &&...args)
		{
			get().m_logger->error(message, std::forward<Args>(args)...);
		}
		template <typename... Args>
		inline static void critical(spdlog::format_string_t<Args...> message, Args &&...args)
		{
			get().m_logger->critical(message, std::forward<Args>(args)...);
		}

		static void trace(const std::string& message);
		static void info(const std::string& message);
		static void warn(const std::string& message);
		static void error(const std::string& message);
		static void critical(const std::string& message);

	private:
		std::shared_ptr<spdlog::logger> m_logger;
	};
}