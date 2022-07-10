#version 460 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aInstancePos;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	gl_Position = projection * model * vec4(aPos + aInstancePos, 1.0f, 0.0f);
}