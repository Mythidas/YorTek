#pragma once

#include <chrono>

namespace Yor
{
	class Time
	{
	private:
		friend class Application;
		typedef std::chrono::steady_clock::time_point TimePoint;

	public:
		static const float getFPS() { return s_averageFPS; }
		static const float getMSPerFrame() { return 1.0f / s_averageFPS * 1000.0f; }
		static const float getDeltaTime() { return s_deltaTime; }
		static const float getFixedDeltaTime() { return s_fixedDeltaTime; }

	private:
		static void _tick();
		static const float FIXED_DELTA_TIME;

	private:
		static TimePoint s_lastFrame;
		static TimePoint s_lastFixedFrame;
		static std::vector<float> s_frameTimes;

		static float s_averageFPS;
		static float s_deltaTime;
		static float s_fixedDeltaTime;
	};
}