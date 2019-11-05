#version 330 core
layout (location = 0) in vec3 m_Pos;
layout (location = 1) in vec3 m_Normal;

out vec3 m_V2fNormal;
out vec3 m_V2fFragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(m_Pos, 1.0f);
	m_V2fNormal = m_Normal;
	m_V2fFragPos = vec3( model * vec4(m_Pos, 1.0f));
}