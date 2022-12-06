#include "Camera.h"

Camera::Camera(int p_worldWidth, int p_worldHeight)
{
	Camera::fovInDegrees = 45.0f;
	Camera::nearPlane = 0.1f;
	Camera::farPlane = 200.0f;

	Camera::view = glm::mat4(1.0f);
	Camera::projection = glm::mat4(1.0f);

	Camera::worldWidth = p_worldWidth;
	Camera::worldHeight = p_worldHeight;
	Camera::position = glm::vec3(0.0f, 0.0f, 0.0f);
	Camera::orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	Camera::up = glm::vec3(0.0f, 1.0f, 0.0f);

	Camera::firstClick = true;
	Camera::speed = 0.1f;
	Camera::sensitivity = 100.0f;

	Camera::UpdateMatricies();
}

Camera::Camera(int p_worldWidth, int p_worldHeight, glm::vec3 startPosition, glm::vec3 startOrientation)
{
	Camera::fovInDegrees = 45.0f;
	Camera::nearPlane = 0.1f;
	Camera::farPlane = 200.0f;

	Camera::view = glm::mat4(1.0f);
	Camera::projection = glm::mat4(1.0f);

	Camera::worldWidth = p_worldWidth;
	Camera::worldHeight = p_worldHeight;
	Camera::position = startPosition;
	Camera::orientation = startOrientation;
	Camera::up = glm::vec3(0.0f, 1.0f, 0.0f);

	Camera::firstClick = true;
	Camera::speed = 0.01f;
	Camera::sensitivity = 100.0f;

	Camera::UpdateMatricies();
}

void Camera::UpdateMatricies()
{
	// Initializes matrices
	Camera::view = glm::lookAt(Camera::position, Camera::position + Camera::orientation, Camera::up);
	Camera::projection = glm::perspective(glm::radians(Camera::fovInDegrees), (float)Camera::worldWidth / Camera::worldHeight, Camera::nearPlane, Camera::farPlane);
	//Camera::projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}

void Camera::UpdateWorldWidthAndHeight(int p_worldWidth, int p_worldHeight) 
{
	Camera::worldWidth = p_worldWidth;
	Camera::worldHeight = p_worldHeight;
}

void Camera::UpdateCamera(GLFWwindow* window)
{
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Camera::position += speed * glm::normalize(Camera::orientation);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Camera::position += speed * -glm::normalize(glm::cross(Camera::orientation, Camera::up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Camera::position += speed * -glm::normalize(Camera::orientation);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Camera::position += speed * glm::normalize(glm::cross(Camera::orientation, Camera::up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Camera::position += speed * Camera::up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Camera::position += speed * -Camera::up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.04f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.01f;
	}


	// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (firstClick)
		{
			glfwSetCursorPos(window, (Camera::worldWidth / 2), (Camera::worldHeight / 2));
			firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (float)(mouseY - (Camera::worldHeight / 2)) / Camera::worldHeight;
		float rotY = sensitivity * (float)(mouseX - (Camera::worldWidth / 2)) / Camera::worldWidth;

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(Camera::orientation, glm::radians(-rotX), glm::normalize(glm::cross(Camera::orientation, Camera::up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, Camera::up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Camera::orientation = newOrientation;
		}

		// Rotates the Orientation left and right
		Camera::orientation = glm::rotate(Camera::orientation, glm::radians(-rotY), Camera::up);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (Camera::worldWidth / 2), (Camera::worldHeight / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}

	Camera::UpdateMatricies();
}

void Camera::UpdateProjection(float p_fovInDegrees, float p_nearPlane, float p_farPlane)
{
	Camera::fovInDegrees = p_fovInDegrees;
	Camera::nearPlane = p_nearPlane;
	Camera::farPlane = p_farPlane;
}

void Camera::sendCameraViewMatrixToShaderProgram(GLint id)
{
	//printf("wwwwwwwwwwwwwwwwwwww %f\n", Camera::speed);
	//printf("%f %f %f %f\n", Camera::view[0][0], Camera::view[0][1], Camera::view[0][2], Camera::view[0][3]);
	//printf("%f %f %f %f\n", Camera::view[1][0], Camera::view[1][1], Camera::view[1][2], Camera::view[1][3]);
	//printf("%f %f %f %f\n", Camera::view[2][0], Camera::view[2][1], Camera::view[2][2], Camera::view[2][3]);
	//printf("%f %f %f %f\n", Camera::view[3][0], Camera::view[3][1], Camera::view[3][2], Camera::view[3][3]);
	glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(Camera::view));
}

void Camera::sendCameraProjectionMatrixToShaderProgram(GLint id)
{
	glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(Camera::projection));
}

glm::vec3 Camera::GetCameraPosition()
{
	return Camera::position;
}

glm::vec3 Camera::GetCameraOrientation()
{
	return Camera::orientation;
}
