#version 300 es

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
//in means input in these cases
out vec3 vertexColor;
out vec3 poscolor;
out vec2 TexCoord;
void main()
{

	gl_Position = vec4(aPos, 1.0);
	vertexColor = aColor;
	poscolor = aPos;
	TexCoord = aTexCoord;
//	TexCoord.y = -TexCoord.y;
}
