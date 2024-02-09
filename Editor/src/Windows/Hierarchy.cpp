#include "Hierarchy.h"
#include "EditorApplication.h"

#include <imgui.h>

namespace Yor::Editor
{
  void Hierarchy::onGUI()
  {
		Shared<Scene> scene = SceneManager::getActive();
		if (!scene->valid()) return;

		// Deselect

		if (Input::isKeyPressed(KeyCode::LeftMouseButton) && ImGui::IsWindowHovered() && !ImGui::IsAnyItemHovered())
		{
			EditorApplication::clearPayload();
		}

		// Right click menu

		if (ImGui::BeginPopupContextWindow("hierarchy_rmb_menu", ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_MouseButtonRight))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
			{
				scene->getRegistry().createEntity();
			}

			ImGui::EndPopup();
		}

		// Draw Entities

		for (Entity ent : SceneView<>(&scene->getRegistry()))
		{
			_drawEntityNode(ent);
		}
  }

	void Hierarchy::_drawEntityNode(Entity& entity)
	{
		Shared<Scene> scene = SceneManager::getActive();

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_FramePadding;
		if (ContextPayload* payload = EditorApplication::getPayload(); payload->isTarget("ENTITY_PAYLOAD"_hs))
		{
			if (*(UUID*)payload->data == entity.getID())
				flags |= ImGuiTreeNodeFlags_Selected;
		}

		bool opened = ImGui::TreeNodeEx((void*)entity.getName().c_str(), flags, entity.getName().c_str());

		if (ImGui::IsItemHovered() && Input::isKeyPressed(KeyCode::LeftMouseButton))
		{
			UUID id = entity.getID();
			EditorApplication::setPayload("ENTITY_PAYLOAD"_hs, &id, sizeof(id));
		}

		if (ImGui::BeginPopupContextItem(0, ImGuiPopupFlags_NoOpenOverExistingPopup | ImGuiPopupFlags_MouseButtonRight))
		{
			UUID id = entity.getID();
			EditorApplication::setPayload("ENTITY_PAYLOAD"_hs, &id, sizeof(id));

			if (ImGui::MenuItem("Delete Entity"))
				entity.destroy();

			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGui::TreePop();
		}
	}
}