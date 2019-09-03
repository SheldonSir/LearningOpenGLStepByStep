#version 330 core
layout (location = 0) in vec3 m_Pos;
layout (location = 1) in vec3 m_Color;
layout (location = 2) in vec2 m_Tex;

out vec3 m_V2FColor;
out vec2 m_V2FTex;

void main()
{
	gl_Position = vec4(m_Pos, 1.0f);
	m_V2FColor = m_Color;
	m_V2FTex = m_Tex;
}