#include "ECS.h"

#include "Components/Camera.h"
#include "Components/Gravity.h"
#include "Components/RigidBody.h"
#include "Components/Light/DirectionalLight.h"
#include "Components/Light/PointLight.h"
#include "Components/Light/SpotLight.h"
#include "Components/Transform.h"


using namespace ecs;


void ECS::registerAllComponents()
{
    command.registerComponent<Transform>()
        .registerComponent<Gravity>()
        .registerComponent<RigidBody>()
        .registerComponent<Camera>()
        .registerComponent<DirectionalLight>()
        .registerComponent<PointLight>()
        .registerComponent<SpotLight>();
}
// namespace ecs