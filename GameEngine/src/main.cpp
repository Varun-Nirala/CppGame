#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shaderProgram.h"
#include "engine.h"

#include "resourceManager.h"

#include "Common/constants.h"

#include "Graphics/point.h"
#include "Graphics/points.h"
#include "Graphics/line.h"
#include "Graphics/lines.h"
#include "Graphics/triangle.h"
#include "Graphics/triangleStrip.h"
#include "Graphics/rectangle.h"
#include "Graphics/circle.h"
#include "Graphics/sphere.h"

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

void drawPoint(Engine& e, ResourceManager& rm);
void drawPoints(Engine& e, ResourceManager& rm);
void drawLine(Engine& e, ResourceManager& rm);
void drawLines(Engine& e, ResourceManager& rm);
void drawTriangle(Engine& e, ResourceManager& rm);
void drawTriangleStrip(Engine& e, ResourceManager& rm);
void drawRectangle(Engine& e, ResourceManager& rm);
void drawCircle(Engine& e, ResourceManager& rm, bool bFilled);
void drawSphere(Engine& e, ResourceManager& rm);

int main()
{
	ResourceManager rm;

	Engine e;
	int major = OPENGL_MAJOR_VERSION;
	int minor = OPENGL_MINOR_VERSION;

	e.init(TITLE, WIDTH, HEIGHT, major, minor);
	e.enableDepthTest();

	glEnable(GL_LINE_SMOOTH);

	std::vector<std::pair<std::string, SHADER_TYPE>> shaders;
	shaders.push_back(std::make_pair(R"(.\resources\Shaders\point.vert)", SHADER_TYPE::VERT));
	shaders.push_back(std::make_pair(R"(.\resources\Shaders\point.frag)", SHADER_TYPE::FRAG));
	rm.addShader("Point_Shader", shaders);

	shaders[0] = std::make_pair(R"(.\resources\Shaders\pointWithMVP.vert)", SHADER_TYPE::VERT);
	shaders[1] = std::make_pair(R"(.\resources\Shaders\pointWithMVP.frag)", SHADER_TYPE::FRAG);
	rm.addShader("PointWithMVP_Shader", shaders);

	//drawPoint(e, rm);
	//drawPoints(e, rm);
	//drawLine(e, rm);
	//drawLines(e, rm);
	//drawTriangle(e, rm);
	//drawTriangleStrip(e, rm);
	//drawRectangle(e, rm);

	//drawCircle(e, rm, false);		// draw wireframe circle

	//drawCircle(e, rm, true);		// draw filled circle
	drawSphere(e, rm);

	e.startLoop();
	return 0;
}

void drawPoint(Engine& e, ResourceManager& rm)
{
	Point *point = new Point(rm.shader("PointWithMVP_Shader"), true, glm::vec2{ 0.0f, 0.0f });
	point->init();
	e.addDrawable(point);
}

void drawPoints(Engine& e, ResourceManager& rm)
{
	Points *points = new Points(rm.shader("PointWithMVP_Shader"), false);
	float inc = 0.01f;
	glm::vec2 start(0.0f, 0.0f);

	for (size_t i = 0; i < 30; ++i)
	{
		points->addPoint(start);
		start.x += inc;
	}
	points->init();
	e.addDrawable(points);
}

void drawLine(Engine& e, ResourceManager& rm)
{
	Line *line = new Line(rm.shader("PointWithMVP_Shader"), false, glm::vec2(0.0f, 0.0f), glm::vec2(0.5f, 0.5f));
	line->init();
	e.addDrawable(line);
}

void drawLines(Engine& e, ResourceManager& rm)
{
	Lines *lines = new Lines(rm.shader("PointWithMVP_Shader"), false);
	lines->addine(glm::vec2(0.0f, 1.0f), glm::vec2(-1.0f, -1.0f));
	lines->addine(glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, -1.0f));

	lines->setMakeLoop(true);
	lines->init();

	e.addDrawable(lines);
}

void drawTriangle(Engine& e, ResourceManager& rm)
{
	Triangle* tri = new Triangle(rm.shader("PointWithMVP_Shader"), false);
	tri->setTriangle({ 
		glm::vec2{0.0f, -1.0f},
		glm::vec2{-1.0f, -1.0f},
		glm::vec2{1.0f, -1.0f}
		});

	tri->init();
	tri->setRotationAngle(15);
	e.addDrawable(tri);
}

void drawTriangleStrip(Engine& e, ResourceManager& rm)
{
	TriangleStrip* triStrip = new TriangleStrip(rm.shader("PointWithMVP_Shader"), false);
	triStrip->addTriangleVertex(glm::vec2{ -1.0f, 1.0f });					// top left
	triStrip->addTriangleVertex(glm::vec2{ -1.0f, -1.0f });					// left
	triStrip->addTriangleVertex(glm::vec2{ 1.0f, 1.0f });					// top right
	triStrip->addTriangleVertex(glm::vec2{ 1.0f, -1.0f });					// right
	triStrip->setDrawInWireFrameMode(true);
	triStrip->init();
	e.addDrawable(triStrip);
}

void drawRectangle(Engine& e, ResourceManager& rm)
{
	Rectangle* rect = new Rectangle(rm.shader("PointWithMVP_Shader"), false);

	rect->setRectangle(-0.9f, 0.9f, 0.8f, 0.8f);
	rect->init();
	rect->setRotationAngle(45);
	e.addDrawable(rect);
}

void drawCircle(Engine& e, ResourceManager& rm, bool bFilled)
{
	Circle *cir = new Circle(rm.shader("PointWithMVP_Shader"), false, 1.0f, glm::vec3(0.0f, 0.0f, kDEFAULT_Z));
	cir->setDrawInWireFrameMode(!bFilled);
	cir->init();
	e.addDrawable(cir);
}

void drawSphere(Engine& e, ResourceManager& rm)
{
	Sphere* sphere = new Sphere(rm.shader("PointWithMVP_Shader"), false, 1.0f, glm::vec3(0.0f, 0.0f, kDEFAULT_Z), 20, 20);
	sphere->setDrawInWireFrameMode(true);
	sphere->init();
	e.addDrawable(sphere);
}