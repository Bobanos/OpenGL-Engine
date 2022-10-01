#pragma once

#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

class Application
{
public:
	GLFWwindow* window;
	unsigned int width;
	unsigned int height;

	Application(const unsigned width, const unsigned height);

	void init(int major, int minor);
	void gameLoop(void);
	void destroy(void);

};

