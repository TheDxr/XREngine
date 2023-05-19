#include "Entity.h"
#include <iostream>
#include <memory>
#include "Model/Model.h"
#include "Shader.h"

// auto pBaseModel = std::make_shared<Model>("Assets/base.obj");

Entity::Entity(int id) { mId = id; }
int Entity::GetId() const { return mId; }
void Entity::SetId(int id) { mId = id; }
void Entity::Render(ShaderProgram &shader)
{
    // TODO: Render the model
    static Model baseModel("../../Assets/base.obj");
    baseModel.Render(shader);
}
void Entity::SetTransform(const Transform &transform) { mTransform = transform; }
Transform Entity::GetTransform() const { return mTransform; }
glm::mat4 Entity::GetModelMat() const
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, mTransform.Position);
    model = glm::scale(model, mTransform.Scale);
    model = glm::rotate(model, glm::radians(mTransform.Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(mTransform.Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(mTransform.Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    return model;
}
void Entity::SetPosition(const glm::vec3 &pos) { mTransform.Position = pos; }
glm::vec3 Entity::GetPosition() const { return mTransform.Position; }
