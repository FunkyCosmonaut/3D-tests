#include "window.h"

float transparency = 0.2;
void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}
	if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
		transparency += 0.001;
	}
}
