#version 330

layout(location = 0)in vec3 attributePos;
layout(location = 1)in vec3 attributeNormal;
layout(location = 2)in vec2 attributeTexCoords;

out vec3 Normal;
out vec3 FragPos;
out vec3 LightPos;
out vec2 TexCoords;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;
uniform vec3 lightPos;

void main() {
    //gl_ModelViewProjectMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    //gl_Position = vec4(attributePos, 1.0);
    gl_Position =  projMat * viewMat * modelMat * vec4(attributePos, 1.0);
    FragPos = vec3(modelMat * vec4(attributePos, 1.0));
    //Normal = vec3(modelMat * vec4(attributeNormal, 1.0));
    Normal = mat3(transpose(inverse(modelMat))) * attributeNormal;
    LightPos = lightPos; 
    TexCoords = attributeTexCoords;
}

