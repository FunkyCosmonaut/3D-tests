#include "window.h"

float transparency = 0.2;
mat4 trans;
mat4 trans2;
extern float vertices2[];
void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}
	if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
		transparency += 0.001;
	}
		//mat4 trans;
		vec3 axis = {0.0f, 0.0f, 1.0f};
		vec3 scale = {0.5f, 0.5f, 0.0f};
		vec3 scale2 = {sin((double)glfwGetTime()),sin((double)glfwGetTime()), 0.0f};
		vec3 move = {-0.9f, 0.9f, 0.0f};
		glm_mat4_identity(trans2);
		glm_mat4_identity(trans);
		glm_translate(trans2, move);
		glm_scale(trans2, scale2);
		glm_scale(trans, scale);
		glm_rotate(trans, (double)glfwGetTime(), axis);
	//	trans = glm_translate(trans, (1.0f, 1.0f, 0.0f));
	for(int i = 0; i < 3; i++){
		printf("%f, %f, %f, %f\n", trans[0][i], trans[1][i], trans[2][i],trans[3][i]);
	}
	printf("\n\n");

	//The thing about printf is that it needs to remain in a function
	//Remember higher dimensions for matricies
	}
