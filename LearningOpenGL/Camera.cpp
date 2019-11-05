#include "Camera.h"
#if 0
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw , float pitch)
	: m_Front(glm::vec3(0.0f, 0.0f, -1.0f))
	, m_MouseSensitivity(SENSITIVITY)
	, m_Zoom(ZOOM)
	, m_Position(position)
	, m_WorldUp(up)
	, m_Yaw(yaw)
	, m_Pitch(pitch)
{
	updateCameraVectors();
}

Camera::Camera(float posx, float posy, float posz, float upx, float upy, float upz, float yaw, float pitch)
	: m_Front(glm::vec3(.0f, .0f, -1.0f))
	, m_MovementSpeed(SPEED)
	, m_MouseSensitivity(SENSITIVITY)
	, m_Zoom(ZOOM)
	, m_Position(posx, posy, posz)
	, m_WorldUp(upx, upy, upz)
	, m_Yaw(yaw)
	, m_Pitch(pitch)
{
	updateCameraVectors();
}

void Camera::ProcessKeyboard(eCameraMovement direction, float deltaTime)
{
	float velocity = m_MovementSpeed * deltaTime;
	switch (direction)
	{
		case eForward:
		{
			m_Position += m_Front * velocity;
			break;
		}
		case eBackward:
		{
			m_Position -= m_Front * velocity;
			break;
		}
		case eLeft:
		{
			m_Position -= m_Right * velocity;
			break;
		}
		case eRight:
		{
			m_Position += m_Right * velocity;
			break;
		}
	}
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= m_MouseSensitivity;
	yoffset *= m_MouseSensitivity;

	m_Yaw += xoffset;
	m_Pitch += yoffset;

	if (constrainPitch)
	{
		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;
	}

	updateCameraVectors();
}


void Camera::ProcessMouseScroll(float yoffset)
{
	if (m_Zoom >= 1.0f && m_Zoom <= ZOOM)
		m_Zoom -= yoffset;
	m_Zoom <= 1.0f ? m_Zoom = 1.0f : m_Zoom;
	m_Zoom >= ZOOM ? m_Zoom = ZOOM : m_Zoom;
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	front.y = sin(glm::radians(m_Pitch));
	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

#endif