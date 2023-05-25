#pragma once

#include "Core/Command.h"

class ECS
{
public:
    ECS() = delete;
    ~ECS() = delete;
    static inline ecs::Command command;
    static void registerAllComponents();
};

