#include "PhysicsSystem.h"
#include "Components/Gravity.h"
#include "Components/RigidBody.h"
#include "Components/Transform.h"
#include "ECS.h"

void PhysicsSystem::update(float dt) {
    for (auto const &entity: entities) {
        auto &rigidBody = ECS::command.getComponent<RigidBody>(entity);
        auto &transform = ECS::command.getComponent<Transform>(entity);
        auto const &gravity = ECS::command.getComponent<Gravity>(entity);

        transform.position += rigidBody.velocity * dt;
        rigidBody.velocity += gravity.force * dt;
    }
}