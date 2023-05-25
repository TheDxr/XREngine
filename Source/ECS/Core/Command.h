#pragma once
#include "ComponentManager.h"
#include "EntityManager.h"
#include "EventManager.h"
#include "SystemManager.h"

namespace ecs
{
class Command
{
public:
    Command(){
        componentManager  = std::make_unique<ComponentManager>();
        entityManager     = std::make_unique<EntityManager>();
        systemManager     = std::make_unique<SystemManager>();
    }
    // Entity 相关方法
    Entity createEntity() { return entityManager->createEntity(); }

    void destroyEntity(Entity entity)
    {
        entityManager->destroyEntity(entity);
        componentManager->entityDestroyed(entity);
        systemManager->entityDestroyed(entity);
    }

    // Component 相关方法
    template <typename T>
    Command & registerComponent(ComponentContainerType containerType = ComponentContainerType::Lazy)
    {
        componentManager->registerComponent<T>(containerType);
        return *this;
    }

    template <typename... T>
    Command & spawn(T&& ... components)
    {
        Entity entity = createEntity();
        (addComponent(entity, components), ...);
        return *this;
    }

    template <typename T>
    Command & addComponent(Entity entity, T&& component)
    {
        componentManager->addComponent<T>(entity, std::forward<T>(component));

        auto signature = entityManager->getSignature(entity);
        signature.set(componentManager->getComponentId<T>(), true);
        entityManager->setSignature(entity, signature);

        systemManager->entitySignatureChanged(entity, signature);
        return *this;
    }

    template <typename T>
    Command & removeComponent(Entity entity)
    {
        componentManager->removeComponent<T>(entity);

        auto signature = entityManager->getSignature(entity);
        signature.set(componentManager->getComponentId<T>(), false);
        entityManager->setSignature(entity, signature);

        systemManager->entitySignatureChanged(entity, signature);
        return *this;
    }

    template <typename T>
    T &getComponent(Entity entity)
    {
        return componentManager->getComponent<T>(entity);
    }

    template <typename T>
    ComponentId getComponentId()
    {
        return componentManager->getComponentId<T>();
    }

    // System 相关方法
    template <typename T>
    std::shared_ptr<T> registerSystem()
    {
        return systemManager->registerSystem<T>();
    }

    template <typename T>
    void setSystemSignature(Signature signature)
    {
        systemManager->setSignature<T>(signature);
    }

    // Event methods
    void addEventListener(EventId eventId, std::function<void(Event&)> const& listener)
    {
        eventManager->addListener(eventId, listener);
    }

    void sendEvent(Event& event)
    {
        eventManager->sendEvent(event);
    }

    void sendEvent(EventId eventId)
    {
        eventManager->sendEvent(eventId);
    }

private:
    std::unique_ptr<ComponentManager> componentManager;
    std::unique_ptr<EntityManager> entityManager;
    std::unique_ptr<SystemManager> systemManager;
    std::unique_ptr<EventManager> eventManager;
};

} // namespace ecs