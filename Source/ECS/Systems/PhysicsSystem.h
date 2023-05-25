#pragma once
#include "Core/System.h"

class PhysicsSystem : public ecs::System
{
public:
    void update(float dt);
};
