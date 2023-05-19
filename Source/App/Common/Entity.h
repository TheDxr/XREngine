#pragma once
#include <glm/glm.hpp>

#include "Components/Transform.h"
#include "OpenGL/Shader.h"


class Entity
{
public:
    Entity() = default;
    ~Entity() = default;
    explicit Entity(int id);
    void SetTransform(const Transform& transform);
    void SetPosition(const glm::vec3& pos);

    [[nodiscard]] int GetId() const;
    [[nodiscard]] Transform GetTransform() const;
    [[nodiscard]] glm::vec3 GetPosition() const;
    [[nodiscard]] glm::mat4 GetModelMat() const;
    void SetId(int id);
    virtual void Render(ShaderProgram& shader);

protected:
    Transform mTransform;
    int mId{};
};
