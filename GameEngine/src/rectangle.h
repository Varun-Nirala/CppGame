#pragma once

#include <glad/glad.h>
#include <iostream>
#include <array>

class Rectangle
{
public:
	~Rectangle();
	Rectangle() = default;

	bool init(const bool bUseEBO);
	void draw(bool bInWireframeMode = false);

private:
	bool initVertexShader();
	bool initFragmentShader();
	bool compileAndLinkShaderProgram();
	bool initVertexArrayObject();
	bool initVertexBufferObject();

	bool initElementBufferObject();

private:
	unsigned int			m_VBO{};
	unsigned int			m_VAO{};
	unsigned int			m_EBO{};
	unsigned int			m_vsID{};
	unsigned int			m_fsID{};
	unsigned int			m_shaderProgram{};
	
	float					*m_vertices{};
	int						*m_indices{};

	GLsizei					m_verticesCount{};
	GLsizei					m_indicesCount{};

	bool					m_bUseEBO{false};
};

Rectangle::~Rectangle()
{
	glDeleteShader(m_vsID);
	glDeleteShader(m_fsID);
	m_vsID = m_fsID = 0;

	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteProgram(m_shaderProgram);

	delete[] m_vertices;
	delete[] m_indices;
	m_vertices = nullptr;
	m_indices = nullptr;

	m_verticesCount = m_indicesCount = 0;
}

bool Rectangle::init(const bool bUseEBO)
{
	m_bUseEBO = bUseEBO;

	bool ret{ true };

	if (m_bUseEBO)
	{
		m_verticesCount = 12;
		m_vertices = new float[m_verticesCount];

		float vertices[] = {
				0.5f,  0.5f, 0.0f,		// Top right
				0.5f, -0.5f, 0.0f,		// Bottom right
			   -0.5f, -0.5f, 0.0f,		// Bottom left
			   -0.5f,  0.5f, 0.0f		// Top left
		};

		std::memcpy(m_vertices, vertices, m_verticesCount * sizeof(float));

		m_indicesCount = 6;
		m_indices = new int[m_indicesCount];

		int indices[] = {
				0, 1, 3,	// 1st triangle
				1, 2, 3		// 2nd triangle
		};

		std::memcpy(m_indices, indices, m_indicesCount * sizeof(int));
	}
	else
	{
		m_verticesCount = 18;
		m_vertices = new float[m_verticesCount];

		float vertices[] = {
			// 1st Triangle
				0.5f,  0.5f, 0.0f,		// Top right
				0.5f, -0.5f, 0.0f,		// Bottom right
			   -0.5f,  0.5f, 0.0f,		// Top left
			// 2nd Triangle
				0.5f, -0.5f, 0.0f,		// Bottom right
			   -0.5f, -0.5f, 0.0f,		// Bottom left
			   -0.5f,  0.5f, 0.0f		// Top left
		};

		std::memcpy(m_vertices, vertices, m_verticesCount * sizeof(float));
	}

	ret &= initVertexShader();
	ret &= initFragmentShader();
	ret &= compileAndLinkShaderProgram();
	ret &= initVertexArrayObject();

	if (m_bUseEBO)
	{
		ret &= initElementBufferObject();
	}

	return ret;
}

void Rectangle::draw(bool bInWireframeMode)
{
	if (bInWireframeMode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glUseProgram(m_shaderProgram);
	glBindVertexArray(m_VAO);
	if (m_bUseEBO)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	glBindVertexArray(0);
}

bool Rectangle::initVertexShader()
{
	const char* vertexShaderSourceCode = "#version 460 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
		"}\n\0";

	m_vsID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vsID, 1, &vertexShaderSourceCode, NULL);
	glCompileShader(m_vsID);

	int success{};
	glGetShaderiv(m_vsID, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		char infoLog[512]{};

		glGetShaderInfoLog(m_vsID, sizeof(infoLog), NULL, infoLog);
		std::cout << "Error:SHADER:VERTEX:COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}
	return true;
}

bool Rectangle::initFragmentShader()
{
	const char* fragmentShaderSourceCode = "#version 460 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

	m_fsID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fsID, 1, &fragmentShaderSourceCode, NULL);
	glCompileShader(m_fsID);

	int success{};
	glGetShaderiv(m_fsID, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		char infoLog[512]{};

		glGetShaderInfoLog(m_fsID, sizeof(infoLog), NULL, infoLog);
		std::cout << "Error:SHADER:FRAGMENT:COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}
	return true;
}

bool Rectangle::compileAndLinkShaderProgram()
{
	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, m_vsID);
	glAttachShader(m_shaderProgram, m_fsID);
	glLinkProgram(m_shaderProgram);

	int success{};
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		char infoLog[512]{};

		glGetProgramInfoLog(m_shaderProgram, sizeof(infoLog), NULL, infoLog);
		std::cout << "Error:SHADER:PROGRAM:LINKING_FAILED\n" << infoLog << std::endl;
		return false;
	}
	return true;
}

bool Rectangle::initVertexArrayObject()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	initVertexBufferObject();
	glBindVertexArray(0);
	return true;
}

bool Rectangle::initVertexBufferObject()
{
	glGenBuffers(1, &m_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, m_verticesCount * sizeof(m_vertices[0]), m_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
}

bool Rectangle::initElementBufferObject()
{
	glGenBuffers(1, &m_EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesCount * sizeof(m_indices[0]), m_indices, GL_STATIC_DRAW);

	return true;
}