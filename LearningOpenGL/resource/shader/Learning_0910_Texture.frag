#version 330 core
in vec3 m_V2FColor;
in vec2 m_V2FTex;

uniform sampler2D wall;
uniform sampler2D awesomeface;

out vec4 m_OutColor;

void main()
{
	m_OutColor = mix(texture(wall, m_V2FTex), texture(awesomeface, m_V2FTex), 0.2f);
}
