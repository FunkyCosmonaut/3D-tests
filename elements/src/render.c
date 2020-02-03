#define STB_IMAGE_IMPLEMENTATION
#include "window.h"
#include <math.h>
#include <cglm/cglm.h>
#include "stb_image.h"

extern float transparency;
extern mat4 trans;
extern mat4 trans2;

unsigned int shaderProgram;
unsigned int VBO[2], VAO, EBO[2];
unsigned int texture;
unsigned int texture2;


//INFO
//

	float vertices[] = {
     0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,// bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,// bottom left
    -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f// top left
};
	float vertices2[] = {
     0.9f,  0.1f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // top right
     0.9f, -0.9f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,// bottom right
    -0.9f, -0.9f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,// bottom left
    -0.9f,  0.9f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f// top left
	};

unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};


unsigned int indices2[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};
char *load_file(char *filename){

	char *buffer = 0;
	long length = 0;
	FILE *f = fopen(filename, "r");
	if(f){
		fseek(f, 0, SEEK_END);
		length = ftell(f);
		fseek(f, 0, SEEK_SET);
		buffer = malloc(length);
		if(buffer)
		{
			fread(buffer, 1, length, f);
		}
		fclose(f);
	}
	return buffer;
	free(buffer);
}

void init(){

	//initialize vertex Buffer Object
//	unsigned int VBO, VAO;
//	moved these decs to top

	glGenVertexArrays(1, &VAO);
	
	glGenBuffers(2, VBO);
	glGenBuffers(2, EBO);
	glBindVertexArray(VAO);
//VBO stuff	
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//EBO stuff
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//second shape
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
//Anytime you add and or updated the VBO memory we need to reconfigure the vertex attrib pointers
//top is position attributes, bottom is color attributes
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);
	//For every object
//	glBindVertexArray(0); //Only for Drawarrays
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//LOAD AND CREATE TEXTURE SHIT VV
	int width, height, nrChannels;

	//gen texture

	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	//PARAMS
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char *data = stbi_load("textures/test.jpg", &width, &height, &nrChannels, 0);
	if(data){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else{
		printf("failed to load textures\n");
	}

stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
data = stbi_load("textures/awesomeface.png", &width, &height, &nrChannels, 0);
if(data)
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
}
else{
	printf("failed to load texture2\n");
}
stbi_image_free(data);
//glActiveTexture(GL_TEXTURE0);
//glActiveTexture(GL_TEXTURE1);

//glEnable(GL_BLEND);
//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glUseProgram(shaderProgram);
glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);
glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture2"), 1);
//I had the transparency uniform here, uniforms that will be updated belong in the loop




	
}

void loadShaders(){
	
	const char *fragmentShaderSource = load_file("src/shader.frag");
	const char *vertexShaderSource = load_file("src/shader.vert"); 

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	printf("%s\n", fragmentShaderSource);
	printf("%s\n", vertexShaderSource);

	glShaderSource(vertexShader, 1 , &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if(!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("ERROR COMPILIN VERTEX SHADER DUMMY\n%s\n", infoLog);
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("ERROR COMPILING FRAGMENT SHADER\n%s\n",infoLog);
	}
	
//	unsigned int shaderProgram;
//	moved this dec to the top for global
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success){
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("ERROR LINKING\n%s\n", infoLog);
	}
	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void render(){

//Order matters when it comes to setting active textures and binding
	glClearColor(0.2f, 0.5f, 0.3, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

//EBO stuff
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glActiveTexture(GL_TEXTURE0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
  glBindTexture(GL_TEXTURE_2D, texture);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//Anytime you add and or updated the VBO memory we need to reconfigure the vertex attrib pointers
//top is position attributes, bottom is color attributes
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
	//For every object
//	glBindVertexArray(0); //Only for Drawarrays
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

glUniform1f(glGetUniformLocation(shaderProgram, "alpha"), transparency);
glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"),1, GL_FALSE, (float *)trans);
	glUseProgram(shaderProgram);
	//update uniform color
	glBindVertexArray(VAO);
//	glDrawArrays(GL_TRIANGLES, 0, 6);
//printf("%f\n", transparency); //Debug

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//Anytime you add and or updated the VBO memory we need to reconfigure the vertex attrib pointers
//top is position attributes, bottom is color attributes
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
	//For every object
//	glBindVertexArray(0); //Only for Drawarrays
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"),1, GL_FALSE, (float *)trans2);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//Moved everything to its own function init.
	//I had the shader here before too,
	////moved it because didn't need to be in the loop
	//
	//Uniform test here
/*	float timeValue = glfwGetTime();
	float flashValue = (sin(timeValue) / 2.0f) + 0.5f;
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	glUniform4f(vertexColorLocation, flashValue, 0.0f, 0.0f, 1.0f);*/
}
