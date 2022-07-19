#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Input/Ikeyboard.h"
#include "Input/Imouse.h"
#include <iostream>

#define GLM_FORCE_SILENT_WARNINGS       // to silent warnings
#include <glm/glm.hpp>

extern const GLint FORWARD;
extern const GLint BACKWARD;
extern const GLint LEFT;
extern const GLint RIGHT;

extern const GLfloat kYAW;
extern const GLfloat kPITCH;
extern const GLfloat kSPEED;
extern const GLfloat kSENSTIVITY;

extern const GLfloat kPITCH_MIN;
extern const GLfloat kPITCH_MAX;
extern const GLfloat kZOOM_MIN;
extern const GLfloat kZOOM_MAX;

class Camera
{
public:
	Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = kYAW, GLfloat pitch = kPITCH);

	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw = kYAW, GLfloat pitch = kPITCH);

	inline GLfloat yaw() const { return m_yaw; }
	inline GLfloat pitch() const { return m_pitch; }
	inline GLfloat roll() const { return m_roll; }

	inline GLfloat speed() const { return m_speed; }
	inline GLfloat mouseSenstivity() const { return m_senstivity; }
	inline GLfloat zoomFactor() const { return m_zoom; }

	inline GLdouble velocity() const { return m_velocity; }

	inline GLfloat near() const { return m_near; }
	inline GLfloat far() const { return m_far; }

	const glm::vec3& position() const { return m_position; }
	const glm::vec3& front() const { return m_front; }
	const glm::vec3& up() const { return m_up; }
	const glm::vec3& right() const { return m_right; }

	const glm::vec3& worldUp() const { return m_worldUp; }

	bool constrainedPitch() const { return m_bConstraintPitch; }
	
	inline void setYaw(GLfloat val) { m_yaw = val; m_bStateChanged = true; }
	inline void setPitch(GLfloat val) { m_pitch = val; m_bStateChanged = true; }
	inline void setRoll(GLfloat val) { m_roll = val; }

	inline void setSpeed(GLfloat val) { m_speed = val; }
	inline void setMouseSenstivity(GLfloat val) { m_senstivity = val; }
	inline void setZoomFactor(GLfloat val) { m_zoom = val; }

	inline void setNear(GLfloat val) { m_near = val; }
	inline void setFar(GLfloat val) { m_far = val; }

	inline void setPosition(glm::vec3 val) { m_position = val; }

	inline void setConstrainedPitch(bool val) { m_bConstraintPitch = val; }

	glm::mat4 viewMatrix() const;
	void update(GLdouble elapsedTimeInMs);

	void onKeyInput(const KeyButton &keybutton);
	void onCursorMove(GLdouble posX, GLdouble posY, GLdouble offsetX, GLdouble offsetY);
	void onScroll(GLdouble offsetX, GLdouble offsetY);
	void onMouseButton(const MouseButton &mousebutton);

	void print(const std::string& prefix = {}) const;
private:
	void recalculateCameraAttributes();

private:
	// Euler's angle
	GLfloat			m_yaw{};	// horizontal circle [left/right]
	GLfloat			m_pitch{};	// vertical circle [up/down]
	GLfloat			m_roll{};

	GLfloat			m_speed{};
	GLfloat			m_senstivity{};
	GLfloat			m_zoom{};

	GLfloat			m_near{};
	GLfloat			m_far{};

	GLdouble		m_velocity{};

	glm::vec3		m_position{};
	glm::vec3		m_front{};
	glm::vec3		m_up{};
	glm::vec3		m_right{};

	glm::vec3		m_worldUp{};

	bool			m_bConstraintPitch{ true };

	bool			m_bStateChanged{ false };
};