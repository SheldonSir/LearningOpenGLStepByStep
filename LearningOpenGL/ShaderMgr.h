#pragma once
#include <glad/glad.h>
#include <iostream>
#include <vector>

class Shader
{
public:
	Shader(const char* vertexShader, const char* fragmentShader);
	~Shader();

	void UseProgram();
	
	template<class Type>
	void SetUniform(const GLchar* key, Type& value) const
	{
		std::cout << __LINE__ << " : Not implement!!!" << std::endl;
	}
	template<>
	void SetUniform(const GLchar* name, int& value) const
	{
		glUniform1i(glGetUniformLocation(m_ShaderId, name), value);
	}

	template<>
	void SetUniform(const GLchar* name, bool& value) const
	{
		glUniform1i(glGetUniformLocation(m_ShaderId, name), value);
	}

	template<>
	void SetUniform(const GLchar* name, float& value) const
	{
		glUniform1f(glGetUniformLocation(m_ShaderId, name), value);
	}

	template<class T>
	void SetUniform(const GLchar* name, std::vector<T>& value) const
	{

	}

	void SetUniform(const GLchar* name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(m_ShaderId, name), x, y, z, w);
	}


private:
	unsigned int m_ShaderId = 0;
};

