#include "EditorCamera.h"

#include <iostream>

namespace Yor::Editor
{
	EditorCamera::EditorCamera()
	{
		clearColor = { 0.4f, 0.5f, 0.6f, 1.0f };
		m_transform.position.z = -5.0f;
		Application::getWindow()->OnMouseScrolled += YT_BIND_FNC(_onScroll);
	}

	void EditorCamera::onUpdate()
	{
		if (!Input::isKeyPressed(KeyCode::RightMouseButton))
		{
			Input::setCursorMode(false);
			return;
		}

		Input::setCursorMode(true);

		// Myth: This is for 3D rotation, don't really need it for 2D. Maybe will make variables to enable it in editor
		//m_transform.Rotation.x -= delta.y;
		//m_transform.Rotation.y -= delta.x;

		if (Input::isKeyPressed(KeyCode::W))
		{
			m_transform.position += m_transform.up() * _getSpeed() * Time::getDeltaTime();
		}
		if (Input::isKeyPressed(KeyCode::S))
		{
			m_transform.position += m_transform.down() * _getSpeed() * Time::getDeltaTime();
		}
		if (Input::isKeyPressed(KeyCode::A))
		{
			m_transform.position += m_transform.left() * _getSpeed() * Time::getDeltaTime();
		}
		if (Input::isKeyPressed(KeyCode::D))
		{
			m_transform.position += m_transform.right() * _getSpeed() * Time::getDeltaTime();
		}
	}

	float EditorCamera::_getSpeed()
	{
		if (Input::isKeyPressed(KeyCode::LeftShift))
			return m_speed * m_fastSpeed;
		return m_speed;
	}

	float EditorCamera::_getScrollSpeed()
	{
		if (Input::isKeyPressed(KeyCode::LeftShift))
			return m_scrollSpeed * m_fastSpeed;
		return m_scrollSpeed;
	}

	bool EditorCamera::_onScroll(float offset)
	{
		if (Input::isKeyPressed(KeyCode::RightMouseButton))
		{
			m_transform.position.z += offset * _getScrollSpeed() * Time::getDeltaTime();
			std::cout << m_transform.position.z << std::endl;
		}

		return false;
	}
}