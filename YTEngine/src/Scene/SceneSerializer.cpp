#include "YTEngine/Scene/SceneSerializer.h"
#include "YTEngine/Scene/SceneView.h"
#include "YTEngine/Reflection/ApplicationDomain.h"

#include <yaml-cpp/yaml.h>

namespace Yor
{
  namespace Utils
  {
    static void _serializeProperty(YAML::Emitter& out, const char* data, const PropertyMeta& meta)
    {
      out << YAML::Key << meta.info.debugName;

      switch (meta.ref)
      {
      case TypeRef::Object:
      {
        ObjectMeta obj = ApplicationDomain::get().findObject(meta.info.id);
        out << YAML::Value << YAML::BeginMap;
        for (auto& prop : obj.properties)
        {
          _serializeProperty(out, data + meta.offset, prop);
        }
        out << YAML::EndMap;

        break;
      }
      case TypeRef::Component:
      {
        break;
      }
      case TypeRef::Int32: out << YAML::Value << *(int*)(data + meta.offset); break;
      case TypeRef::Int64: out << YAML::Value << *(int64_t*)(data + meta.offset); break;
      case TypeRef::UInt32: out << YAML::Value << *(uint32_t*)(data + meta.offset); break;
      case TypeRef::UInt64: out << YAML::Value << *(uint64_t*)(data + meta.offset); break;
      case TypeRef::Float: out << YAML::Value << *(float*)(data + meta.offset); break;
      case TypeRef::Double: out << YAML::Value << *(double*)(data + meta.offset); break;
      case TypeRef::String: out << YAML::Value << *(std::string*)(data + meta.offset); break;
      }
    }

    static void _serializeObject(YAML::Emitter& out, const ObjectMeta& meta, const char* data)
    {
      out << YAML::Key << meta.info.debugName << YAML::BeginMap;
      for (auto& prop : meta.properties)
      {
        _serializeProperty(out, data, prop);
      }
      out << YAML::EndMap;
    }

    static void _serializeEntity(YAML::Emitter& out, const Entity& entity)
    {
      out << YAML::BeginMap;
      out << YAML::Key << "ID" << YAML::Value << (uint64_t)entity.getID();
      out << YAML::Key << "Name" << YAML::Value << entity.getName();
      out << YAML::Key << "Active" << YAML::Value << entity.getActive();
      out << YAML::Key << "Parent" << YAML::Value << entity.getParentID();
      Transform _transform = entity.getTransform();
      _serializeObject(out, ApplicationDomain::get().findObject(Type<Transform>().id()), (const char*)&_transform);
      out << YAML::Key << "Children" << YAML::Value << YAML::BeginMap;
      int count = 0;
      for (auto& child : entity.getChildren())
      {
        out << YAML::Key << "ChildID" << count << YAML::Value << (uint64_t)entity.getID();
      }
      out << YAML::EndMap;

      out << YAML::Key << "Components" << YAML::Value << YAML::BeginMap;

      for (auto& comp : entity.getComponents())
      {
        char* data = (char*)entity.getComponent(comp.info.id);

        out << YAML::Key << comp.info.debugName << YAML::Value << YAML::BeginMap;
        for (auto& prop : comp.properties)
        {
          _serializeProperty(out, data, prop);
        }
        out << YAML::EndMap;
      }

      out << YAML::EndMap;
      out << YAML::EndMap;
    }

    static void _deserializeProperty(const YAML::Node& in, char* data, const PropertyMeta& meta)
    {
      char* propData = data + meta.offset;

      switch (meta.ref)
      {
      case TypeRef::Object:
      {
        ObjectMeta obj = ApplicationDomain::get().findObject(meta.info.id);
        for (auto& prop : obj.properties)
        {
          if (in[prop.info.debugName])
          {
            YAML::Node propIn = in[prop.info.debugName];
            _deserializeProperty(propIn, propData, prop);
          }
        }

        break;
      }
      case TypeRef::Component:
      {
        break;
      }
      case TypeRef::Int32: *(int*)propData = in.as<int>(); break;
      case TypeRef::Int64: *(int64_t*)propData = in.as<int64_t>(); break;
      case TypeRef::UInt32: *(uint32_t*)propData = in.as<uint32_t>(); break;
      case TypeRef::UInt64: *(uint64_t*)propData = in.as<uint64_t>(); break;
      case TypeRef::Float: *(float*)propData = in.as<float>(); break;
      case TypeRef::Double: *(double*)propData = in.as<double>(); break;
      case TypeRef::String: *(std::string*)propData = in.as<std::string>(); break;
      }
    }

    static void _deserializeObject(const YAML::Node& in, char* data, const ObjectMeta& meta)
    {
      for (auto& prop : meta.properties)
      {
        if (in[prop.info.debugName])
        {
          YAML::Node propIn = in[prop.info.debugName];
          _deserializeProperty(propIn, data, prop);
        }
      }
    }

    static void _deserializeEntity(const YAML::Node& in, Shared<Scene> scene)
    {
      // Load ID & Name
      UUID id = in["ID"].as<uint64_t>();
      std::string name = in["Name"].as<std::string>();
      Entity ent = scene->getRegistry().createEntity(name, id);

      // Load Active & Parent
      ent.setActive(in["Active"].as<bool>());
      ent.setParentID(in["Parent"].as<uint64_t>());

      // Load Transform
      Transform& _transform = ent.getTransformRef();
      ObjectMeta _transMeta = ApplicationDomain::get().findObject(Type<Transform>().id());
      _deserializeObject(in[_transMeta.info.debugName], (char*)&_transform, _transMeta);

      // Load Children
      auto children = in["Children"];
      for (auto child : children)
      {
        ent.addChild(child.as<uint64_t>());
      }

      auto comps = in["Components"];
      if (!comps) return;

      for (auto comp : comps)
      {
        ObjectMeta meta = ApplicationDomain::get().findComponent(Stringf::hash(comp.first.as<std::string>()));
        char* data = (char*)ent.addComponent(meta.info.id);
        if (!data) continue;

        YAML::Node compIn = comp.second;
        for (auto& prop : meta.properties)
        {
          if (compIn[prop.info.debugName])
          {
            YAML::Node propIn = compIn[prop.info.debugName];
            _deserializeProperty(propIn, data, prop);
          }
        }
      }
    }
  }

  bool SceneSerializer::save(Shared<Scene> scene, const Path& dst)
  {
    if (!scene || !scene->getPath().isFile()) return false;

    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "Scene" << YAML::Value << "Scene Tag Placeholder";
    out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

    for (Entity ent : SceneView<>(&scene->getRegistry()))
    {
      Utils::_serializeEntity(out, ent);
    }

    out << YAML::EndSeq;
    out << YAML::EndMap;

    dst.write(out.c_str());

    return true;
  }

  bool SceneSerializer::load(Shared<Scene> scene, const Path& src)
  {
    if (!scene || !scene->getPath().isFile() || !scene->getPath().exists()) return false;

    YAML::Node in = YAML::Load(scene->getPath().readToString());
    if (!in["Scene"]) return false;

    auto entities = in["Entities"];
    if (!entities) return false;

    for (auto ent : entities)
    {
      YAML::Node entIn = (YAML::Node)ent;
      Utils::_deserializeEntity(entIn, scene);
    }

    return true;
  }

  Shared<Scene> SceneSerializer::copy(Shared<Scene> scene)
  {
    return Shared<Scene>();
  }
}