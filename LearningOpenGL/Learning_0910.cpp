#if 0
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ShaderMgr.h"
#include "Include/stb_image.h"

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(600, 800, "Learning_0910", nullptr, nullptr);
	if (nullptr == window)
	{
		std::cout << __LINE__ << " Create Window Error" << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int w, int h){
		glViewport(0, 0, w, h);
	});

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << __LINE__ << " Load glad error" << std::endl;
		return -1;
	}

	// char buf[MAX_PATH] = { 0 };
	// std::cout << _fullpath(buf, ".", MAX_PATH) << std::endl;
	// char drive[MAX_PATH] = { 0 };
	// char dir[MAX_PATH] = { 0 };
	// char name[MAX_PATH] = { 0 };
	// char ext[MAX_PATH] = { 0 };
	// 
	// 
	// _splitpath_s(__FILE__, drive, sizeof(drive), dir, sizeof(dir), name, sizeof(name), ext, sizeof(ext));
	// std::cout << drive << std::endl;
	// std::cout << dir << std::endl;
	// std::cout << name << std::endl;
	// std::cout << ext << std::endl;
	//Shader shader("resource/shader/Learning_0902_Texture.vert", "resource/shader/Learning_0910_Texture.frag");

	Shader shader("resource/shader/Learning_0902_Texture.vert", "resource/shader/Learning_0910_Texture_Question4.frag");

	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	unsigned int vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);

	unsigned int tex[2] = { 0 };
	glGenTextures(2, tex);
	glBindTexture(GL_TEXTURE_2D, tex[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(true);

	int tw, th, tc;
	char absolutePath[MAX_PATH] = { 0 };
	unsigned char* data = stbi_load(_fullpath(absolutePath, "resource/texture/wall.jpg", MAX_PATH), &tw, &th, &tc, 0);
	if (nullptr != data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tw, th, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << __LINE__ << " load wall.jpg failed" << std::endl;
	}

	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, tex[1]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load(_fullpath(absolutePath, "resource/texture/awesomeface.png", MAX_PATH), &tw, &th, &tc, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << __LINE__ << " load awesomeface.png failed" << std::endl;
	}
	stbi_image_free(data);

	float interpolate = 0.2f;
	shader.UseProgram();
	shader.SetUniform("wall", 0);
	shader.SetUniform("awesomeface", 1);
	shader.SetUniform("interpolate", interpolate);

	auto ProcessInput = [&interpolate, &shader](GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			interpolate += 0.001f;
			if (interpolate >= 1.0f)
				interpolate = 1.0f;
			shader.SetUniform("interpolate", interpolate);
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			interpolate -= 0.001f;
			if (interpolate <= 0.0f)
				interpolate = 0.0f;
			shader.SetUniform("interpolate", interpolate);
		}
	};

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex[1]);

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
		glBindVertexArray(vao);
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteTextures(2, tex);

	glfwTerminate();
	return 0;
}

#endif // 1
