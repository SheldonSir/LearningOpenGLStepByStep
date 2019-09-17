#include "Include/glm/glm/glm.hpp"
#include "Include/glm/glm/gtc/matrix_transform.hpp"
#include "Include/glm/glm/gtc/type_ptr.hpp"
#include <iostream>

int main()
{
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f);
	/*
		构造一个平移矩阵

		| 1 0 0 1 |
		| 0 1 0 1 |
		| 0 0 1 0 |
		| 0 0 0 1 |
	*/
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));


	vec = trans * vec;
	std::cout << vec.x << ", " << vec.y << ", " << vec.z <<", "<< vec.w << std::endl;
	return 0;
}