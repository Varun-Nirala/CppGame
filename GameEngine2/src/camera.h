#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Display/displayWindow.h"

#define IS_2D

class Camera
{
public:
	explicit Camera(glm::vec2 position = glm::vec2{0.0f, 0.0f})
	{
		m_position = position;
		adjustProjection();
	}

	const glm::vec2& getPosition() const
	{
		return m_position;
	}

	glm::vec2& getPosition()
	{
		return m_position;
	}

	void adjustProjection()
	{
		m_projectionMatrix = glm::mat4(1.0f);
#if defined(IS_2D)
		m_projectionMatrix = glm::ortho(0.0f, (GLfloat)DisplayWindow::getInstance().getWidth(), 0.0f, (GLfloat)DisplayWindow::getInstance().getHeight(), 0.0f, 100.0f);
#else
		m_projectionMatrix = glm::perspective(glm::radians(camera.zoomFactor()), DisplayWindow::getInstance().aspectRatio(), 0.0f, 100.0f);
#endif
	}

	glm::mat4 getViewMatrix()
	{
		glm::vec3 cameraFront{ 0.0f, 0.0f, -1.0f };
		glm::vec3 cameraUp{ 0.0f, 1.0f, 0.0f };
		m_viewMatrix = glm::mat4(1.0f);

		cameraFront.x += m_position.x;
		cameraFront.y += m_position.y;

		m_viewMatrix = glm::lookAt(glm::vec3{ m_position.x, m_position.y, 20.0f }, 
			cameraFront, cameraUp);

		return m_viewMatrix;
	}

	glm::mat4 getProjectionMatrix() const
	{
		return m_projectionMatrix;
	}

private:
	glm::mat4	m_projectionMatrix{};
	glm::mat4	m_viewMatrix{};
	glm::vec2	m_position{};
};