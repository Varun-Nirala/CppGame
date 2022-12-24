#include "shaderProgram.h"
#include "Common/logger.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cassert>

ShaderProgram::ID_Type ShaderProgram::createShader()
{
	return glCreateProgram();
}

void ShaderProgram::destroyShader(ID_Type &programID)
{
	if (programID)
	{
		glDeleteProgram(programID);
	}
	programID = 0;
}

bool ShaderProgram::attachShader(const std::string& filepath, SHADER_TYPE type, ID_Type& programID)
{
	std::ifstream srcFile(filepath);

	if (!srcFile)
	{
		ns_Util::Logger::LOG_ERROR("Failed to open file : ", filepath, '\n');
		assert(false);
		return false;
	}

	std::string srcCode;

	srcFile.seekg(0, std::ios::end);
	const size_t fileSize = srcFile.tellg();
	srcCode.reserve(fileSize);
	srcFile.seekg(0, std::ios::beg);
	srcCode.assign((std::istreambuf_iterator<char>(srcFile)), std::istreambuf_iterator<char>());

	ID_Type shaderID{};

	if (type == SHADER_TYPE::VERT)
	{
		shaderID = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (type == SHADER_TYPE::FRAG)
	{
		shaderID = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else if (type == SHADER_TYPE::TESC)
	{
		shaderID = glCreateShader(GL_TESS_CONTROL_SHADER);
	}
	else if (type == SHADER_TYPE::TESE)
	{
		shaderID = glCreateShader(GL_TESS_EVALUATION_SHADER);
	}
	else if (type == SHADER_TYPE::GEOM)
	{
		shaderID = glCreateShader(GL_GEOMETRY_SHADER);
	}
	else if (type == SHADER_TYPE::COMP)
	{
		shaderID = glCreateShader(GL_COMPUTE_SHADER);
	}

	const GLchar* src = srcCode.c_str();
	glShaderSource(shaderID, 1, &src, NULL);
	glCompileShader(shaderID);

	GLint retCode{};
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &retCode);

	if (!retCode)
	{
		char infoLog[512]{};
		glGetShaderInfoLog(shaderID, sizeof(infoLog), NULL, infoLog);

		ns_Util::Logger::LOG_ERROR("SHADER:COMPILATION_FAILED : ", filepath, " : ", infoLog, '\n');
		assert(false);
		return false;
	}

	glAttachShader(programID, shaderID);
	glDeleteShader(shaderID);

	return true;
}

bool ShaderProgram::linkShader(ID_Type& programID)
{
	glLinkProgram(programID);

	GLint retCode{};
	glGetProgramiv(programID, GL_LINK_STATUS, &retCode);

	if (!retCode)
	{
		char infoLog[512]{};
		glGetProgramInfoLog(programID, sizeof(infoLog), NULL, infoLog);

		ns_Util::Logger::LOG_ERROR("SHADER:LINKING_FAILED : ", infoLog, '\n');
		assert(false);
		return false;
	}
	return true;
}

void ShaderProgram::setUnifrom_b(const ID_Type programID, const std::string& name, bool value)
{
	glUniform1i(getLocation(programID, name.c_str()), (GLint)value);
}

void ShaderProgram::setUniform_i(const ID_Type programID, const std::string& name, GLint value)
{
	glUniform1i(getLocation(programID, name.c_str()), value);
}

void ShaderProgram::setUniform_ui(const ID_Type programID, const std::string& name, GLuint value)
{
	glUniform1ui(getLocation(programID, name.c_str()), value);
}

void ShaderProgram::setUniform_f(const ID_Type programID, const std::string& name, GLfloat value)
{
	glUniform1f(getLocation(programID, name.c_str()), value);
}

void ShaderProgram::setUniform_iv(const ID_Type programID, const std::string& name, glm::ivec2 vec)
{
	glUniform2iv(getLocation(programID, name.c_str()), 1, glm::value_ptr(vec));
}

void ShaderProgram::setUniform_iv(const ID_Type programID, const std::string& name, glm::ivec3 vec)
{
	glUniform3iv(getLocation(programID, name.c_str()), 1, glm::value_ptr(vec));
}

void ShaderProgram::setUniform_iv(const ID_Type programID, const std::string& name, glm::ivec4 vec)
{
	glUniform4iv(getLocation(programID, name.c_str()), 1, glm::value_ptr(vec));
}

void ShaderProgram::setUniform_uiv(const ID_Type programID, const std::string& name, glm::uvec2 vec)
{
	glUniform2uiv(getLocation(programID, name.c_str()), 1, glm::value_ptr(vec));
}

void ShaderProgram::setUniform_uiv(const ID_Type programID, const std::string& name, glm::uvec3 vec)
{
	glUniform3uiv(getLocation(programID, name.c_str()), 1, glm::value_ptr(vec));
}

void ShaderProgram::setUniform_uiv(const ID_Type programID, const std::string& name, glm::uvec4 vec)
{
	glUniform4uiv(getLocation(programID, name.c_str()), 1, glm::value_ptr(vec));
}

void ShaderProgram::setUniform_fv(const ID_Type programID, const std::string& name, glm::vec2 vec)
{
	glUniform2fv(getLocation(programID, name.c_str()), 1, glm::value_ptr(vec));
}

void ShaderProgram::setUniform_fv(const ID_Type programID, const std::string& name, glm::vec3 vec)
{
	glUniform3fv(getLocation(programID, name.c_str()), 1, glm::value_ptr(vec));
}

void ShaderProgram::setUniform_fv(const ID_Type programID, const std::string& name, glm::vec4 vec)
{
	glUniform4fv(getLocation(programID, name.c_str()), 1, glm::value_ptr(vec));
}

void ShaderProgram::setUniform_1iv(const ID_Type programID, const std::string& name, GLsizei count, GLint* ptr)
{
	glUniform1iv(getLocation(programID, name.c_str()), count, ptr);
}

void ShaderProgram::setUniform_2iv(const ID_Type programID, const std::string& name, GLsizei count, GLint* ptr)
{
	glUniform2iv(getLocation(programID, name.c_str()), count, ptr);
}

void ShaderProgram::setUniform_3iv(const ID_Type programID, const std::string& name, GLsizei count, GLint* ptr)
{
	glUniform3iv(getLocation(programID, name.c_str()), count, ptr);
}

void ShaderProgram::setUniform_4iv(const ID_Type programID, const std::string& name, GLsizei count, GLint* ptr)
{
	glUniform4iv(getLocation(programID, name.c_str()), count, ptr);
}

void ShaderProgram::setUniform_1uiv(const ID_Type programID, const std::string& name, GLsizei count, GLuint* ptr)
{
	glUniform1uiv(getLocation(programID, name.c_str()), count, ptr);
}

void ShaderProgram::setUniform_2uiv(const ID_Type programID, const std::string& name, GLsizei count, GLuint* ptr)
{
	glUniform2uiv(getLocation(programID, name.c_str()), count, ptr);
}

void ShaderProgram::setUniform_3uiv(const ID_Type programID, const std::string& name, GLsizei count, GLuint* ptr)
{
	glUniform3uiv(getLocation(programID, name.c_str()), count, ptr);
}

void ShaderProgram::setUniform_4uiv(const ID_Type programID, const std::string& name, GLsizei count, GLuint* ptr)
{
	glUniform4uiv(getLocation(programID, name.c_str()), count, ptr);
}

void ShaderProgram::setUniform_1fv(const ID_Type programID, const std::string& name, GLsizei count, GLfloat* ptr)
{
	glUniform1fv(getLocation(programID, name.c_str()), count, ptr);
}

void ShaderProgram::setUniform_2fv(const ID_Type programID, const std::string& name, GLsizei count, GLfloat* ptr)
{
	glUniform2fv(getLocation(programID, name.c_str()), count, ptr);
}

void ShaderProgram::setUniform_3fv(const ID_Type programID, const std::string& name, GLsizei count, GLfloat* ptr)
{
	glUniform3fv(getLocation(programID, name.c_str()), count, ptr);
}

void ShaderProgram::setUniform_4fv(const ID_Type programID, const std::string& name, GLsizei count, GLfloat* ptr)
{
	glUniform4fv(getLocation(programID, name.c_str()), count, ptr);
}

void ShaderProgram::setUniform_fm(const ID_Type programID, const std::string& name, glm::mat2 mat, bool bIsTranspose)
{
	glUniformMatrix2fv(getLocation(programID, name.c_str()), 1, bIsTranspose ? GL_TRUE : GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::setUniform_fm(const ID_Type programID, const std::string& name, glm::mat3 mat, bool bIsTranspose)
{
	glUniformMatrix3fv(getLocation(programID, name.c_str()), 1, bIsTranspose ? GL_TRUE : GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::setUniform_fm(const ID_Type programID, const std::string& name, glm::mat4 mat, bool bIsTranspose)
{
	glUniformMatrix4fv(getLocation(programID, name.c_str()), 1, bIsTranspose ? GL_TRUE : GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::setUniform_fm(const ID_Type programID, const std::string& name, glm::mat2x3 mat, bool bIsTranspose)
{
	glUniformMatrix2x3fv(getLocation(programID, name.c_str()), 1, bIsTranspose ? GL_TRUE : GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::setUniform_fm(const ID_Type programID, const std::string& name, glm::mat3x2 mat, bool bIsTranspose)
{
	glUniformMatrix3x2fv(getLocation(programID, name.c_str()), 1, bIsTranspose ? GL_TRUE : GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::setUniform_fm(const ID_Type programID, const std::string& name, glm::mat2x4 mat, bool bIsTranspose)
{
	glUniformMatrix2x4fv(getLocation(programID, name.c_str()), 1, bIsTranspose ? GL_TRUE : GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::setUniform_fm(const ID_Type programID, const std::string& name, glm::mat4x2 mat, bool bIsTranspose)
{
	glUniformMatrix4x2fv(getLocation(programID, name.c_str()), 1, bIsTranspose ? GL_TRUE : GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::setUniform_fm(const ID_Type programID, const std::string& name, glm::mat3x4 mat, bool bIsTranspose)
{
	glUniformMatrix3x4fv(getLocation(programID, name.c_str()), 1, bIsTranspose ? GL_TRUE : GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::setUniform_fm(const ID_Type programID, const std::string& name, glm::mat4x3 mat, bool bIsTranspose)
{
	glUniformMatrix4x3fv(getLocation(programID, name.c_str()), 1, bIsTranspose ? GL_TRUE : GL_FALSE, glm::value_ptr(mat));
}

GLint ShaderProgram::getLocation(const ID_Type programID, const char* name)
{
	GLint loc = glGetUniformLocation(programID, name);
	if (loc == -1)
	{
		ns_Util::Logger::LOG_ERROR("Uniform not found : ", name, '\n');
	}
	return loc;
}