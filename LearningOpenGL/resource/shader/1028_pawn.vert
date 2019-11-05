#version 330 core
layout (location = 0) in vec3 m_Pos;
layout (location = 1) in vec3 m_Normal;

out vec3 m_V2fFragPos;
out vec3 m_V2fNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;			 

void main()
{
	m_V2fFragPos = vec3(model * vec4(m_Pos, 1.0f));
	m_V2fNormal = mat3(transpose(inverse(model))) *m_Normal;

	gl_Position = projection * view * model * vec4(m_Pos, 1.0f);
}