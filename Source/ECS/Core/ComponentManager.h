#pragma once
#include <cassert>
#include <memory>
#include <unordered_map>
#include <variant>

#include "Ecs.h"
#include "World.h"


namespace ecs
{
enum ComponentContainerType
{
    Array,
    Lazy,
    Pools
};
class ComponentManager
{
public:
    template <typename T>
    void registerComponent(ComponentContainerType containerType)
    {
        // 获取指向名字的指针
        const char *typeName = typeid(T).name();
        assert(
            componentIdMap.find(typeName) == componentIdMap.end() &&
            "Registering component type more than once.");
        // 把新的ComponentType加入映射
        componentIdMap.insert({typeName, nextComponentId});
        if(containerType == ComponentContainerType::Array) {
            componentDataMap.insert({typeName, std::make_shared<ComponentArray<T>>()});
        }
        if(containerType == ComponentContainerType::Lazy) {
            componentDataMap.insert({typeName, std::make_shared<ComponentLazy<T>>()});
        }
        // 递增表示可用的ComponentType的变量
        ++nextComponentId;
    }

    template <typename T>
    auto getComponentId()
    {
        const char *typeName = typeid(T).name();

        assert(
            componentIdMap.find(typeName) != componentIdMap.end() &&
            "Component not registered before use.");

        // 根据T获得该类型的Component对应的ID
        return componentIdMap[typeName];
    }

    template <typename T>
    void addComponent(Entity entity, T &&component)
    {
        const char *typeName = typeid(T).name();
        assert(
            componentIdMap.find(typeName) != componentIdMap.end() &&
            "Component not registered before use.");

        if(auto ptr = std::dynamic_pointer_cast<ComponentLazy<T>>(componentDataMap[typeName]);ptr != nullptr)
        {
            ptr->insertData(entity, std::forward<T>(component));
            return;
        }

        if(auto ptr = std::dynamic_pointer_cast<ComponentArray<T>>(componentDataMap[typeName]);ptr != nullptr)
        {
            ptr->insertData(entity, std::forward<T>(component));
            return;
        }

//        auto& data = *componentDataMap[typeName];
//        if(typeid(data) == typeid(ComponentArray<T>))
//            return std::dynamic_pointer_cast<ComponentArray<T>>(componentDataMap[typeName])
//                ->InsertData(entity, std::forward<T>(component));
//        if(typeid(data) == typeid(ComponentLazy<T>))
//            return std::dynamic_pointer_cast<ComponentLazy<T>>(componentDataMap[typeName])
//                ->InsertData(entity, std::forward<T>(component));
        throw std::runtime_error("Component not registered before use.");
    }

    template <typename T>
    void removeComponent(Entity entity)
    {
        const char *typeName = typeid(T).name();
        assert(
            componentIdMap.find(typeName) != componentIdMap.end() &&
            "Component not registered before use.");
        if(auto ptr = std::dynamic_pointer_cast<ComponentLazy<T>>(componentDataMap[typeName]);ptr != nullptr)
        {
            ptr->removeData(entity);
            return;
        }
        if(auto ptr = std::dynamic_pointer_cast<ComponentArray<T>>(componentDataMap[typeName]);ptr != nullptr)
        {
            ptr->removeData(entity);
            return;
        }
        throw std::runtime_error("Component not registered before use.");
    }

    template <typename T>
    T &getComponent(Entity entity)
    {
        const char *typeName = typeid(T).name();
        assert(
            componentIdMap.find(typeName) != componentIdMap.end() &&
            "Component not registered before use.");
        if(auto ptr = std::dynamic_pointer_cast<ComponentLazy<T>>(componentDataMap[typeName]);ptr != nullptr)
        {
            return ptr->getData(entity);
        }
        if(auto ptr = std::dynamic_pointer_cast<ComponentArray<T>>(componentDataMap[typeName]);ptr != nullptr)
        {
            return ptr->getData(entity);
        }
        throw std::runtime_error("Component not registered before use.");
    }

    void entityDestroyed(Entity entity)
    {
        // 将每个ComponentArray中该entity对应的Component删掉
        for(auto const &pair : componentDataMap) {
            auto const &component = pair.second;
            component->entityDestroyed(entity);
        }
    }

private:
    // 通过ComponentType查找ComponentId
    ComponentIdMap componentIdMap{};
    // 指向下一个将要注册的ComponentId
    ComponentId nextComponentId{};
    // using ComponentPools = std::unordered_map<ComponentId, std::shared_ptr<Pool>>;
    ComponentDataMap componentDataMap{};

//    template <typename T>
//    std::variant<std::shared_ptr<ComponentLazy<T>>, std::shared_ptr<ComponentArray<T>>>
//        GetComponentData()
//    {
//        const char *typeName = typeid(T).name();
//        assert(
//            componentIdMap.find(typeName) != componentIdMap.end() &&
//            "Component not registered before use.");
//        if(typeid(componentDataMap[typeName]) == typeid(ComponentArray<T>))
//            return std::dynamic_pointer_cast<ComponentArray<T>>(componentDataMap[typeName]);
//        if(typeid(componentDataMap[typeName]) == typeid(ComponentLazy<T>))
//            return std::dynamic_pointer_cast<ComponentLazy<T>>(componentDataMap[typeName]);
//    }
};

} // namespace ecs
