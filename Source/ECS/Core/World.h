#pragma once

#include <functional>
#include <iostream>
#include "Containers/SparseSet.h"
#include "Containers/DenseMap.h"
#include "Ecs.h"

namespace ecs {
    class Pool
    {
    public:
        std::vector<void *> instances;
        std::vector<void *> cachedInstances;

        using CreateInstanceFunc  = void *(*)();
        using DestroyInstanceFunc = void (*)(void *);

        CreateInstanceFunc createFunc;
        DestroyInstanceFunc destroyFunc;

        Pool(CreateInstanceFunc create, DestroyInstanceFunc destroy)
                : createFunc(create), destroyFunc(destroy)
        {}

        void *create()
        {
            if(!cachedInstances.empty()) {
                instances.push_back(cachedInstances.back());
                cachedInstances.pop_back();
                return instances.back();
            }
            else {
                instances.push_back(createFunc());
            }
            return instances.back();
        }

        void destroy(void *instance)
        {
            auto it = std::find(instances.begin(), instances.end(), instance);
            if(it != instances.end()) {
                cachedInstances.push_back(*it);
                std::swap(*it, instances.back());
                instances.pop_back();
            }
            else {
                assert(false && "Destroying instance that doesn't belong to this pool");
            }
        }
        ~Pool()
        {
            // for(auto instance : Instances) {
            //     Destroy(instance);
            // }
        }
    };

class IComponentData {
public:
    virtual ~IComponentData() = default;
    virtual void entityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentData {
public:
    ComponentArray(){
        componentData.resize(MAX_ENTITIES);
    }
    void insertData(Entity entity, T component) {
        assert(!entities.contains(entity) && "Component added to same entity more than once.");
        entities.insert(entity);
        componentData[entity] = std::forward<T>(component);
    }

    void removeData(Entity entity) {
        assert(entities.contains(entity) && "Removing non-existent component.");
    }

    T &getData(Entity entity) {
        assert(entities.contains(entity) && "Retrieving non-existent component.");
        return componentData[entity];
    }

    void entityDestroyed(Entity entity) override {
        entities.remove(entity);
    }
    size_t size() const {
        return componentData.size() + entities.size();
    }
private:
    SparseSet<Entity, 128> entities;
    std::vector<T> componentData;
};

template<typename T>
class ComponentLazy : public IComponentData {
public:
    void insertData(Entity entity, T&& component) {
        assert(!entities.contains(entity) && "Component added to same entity more than once.");
        entities.insert(entity);
        componentData.insert(entity, std::forward<T>(component));
    }
    void removeData(Entity entity) {
        assert(entities.contains(entity) && "Removing non-existent component.");
        componentData.remove(entity);
    }
    T &getData(Entity entity) {
        assert(entities.contains(entity) && "Retrieving non-existent component.");
        return componentData[entity];
    }
    void entityDestroyed(Entity entity) override {
        entities.remove(entity);
    }
    [[nodiscard]] size_t size() const {
        return componentData.size() + entities.size();
    }
private:
    SparseSet<Entity, 128> entities;
    DenseMap<Entity, T> componentData{MAX_ENTITIES};
};

template<typename T>
class ComponentPool : public IComponentData {
public:
    ComponentPool(){
        components.resize(MAX_ENTITIES);
        // mSize = 0;
    }
    void insertData(Entity entity, T&& component) {
        assert(!entities.contains(entity) && "Component added to same entity more than once.");
        // TODO: 这里需要一个Pool
    }

    void removeData(Entity entity) {
        assert(entities.contains(entity) && "Removing non-existent component.");

    }

    T &getData(Entity entity) {
        assert(entities.contains(entity) && "Retrieving non-existent component.");
        assert(components[entity] != nullptr && "Retrieving non-existent component.");
        return *components[entity];
    }

    void entityDestroyed(Entity entity) override {
        entities.remove(entity);
    }
    size_t size() const {
        return 0;
    }
private:
    SparseSet<Entity, 128> entities;
    Pool pool;
    std::vector<T *> components;
};

using ComponentDataMap = std::unordered_map<const char *, std::shared_ptr<IComponentData>>;
using ComponentIdMap = std::unordered_map<const char *, ComponentId>;

} // namespace ecs