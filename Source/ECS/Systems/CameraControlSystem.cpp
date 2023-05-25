#include "CameraControlSystem.h"

#include "Components/Transform.h"
#include "Core/Command.h"


namespace ecs
{
void CameraControlSystem::init()
{
//    command.addEventListener(
//        METHOD_LISTENER(Events::Window::INPUT, CameraControlSystem::InputListener));
}

void CameraControlSystem::update(float dt)
{
//    for(auto &entity : mEntities) {
//        auto &transform = command.getComponent<Transform>(entity);
//
//        float speed = 20.0f;
//
//
//        if(mButtons.test(static_cast<std::size_t>(InputButtons::W))) {
//            transform.position.z -= (dt * speed);
//        }
//
//        else if(mButtons.test(static_cast<std::size_t>(InputButtons::S))) {
//            transform.position.z += (dt * speed);
//        }
//
//
//        if(mButtons.test(static_cast<std::size_t>(InputButtons::Q))) {
//            transform.position.y += (dt * speed);
//        }
//
//        else if(mButtons.test(static_cast<std::size_t>(InputButtons::E))) {
//            transform.position.y -= (dt * speed);
//        }
//
//
//        if(mButtons.test(static_cast<std::size_t>(InputButtons::A))) {
//            transform.position.x -= (dt * speed);
//        }
//
//        else if(mButtons.test(static_cast<std::size_t>(InputButtons::D))) {
//            transform.position.x += (dt * speed);
//        }
//    }
}

void CameraControlSystem::inputListener(Event &event)
{
   // mButtons = event.getParam<std::bitset<8>>(Events::Window::Input::INPUT);
}

} // namespace ecs