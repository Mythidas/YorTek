#include "Inspector.h"
#include "EditorApplication.h"

#include <imgui.h>

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
      }
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