#include "window.h"
#include <math.h>

unsigned int shaderProgram;
unsigned int VBO[2], VAO;
char *load_file(char *filename){

	char *buffer = 0;
	long length;
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
}

void init(){
/*	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};*/
	float vertices[] = {
    // first triangle
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f,  0.5f, 0.0f };  // top left
    // second triangle
	float vertices1[] = {
		 0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
};
	//initialize vertex Buffer Object
//	unsigned int VBO, VAO;
//	moved these decs to top

	glGenVertexArrays(1, &VAO);
	
	glGenBuffers(2, &VBO);
	glBindVertexArray(VAO); 
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//For every object
	glBindVertexArray(0);




	}

void loadShaders(){
	
	const char *fragmentShaderSource = load_file("src/shader.frag");
	const char *vertexShaderSource = load_file("src/shader.vert"); 

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	printf("%s\n", fragmentShaderSource);

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


	glClearColor(0.2f, 0.5f, 0.3, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glBindVertexBuffer(0, VBO[0], 0, 3 * sizeof(float));
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexBuffer(0, VBO[1], 0, 3 * sizeof(float));
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
	//Moved everything to its own function init.
	//I had the shader here before too,
	////moved it because didn't need to be in the loop
}
