#pragma once
#include <array>
#include <cassert>
#include <queue>

#include "Ecs.h"

namespace ecs
{
class EntityManager
{
public:
    EntityManager()
    {
        // 用所有有效的Entity进行初始化
        for(Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
            availableEntities.push(entity);
        }
    }

    Entity createEntity()
    {
        assert(livingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

        // 从队列首部拿出一个ID
        Entity id = availableEntities.front();
        availableEntities.pop();
        ++livingEntityCount;
        return id;
    }

    void destroyEntity(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        // 重置signature
        signatures[entity].reset();

        // 把销毁的Entity的Id从新放回队列的尾部
        availableEntities.push(entity);
        --livingEntityCount;
    }

    void setSignature(Entity entity, Signature signature)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        signatures[entity] = signature;
    }

    Signature getSignature(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        return signatures[entity];
    }

private:
    // 所有未使用的ID
    std::queue<Entity> availableEntities{};

    // 用于管理Entity和对应的Signature
    std::array<Signature, MAX_ENTITIES> signatures{};

    // 当前可用的EntityId的数量
    uint32_t livingEntityCount{};
};
} // namespace ecs