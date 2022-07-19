#include "camera.h"
#include "Input/Ikeyboard.h"
#include "Input/Imouse.h"
#include "Common/logger.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Common/constants.h"

#include "utility.h"

const GLint FORWARD			= KEY_W;
const GLint BACKWARD		= KEY_S;
const GLint LEFT			= KEY_A;
const GLint RIGHT			= KEY_D;

const GLfloat kYAW			= -90.0f;
const GLfloat kPITCH		= 0.0f;
const GLfloat kSPEED		= 2.5f;
const GLfloat kSENSTIVITY	= 0.1f;

const GLfloat kPITCH_MIN	= -89.0f;
const GLfloat kPITCH_MAX	= 89.0f;
const GLfloat kZOOM_MIN		= 1.0f;
const GLfloat kZOOM_MAX		= 45.0f;

Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up, GLfloat yaw, GLfloat pitch)
    : m_position{ pos }
    , m_front(front)
    , m_worldUp{ up }
    , m_yaw{ yaw }
    , m_pitch{ pitch }
    , m_speed { kSPEED }
    , m_senstivity { kSENSTIVITY }
    , m_zoom { kZOOM_MAX }
    , m_near(kORTHOGRAPHIC_NEAR)
    , m_far(kORTHOGRAPHIC_FAR)
{
    recalculateCameraAttributes();
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch)
    : m_position{ posX, posY, posZ }
    , m_worldUp{ upX, upY, upZ }
    , m_yaw{ yaw }
    , m_pitch{ pitch }
    , m_speed{ kSPEED }
    , m_senstivity{ kSENSTIVITY }
    , m_zoom{ kZOOM_MAX }
    , m_near(kORTHOGRAPHIC_NEAR)
    , m_far(kORTHOGRAPHIC_FAR)
{
    recalculateCameraAttributes();
}

glm::mat4 Camera::viewMatrix() const
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::update(GLdouble elapsedTimeInMs)
{
    m_velocity = m_speed * (elapsedTimeInMs / 1000.0f);
    if (m_bStateChanged)
    {
        recalculateCameraAttributes();
        m_bStateChanged = false;
    }
}

void Camera::onKeyInput(const KeyButton& keybutton)
{
    if (keybutton.keycode == FORWARD)
    {
        m_position += m_front * (GLfloat)m_velocity;
    }
    else if (keybutton.keycode == BACKWARD)
    {
        m_position -= m_front * (GLfloat)m_velocity;
    }
    else if (keybutton.keycode == LEFT)
    {
        m_position -= m_right * (GLfloat)m_velocity;
    }
    else if (keybutton.keycode == RIGHT)
    {
        m_position += m_right * (GLfloat)m_velocity;
    }
}

void Camera::onCursorMove(GLdouble posX, GLdouble posY, GLdouble offsetX, GLdouble offsetY)
{
    (void)posX;
    (void)posY;
    offsetX *= m_senstivity;
    offsetY *= m_senstivity;

    m_yaw += (GLfloat)offsetX;
    m_pitch += (GLfloat)offsetY;

    if (constrainedPitch())
    {
        glm::clamp(m_pitch, kPITCH_MIN, kPITCH_MAX);
    }

    m_bStateChanged = true;
}

void Camera::onScroll(GLdouble offsetX, GLdouble offsetY)
{
    (void)offsetX;
    m_zoom -= static_cast<GLfloat>(offsetY);
    glm::clamp(m_zoom, kZOOM_MIN, kZOOM_MAX);
}

void Camera::onMouseButton(const MouseButton& mousebutton)
{
    (void)mousebutton;
}

void Camera::print(const std::string& prefix) const
{
    using ns_Util::Logger;
    Logger::LOG_MSG(prefix, "Camera\n");
    Logger::LOG_MSG(prefix, "  Yaw, Pitch, Roll  : ", m_yaw, ", ", m_pitch, ", ", m_roll, '\n');
    Logger::LOG_MSG(prefix, "  Movement Speed    : ", m_speed, '\n');
    Logger::LOG_MSG(prefix, "  Mouse Senstivity  : ", m_senstivity, '\n');
    Logger::LOG_MSG(prefix, "  Zoom Factor       : ", m_zoom, '\n');
    Logger::LOG_MSG(prefix, "  Near and Far      : ", m_near, ", ", m_far, '\n');
    Logger::LOG_MSG(prefix, "  Current Velocity  : ", m_velocity, '\n');
    Logger::LOG_MSG(prefix, "  Position          : ", Utility::glmVecAsString(m_position), '\n');
    Logger::LOG_MSG(prefix, "  Front             : ", Utility::glmVecAsString(m_front), '\n');
    Logger::LOG_MSG(prefix, "  Right             : ", Utility::glmVecAsString(m_right), '\n');
    Logger::LOG_MSG(prefix, "  Up                : ", Utility::glmVecAsString(m_up), '\n');
    Logger::LOG_MSG(prefix, "  World Up          : ", Utility::glmVecAsString(m_worldUp), '\n');
    Logger::LOG_MSG(prefix, "  Pitch Constrained : ", m_bConstraintPitch ? "True" : "False", '\n');
    Logger::LOG_MSG('\n');
}

void Camera::recalculateCameraAttributes()
{
    GLfloat radYaw = glm::radians(m_yaw);
    GLfloat radPitch = glm::radians(m_pitch);

    // calculation of new front based on changes in yaw and picth
    m_front.x = cos(radYaw) * cos(radPitch);
    m_front.y = sin(radPitch);
    m_front.z = sin(radYaw) * cos(radPitch);

    m_front = glm::normalize(m_front);

    // calculation of right and up using new fromt
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}