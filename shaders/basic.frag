#version 450

layout (location = 0) out vec4 outColour;

layout (location = 1) in vec3 vertColour;

void main()
{
	outColour = vec4(vertColour, 1.0f);//vec4(1.0f, 1.0f, 0.0f, 1.0f);
}