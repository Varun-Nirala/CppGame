#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Display/displayWindow.h"
#include "Renderer/shaderProgram.h"

#include "Common/constants.h"


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
	DisplayWindow& window = DisplayWindow::getInstance();
	window.loop();
	/*std::vector<std::pair<std::string, SHADER_TYPE>> shaders;
	shaders.push_back(std::make_pair(R"(.\resources\Shaders\point.vert)", SHADER_TYPE::VERT));
	shaders.push_back(std::make_pair(R"(.\resources\Shaders\point.frag)", SHADER_TYPE::FRAG));
	
	shaders[0] = std::make_pair(R"(.\resources\Shaders\pointWithMVP.vert)", SHADER_TYPE::VERT);
	shaders[1] = std::make_pair(R"(.\resources\Shaders\pointWithMVP.frag)", SHADER_TYPE::FRAG);
	*/
	return 0;
}