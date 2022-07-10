#include "debugOpenGL.h"

std::string DebugOpenGL::m_str;
std::vector<GLuint> DebugOpenGL::m_msgIDsToIgnore{ 131169, 131185, 131218, 131204 };

bool DebugOpenGL::init()
{
	GLint flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		ns_Util::Logger::LOG_INFO("OpenGL debug context successfully initialized.\n");
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(DebugOpenGL::openGL_debugCB, nullptr);		// 2nd arg is user parameters

		// for filtering
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		return true;
	}
	ns_Util::Logger::LOG_ERROR("OpenGL debug context initialization error.\n");
	return false;
}

void DebugOpenGL::errorTypeToString(GLenum type)
{
	switch (type)
	{
		case GL_DEBUG_TYPE_ERROR:
			m_str += "Type     : Error\n";
			break;

		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			m_str += "Type     : Deprecated Behaviour\n";
			break;

		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			m_str += "Type     : Undefined Behaviour\n";
			break;

		case GL_DEBUG_TYPE_PORTABILITY:
			m_str += "Type     : Portability\n";
			break;

		case GL_DEBUG_TYPE_PERFORMANCE:
			m_str += "Type     : Performance\n";
			break;

		case GL_DEBUG_TYPE_MARKER:
			m_str += "Type     : Marker\n";
			break;
		
		case GL_DEBUG_TYPE_PUSH_GROUP:
			m_str += "Type     : Push Group\n";
			break;

		case GL_DEBUG_TYPE_POP_GROUP:
			m_str += "Type     : Pop Group\n";
			break;

		case GL_DEBUG_TYPE_OTHER:
			m_str += "Type     : Other\n";
			break;

		default:
			break;
	}
}

void DebugOpenGL::errorSourceToString(GLenum src)
{
	switch (src)
	{
		case GL_DEBUG_SOURCE_API:
			m_str += "Source   : API\n";
			break;

		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			m_str += "Source   : Window System\n";
			break;

		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			m_str += "Source   : Shader Compiler\n";
			break;

		case GL_DEBUG_SOURCE_THIRD_PARTY:
			m_str += "Source   : Third Party\n";
			break;

		case GL_DEBUG_SOURCE_APPLICATION:
			m_str += "Source   : Application\n";
			break;

		case GL_DEBUG_SOURCE_OTHER:
			m_str += "Source   : Other\n";
			break;

		default:
			break;
	}
}

void DebugOpenGL::errorSeverityToString(GLenum severity)
{
	switch (severity)
	{
		case GL_DEBUG_SEVERITY_HIGH:
			m_str += "Severity : High\n";
			break;

		case GL_DEBUG_SEVERITY_MEDIUM:
			m_str += "Severity : Medium\n";
			break;

		case GL_DEBUG_SEVERITY_LOW:
			m_str += "Severity : Low\n";
			break;

		case GL_DEBUG_SEVERITY_NOTIFICATION:
			m_str += "Severity : Notification\n";
			break;

		default:
			break;
	}
}

void APIENTRY DebugOpenGL::openGL_debugCB(GLenum src, GLenum type, GLuint id, GLenum severity, GLsizei len, const char* msg, const void* userParams)
{
	(void)userParams;
	(void)len;
	if (m_msgIDsToIgnore.end() != std::find(m_msgIDsToIgnore.begin(), m_msgIDsToIgnore.end(), id))
	{
		return;
	}
	using ns_Util::Logger;

	Logger::LOG_ERROR("-----------------------------\n");
	Logger::LOG_ERROR("OpenGL Debug Msg (", id, ") : ", msg, '\n');

	errorTypeToString(type);
	errorSeverityToString(severity);
	errorSourceToString(src);
	Logger::LOG_ERROR(m_str, "\n-----------------------------\n");
}