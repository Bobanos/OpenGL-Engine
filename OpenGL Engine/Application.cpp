#include "Application.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "Scene.h"

#include "Models/sphere.h"
#include "Models/plain.h"
#include "Models/plain_uv.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "Models/tree.h"
#include "Models/gift.h"
#include "Models/bushes.h"
#include "Models/skycube.h"

#include "SOIL.h"


//Include GLM  
#include "glm/glm.hpp"
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

Application::Application(const unsigned width, const unsigned height)
{
	Application::width = width;
	Application::height = height;

	init();
	gameLoop();
	destroy();
}

void Application::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void Application::window_focus_callback(GLFWwindow* window, int focused)
{
	printf("window_focus_callback \n");
}

void Application::window_iconify_callback(GLFWwindow* window, int iconified)
{
	printf("window_iconify_callback \n");
}

void Application::window_size_callback(GLFWwindow* window, int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Application::cursor_callback(GLFWwindow* window, double x, double y)
{
	printf("cursor_callback \n");
}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}

void Application::set_error_callback()
{
	glfwSetErrorCallback(error_callback);
}

void Application::set_callbacks()
{
	// Sets the key callback
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, button_callback);
	glfwSetWindowFocusCallback(window, window_focus_callback);
	glfwSetWindowIconifyCallback(window, window_iconify_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
}

void Application::init()
{
	set_error_callback();
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(width, height, "ZPG", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	set_callbacks();

	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
}

void Application::init(int major, int minor)
{
	//window;
	//set_error_callback();
	//if (!glfwInit()) {
	//	fprintf(stderr, "ERROR: could not start GLFW3\n");
	//	exit(EXIT_FAILURE);
	//}

	////inicializace konkretni verze
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//window = glfwCreateWindow(width, height, "ZPG", NULL, NULL);
	//if (!window) {
	//	glfwTerminate();
	//	exit(EXIT_FAILURE);
	//}

	//glfwMakeContextCurrent(window);
	//glfwSwapInterval(1);

	//// start GLEW extension handler
	//glewExperimental = GL_TRUE;
	//glewInit();

	//set_callbacks();

	//// get version info
	//printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	//printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	//printf("Vendor %s\n", glGetString(GL_VENDOR));
	//printf("Renderer %s\n", glGetString(GL_RENDERER));
	//printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	//int revision;
	//glfwGetVersion(&major, &minor, &revision);
	//printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	//int width, height;
	//glfwGetFramebufferSize(window, &width, &height);
	////float ratio = width / (float)height;
	//glViewport(0, 0, width, height);


	////glMatrixMode(GL_PROJECTION);
	////glLoadIdentity();
	////glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
}

void Application::gameLoop()
{
	Scene scene(width, height);


	Model model2;
	model2.generate_VBO(suziSmooth, sizeof(suziSmooth), sizeof(suziSmooth) / 6);
	model2.generate_VAO6();
	DrawableObject drawableObject3 = DrawableObject(&model2);
	//drawableObject3.model->generate_VBO(suziSmooth, sizeof(suziSmooth), sizeof(suziSmooth) / 6);
	//drawableObject3.model->generate_VAO6();
	drawableObject3.Translate(glm::vec3(0.0f, 0.0f, -1.2f));
	//drawableObject3.Scale(glm::vec3(0.7f));
	//drawableObject3.Rotate(180.f, glm::vec3(0.0f, 1.0f, 0.0f));

	Model model3;
	DrawableObject drawableObject4 = DrawableObject(&model3);
	drawableObject4.model->generate_VBO(plain, sizeof(plain), sizeof(plain) / 6);
	drawableObject4.model->generate_VAO6();
	drawableObject4.Translate(glm::vec3(0.0f, -1.0f, 0.0f));
	//drawableObject4.Rotate(180.f, glm::vec3(0.0f, 1.0f, 0.0f));
	drawableObject4.Scale(glm::vec3(10.0f));
	//drawableObject4.Rotate(45.f, glm::vec3(1.0f, 0.0f, 0.0f));

	Model model4;
	DrawableObject drawableObject5 = DrawableObject(&model4);
	drawableObject5.model->generate_VBO(plain_uv, sizeof(plain_uv), sizeof(plain_uv) / 8);
	drawableObject5.model->generate_VAO8();
	drawableObject5.Translate(glm::vec3(0.0f, -1.0f, 0.0f));
	//drawableObject5.Rotate(180.f, glm::vec3(0.0f, 1.0f, 0.0f));
	//drawableObject5.Scale(glm::vec3(10.0f));
	drawableObject5.Rotate(45.f, glm::vec3(1.0f, 0.0f, 0.0f));

	DrawableObject drawableObject6 = DrawableObject(&model4);
	drawableObject6.model->generate_VBO(plain_uv, sizeof(plain_uv), sizeof(plain_uv) / 8);
	drawableObject6.model->generate_VAO8();
	drawableObject6.Translate(glm::vec3(0.0f, -1.0f, -3.0f));
	//drawableObject5.Rotate(180.f, glm::vec3(0.0f, 1.0f, 0.0f));
	//drawableObject5.Scale(glm::vec3(10.0f));
	drawableObject6.Rotate(45.f, glm::vec3(1.0f, 0.0f, 0.0f));


	ShaderProgram shader_program;
	shader_program.AttachShaders("default.vert", "default.frag");
	shader_program.LinkProgram();
	shader_program.CheckLinkStatus();

	ShaderProgram shader_program2;
	shader_program2.AttachShaders("phong.vert", "phong.frag");
	shader_program2.LinkProgram();
	shader_program2.CheckLinkStatus();

	ShaderProgram shader_program3;
	shader_program3.AttachShaders("texture.vert", "texture.frag");
	shader_program3.LinkProgram();
	shader_program3.CheckLinkStatus();



//	/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		//Vertex Array Object (VAO)
//	GLuint VBO = 0;
//	glGenBuffers(1, &VBO); // generate the VBO
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(skycube), &skycube[0], GL_STATIC_DRAW);
//
//	GLuint VAO = 0;
//	glGenVertexArrays(1, &VAO); //generate the VAO
//	glBindVertexArray(VAO); //bind the VAO
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//	//enable vertex attributes
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
//
//	ShaderProgram shader_program4;
//	shader_program4.AttachShaders("skybox.vert", "skybox.frag");
//	shader_program4.LinkProgram();
//	shader_program4.CheckLinkStatus();
//
//
//
//
//
//	Model model;
//	DrawableObject drawableObject = DrawableObject(&model3);
//	drawableObject.model->generate_VBO(plain_uv, sizeof(plain_uv), sizeof(plain_uv) / 8);
//	drawableObject.model->generate_VAO8();
//	//drawableObject.Translate(glm::vec3(0.0f, -1.0f, 0.0f));
//	//drawableObject.Rotate(180.f, glm::vec3(0.0f, 1.0f, 0.0f));
//	drawableObject.Scale(glm::vec3(0.3f));
//	drawableObject.Rotate(90.f, glm::vec3(1.0f, 0.0f, 0.0f));
//
//	ShaderProgram shader_program3;
//	shader_program3.AttachShaders("texture.vert", "texture.frag");
//	shader_program3.LinkProgram();
//	shader_program3.CheckLinkStatus();
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//	//Bind the first texture to the first texture unit.
//	glActiveTexture(GL_TEXTURE0); // 33984 = GL_TEXTURE0
//	//2D texture
//	GLuint textureID1 = SOIL_load_OGL_texture("Textures/test.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
//	if (textureID1 == NULL) {
//		std::cout << "An error occurred while loading texture." << std::endl;
//		//exit(EXIT_FAILURE);
//	}
//	glBindTexture(GL_TEXTURE_2D, textureID1);
//
//
//
//	//Cube Map (SkyBox)
	//glActiveTexture(GL_TEXTURE1);
//	GLuint textureID2 = SOIL_load_OGL_cubemap("Textures/posx.jpg", "Textures/negx.jpg", "Textures/posy.jpg", "Textures/negy.jpg", "Textures/posz.jpg", "Textures/negz.jpg", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
//	if (textureID2 == NULL) {
//		std::cout << "An error occurred while loading texture." << std::endl;
//		//exit(EXIT_FAILURE);
//	}
//	glBindTexture(GL_TEXTURE_2D, textureID2);
//
//
//
//
//	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
//






	Texture texture5(5);
	texture5.LoadTexture("Textures/test.png");
	texture5.BindTexture();
	Texture texture6(6);
	texture6.LoadTexture("Textures/grass.png");
	texture6.BindTexture();


	scene.AddToVectorModelsShaders(&drawableObject3, &shader_program2);
	scene.AddToVectorModelsShaders(&drawableObject4, &shader_program2);
	scene.AddToVectorModelsShadersTextures(&drawableObject5, &shader_program3, &texture5);
	scene.AddToVectorModelsShadersTextures(&drawableObject6, &shader_program3, &texture6);
	//scene.AddToVector(&drawableObject, &shader_program3);

	//glm::mat4 M = glm::mat4(1.0f);
	//M = glm::scale(M, glm::vec3(0.1f));

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_DEPTH_CLAMP);

	while (!glfwWindowShouldClose(window)) {
		// clear color and depth buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// draw all objects


		//shader_program3.UseProgram();
		//drawableObject.UniformMatrix4fv(shader_program3.GetUniformLocation("modelMatrix"));
		//glUniform1i(shader_program3.GetUniformLocation("textureUnitID"), 0);// set TU 0
		//drawableObject.model->bind_VAO();
		//drawableObject.DrawArrays();


		//shader_program4.UseProgram();
		//glUniformMatrix4fv(shader_program4.GetUniformLocation("modelMatrix"), 1, GL_FALSE, &M[0][0]);
		//glUniform1i(shader_program4.GetUniformLocation("skybox"), 0); // set TU 1
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 36);






		//glClear(GL_DEPTH_BUFFER_BIT);


		scene.camera->UpdateWorldWidthAndHeight(Application::width, Application::height);
		scene.camera->UpdateCamera(window);
		scene.DrawAllObjects();

		// update other events like input handling
		glfwPollEvents();
		// put the stuff weve been drawing onto the display
		glfwSwapBuffers(window);
	}
}

void Application::destroy()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}


