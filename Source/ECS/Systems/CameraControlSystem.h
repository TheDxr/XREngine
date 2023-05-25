#pragma once

#include "Core/Event.h"
#include "Core/System.h"


namespace ecs
{

class CameraControlSystem : public System
{
public:
    void init();

    void update(float dt);

private:
   // std::bitset<8> mButtons;

    void inputListener(Event &event);
};
} // namespace ecs