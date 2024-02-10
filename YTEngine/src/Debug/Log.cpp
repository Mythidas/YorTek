#include "YTEngine/Debug/Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Yor
{
	Log::Log()
	{
		spdlog::set_pattern("%^[%T] %v%$");

		m_logger = spdlog::stdout_color_mt("App");
		m_logger->set_level(spdlog::level::trace);
	}

	void Log::trace(const std::string& message)
	{
		get().m_logger->trace(message);
	}

	void Log::info(const std::string& message)
	{
		get().m_logger->info(message);
	}

	void Log::warn(const std::string& message)
	{
		get().m_logger->warn(message);
	}

	void Log::error(const std::string& message)
	{
		get().m_logger->error(message);
	}

	void Log::critical(const std::string& message)
	{
		get().m_logger->critical(message);
	}
}