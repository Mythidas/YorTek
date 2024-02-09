#include "YTEngine/Core/Time.h"

namespace Yor
{
	const float Time::FIXED_DELTA_TIME = 0.02f;

	Time::TimePoint Time::s_lastFrame = std::chrono::high_resolution_clock::now();
	Time::TimePoint Time::s_lastFixedFrame;

	std::vector<float> Time::s_frameTimes;

	float Time::s_averageFPS;
	float Time::s_deltaTime;
	float Time::s_fixedDeltaTime;

	static float s_OneSecond = 1.0f;

	void Time::_tick()
	{
		TimePoint now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> delta = now - s_lastFrame;
		s_lastFrame = now;
		s_deltaTime = delta.count();

		s_OneSecond -= s_deltaTime;
		if (s_OneSecond < 0.0f)
		{
			float total = 0.0f;
			for (auto& ds : s_frameTimes)
				total += ds;

			s_averageFPS = 1.0f / (total / s_frameTimes.size());
			s_frameTimes.clear();
			s_OneSecond = 1.0f;
		}
		else
		{
			s_frameTimes.push_back(s_deltaTime);
		}

		std::chrono::duration<float> fixedDelta = now - s_lastFixedFrame;
		if (fixedDelta.count() >= FIXED_DELTA_TIME)
		{
			s_lastFixedFrame = now;
			s_fixedDeltaTime = fixedDelta.count();
		}
		else
		{
			s_fixedDeltaTime = 0.0f;
		}
	}
}