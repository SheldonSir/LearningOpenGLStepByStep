#if 1
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderMgr.h"
#include "Camera.h"
#include <iostream>

unsigned int Width = 1920, Height = 768;

float lastX = 0.0f , lastY = 0.0f;
bool firstMouse = true;

float deltaFrame = 0.0f;
float lastFrame = 0.0f;
Camera camera(glm::vec3(.0f, 5.0f, 3.0f));


void ProcessInput(GLFWwindow*);

glm::vec3 lightPos = glm::vec3(.0f, 5.0f, .0f);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(Width, Height, "Learning_1105", nullptr, nullptr);
	if (nullptr == window)
	{
		std::cout << " Create Window Failed" << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int w, int h) {
		glViewport(0, 0, w, h);
	});

	// 设置鼠标控制镜头pitch 和 yaw
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {

		if (firstMouse)
		{
			lastX = x;
			lastY = y;
			firstMouse = false;
		}

		float xoffset = x - lastX;
		float yoffset = lastY - y;

		lastX = x;
		lastY = y;

		camera.ProcessMouseMovement(xoffset, yoffset);
	});

	glfwSetScrollCallback(window, [](GLFWwindow* window, double x, double y) {
		camera.ProcessMouseScroll((float)y);
	});

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress)))
	{
		std::cout << "Load GL Loader Failed" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	Shader pawnShader("resource/shader/1028_pawn.vert", "resource/shader/1028_pawn.frag");
	Shader lightShader("resource/shader/1028_light.vert", "resource/shader/1028_light.frag");

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	unsigned int pawnVAO, vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &pawnVAO);
	glBindVertexArray(pawnVAO);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glEnableVertexAttribArray(0);

	camera.Front = glm::vec3(0.0f);
		
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaFrame = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ProcessInput(window);

		glClearColor(.1f, .1f, .1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		pawnShader.Use();
		pawnShader.SetUniform("lightPos", lightPos); //灯在5米高的地方
		pawnShader.SetUniform("viewPos", camera.Position);
		pawnShader.SetUniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f)); // 白光
		pawnShader.SetUniform("pawnColor", glm::vec3(1.0f, 0.5f, 0.31f)); // 珊瑚红

		glm::mat4 model(1.0f);
		model = glm::scale(model, glm::vec3(5.0f, 0.2f, 5.0f));
		pawnShader.SetUniform("model", model);
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)(Width / Height), 0.001f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		pawnShader.SetUniform("projection", projection);
		pawnShader.SetUniform("view", view);

		glBindVertexArray(pawnVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		lightShader.Use();
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightShader.SetUniform("model", model);
		lightShader.SetUniform("view", view);
		lightShader.SetUniform("projection", projection);
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &pawnVAO);
	glDeleteVertexArrays(1, &lightVAO);

	glfwTerminate();
	return 0;
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaFrame);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaFrame);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaFrame);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaFrame);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaFrame);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaFrame);
}

#endif // 1
