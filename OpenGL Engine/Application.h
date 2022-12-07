#pragma once

//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

//Include GLM  
#include "glm/glm.hpp"
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtx/string_cast.hpp>

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <SOIL.h>

#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags


#include <iostream>
#include <fstream>
#include <iomanip>   // std::setprecision, std::setw
#include <vector>


#include "Model.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "Scene.h"
#include "Skybox.h"

#include "Models/sphere.h"
#include "Models/plain.h"
#include "Models/plain_uv.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "Models/tree.h"
#include "Models/gift.h"
#include "Models/bushes.h"
#include "Models/skycube.h"


class Application
{
public:
	GLFWwindow* window;
	unsigned int width;
	unsigned int height;

	Application(const unsigned width, const unsigned height);

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);

	void set_error_callback();
	void set_callbacks();

	void set_camera();

	void init();
	void init(int major, int minor);

	void gameLoop(void);
	void destroy(void);

};

