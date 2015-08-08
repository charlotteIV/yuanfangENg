#version 330 core

in vec3 position;
in vec2 textureCoords;
in vec3 normal;

out vec2 TextureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector[4];
out vec3 toCameraVector;
out float visibility;

uniform mat4 transformMatrix; 
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition[4];

const float density = 0.0035;
const float gradient = 5.0;

void main(void){
	vec4 worldPosition = transformMatrix * vec4(position, 1.0f);
	vec4 positionRelativeCamera = viewMatrix * worldPosition;
    gl_Position = projectionMatrix * positionRelativeCamera;
    TextureCoords = textureCoords;
	
	surfaceNormal = (transformMatrix * vec4(normal, 0.0f)).xyz;
	for(int i=0; i<4; i++){
		toLightVector[i] = lightPosition[i] - worldPosition.xyz;
	}
	toCameraVector = (inverse(viewMatrix) * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz - worldPosition.xyz;
	
	float distance = length(positionRelativeCamera.xyz);
	visibility = exp(-pow((distance * density), gradient));
	visibility = clamp(visibility, 0.0, 1.0);
 }