#version 330 core
layout (location = 0) in vec3 m_Pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(m_Pos, 1.0f);
}