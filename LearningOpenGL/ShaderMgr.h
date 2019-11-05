#pragma once
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <Include/glm/glm/glm.hpp>
#include <Include/glm/glm/gtc/matrix_transform.hpp>
#include <Include/glm/glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader(const char* vertexShader, const char* fragmentShader);
	~Shader();

	void UseProgram();
	void Use();
	
	template<class Type>
	void SetUniform(const GLchar* key, const Type& value) const
	{
		std::cout << __LINE__ << " : Not implement!!!" << std::endl;
	}
	template<>
	void SetUniform(const GLchar* name, const int& value) const
	{
		glUniform1i(glGetUniformLocation(m_ShaderId, name), value);
	}

	template<>
	void SetUniform(const GLchar* name, const bool& value) const
	{
		glUniform1i(glGetUniformLocation(m_ShaderId, name), value);
	}

	template<>
	void SetUniform(const GLchar* name, const float& value) const
	{
		glUniform1f(glGetUniformLocation(m_ShaderId, name), value);
	}

	template<class T>
	void SetUniform(const GLchar* name, const std::vector<T>& value) const
	{

	}

	void SetUniform(const GLchar* name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(m_ShaderId, name), x, y, z, w);
	}

	void SetUniform(const GLchar* name, glm::mat4 matrix4x4f)
	{
		unsigned int location = glGetUniformLocation(m_ShaderId, name);
		//assert(target != 0);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix4x4f));
	}

	void SetUniform(const GLchar* name, glm::vec3 value)
	{
		unsigned int location = glGetUniformLocation(m_ShaderId, name);
		glUniform3fv(location, 1, &value[0]);
	}

	void SetUniform(const GLchar* name, float x, float y, float z)
	{
		unsigned int location = glGetUniformLocation(m_ShaderId, name);

		glUniform3f(location, x, y, z);
	}

public:
	unsigned int m_ShaderId = 0;
};

