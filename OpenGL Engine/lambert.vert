#version 400

layout(location=0) in vec3 vp;
layout(location=1) in vec3 vn;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 worldPos;
out vec4 worldNorm;

void main () {
	worldPos = modelMatrix * vec4 ( vp ,1.0);
	mat4 normal = modelMatrix;
	worldNorm = transpose(inverse(modelMatrix)) * vec4(vn, 1.0);
    gl_Position = modelMatrix * viewMatrix * projectionMatrix * vec4 ( vp ,1.0);
}