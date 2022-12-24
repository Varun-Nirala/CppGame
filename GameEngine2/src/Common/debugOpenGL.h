#pragma once

#include <vector>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "logger.h"

class DebugOpenGL
{
public:
	static bool init();

	static void errorTypeToString(GLenum);

	static void errorSourceToString(GLenum);

	static void errorSeverityToString(GLenum);

	static void APIENTRY openGL_debugCB(
		GLenum src,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei len,
		const char* msg,
		const void* userParams
	);

private:
	static std::string				m_str;
	static std::vector<GLuint>		m_msgIDsToIgnore;
};