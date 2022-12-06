#pragma once


//Include GLEW
#include <GL/glew.h>

#include<GLFW/glfw3.h>

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>

//Include GLM  
#include "glm/glm.hpp"
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

class Camera
{
public:
	Camera(int worldWidth, int worldHeight);
	Camera(int worldWidth, int worldHeight, glm::vec3 startPosition, glm::vec3 startOrientation);

	void UpdateCamera(GLFWwindow* window);
	void UpdateProjection(float p_fovInDegrees, float p_nearPlane, float p_farPlane);
	void UpdateWorldWidthAndHeight(int p_worldWidth, int p_worldHeight);

	void sendCameraViewMatrixToShaderProgram(GLint id);
	void sendCameraProjectionMatrixToShaderProgram(GLint id);

	glm::vec3 GetCameraPosition();
	glm::vec3 GetCameraOrientation();

private:
	glm::mat4 view;
	glm::mat4 projection;

	glm::vec3 position;
	glm::vec3 orientation;
	glm::vec3 up;

	int worldWidth;
	int worldHeight;

	// Prevents the camera from jumping around when first clicking left click
	bool firstClick;

	// Adjust the speed of the camera and it's sensitivity when looking around
	float speed;
	float sensitivity;

	float fovInDegrees; 
	float nearPlane; 
	float farPlane;

	void UpdateMatricies();
};

