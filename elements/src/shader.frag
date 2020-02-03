#version 300 es
out mediump vec4 FragColor;
in mediump vec3 vertexColor;
in mediump vec3 poscolor;
in mediump vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;
uniform mediump float alpha;
//create time function in the future
//uniform mediump vec4 ourColor;

//Fragment shader without any attributes will render black at least on my PC
//It can render white too
void main()
{
//	FragColor = vec4(poscolor+.3, 1.0);
	FragColor = mix(texture(ourTexture, TexCoord), texture(ourTexture2, TexCoord*2.0), alpha+0.5) *  vec4(poscolor+.3, 1.0);
//	FragColor = texture(ourTexture, TexCoord);
}

