#version 330 core

in vec3 position;
out vec3 textureCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main(){
	gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.0f);
	
	textureCoords = position;
}