#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <string>

#define GLM_FORCE_SILENT_WARNINGS       // to silent warnings
#include <glm/glm.hpp>

enum class SHADER_TYPE
{
	VERT,
	FRAG,
	TESC,
	TESE,
	GEOM,
	COMP
};

class ShaderProgram
{
public:
	using ID_Type = GLuint;

	static ID_Type createShader();
	static 	void destroyShader(ID_Type &programID);

	static bool attachShader(const std::string& filepath, SHADER_TYPE type, ID_Type& programID);
	static bool linkShader(ID_Type& programID);

	static void activate(ID_Type programID) { glUseProgram(programID); }
	static void deactivate() { glUseProgram(0); }

	static void setUnifrom_b(const ID_Type programID, const std::string& name, bool value);
	static void setUniform_i(const ID_Type programID, const std::string& name, GLint value);
	static void setUniform_ui(const ID_Type programID, const std::string& name, GLuint value);
	static void setUniform_f(const ID_Type programID, const std::string& name, GLfloat value);
	
	static void setUniform_iv(const ID_Type programID, const std::string& name, glm::ivec2 vec);
	static void setUniform_iv(const ID_Type programID, const std::string& name, glm::ivec3 vec);
	static void setUniform_iv(const ID_Type programID, const std::string& name, glm::ivec4 vec);

	static void setUniform_uiv(const ID_Type programID, const std::string& name, glm::uvec2 vec);
	static void setUniform_uiv(const ID_Type programID, const std::string& name, glm::uvec3 vec);
	static void setUniform_uiv(const ID_Type programID, const std::string& name, glm::uvec4 vec);

	static void setUniform_fv(const ID_Type programID, const std::string& name, glm::vec2 vec);
	static void setUniform_fv(const ID_Type programID, const std::string& name, glm::vec3 vec);
	static void setUniform_fv(const ID_Type programID, const std::string& name, glm::vec4 vec);

	static void setUniform_1iv(const ID_Type programID, const std::string& name, GLsizei count, GLint* ptr);
	static void setUniform_2iv(const ID_Type programID, const std::string& name, GLsizei count, GLint* ptr);
	static void setUniform_3iv(const ID_Type programID, const std::string& name, GLsizei count, GLint* ptr);
	static void setUniform_4iv(const ID_Type programID, const std::string& name, GLsizei count, GLint* ptr);

	static void setUniform_1uiv(const ID_Type programID, const std::string& name, GLsizei count, GLuint* ptr);
	static void setUniform_2uiv(const ID_Type programID, const std::string& name, GLsizei count, GLuint* ptr);
	static void setUniform_3uiv(const ID_Type programID, const std::string& name, GLsizei count, GLuint* ptr);
	static void setUniform_4uiv(const ID_Type programID, const std::string& name, GLsizei count, GLuint* ptr);

	static void setUniform_1fv(const ID_Type programID, const std::string& name, GLsizei count, GLfloat* ptr);
	static void setUniform_2fv(const ID_Type programID, const std::string& name, GLsizei count, GLfloat* ptr);
	static void setUniform_3fv(const ID_Type programID, const std::string& name, GLsizei count, GLfloat* ptr);
	static void setUniform_4fv(const ID_Type programID, const std::string& name, GLsizei count, GLfloat* ptr);

	static void setUniform_fm(const ID_Type programID, const std::string& name, glm::mat2 mat, bool bIsTranspose = false);
	static void setUniform_fm(const ID_Type programID, const std::string& name, glm::mat3 mat, bool bIsTranspose = false);
	static void setUniform_fm(const ID_Type programID, const std::string& name, glm::mat4 mat, bool bIsTranspose = false);
	static void setUniform_fm(const ID_Type programID, const std::string& name, glm::mat2x3 mat, bool bIsTranspose = false);
	static void setUniform_fm(const ID_Type programID, const std::string& name, glm::mat3x2 mat, bool bIsTranspose = false);
	static void setUniform_fm(const ID_Type programID, const std::string& name, glm::mat2x4 mat, bool bIsTranspose = false);
	static void setUniform_fm(const ID_Type programID, const std::string& name, glm::mat4x2 mat, bool bIsTranspose = false);
	static void setUniform_fm(const ID_Type programID, const std::string& name, glm::mat3x4 mat, bool bIsTranspose = false);
	static void setUniform_fm(const ID_Type programID, const std::string& name, glm::mat4x3 mat, bool bIsTranspose = false);

private:
	static GLint getLocation(const ID_Type programID, const char* name);
};