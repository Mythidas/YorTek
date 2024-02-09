#pragma once

#include "YTEngine.h"

#include <glm/glm.hpp>

namespace Yor::Editor
{
	class EditorCamera : public Camera
	{
	public:
		EditorCamera();

		void onUpdate();

		Transform& getTransform() { return m_transform; }

	private:
		float _getSpeed();
		float _getScrollSpeed();
		bool _onScroll(float offset);

	private:
		Transform m_transform{};
		float m_speed{ 3.0f };
		float m_scrollSpeed{ 400.0f };
		float m_fastSpeed{ 3.0f };
	};
}