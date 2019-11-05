#version 330 core
layout (location = 0) in vec3 m_Pos;
layout (location = 1) in vec2 m_Tex;

out vec2 m_V2FTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(m_Pos, 1.0f);
	m_V2FTex = m_Tex;
}