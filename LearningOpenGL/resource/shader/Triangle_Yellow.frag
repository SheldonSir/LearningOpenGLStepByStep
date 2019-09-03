#version 330 core
out vec4 m_FragColor;

uniform vec4 m_UniformColor;
void main()
{
	m_FragColor = m_UniformColor;
}