#version 330 core

in vec4 m_V2FPos;
out vec4 m_OutColor;

void main()
{
	m_OutColor = m_V2FPos;
}