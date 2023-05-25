#pragma once
#include <cassert>
#include <memory>
#include <unordered_map>

#include "System.h"
#include "Ecs.h"

namespace ecs
{

class SystemManager
{
public:
    template <typename T>
    std::shared_ptr<T> registerSystem()
    {
        const char *typeName = typeid(T).name();

        assert(systemMap.find(typeName) == systemMap.end() && "Registering system more than once.");

        auto system = std::make_shared<T>();
        systemMap.insert({typeName, system});
        return system;
    }

    template <typename T>
    void setSignature(Signature signature)
    {
        const char *typeName = typeid(T).name();

        assert(systemMap.find(typeName) != systemMap.end() && "System used before registered.");

        // 设置System的签名，该签名描述了该System包含了哪些Component
        signatureMap.insert({typeName, signature});
    }

    void entityDestroyed(Entity entity)
    {
        for(auto const &pair : systemMap) {
            auto const &system = pair.second;

            system->entities.erase(entity);
        }
    }

    void entitySignatureChanged(Entity entity, Signature entitySignature)
    {
        for(auto const &pair : systemMap) {
            auto const &type            = pair.first;
            auto const &system          = pair.second;
            auto const &systemSignature = signatureMap[type];

            // 如果Entity包含了System所需的所有Component
            if((entitySignature & systemSignature) == systemSignature) {
                system->entities.insert(entity);
            }
            // 否则删除该Entity（说明此时System需要的某些Component没有被该Entity包含）
            // 此时System无法处理该Entity
            else {
                system->entities.erase(entity);
            }
        }
    }

private:
    // 包含所有的签名
    std::unordered_map<const char *, Signature> signatureMap{};

    // 包含所有的System
    std::unordered_map<const char *, std::shared_ptr<System>> systemMap{};
};
} // namespace ecs