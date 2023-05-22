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
    std::shared_ptr<T> RegisterSystem()
    {
        const char *typeName = typeid(T).name();

        assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once.");

        auto system = std::make_shared<T>();
        mSystems.insert({typeName, system});
        return system;
    }

    template <typename T>
    void SetSignature(Signature signature)
    {
        const char *typeName = typeid(T).name();

        assert(mSystems.find(typeName) != mSystems.end() && "System used before registered.");

        // 设置System的签名，该签名描述了该System包含了哪些Component
        mSignatures.insert({typeName, signature});
    }

    void EntityDestroyed(Entity entity)
    {
        for(auto const &pair : mSystems) {
            auto const &system = pair.second;

            system->Entities.erase(entity);
        }
    }

    void EntitySignatureChanged(Entity entity, Signature entitySignature)
    {
        for(auto const &pair : mSystems) {
            auto const &type            = pair.first;
            auto const &system          = pair.second;
            auto const &systemSignature = mSignatures[type];

            // 如果Entity包含了System所需的所有Component
            if((entitySignature & systemSignature) == systemSignature) {
                system->Entities.insert(entity);
            }
            // 否则删除该Entity（说明此时System需要的某些Component没有被该Entity包含）
            // 此时System无法处理该Entity
            else {
                system->Entities.erase(entity);
            }
        }
    }

private:
    // 包含所有的签名
    std::unordered_map<const char *, Signature> mSignatures{};

    // 包含所有的System
    std::unordered_map<const char *, std::shared_ptr<System>> mSystems{};
};
} // namespace ecs