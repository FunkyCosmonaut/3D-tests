#include "window.h"

int main(){

	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//YES


	//The Window shiz
	GLFWwindow* window = glfwCreateWindow(800, 600, "TEST", NULL, NULL);
	if(window == NULL)
	{
		printf(" FAILED TO CREATE WINDOW\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if(!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to intialize GLAD\n");
		return -1;
	}

	glViewport(0, 0, 800, 600);

	//*******************************************************************
	//REZIZE CALLBACKS
	//*******************************************************************
	
	//void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//*******************************************************************
	
	//loop //Fucking Hell, days of suffering and all this time
	//I was beating my head in because my shaders weren't loaded before setting uniforms
	loadShaders();
	init();


	while(!glfwWindowShouldClose(window))
	{
		processInput(window);
		render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
