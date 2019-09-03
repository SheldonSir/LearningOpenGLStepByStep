//file extensions: glsl, frag, vert, geom, comp, tesse, tessc
#version 330 core
layout (location = 0) in vec3 m_Pos;
layout (location = 1) in vec3 m_Color;
out vec3 m_Color2Frag;

void main()
{
	gl_Position = vec4(m_Pos, 1.0f);
	m_Color2Frag = m_Color;
}