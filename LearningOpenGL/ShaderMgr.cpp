#include "ShaderMgr.h"
#include <string>
#include <fstream>
#include <sstream>



Shader::Shader(const char* vertexShader, const char* fragmentShader)
{
	// 1.read vertex shader & fragment shader source from file
	std::string vertexCode, fragmentCode;
	std::ifstream vsf, fsf;
	
	// 保证ifstream对象可以抛出异常
	vsf.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fsf.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try 
	{
		vsf.open(vertexShader);
		fsf.open(fragmentShader);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vsf.rdbuf();
		fShaderStream << fsf.rdbuf();
		vsf.close();
		fsf.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout <<__LINE__ << " Error::Shader::File not succesfully read \t" << e.what()<<std::endl;
	}

	const char* pVertexCode = vertexCode.c_str();
	const char* pFragmentCode = fragmentCode.c_str();
	
	int success = 0;
	char infoLog[512] = { 0 };

	unsigned int vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &pVertexCode, nullptr);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::cout << __LINE__ << " : \t" << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &pFragmentCode, nullptr);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 1, nullptr, infoLog);
		std::cout << __LINE__ << " : \t" << infoLog << std::endl;
	}

	m_ShaderId = glCreateProgram();
	glAttachShader(m_ShaderId, vertex);
	glAttachShader(m_ShaderId, fragment);
	glLinkProgram(m_ShaderId);

	glGetProgramiv(m_ShaderId, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_ShaderId, 512, nullptr, infoLog);
		std::cout << __LINE__ << " : \t" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


Shader::~Shader()
{
}

void Shader::UseProgram()
{
	glUseProgram(m_ShaderId);
}

void Shader::Use()
{
	glUseProgram(m_ShaderId);
}