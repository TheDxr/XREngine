#version 330

layout(location = 0)in vec3 attributePos;

out vec3 FragPos;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main(void)
{
    gl_Position =  projMat * viewMat * modelMat * vec4(attributePos, 1.0);
    FragPos = vec3(modelMat * vec4(attributePos, 1.0));
}
