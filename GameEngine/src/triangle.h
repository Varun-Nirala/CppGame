#pragma once

#include <glad/glad.h>
#include <iostream>
#include <array>

class Triangle
{
public:
	~Triangle();
	Triangle() = default;

	bool init();
	void draw();

private:
	bool initVertexShader();
	bool initFragmentShader();
	bool compileAndLinkShaderProgram();
	bool initVertexArrayObject();
	bool initVertexBufferObject();

private:
	unsigned int			m_VBO{};			// vertex buffer object
	unsigned int			m_VAO{};			// vertex array object [array of VBO]
	unsigned int			m_vsID{};
	unsigned int			m_fsID{};
	unsigned int			m_shaderProgID{};
	std::array<float, 9>	m_vertices;
};

Triangle::~Triangle()
{
	glDeleteShader(m_vsID);
	glDeleteShader(m_fsID);
	m_vsID = m_fsID = 0;

	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteProgram(m_shaderProgID);
}

bool Triangle::init()
{
	m_vertices = { -0.5f, -0.5f, 0.0f,
					0.5f, -0.5f, 0.0f,
					0.0f,  0.5f, 0.0f };

	bool ret{ true };

	ret &= initVertexShader();
	ret &= initFragmentShader();
	ret &= compileAndLinkShaderProgram();
	ret &= initVertexArrayObject();

	return ret;
}

void Triangle::draw()
{
	glUseProgram(m_shaderProgID);
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

bool Triangle::initVertexShader()
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

bool Triangle::initFragmentShader()
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

bool Triangle::compileAndLinkShaderProgram()
{
	m_shaderProgID = glCreateProgram();
	glAttachShader(m_shaderProgID, m_vsID);
	glAttachShader(m_shaderProgID, m_fsID);
	glLinkProgram(m_shaderProgID);

	int success = 0;
	glGetProgramiv(m_shaderProgID, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512]{};

		glGetProgramInfoLog(m_shaderProgID, sizeof(infoLog), NULL, infoLog);
		std::cout << "Error:SHADER:PROGRAM:LINKING_FAILED\n" << infoLog << std::endl;
		return false;
	}

	return true;
}

bool Triangle::initVertexArrayObject()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	initVertexBufferObject();
	glBindVertexArray(0);
	return true;
}

bool Triangle::initVertexBufferObject()
{
	glGenBuffers(1, &m_VBO);

	//bind the newly created buffer to the GL_ARRAY_BUFFER target
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	//is a function specifically targeted to copy user-defined data into the currently bound buffer
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(m_vertices[0]), m_vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
}