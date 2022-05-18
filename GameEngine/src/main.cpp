#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "triangle.h"
#include "rectangle.h"

// opengl screen
// -1,1        1,1
//	  __________
//   |			|
//   |			|
//   |			|
//	 |__________|
// -1,-1	   1,-1

void fb_size_cb(GLFWwindow *window, int w, int h)
{
	(void)window;
	glViewport(0, 0, w, h);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window.\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, fb_size_cb);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init GLAD.\n";
		return -1;
	}

	Triangle t;
	t.init();

	Rectangle r;
	r.init(true);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//t.draw();
		r.draw(true);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}