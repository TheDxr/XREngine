#version 450

layout (location = 0) in vec2 aPos;

layout(push_constant) uniform PushConstants {
    vec2 offset;
} pushConstants;

void main(){
    gl_Position = vec4(aPos + pushConstants.offset, 0.0, 1.0);
}