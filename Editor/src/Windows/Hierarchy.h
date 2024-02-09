#pragma once

#include "YTEngine.h"
#include "GUI/EditorWindow.h"

namespace Yor::Editor
{
	class Hierarchy : public EditorWindow
	{
	public:
		virtual void onGUI() override;

		virtual const char* getWindowTitle() const { return "Hierarchy"; }

	private:
		void _drawEntityNode(Entity& entity);
	};
}