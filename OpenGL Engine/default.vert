#version 400
layout(location=0) in vec3 vp;
layout(location=1) in vec3 vo;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec4 colour;
void main () {
     gl_Position = projectionMatrix * viewMatrix* modelMatrix * vec4 ( vp ,1.0);
	 colour = vec4 ( vo ,1.0);
}