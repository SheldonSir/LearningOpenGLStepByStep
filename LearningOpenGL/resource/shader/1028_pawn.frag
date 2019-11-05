#version 330 core

out vec4 m_FragColor;

in vec3 m_V2fFragPos;
in vec3 m_V2fNormal;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 pawnColor;

void main()
{
	// ambient
	float ambientStrength = 0.1f;
	vec3 ambient = lightColor * ambientStrength;

	// diffuse
	vec3 norm = normalize(m_V2fNormal);
	vec3 lightDir = normalize(lightPos - m_V2fFragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = lightColor * diff;

	// specular
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPos - m_V2fFragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = lightColor * spec * specularStrength;

	vec3 result = (ambient + diffuse + specular) * pawnColor;
	m_FragColor = vec4(result, 1.0f);
}