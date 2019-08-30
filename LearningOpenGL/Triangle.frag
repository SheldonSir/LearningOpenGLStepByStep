#version 330 core
out vec4 m_FragColor;
in vec3 m_Color2Frag;

void main()
{
	m_FragColor = vec4(m_Color2Frag, 1.0f);
}