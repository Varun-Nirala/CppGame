#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shaderProgram.h"
#include "engine.h"

#include "Graphics/point.h"
#include "Graphics/points.h"

// opengl screen
// -1,1        1,1
//	  __________
//   |			|
//   |			|
//   |			|
//	 |__________|
// -1,-1	   1,-1

// GLSL extensions
// .vert -> vertex shader
// .tesc -> Tessellation control shader
// .tese -> Tessellation evaluation shader
// .geom -> Geometry shader
// .frag -> Fragment shader
// .comp -> Compute shader

int main()
{
	Engine e;
	int major = 4;
	int minor = 6;

	e.init("Hello", 800, 600, major, minor);

	ShaderProgram pointShader;
	GLuint pointShaderID = pointShader.createShader();
	pointShader.attachShader(R"(.\resources\Shaders\point.vert)", SHADER_TYPE::VERT, pointShaderID);
	pointShader.attachShader(R"(.\resources\Shaders\point.frag)", SHADER_TYPE::FRAG, pointShaderID);
	pointShader.linkShader(pointShaderID);

	//Point p(pointShaderID, true,  glm::vec2{ 0.5f, 0.5f });
	Points p(pointShaderID, true);

	float inc = 0.001f;
	glm::vec3 start(0.0f);
	for (size_t i = 0; i < 300; ++i)
	{
		p.addPoint(start);
		start.y += inc;

	}

	p.init();

	e.addDrawable(&p);

	e.startLoop();
	return 0;
}