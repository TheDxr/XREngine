#pragma once
#include <set>

#include "Ecs.h"

namespace ecs
{

class System
{
public:
    // 包含所有满足component要求的的实体
    std::set<Entity> Entities;
};
}