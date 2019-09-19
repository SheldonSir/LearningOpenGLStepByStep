#version 330 core
layout (location = 0) in vec3 m_Pos;
layout (location = 1) in vec2 m_Tex;

out vec2 m_V2FTex;

uniform mat4 m_Transform;
void main()
{
	gl_Position = m_Transform * vec4(m_Pos, 1.0f);
	m_V2FTex = m_Tex;
}