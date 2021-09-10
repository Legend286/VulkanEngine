#version 450

vec2 positions[3] = vec2[](
	vec2(0.0f, -0.5f),
	vec2(0.5f, 0.5f),
	vec2(-0.5f, 0.5f)
);

vec3 colours[3] = vec3[](
	vec3(1.0f, 0.0f,0.0f),
	vec3(0.0f, 1.0f, 0.0f),
	vec3(0.0f, 0.0f, 1.0f)	
);

layout (location = 1) out vec3 vertColour;

void main()
{
	vertColour = colours[gl_VertexIndex];
	gl_Position = vec4(positions[gl_VertexIndex], 0.0f, 1.0f);
}