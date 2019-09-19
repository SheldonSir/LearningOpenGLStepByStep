#if 1
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ShaderMgr.h"
#include "Include/stb_image.h"
#include "Include/glm/glm/glm.hpp"
#include "Include/glm/glm/gtc/matrix_transform.hpp"
#include "Include/glm/glm/gtc/type_ptr.hpp"

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(600, 800, "Learning_0917", nullptr, nullptr);
	if (nullptr == window)
	{
		std::cout << __LINE__ << " : Create window failed" << std::endl;
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int w, int h) {
		glViewport(0, 0, w, h);
	});

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << __LINE__ << " : Load gl loader failed" << std::endl;
		return -1;
	}

	Shader shader("resource/shader/Learning_0917_Texture_Transform.vert", "resource/shader/Learning_0917_Texture_Transform.frag");

	float vertices[] = {
		// positions          // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	unsigned int tex, tex2;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(true);

	int tw, th, tc;
	char path[MAX_PATH] = { 0 };
	unsigned char* data = stbi_load(_fullpath(path, "resource/texture/awesomeface.png", MAX_PATH), &tw, &th, &tc, 0);
	if (nullptr != data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << __LINE__ << " : load awesomeface.png failed" << std::endl;
	}
	stbi_image_free(data);

	glGenTextures(1, &tex2);
	glBindTexture(GL_TEXTURE_2D, tex2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// 超出的纹理坐标继续重复纹理图片
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	memset(path, 0, MAX_PATH);
	data = stbi_load(_fullpath(path, "resource/texture/wall.jpg", MAX_PATH), &tw, &th, &tc, 0);
	if (nullptr != data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tw, th, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << __LINE__ << " : load wall.jpg failed" << std::endl;
	}
	stbi_image_free(data);

	shader.UseProgram();
	shader.SetUniform("m_Sampler1", 0);
	shader.SetUniform("m_Sampler2", 1);

	auto ProcessInput = [](GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
	};

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex2);

		glm::mat4x4 transform = glm::mat4x4(1.0f);
		float time = (float)glfwGetTime();

		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform, time, glm::vec3(0.0f, 0.0f, 1.0f));

		//std::cout << __LINE__ << " : " << time << std::endl;

		shader.UseProgram();
		unsigned int transformLoc = glGetUniformLocation(shader.m_ShaderId, "m_Transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		transform = glm::mat4(1.0f); // reset it to identity matrix
		transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
		float scaleAmount = sin(glfwGetTime());
		transform = glm::scale(transform, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteTextures(1, &tex);
	glDeleteTextures(1, &tex2);

	glfwTerminate();
	return 0;
}
#endif // 1
