#include "Scene.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/stringbuffer.h>

#include "rapidjson/writer.h"
#include "Mesh.h"


void Scene::Load(const std::filesystem::path &Path)
{
    std::ifstream ifs(Path);
    rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document json;
    json.ParseStream(isw);

    if(json.HasMember("Version")) {
        //        if(Version::String != json["Version"].get<std::string>()) {
        //            throw std::exception("Invalid version");
        //        }
    }

    //    if(json.HasMember("Textures")) {
    //        const auto &JsonTextures = json["Textures"];
    //        for(auto iter = JsonTextures.Begin(); iter != JsonTextures.End(); ++iter) {
    //           // Asset::TextureImportOptions Options = {};
    //           // Options.Path                        = Process::ExecutableDirectory / iter.key();
    //
    //            if(auto &Value = iter.Value(); Value.contains("Options")) {
    //                auto &JsonOptions = Value["Options"];
    //                JsonGetIfExists<bool>(JsonOptions, "sRGB", Options.sRGB);
    //                JsonGetIfExists<bool>(JsonOptions, "GenerateMips", Options.GenerateMips);
    //            }
    //
    //            AssetManager->LoadTexture(Options);
    //        }
    //    }

    if(json.HasMember("Meshes")) {
        const auto &jsonMeshes = json["Meshes"];

        for(auto iter = jsonMeshes.MemberBegin(); iter != jsonMeshes.MemberEnd(); ++iter) {
            std::cout << iter->name.GetString() << std::endl;
            //            Asset::MeshImportOptions Options = {};
            //            Options.Path                     = Process::ExecutableDirectory / iter.key();
            //
            //            auto &Value = iter.value();
            //            if(Value.contains("Options")) {
            //                auto &JsonOptions = Value["Options"];
            //                JsonGetIfExists<bool>(JsonOptions, "GenerateMeshlets", Options.GenerateMeshlets);
            //            }
            //
          //  Models.emplace_back(iter->name.GetString());
        }
    }

    //    if(json.HasMember("Camera")) {
    //        if(auto iter = json.find("Camera"); iter != json.end()) {
    //            Reflection::ForEachAttributeIn<CameraComponent>([&](auto &&Attribute) {
    //                const auto &Value = iter.value();
    //
    //                const char *Name = Attribute.GetName();
    //                if(Value.contains(Name)) {
    //                    Attribute.Set(*Camera, Value[Name].template get<decltype(Attribute.GetType())>());
    //                }
    //            });
    //        }
    //    }

    //    if(json.HasMember("World")) {
    //        World->Clear(false);
    //
    //        const auto &JsonWorld = json["World"];
    //        for(const auto &JsonEntity : JsonWorld) {
    //            Actor Actor = World->CreateActor();
    //            ComponentDeserializer<CoreComponent>(JsonEntity, &Actor);
    //            ComponentDeserializer<LightComponent>(JsonEntity, &Actor);
    //            ComponentDeserializer<SkyLightComponent>(JsonEntity, &Actor);
    //            ComponentDeserializer<StaticMeshComponent>(JsonEntity, &Actor);
    //            if(Actor.HasComponent<SkyLightComponent>()) {
    //                auto &SkyLight        = Actor.GetComponent<SkyLightComponent>();
    //                SkyLight.Handle.Type  = Asset::AssetType::Texture;
    //                SkyLight.Handle.State = false;
    //                SkyLight.Handle.Id    = SkyLight.HandleId;
    //            }
    //            if(Actor.HasComponent<StaticMeshComponent>()) {
    //                auto &StaticMesh        = Actor.GetComponent<StaticMeshComponent>();
    //                StaticMesh.Handle.Type  = Asset::AssetType::Mesh;
    //                StaticMesh.Handle.State = false;
    //                StaticMesh.Handle.Id    = StaticMesh.HandleId;
    //            }
    //       }
    //}
}
void Scene::Render(ShaderProgram &shaderProgram) {
//    for(auto &Model : Models) {
//        Model.Render(shaderProgram);
//    }
}


//            rapidjson::StringBuffer buffer;
//            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
//
//            iter.Accept(writer);
//            // Output {"project":"rapidjson","stars":11}
//            std::cout << buffer.GetString() << std::endl;