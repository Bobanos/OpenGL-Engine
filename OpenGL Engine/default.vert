#version 330
layout(location=0) in vec4 vp;
layout(location=1) in vec4 vo;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec4 colour;
void main () {
     gl_Position = (modelMatrix * viewMatrix * projectionMatrix) * vp;
	  colour = vo;
}