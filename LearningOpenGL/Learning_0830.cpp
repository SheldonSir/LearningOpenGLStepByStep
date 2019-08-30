#include "ShaderMgr.h"
#include <GLFW/glfw3.h>


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(600, 800, "Learning_0820", nullptr, nullptr);
	if (nullptr == window)
	{
		std::cout << __LINE__ << " : create GLFWwindow failed " << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int w, int h) {
		glViewport(0, 0, w, h);
	});

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << __LINE__ << " : load GL loader failed " << std::endl;
		return -1;
	}

	Shader m_TinyShader("Triangle_Out_Pos.vert", "Triangle_Out_Pos.frag");
	Shader m_TinyShader2("Triangle.vert", "Triangle_Yellow.frag");

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

	unsigned int vao[2] = { 0 };
	unsigned int vbo[2] = { 0 };

	glGenVertexArrays(2, vao);
	glGenBuffers(2, vbo);

	//----------------first vao and vbo-------------------------
	glBindVertexArray(vao[0]);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)/2, vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//----------------second vao and vbo-------------------------
	glBindVertexArray(vao[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)/2, &vertices[sizeof(vertices) / (sizeof(float) * 2)], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//------------------------------------------------------------
	auto processInput = [](GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
	};


	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_TinyShader.UseProgram();
		glBindVertexArray(vao[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		m_TinyShader2.UseProgram();
		float t = (float)glfwGetTime();
		float c = (sin(t) / 2.0f) + 0.5f;
		m_TinyShader2.SetUniform("m_UniformColor", 0.0f, c, 0.0f, 1.0f);
		
		glBindVertexArray(vao[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, vao);
	glDeleteBuffers(2, vbo);
	glfwTerminate();
	return 0;
}