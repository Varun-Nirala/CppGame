#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shaderProgram.h"
#include "engine.h"

#include "resourceManager.h"

#include "Graphics/point.h"
#include "Graphics/points.h"
#include "Graphics/line.h"
#include "Graphics/lines.h"

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

void drawPoint(Engine &e, ResourceManager& rm);
void drawPoints(Engine& e, ResourceManager& rm);
void drawLine(Engine& e, ResourceManager& rm);
void drawLines(Engine& e, ResourceManager& rm);

int main()
{
	ResourceManager rm;

	Engine e;
	int major = 4;
	int minor = 6;

	e.init("Hello", 800, 600, major, minor);

	std::vector<std::pair<std::string, SHADER_TYPE>> shaders;
	shaders.push_back(std::make_pair(R"(.\resources\Shaders\point.vert)", SHADER_TYPE::VERT));
	shaders.push_back(std::make_pair(R"(.\resources\Shaders\point.frag)", SHADER_TYPE::FRAG));
	rm.addShader("Point_Shader", shaders);

	drawPoint(e, rm);

	drawPoints(e, rm);

	drawLine(e, rm);
	
	drawLines(e, rm);

	e.startLoop();
	return 0;
}

void drawPoint(Engine& e, ResourceManager& rm)
{
	Point *point = new Point(rm.shader("Point_Shader"), true, glm::vec2{ -0.5f, -0.5f });
	point->init();
	e.addDrawable(point);
}

void drawPoints(Engine& e, ResourceManager& rm)
{
	Points *points = new Points(rm.shader("Point_Shader"), false);
	float inc = 0.001f;
	glm::vec3 start(0.0f);
	for (size_t i = 0; i < 300; ++i)
	{
		points->addPoint(start);
		start.y += inc;
	}
	points->init();
	e.addDrawable(points);
}

void drawLine(Engine& e, ResourceManager& rm)
{
	Line *line = new Line(rm.shader("Point_Shader"), false, glm::vec2(0.5f, 0.0f), glm::vec2(0.5f, 0.5f));
	line->init();
	e.addDrawable(line);
}

void drawLines(Engine& e, ResourceManager& rm)
{
	Lines *lines = new Lines(rm.shader("Point_Shader"), false);
	lines->addine(glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, -1.0f));
	lines->addine(glm::vec2(1.0f, -1.0f), glm::vec2(0.0f, 1.0f));

	lines->setMakeLoop(true);
	lines->init();

	e.addDrawable(lines);
}