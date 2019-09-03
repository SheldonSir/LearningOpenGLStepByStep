#version 330 core
in vec3 m_V2FColor;
in vec2 m_V2FTex;

out vec4 m_OutColor;

uniform sampler2D m_Sampler;

void main()
{
	m_OutColor = texture(m_Sampler, m_V2FTex);
	//m_OutColor = vec4(m_V2FColor, 1.0f);
}