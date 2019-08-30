#if false
#include "ShaderMgr.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void FrameBufferSizeFun(GLFWwindow*, int, int);
void ProcessInput(GLFWwindow*);
int main()
{
	// init glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create window context
	GLFWwindow* window = glfwCreateWindow(600, 800, "Learning_0827", nullptr, nullptr);
	if (nullptr == window)
	{
		std::cout << __LINE__ << " : Create Window Failed" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeFun);

	// load glad 加载系统相关的OpenGL函数指针地址的函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << __LINE__ << " : Load OpenGL Loader Failed" << std::endl;
		glfwTerminate();
	}

	// load shader and link shader to program
	Shader m_ThinyShader("Triangle.vert", "Triangle.frag");

	// vertex attributes
	//float vertices[] = {
	//	-0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	//	0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	//	//0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	//	-0.5f, -0.5f, 0.0, 0.0f, 0.0f, 1.0f,
	//	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f

	//};

	float vertices[] = {
		// first triangle
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 
		// second triangle
		 0.0f, -0.5f, 0.0f,  // left
		 0.9f, -0.5f, 0.0f,  // right
		 0.45f, 0.5f, 0.0f   // top 
	};

	unsigned indices[] = {
		0, 1, 2,
		1, 2, 3
	};
	unsigned int vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	//glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);*/
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_ThinyShader.UseProgram();
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		//glDrawArrays(GL_TRIANGLES, 1, 3);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //线框模式
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	//glDeleteBuffers(1, &ebo);

	glfwTerminate();
	return 0;
}

void FrameBufferSizeFun(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}
void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
#endif