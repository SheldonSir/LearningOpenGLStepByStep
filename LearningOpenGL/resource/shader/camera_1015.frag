#version 330 core
in vec2 m_V2FTex;

out vec4 m_OutColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	m_OutColor = mix(texture(texture1, m_V2FTex), texture(texture2, m_V2FTex), 0.2);
}