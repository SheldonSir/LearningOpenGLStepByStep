#version 330 core
in vec2 m_V2FTex;

out vec4 m_OutColor;

uniform sampler2D m_Sampler1;
uniform sampler2D m_Sampler2;

void main()
{
	m_OutColor = mix(texture(m_Sampler1, m_V2FTex), texture(m_Sampler2, m_V2FTex), 0.2);
}