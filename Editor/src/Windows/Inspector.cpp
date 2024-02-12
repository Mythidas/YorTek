#include "Inspector.h"
#include "EditorApplication.h"
#include "GUI/Controls.h"

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

namespace Yor::Editor
{
  void Inspector::onGUI()
  {
    ContextPayload* payload = EditorApplication::getPayload();
    
    switch (payload->targetID)
    {
    case "ENTITY_PAYLOAD"_hs: _drawEntityInfo(); break;
    }
  }

  void Inspector::_drawEntityInfo()
  {
    ContextPayload* payload = EditorApplication::getPayload();

    auto entity = Entity(*(UUID*)payload->data);

    {// Draw Active & Name
      bool& _active = entity.getActiveRef();
      ImGui::Checkbox("##active", &_active);

      ImGui::SameLine();
      std::string& _name = entity.getNameRef();
      ImGui::InputText("##name", &_name);
      ImGui::Separator();
    }

    {// Draw Transform
      float xSize = ImGui::GetContentRegionAvail().x;
      bool transNode = ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_FramePadding);
      ImGui::SameLine(xSize - 15.0f);
      if (ImGui::Button("R"))
      {
        ImGui::OpenPopup("##rem_res_comp");
      }

      if (ImGui::BeginPopup("##rem_res_comp"))
      {
        if (ImGui::MenuItem("Reset Component"))
        {
          entity.setTransform({});
        }

        ImGui::EndPopup();
      }

      if (transNode)
      {
        ImGui::Separator();
        Transform& _transform = entity.getTransformRef();
        Controls::Vector3("Position", _transform.position);
        ImGui::Spacing();
        Controls::Vector3("Rotation", _transform.rotation);
        ImGui::Spacing();
        Controls::Vector3("Scale", _transform.scale);

        ImGui::Spacing();
        ImGui::TreePop();
      }
    }
    ImGui::Separator();

    // Draw Components
    for (auto& comp : entity.getComponents())
    {
      char* data = (char*)SceneManager::getActive()->getRegistry().getComponent(entity.getID(), comp.info.id);

      bool node = ImGui::TreeNodeEx(comp.info.name.c_str(), ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding);

      ImGui::SameLine(ImGui::GetContentRegionAvail().x - 15.0f);
      if (ImGui::Button("R"))
      {
        ImGui::OpenPopup("##rem_res_comp");
      }

      if (ImGui::BeginPopup("##rem_res_comp"))
      {
        if (ImGui::MenuItem("Reset Component"))
        {
          SceneManager::getActive()->getRegistry().removeComponent(entity.getID(), comp.info.id);
          SceneManager::getActive()->getRegistry().addComponent(entity.getID(), comp.info.id);
        }

        if (ImGui::MenuItem("Remove Component"))
        {
          SceneManager::getActive()->getRegistry().removeComponent(entity.getID(), comp.info.id);
        }

        ImGui::EndPopup();
      }

      if (node)
      {
        for (auto& prop : comp.properties)
        {
          _drawVariableInfo(data, prop);
        }

        ImGui::Spacing();
        ImGui::TreePop();
      }
    }

    // Add components
    ImGui::Spacing();
    if (ImGui::Button("Add Component", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
      ImGui::OpenPopup("Add Component");

    if (ImGui::BeginPopup("Add Component"))
    {
      for (auto& component : ApplicationDomain::get().getAllComponents())
      {
        if (SceneManager::getActive()->getRegistry().hasComponent(entity.getID(), component.second.info.id))
          continue;

        if (ImGui::MenuItem(component.second.info.name.c_str()))
        {
          entity.addComponent(component.second.info.id);
          ImGui::CloseCurrentPopup();
        }
      }

      ImGui::EndPopup();
    }
  }

  void Inspector::_drawVariableInfo(char* data, PropertyMeta meta)
  {
    if (meta.ref == TypeRef::Object)
    {
      auto& object = ApplicationDomain::get().findComponent(meta.info.id);

      for (auto& prop : object.properties)
      {
        _drawVariableInfo(data + meta.offset, prop);
      }
    }
    else if (meta.ref == TypeRef::Bool)
    {
      ImGui::Checkbox(meta.info.name.c_str(), (bool*)(data + meta.offset));
    }
    else if (meta.ref == TypeRef::Float)
    {
      ImGui::DragFloat(meta.info.name.c_str(), (float*)(data + meta.offset));
    }
  }
}