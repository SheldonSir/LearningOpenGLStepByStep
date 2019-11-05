#version 330 core
in vec3 m_V2fNormal;
in vec3 m_V2fFragPos;

out vec4 m_OutColor;

uniform vec3 LightPos;
uniform vec3 LightColor;
uniform vec3 PawnColor;

void main()
{
	vec3 norm = normalize(m_V2fNormal);
	vec3 lightDir = normalize(LightPos - m_V2fFragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * LightColor;
	
	float ambientStrength = 0.5f;
	vec3 ambient = LightColor * ambientStrength;

	vec3 result = (diffuse + ambient) * PawnColor;
	m_OutColor = vec4(result, 1.0f);
}