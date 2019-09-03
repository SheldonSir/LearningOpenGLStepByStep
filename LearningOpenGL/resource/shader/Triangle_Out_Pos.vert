#version 330 core

layout (location = 0) in vec3 m_InPos;

out vec4 m_V2FPos;

void main()
{
	gl_Position = vec4(m_InPos, 1.0f);
	m_V2FPos = gl_Position;
}