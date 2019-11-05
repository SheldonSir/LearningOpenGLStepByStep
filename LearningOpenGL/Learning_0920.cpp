#if 0
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ShaderMgr.h"
#include "Include/stb_image.h"
#include "Include/glm/glm/gtc/matrix_transform.hpp"
#include "Include/glm/glm/glm.hpp"
#include "Include/glm/glm/gtc/type_ptr.hpp"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(600, 800, "Learning_0920", nullptr, nullptr);
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
		std::cout << __LINE__ << " : Load gl loader failed " << std::endl;
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	Shader shader("resource/shader/6.2.coordinate_systems.vert", "resource/shader/6.2.coordinate_systems.frag");

	 // set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// -z 轴面
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		// +z 轴面
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		// -x 轴面
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		// +x 轴面
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 // -y 轴面
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		// +y 轴面 
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	// world space positions of our cubes
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	unsigned int vao, vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	unsigned int tex1, tex2;
	glGenTextures(1, &tex1);
	glBindTexture(GL_TEXTURE_2D, tex1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	char path[MAX_PATH] = { 0 };
	int tw, th, tc;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(_fullpath(path, "resource/texture/wall.jpg", MAX_PATH), &tw, &th, &tc, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tw, th, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << __LINE__ << "load wall.jpg failed" << std::endl;
	}
	stbi_image_free(data);

	glGenTextures(1, &tex2);
	glBindTexture(GL_TEXTURE_2D, tex2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load(_fullpath(path, "resource/texture/awesomeface.png", MAX_PATH), &tw, &th, &tc, 0);
	if (nullptr != data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << __LINE__ << "load awesomeface.png failed" << std::endl;
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

		glClearColor(.2f, .3f, .3f, .0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, tex1);
		glActiveTexture(1);
		glBindTexture(GL_TEXTURE_2D, tex2);

		shader.UseProgram();

		glm::mat4 model(1.0f);
		glm::mat4 view(1.0f);
		glm::mat4 projection(1.0f);
		
		//model = glm::translate(model, glm::vec3(.0f, .0f, -3.0f));
		//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));		
		view = glm::translate(view, glm::vec3(.0f, .0f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, .1f, 100.0f);

		unsigned int modelLoc = glGetUniformLocation(shader.m_ShaderId, "model");
		unsigned int viewLoc = glGetUniformLocation(shader.m_ShaderId, "view");
		unsigned int projectionLoc = glGetUniformLocation(shader.m_ShaderId, "projection");
		
		
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(vao);

		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			if (i % 3 == 0)
				angle = (float)glfwGetTime() * 25.0f;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	
	glDeleteTextures(1, &tex1);
	glDeleteTextures(1, &tex2);

	glfwTerminate();
	return 0;
}
#endif // 1
