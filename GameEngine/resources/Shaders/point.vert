#version 460 core
layout (location = 0) in vec3 aPoint;

void main()
{
	gl_Position = vec4(aPoint, 1.0f);
}