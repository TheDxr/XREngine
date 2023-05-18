#version 330

out vec4 FragColor;
in vec3 FragPos;

uniform vec3 objRawColor;

void main()
{
	FragColor = vec4(objRawColor, 1.0);
}

